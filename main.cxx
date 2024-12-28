#include "APXviewer.h"


const char* WINDOW_TITLE            = "APXviewer"; 
const short WINDOW_WIDTH            = 1000;
const short WINDOW_HEIGHT           = 700;

const short MENU_BAR_X              = 0;
const short MENU_BAR_Y              = 0;
const short MENU_BAR_WIDTH          = WINDOW_WIDTH;
const short MENU_BAR_HEIGHT         = 30;

const short MOVEABLE_IMAGE_X        = 0;
const short MOVEABLE_IMAGE_Y        = MENU_BAR_HEIGHT;
const short MOVEABE_IMAGE_WIDTH     = WINDOW_WIDTH;
const short MOVEABE_IMAGE_HEIGHT    = WINDOW_HEIGHT;

const Fl_Color      MAIN_COLOR      = fl_rgb_color(51, 57, 59);
const Fl_Color      LABEL_COLOR     = FL_WHITE;
const Fl_PNG_Image* WINDOW_ICON     = new Fl_PNG_Image("aphex_twin.png");

bool image_open = false;


extern void build_window();
extern void build_menu_bar();
extern void build_moveable_image();
extern void build_file_chooser();

extern void quit_callback(Fl_Widget* widget, void* data);
extern void open_image_callback(Fl_Widget* widget, void* data);

extern void update_window_title(const char* title);


Fl_Double_Window*   window;
Menu_Bar*           menu_bar;
Moveable_Image*     moveable_image;
Fl_File_Chooser*    file_chooser;
Fl_Menu_Item        menu_item[] = 
{
    {"Open image...", FL_COMMAND + 'o', open_image_callback},
    {0}
};



void build_window() {
    window = new Fl_Double_Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    window->callback(quit_callback);
    window->size_range(350, 300); 
    window->icon(WINDOW_ICON);
    window->color(MAIN_COLOR);
}

void build_menu_bar() {
    menu_bar = new Menu_Bar(MENU_BAR_X, MENU_BAR_Y, MENU_BAR_WIDTH, MENU_BAR_HEIGHT);
    menu_bar->copy(menu_item);
    menu_bar->box(FL_FLAT_BOX);
    menu_bar->color(MAIN_COLOR);
    menu_bar->textcolor(LABEL_COLOR);
}

void build_moveable_image() {
    moveable_image = new Moveable_Image(window, MOVEABLE_IMAGE_X, MOVEABLE_IMAGE_Y);
}

void build_file_chooser() {
    file_chooser = new Fl_File_Chooser(".", "*.{jpg,jpeg,png}", Fl_File_Chooser::SINGLE, "Choose image");
}


void quit_callback(Fl_Widget* widget, void* data) {
    if (image_open) {
        short ans = fl_choice("Do you really want to exit?", "No", "Yes", NULL);
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

    if(file_chooser->count() == 0) //* If no image selected
    	return;
    const char* file_path = file_chooser->value();
    image_open = true;
    moveable_image->setImage(file_path);
    update_window_title(file_path);
    Fl::redraw();
}


void update_window_title(const char* title) {
    if (image_open) {
        char label[260];
        snprintf(label, sizeof(label), "%s - %s", WINDOW_TITLE, title);
        window->copy_label(label);
    } else {
        window->label(WINDOW_TITLE); 
    }
}


int main() {
    build_window();
    build_moveable_image();
    build_menu_bar();
    build_file_chooser();

    window->resizable(menu_bar);
    window->end();
    window->show();
    return Fl::run();
}