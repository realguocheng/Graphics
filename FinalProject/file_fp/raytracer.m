% CG Final Projects
% Compare your result with OpenGL's


clc, clear;

%----------------------------------------------------------
%          Variables' Statements and Initialization
%----------------------------------------------------------
global width;

% Image size
width = 400;
img = zeros(width, width, 3);

% Sphere: position, radius, color
global sphere_p sphere_r sphere_c;

% Ambient light
global ambient_light;

% Point lights intensity and position
global lights_i lights_p;

% Coefficients in light model
global Ka Kd Ks n_shiny rc;

% 7 'H2O'
sphere_p = [0 0 0; 0 -0.5 0; 0 0 -0.5
            0 2 0; 0 2 0.5; -0.5 2 0   % Up
            0 -2 0; 0 -2.5 0; -0.5 -2 0  % Down
            -2 0 0; -2 0.5 0; -2.5 0 0 % Right
            2 0 0; 2 -0.5 0; 2 0 0.5   % Left
            0 0 2; 0 0.5 2; -0.5 0 2  % Back
            0 0 -2; -0.5 0 -2; 0 0 -2.5 % Front
            ];
thetaY = 40;
thetaX = 30;
% Rotation Matrix
Ry = [cosd(thetaY) 0 -sind(thetaY)
     0 1 0
     sind(thetaY) 0 cosd(thetaY)];
Rx = [1 0 0
      0 cosd(thetaX) -sind(thetaX)
      0 sind(thetaX) cosd(thetaX)];
sphere_p = (Rx * Ry * sphere_p')';

sphere_r = repmat([0.7; 0.5; 0.5], 7, 1);
sphere_c = repmat([255 0 0; 255*ones(2, 3)], 7, 1);

Ka = 1;
Kd = 1;
Ks = 1;
n_shiny = 24;
rc = 0.3;

ambient_light = 2;

% More lights can be added by extending matrixes beblow.
lights_i = 8;
lights_p = [-4 4 -11];


%----------------------------------------------------------
%                   Scan Conversion
%----------------------------------------------------------
hs = width / 2;

for i = 1 : width
    for j = 1 : width
        ray = [(hs-j)/width (hs-i)/width 1];
        img(i, j, :) = trace_ray([0 0 -7], ray, 1, width, 1);
    end
end

imshow(uint8(img));

%----------------------------------------------------------
%                   Function Defination
%----------------------------------------------------------

% Find the closest intersection in space
function [I, Idx] = closest_intersection(e, v, d_min, d_max) 

    I = 0;    % Intersection point
    D = Inf;  % distance from orign to sphere center
    Idx = 0;  % sphere index - 1,2,3
    
    global sphere_p sphere_r;
    
    a = v * v';
    
    for i = 1 : size(sphere_p, 1)
        b = 2 * (e - sphere_p(i, :)) * v';
        c = (e - sphere_p(i, :)) * (e - sphere_p(i, :))' - sphere_r(i)^2;
        
        dlt = b^2 - 4*a*c;
        % Check if the ray shot the sphere
        if dlt >= 0
           x1 = (-b - sqrt(dlt)) / (2*a);
           x2 = (-b + sqrt(dlt)) / (2*a);
           x = min([x1 x2]);
           
           % Remain the nearest one
           if x < d_max && x > d_min && x < D
              D = x;
              Idx = i;
              I = e + x * v;
           end
        end
        
    end
end

% Trace the ray and compute colors of intersections
function color = trace_ray(e, V, d_min, d_max, depth)

    [X, id] = closest_intersection(e, V, d_min, d_max); 
    if id == 0
        % Background is black
        color = [0 0 0];
        return
    end
    
    global sphere_p sphere_c ambient_light lights_p lights_i;
    global width Ka Ks Kd n_shiny rc;
    
    N = (X - sphere_p(id, :));    % normal vector
    N = N / norm(N);
    
    R = [];
    
    % Compute integrated light intensity
    SI = Ka * ambient_light; 
    for i = 1 : size(lights_p, 1)       
        L = lights_p(i, :) - X;
        R = 2*N*(N * L') - L;
        
%         L = L / norm(L);
%         V = -V / norm(V);
%         H = (L + V) / norm(L + V);
     
        % If not in shadow
        if N * L' > 0
            diffuse_light = Kd * (N * L') / (norm(N) * norm(L));
            specular_light = Ks * ((R * V') / (norm(R) * norm(V)))^n_shiny;
            %specular_light = max(0, Ks * ((N * H') / (norm(N) * norm(H)))^n_shiny);
            SI = SI + lights_i(i) * (diffuse_light + specular_light);
        end
    end
    
    % Compute color at intersection
    if N * L' > 0
        color = sphere_c(id, :)*1.77*(1-4.4^(-SI/16)) + (255 - sphere_c(id, :))*specular_light;
    else
        color = sphere_c(id, :)*1.77*(1-4.4^(-SI/18));
    end

    % Trace reflected light
    depth = depth - 1;    
    if depth > 0
       color = (1 - rc) * color + rc * trace_ray(X, R, 1/width, width, depth);
    end
end
