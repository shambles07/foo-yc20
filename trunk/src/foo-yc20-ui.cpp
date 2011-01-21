/*
    Foo-YC20 UI
    Copyright (C) 2010  Sampo Savolainen <v2@iki.fi>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <foo-yc20-ui.h>

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// C-functions to wrap gtk/gdk signal handlers to C++ functions

static void yc20ui_size_request(GtkWidget *widget, GtkRequisition *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
        ui->size_request(event);
}

static void yc20ui_size_allocate(GtkWidget *widget, GtkAllocation *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
        ui->size_allocate(event);
}

static gboolean yc20ui_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
	if (event) {
		ui->draw(event->area.x, event->area.y, event->area.width, event->area.height, true);
	} else {
		ui->draw(-1, -1, -1, -1, true);

	}

	return true;
}

static void yc20ui_realize(GtkWidget *widget, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
        ui->realize();
}

static gboolean yc20ui_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
	ui->mouse_movement(event->x, event->y);
	return true;
}

static gboolean yc20ui_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
        ui->button_pressed(event->x, event->y);
	return true;
}

static gboolean yc20ui_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
        YC20UI *ui = (YC20UI *)data;
        ui->button_released(event->x, event->y);
        return true;
}


#ifdef __cplusplus
}
#endif




YC20UI::YC20UI(YC20Processor *parent)
	: YC20BaseUI(parent)
{
	drawingArea = GTK_WIDGET(gtk_drawing_area_new());

	memset(draggablePerCC, 0, sizeof(Wdgt::Draggable *)*127);

        // Gtk signals
        g_signal_connect (drawingArea, "size-request",         G_CALLBACK( yc20ui_size_request ), this);
        g_signal_connect (drawingArea, "size-allocate",        G_CALLBACK( yc20ui_size_allocate ), this);
        g_signal_connect (drawingArea, "expose-event",         G_CALLBACK( yc20ui_expose_event ), this);
	g_signal_connect (drawingArea, "realize",              G_CALLBACK( yc20ui_realize ), this);

        g_signal_connect (drawingArea, "motion-notify-event",  G_CALLBACK( yc20ui_motion_notify_event ), this);
        g_signal_connect (drawingArea, "button-press-event",   G_CALLBACK( yc20ui_button_press_event ), this);
        g_signal_connect (drawingArea, "button-release-event", G_CALLBACK( yc20ui_button_release_event ), this);

        // Event mask
        gint mask = gtk_widget_get_events(drawingArea);

        mask |= GDK_POINTER_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK;

        gtk_widget_set_events(drawingArea, mask);


	/*
	Wdgt::Draggable *c;

	// Pitch, volume & bass volume
	c = wdgtPerLabel["pitch"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["volume"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["bass volume"];
	draggablePerCC[c->getCC()] = c;

	// Vibrato section
	// Instead of the touch vibrato, we have a realism switch
	c = wdgtPerLabel["realism"];
	draggablePerCC[c->getCC()] = c;
	
	c = wdgtPerLabel["depth"];
	draggablePerCC[c->getCC()] = c;
	x += 40.0 + pitch_x;

	c = wdgtPerLabel["speed"];
	draggablePerCC[c->getCC()] = c;

	// Bass
	c = wdgtPerLabel["16' b"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["8' b"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["bass manual"];
	draggablePerCC[c->getCC()] = c;

	// Section I
	c = wdgtPerLabel["16' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["8' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["4' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["2 2/3' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["2' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["1 3/5' i"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["1' i"];
	draggablePerCC[c->getCC()] = c;

	// Balance & Brightness
	c = wdgtPerLabel["balance"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["bright"];
	draggablePerCC[c->getCC()] = c;

	// Section II
	c = wdgtPerLabel["16' ii"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["8' ii"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["4' ii"];
	draggablePerCC[c->getCC()] = c;

	c = wdgtPerLabel["2' ii"];
	draggablePerCC[c->getCC()] = c;

	// Percussion
	c = wdgtPerLabel["percussive"];
	draggablePerCC[c->getCC()] = c;
	*/

	// Make the map
	for (std::list<Wdgt::Draggable *>::iterator i = wdgts.begin(); i !=  wdgts.end(); ++i) {
		Wdgt::Draggable *o = (*i);

		Control *c = yc20->getControl(o->getName());
		draggablePerCC[c->getCC()] = o;
		
	}


	// Create the ringbuffer and start the timeout thread
	exposeRingbuffer = jack_ringbuffer_create(sizeof(Wdgt::Draggable *)*1000);
	if (exposeRingbuffer == NULL) {
		throw "Could not create ringbuffer";
	}
	idleSignalTag = g_timeout_add(10, idleTimeout, this);

}

