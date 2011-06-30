#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "qDoubleSlider.h"
#include <QtGui/QSlider>
#include <QtGui/QMotifStyle>
#include <QtGui/QCleanlooksStyle>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QProxyStyle>
#include <QtGui/QBoxLayout>

 int main(int argc, char *argv[])
 {
   //Q_INIT_RESOURCE(application);
  
     QApplication app(argc, argv);
     app.setOrganizationName("Numerical Rocks");
     app.setApplicationName("Application Example");
     QStyle * style;
     style = new QCleanlooksStyle();
     //style = new QProxyStyle();
     app.setStyle(style);

     QMainWindow mainWin;
     

     QWidget * w = new QWidget();

     //QLayout * layout = new QBoxLayout(QBoxLayout::LeftToRight);
     //w->setLayout(layout);

     

     
     //QSlider * slider;
     QDoubleSlider * slider;
     //slider = new QDoubleSlider(Qt::Horizontal,w);
     slider = new QDoubleSlider(Qt::Horizontal,w);
     //slider->setTickPosition(QSlider::TicksBelow);
     //slider->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
     slider->setMinimumWidth(500);
     mainWin.resize(500,40);

     mainWin.setCentralWidget(w);
     

     mainWin.show();
     return app.exec();

 }
