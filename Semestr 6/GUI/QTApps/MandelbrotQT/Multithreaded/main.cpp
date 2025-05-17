#include <QApplication>

#include "mandelbrotwidget.h"

int main(int argc, char** argv){
    QApplication app(argc, argv);
    
    MandelbrotWidget widget;
    widget.resize(800,600);
    widget.setWindowTitle("Multi-threaded Mandelbrot Set");
    widget.show();
    
    return app.exec();
}
