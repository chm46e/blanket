#include <X11/Xlib.h>
#include <IL/il.h>
#include "dr.h"
#include "util.h"

XImage *drCreateImage(Display *dpy, Visual *visual, char *path, int w, int h)
{
    ilInit();
    ilLoadImage(path);
    ILubyte *data = ilGetData();

    return XCreateImage(dpy, visual, 8, ZPixmap, 0, (char *)data, w, h, 32, 0);
}
