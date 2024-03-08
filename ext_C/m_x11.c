#include <ruby.h>
#include <X11/Xlib.h>
#include <math.h>

void check_x11(volatile VALUE self, volatile VALUE msg) {
    Display *d;
    Window w;
    XEvent e;
    int s;
    char* message =  StringValuePtr(msg);

    if (!(d = XOpenDisplay(NULL))) {
        fprintf(stderr, "Couldn't open display, but Ruby is awesome!\n");
        exit(1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d,s), 0, 0, 410, 200, 0, 
                            0, WhitePixel(d,s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d,w);

    while (1) {
        XNextEvent(d, &e);
        if (e.type == Expose) {
            XDrawString(d, w, DefaultGC(d, s), 5, 15, message, 17);
        }
    }

    XCloseDisplay(d);
}

void Init_m_x11() {
  // NOTE: need the config line $LDFLAGS << " -lX11" at the file "extconf.rb"
  // we have to global vars: $CFLAGS and $LDFLAGS.
  // $LDFLAGS is to define the lib to run the code in ruby
  // $CFLAGS is to define the lib to run the code in C
  // call it in irb: RbConfig::CONFIG["CFLAGS"] or RbConfig::CONFIG["LDFLAGS"]

  rb_define_global_function("x11", check_x11, 1);
}