#include "fltk.h"
#include <string>
#include <memory>


struct Menu_Bar : Fl_Menu_Bar {
    Menu_Bar(int x, int y, int w, int h) : Fl_Menu_Bar(x, y, w, h) {}

    void resize(int x, int y, int w, int h) override { Fl_Menu_Bar::resize(x, y, w, this->h()); }
};


class Moveable_Image : public Fl_Widget {
public:
    Moveable_Image(Fl_Window* scrn, int w, int h) : Fl_Widget(0, 0, 0, 0), screen(scrn), _drag_x(0), _drag_y(0),
                                                    _border_width(w), _border_height(h) { fl_register_images(); } //
    ~Moveable_Image() {
        if (shared_image) 
            shared_image->release();
    }

    void setImage(const char* image_name) {
        if (shared_image) 
            shared_image->release();
        
        shared_image = Fl_Shared_Image::get(image_name);

        //* Reduce shared_image proportionally, 
        //* if it size is larger than the screen
        if (shared_image->w() > screen->w() || shared_image->h() > screen->h()) {
            Fl_Image* temp;
            float aspect_ratio = static_cast<float>(shared_image->w()) / shared_image->h();

            if (shared_image->w() > shared_image->h()) 
                temp = shared_image->copy(screen->w(), screen->w() / aspect_ratio);
            else 
                temp = shared_image->copy(screen->h() * aspect_ratio, screen->h());
            
            shared_image = (Fl_Shared_Image *)temp;
        }

        size(shared_image->w(), shared_image->h());
        setPosCenter();
    }

    int handle(int event) {
        switch(event) 
        {
            case FL_PUSH:{
                _drag_x = Fl::event_x();
                _drag_y = Fl::event_y();
                return 1;
            }

            case FL_DRAG: {
                int dx = Fl::event_x() - _drag_x;    //* Compute position projection
                int dy = Fl::event_y() - _drag_y;    //* on x and y axis
                position(x() + dx, y() + dy);
                _drag_x = Fl::event_x();
                _drag_y = Fl::event_y();
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

    void setPosCenter() {
        //* Compute position with menu_bar dimensions
        position((screen->w()- w()) / 2 + _border_width / 2, (screen->h() - h()) / 2 + _border_height / 2); 
    }
    
private:
    Fl_Window* screen;
    Fl_Shared_Image* shared_image;
    int _drag_x, _drag_y;
    int _border_width, _border_height; //* menu_bar dimensions
};
