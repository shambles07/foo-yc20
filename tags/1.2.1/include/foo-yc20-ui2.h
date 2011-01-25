/*
    Foo-YC20 UI2 Header
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


#ifndef _FOO_YC20_UI2_H
#define _FOO_YC20_UI2_H

#include <stdint.h>

#include <gtk/gtk.h>

#include <wdgt.h>
#include <yc20_wdgts.h>

typedef void (*parameterchange_callback)(void *, uint32_t, float);

class YC20UI2
{
	public:
		YC20UI2();

		virtual ~YC20UI2();

		GtkWidget *getWidget() { return drawingArea; }

		void setControlFromLV2(int, float);
		void setParameterChangedCallback(parameterchange_callback, void *);

		// Events
		void size_request(GtkRequisition *);
		void size_allocate(GtkAllocation *);
		bool expose(GdkEventExpose *);

		bool motion_notify_event(GdkEventMotion *);
		bool button_press_event(GdkEventButton *);
		bool button_release_event(GdkEventButton *);

	private:
		GtkWidget       *drawingArea;

		float ui_scale;

		bool exposeWdgt(Wdgt::Object *);

		Wdgt::Object    *identifyWdgt(GdkEventMotion *);

		Wdgt::Object    *_hoverWdgt;
		Wdgt::Draggable *_dragWdgt;
		Wdgt::Object    *_buttonPressWdgt;

		int _dragStartX;
		int _dragStartY;
		float _predrag_value;

		std::list<Wdgt::Object *> wdgts;
		Wdgt::Draggable* draggablePerLV2Port[27];

		parameterchange_callback parameter_changed;
		void *parameter_changed_obj;

		// Images
		cairo_surface_t *_image_background;
		cairo_surface_t *drawbarWhiteImages[4];
		cairo_surface_t *drawbarBlackImages[4];
		cairo_surface_t *drawbarGreenImages[4];
		cairo_surface_t *potentiometerImage;
};


#endif /* _FOO_YC20_UI2_H */