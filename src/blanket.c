#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

static Display *dpy;
static Screen *screen;
static Window root, win;
static Visual *visual;
static GC gc;
static int depths;
static int screennum;
static int ww, wh;
static int running = 1;

static XImage *bg;
static Pixmap bgpm;

static void createbg(void);
static void handler(XEvent *ev);
static void run(void);
static void setup(void);
static void cleanup(void);

#include "util.h"
#include "dr.h"

void createbg(void)
{
	/* idunno where to place jpg for global access */
	bg = drCreateImage(dpy, visual, "res/background.jpg", ww, wh);
	bgpm = XCreatePixmap(dpy, win, ww, wh, 8);
	XPutImage(dpy, bgpm, gc, bg, 0, 0, 0, 0, ww, wh); /* error: BadMatch (invalid parameter attributes) */
}

void handler(XEvent *ev)
{
	switch (ev->type) {
		case Expose:
			{
				XCopyArea(dpy, bgpm, win, gc, 0, 0, ww, wh, 0, 0); /* error2: BadMatch (invalid parameter attributes)*/
			}
			break;
		case GraphicsExpose:
			{

			}
		case KeyPress: break;
		case KeyRelease:
			{
				char key[1];

				XLookupString(&ev->xkey, key, 1, NULL, NULL);
				if (key[0] == 'c' || key[0] == 'q')
					running = 0;
			}
			break;
	}
}

void run(void)
{
	XEvent ev;

	/* main event loop */
	XSync(dpy, False);
	while (running && !XNextEvent(dpy, &ev))
		handler(&ev);

}

void setup(void)
{
	XSetWindowAttributes wa;
	XSizeHints size;

	/* init window */
	screennum = XDefaultScreen(dpy);
	screen = XScreenOfDisplay(dpy, screennum);
	ww = XWidthOfScreen(screen) / 2; /* for some reason shows as double (I have 2 mons) */
	wh = XHeightOfScreen(screen);
	root = XRootWindow(dpy, screennum);
	visual = XDefaultVisual(dpy, screennum);
	depths = XDefaultDepth(dpy, screennum);
	gc = XDefaultGC(dpy, screennum);
	win = XCreateSimpleWindow(dpy, root, 0, 0, ww, wh, 0, 0, 0);

	/* min/max width/height */
	size.min_width = size.max_width = ww;
	size.min_height = size.max_height = wh;
	size.flags = PMinSize|PMaxSize;
	XSetWMNormalHints(dpy, win, &size);

	XStoreName(dpy, win, "blanket");

	/* window attributes */
	wa.cursor = None;
	wa.event_mask = KeyPressMask|KeyReleaseMask|ExposureMask;
	XChangeWindowAttributes(dpy, win, CWCursor|CWEventMask, &wa);
	XSelectInput(dpy, win, wa.event_mask);

	XMapWindow(dpy, win);
}

void cleanup(void)
{
	XFreePixmap(dpy, bgpm);
	XFreeGC(dpy, gc);
	XUngrabKey(dpy, AnyKey, AnyModifier, win);
	XDestroyWindow(dpy, win);
	XSync(dpy, False);
}

int main()
{
	if (!(dpy = XOpenDisplay(NULL)))
		die("Cannot open display", 7);

	setup();
	createbg();
	run();
	cleanup();

	XCloseDisplay(dpy);
	return 0;
}
