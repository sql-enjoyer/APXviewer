#include "APXviewer.h"


extern void build_window();
extern void build_menu_bar();
extern void build_moveable_image();
extern void build_file_chooser();

extern void quit_callback(Fl_Widget* widget, void* data);
extern void open_image_callback(Fl_Widget* widget, void* data);


Fl_Window*          window;
Fl_Menu_Bar*        menu_bar;
Moveable_Image*     moveable_image;
Fl_File_Chooser*    file_chooser;

Fl_Menu_Item    menu_item[] = 
{
    {"Open image...", FL_COMMAND + 'o', open_image_callback},
    {"Quit", FL_COMMAND + 'q', quit_callback},
    {0}
};



void build_window() {
    window = new Fl_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    window->callback(quit_callback);
}

void build_menu_bar() {
    menu_bar = new Fl_Menu_Bar(MENU_BAR_X, MENU_BAR_Y, MENU_BAR_WIDTH, MENU_BAR_HEIGHT);
    menu_bar->copy(menu_item);
}

void build_moveable_image() {
    moveable_image = new Moveable_Image(MOVEABLE_IMAGE_X, MOVEABLE_IMAGE_Y);
}

void build_file_chooser() {
    file_chooser = new Fl_File_Chooser(".", "*.{jpg,jpeg}", Fl_File_Chooser::SINGLE, "Choose image");
}



void quit_callback(Fl_Widget* widget, void* data) {
    if (image_open) {
        short ans = fl_choice("Вы действительно хотите выйти?", "Нет", "Да", NULL);
        if (ans == 1)
            exit(0);
    } else {
        exit(0);
    }
}

void open_image_callback(Fl_Widget* widget, void* data) {
    file_chooser->show();
    while (file_chooser->shown())
        Fl::wait();

    if(!file_chooser->count())
    	return;
    const char* file_path = file_chooser->value();
    moveable_image->setImage(file_path);
    moveable_image->redraw();
}


int main() {
    build_window();
    build_moveable_image();
    build_menu_bar();
    build_file_chooser();

    window->end();
    window->show();
    return Fl::run();
}