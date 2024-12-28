#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.H>

int main(int argc, char** argv) {
    Fl_Window window(800, 600, "Resizable Menu Bar Example");

    Fl_Menu_Bar* menu_bar = new Fl_Menu_Bar(0, 0, window.w(), 30);
    // Добавьте элементы меню здесь


    window.resizable(menu_bar); // Устанавливаем menu_bar как изменяемый элемент
    window.show(argc, argv);
    return Fl::run();
}