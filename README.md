# blanket
Xlib based garbage status window\
Was created by the anger of the slow project: eww\
I'm kinda horrible at coding, so save your emotions until you see the code lol
## Dependencies
* DevIL 1.8.0 (http://openil.sourceforge.net/)
* gcc, make, xorg, etc idunno
## Build
```
$ make
$ ./blanket
```
In the case of the devil library not found:\
Either set the LD_LIBRARY_PATH env. variable to /usr/local/lib:
```
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```
or run:
```
$ LD_LIBRARY_PATH=/usr/local/lib ./blanket
```
## Notes
Make sure to launch the program from the project's root directory or DevIL won't be able to find the background image\
and yes, it doesnt work currently aka has errors
