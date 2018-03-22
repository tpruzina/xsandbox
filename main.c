#include <X11/Xlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int secure=0;

static void
toggle_secure_input(Display *dpy, Window w)
{
    if (secure)
    {
	XUngrabKeyboard(dpy, CurrentTime);
    }
    else
    {
	if (XGrabKeyboard(dpy, w, False, GrabModeAsync, GrabModeAsync, CurrentTime)
	    == GrabSuccess)
        {
	    printf("Secure\n");
            secure = !secure;
	}
        else
        {
            fprintf(stderr, "Failed to grab the keyboard\n");
	}
    }
}


Window
get_current_window(Display *dpy)
{
    Window foo, w;
    int bar;

    do
        (void) XQueryPointer(dpy, DefaultRootWindow(dpy), &foo, &w, &bar, &bar, &bar, &bar, &bar);
    while(w <= 0);

    return w;
}

Display *
get_current_dpy(void)
{
    return XOpenDisplay(NULL);
}

int main()
{

    Display *dpy = get_current_dpy();
    Window w = get_current_window(dpy);

    toggle_secure_input(dpy, w);
    sleep(10);
    toggle_secure_input(dpy, w);

    return 0;
}
