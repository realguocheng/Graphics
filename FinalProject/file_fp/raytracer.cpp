/*
 * Ray Tracing
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

static int slices = 256;
static int stacks = 256;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();

        glTranslated(0, 0, -7);
        // Rotate about X and Y axis
        glRotated(-30, 1, 0, 0);
        glRotated(-40, 0, 1, 0);

        // Center
        glPushMatrix();
        glColor3d(1,0,0);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0, -0.5, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0, 0, 0.5);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Up
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(0, 2, 0);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0.5, 0, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0, 0, -0.5);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Down
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(0, -2, 0);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0, -0.5, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0.5, 0, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Left
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(-2, 0, 0);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0, -0.5, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0, 0, -0.5);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Right
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(2, 0, 0);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0, 0.5, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0.5, 0, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Back
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(0, 0, -2);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0, 0.5, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0.5, 0, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

        // Front
        glPushMatrix();
        glColor3d(1,0,0);
            glTranslated(0, 0, 2);
            glutSolidSphere(0.7,slices,stacks);

            glColor3d(1, 1, 1);
            glPushMatrix();
                glTranslated(0.5, 0, 0);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0, 0, 0.5);
                glutSolidSphere(0.5,slices,stacks);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();


    glutSwapBuffers();
}


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 4.0f, 4.0f, 4.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Ray Tracing");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);


    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
