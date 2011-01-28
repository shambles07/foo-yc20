/*
    Foo-YC20 UI Header
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


#ifndef _FOO_YC20_UI_H
#define _FOO_YC20_UI_H

#include <stdint.h>

#include <gtk/gtk.h>

#include <jack/ringbuffer.h>

#include <wdgt.h>
#include <yc20_wdgts.h>
#include <foo-yc20.h>

class YC20UI : public YC20Exposable
{
	public:
		YC20UI(YC20Processor *);

		virtual ~YC20UI();

		GtkWidget *getWidget() { return drawingArea; }

		virtual void queueExpose(int cc);

		virtual void updateControlsFromState();

		// Events
		void size_request(GtkRequisition *);
		void size_allocate(GtkAllocation *);
		bool expose(GdkEventExpose *);
		void realize();

		bool motion_notify_event(GdkEventMotion *);
		bool button_press_event(GdkEventButton *);
		bool button_release_event(GdkEventButton *);

	private:
		YC20Processor *yc20;

		GtkWidget *drawingArea;

		float ui_scale;

		bool exposeWdgt(Wdgt::Object *);



		bool draw_queue();

		Wdgt::Object *identifyWdgt(GdkEventMotion *);

		Wdgt::Object *_hoverWdgt;
		Wdgt::Draggable *_dragWdgt;
		Wdgt::Object *_buttonPressWdgt;

		int _dragStartX;
		int _dragStartY;
		float _predrag_value;

		std::list<Wdgt::Object *> wdgts;

		std::map<std::string, Wdgt::Object *> wdgtPerLabel;
		Wdgt::Draggable *draggablePerCC[127];

		bool _ready_to_draw;

		// Idle-timeout redraw things

		jack_ringbuffer_t *exposeRingbuffer;
		static gboolean idleTimeout(gpointer );
		void handleExposeEvents();
		gint idleSignalTag;

		// Images
		cairo_surface_t *_image_background;
		cairo_surface_t *drawbarWhiteImages[4];
		cairo_surface_t *drawbarBlackImages[4];
		cairo_surface_t *drawbarGreenImages[4];
		cairo_surface_t *potentiometerImage;
};


#endif /* _FOO_YC20_UI_H */