void
YC20UI::updateControlsFromState()
{
	for (std::list<Wdgt::Draggable *>::iterator i = wdgts.begin(); i != wdgts.end(); ++i) {
		Wdgt::Draggable *o = (*i);
		Wdgt::Draggable *draggable = dynamic_cast<Wdgt::Draggable *>(o);
		if (draggable != NULL) {
			draggable->setValue( *draggable->getZone() );
		}
	}
}


void
YC20UI::size_request(GtkRequisition *req)
{
	//std::cerr << "size_request: " << req->width << " x " << req->height << std::endl;

	if (req->width > 1280) {
		req->width = 1280;
	} else if (req->width < 768) {
		req->width = 768;
	}

	float scale = (float)req->width/1280.0;

	set_scale(scale);

	req->height = 200.0 * scale;
}


void 
YC20UI::size_allocate(GtkAllocation *alloc)
{
        if (alloc->width > 1280) {
                alloc->width = 1280;
        } else if (alloc->width < 768) {
                alloc->width = 768;
        }

	float scale = (float)alloc->width/1280.0;

	set_scale(scale);

        alloc->height = 200.0 * scale;
}

void
YC20UI::realize()
{
	GdkGeometry geom;
	geom.min_width  = 768;
	geom.min_height = 120; // 200.0 * (768.0 / 1280.0);
	geom.max_width  = 1280;
	geom.max_height = 200;

	geom.min_aspect = 1280.0/200.0;
	geom.max_aspect = 1280.0/200.0;

	geom.width_inc  = 64;
	geom.height_inc = 10;

	GtkWidget *top = gtk_widget_get_toplevel(drawingArea);
	if (top == NULL) {
		std::cerr << "No toplevel widget?!?!" << std::endl;
		return;
	}

	GtkWindow *window = GTK_WINDOW(top);
	if (window == NULL) {
		std::cerr << "could not find the toplevel window. weird." << std::endl;
		return;
	}
	
	GdkWindowHints hints = (GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE | GDK_HINT_ASPECT | GDK_HINT_RESIZE_INC);
	gtk_window_set_geometry_hints(window, NULL, &geom, hints);
}

gboolean 
YC20UI::idleTimeout(gpointer data)
{
	YC20UI *obj = (YC20UI *)data;
	obj->handleExposeEvents();

	return true;
}

void
YC20UI::handleExposeEvents()
{
	Wdgt::Draggable *obj;

	while ( jack_ringbuffer_read(exposeRingbuffer, 
	                             (char *)&obj,
	                             sizeof(Wdgt::Draggable *)) == sizeof(Wdgt::Draggable *)) {
		obj->setValue( *obj->getZone() );
		draw_wdgt(obj);
	}
}

void
YC20UI::queueExpose(int cc)
{
	Wdgt::Draggable *obj = draggablePerCC[cc];
	if (obj == NULL) {
		std::cerr << "Tried to queue an expose event for a non-existent control" << std::endl;
		return;
	}

	int i = jack_ringbuffer_write(exposeRingbuffer, (char *)&obj, sizeof(Wdgt::Draggable *));
	if (i != sizeof(Wdgt::Draggable *)) {
		std::cerr << "Ringbuffer full!" << std::endl;
	}
}

YC20UI::~YC20UI()
{
	g_source_remove(idleSignalTag);

	jack_ringbuffer_free(exposeRingbuffer);
}

