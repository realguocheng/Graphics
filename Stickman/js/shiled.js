document.onkeydown = function (e) {
				e = e || window.event;//Get event
				if (e.ctrlKey) {
					var c = e.which || e.keyCode;//Get key code
					switch (c) {
						case 83://Block Ctrl+S
							e.preventDefault();     
							e.stopPropagation();
						break;
					}
				}
			};