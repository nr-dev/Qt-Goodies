#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "qDoubleSlider.h"

 int main(int argc, char *argv[])
 {
   //Q_INIT_RESOURCE(application);

     QApplication app(argc, argv);
     app.setOrganizationName("Trolltech");
     app.setApplicationName("Application Example");
     QMainWindow mainWin;
     

     mainWin.setCentralWidget(new QDoubleSlider());

     mainWin.show();
     return app.exec();
 }
