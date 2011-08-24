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
  QApplication app(argc, argv);
  app.setOrganizationName("Numerical Rocks");
  app.setApplicationName("Application Example");
  QStyle * style;
  style = new QCleanlooksStyle();
  //style = new QProxyStyle();
  app.setStyle(style);

  QMainWindow mainWin;
  mainWin.setContentsMargins(0,0,0,0);

  QWidget * w = new QWidget(&mainWin);
  mainWin.setCentralWidget(w);


  QLayout * layout = new QHBoxLayout(w);
  w->setLayout(layout);

  QDoubleSlider * slider;
  slider = new QDoubleSlider(Qt::Horizontal,w);
  //slider->setTickPosition(QSlider::TicksBelow);
  slider->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
  layout->addWidget(slider);

  mainWin.show();
  return app.exec();

}
