#include "fltk.h"

const char* WINDOW_TITLE            = "APXviewer"; 
const short WINDOW_WIDTH            = 1000;
const short WINDOW_HEIGHT           = 700;

const short MENU_BAR_X              = 0;
const short MENU_BAR_Y              = 0;
const short MENU_BAR_WIDTH          = WINDOW_WIDTH;
const short MENU_BAR_HEIGHT         = 30;

const short MOVEABLE_IMAGE_X        = 0;
const short MOVEABLE_IMAGE_Y        = 0;


bool image_open = false;


class General_Image : public Fl_RGB_Image {
public:
    General_Image(const char* image_name) : Fl_RGB_Image(nullptr, 0, 0, 3) {
        
    }
private:

};


class Moveable_Image : public Fl_Widget {
public:
    Moveable_Image(short x, short y) : Fl_Widget(x, y, 0, 0) {}
    
    void setImage(const char* image_name) {
        if(original_image)
            delete original_image;

        original_image = new General_Image(image_name);
	    shared_image = Fl_Shared_Image::get(original_image);
	    size(shared_image->w(), shared_image->h());
    }

    int handle(int event) {
        switch(event) 
        {
            case FL_PUSH:{
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                return 1;
            }

            case FL_DRAG: {
                int dx = Fl::event_x() - drag_x;
                int dy = Fl::event_y() - drag_y;
                position(x() + dx, y() + dy);
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                Fl::redraw();
                return 1;
            }

        }
        return Fl_Widget::handle(event);
    }

    void draw() override {
        if(shared_image)
            shared_image->draw(x(), y());
    }

private:
    General_Image* original_image;
    Fl_Shared_Image *shared_image;
    short drag_x, drag_y;
};
