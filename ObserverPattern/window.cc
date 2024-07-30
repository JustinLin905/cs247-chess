#include "window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Xwindow::Xwindow(int width, int height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix =
        XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0, (XGCValues*)0);

    XFlush(d);
    XFlush(d);

    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[10][10] = {"white", "black", "red", "green", "blue",
                               "cyan", "yellow", "magenta", "orange", "brown"};

    cmap = DefaultColormap(d, DefaultScreen(d));
    for (int i = 0; i < 5; ++i) {
        XParseColor(d, cmap, color_vals[i], &xcolour);
        XAllocColor(d, cmap, &xcolour);
        colours[i] = xcolour.pixel;
    }

    XSetForeground(d, gc, colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
    hints.height = hints.base_height = hints.min_height = hints.max_height =
        height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);

    usleep(1000);

    // Make sure we don't race against the Window being shown
    XEvent ev;
    while (1) {
        XNextEvent(d, &ev);
        if (ev.type == Expose) break;
    }
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, const std::string& msg, bool fancy, bool whiteText) {
    XFontStruct* font;
    if (fancy) {
        const char* fontname = "-*-helvetica-*-r-*-*-24-*-*-*-*-*-*-*";
        font = XLoadQueryFont(d, fontname);
        if (!font) {
            std::cerr << "Unable to load font: " << fontname << std::endl;
            return;
        }
        XSetFont(d, DefaultGC(d, s), font->fid);
    }

    // Set the text color
    if (whiteText) {
        XSetForeground(d, DefaultGC(d, s), WhitePixel(d, s));
    } else {
        XSetForeground(d, DefaultGC(d, s), BlackPixel(d, s));
    }

    // Draw the string
    XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());

    if (fancy)
        XFreeFont(d, font);
}
