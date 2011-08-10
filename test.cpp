#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "qDoubleSlider.h"
#include <QtGui/QSlider>
#include <QtGui/QMotifStyle>
#include <QtGui/QCleanlooksStyle>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QProxyStyle>
#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>

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

     //mainWin.setLayout(mLayout);

     /*
     QWidget * w = new QPushButton(&mainWin);
     mainWin.setCentralWidget(w);
     */
     QWidget * w = new QWidget(&mainWin);
     mainWin.setCentralWidget(w);


     //QLayout * layout = new QBoxLayout(QBoxLayout::LeftToRight);
     //w->setLayout(layout);
     //QLayout * layout = new QGridLayout(w);
     QLayout * layout = new QHBoxLayout(w);
     w->setLayout(layout);

#if 0
     QSlider * slider;
     slider = new QSlider(Qt::Horizontal,w);
#else
     QDoubleSlider * slider;
     slider = new QDoubleSlider(Qt::Horizontal,w);
#endif
     //slider->setTickPosition(QSlider::TicksBelow);
     slider->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
     slider->setMinimumWidth(500);

     layout->addWidget(slider);

     mainWin.resize(500,80);

     //mainWin.setCentralWidget(w);


     mainWin.show();
     return app.exec();

 }
