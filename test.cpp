#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include "qDoubleRangeSlider.h"
#include <QtGui/QSlider>
#include <QtGui/QMotifStyle>
#include <QtGui/QCleanlooksStyle>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QProxyStyle>
#include <QtGui/QBoxLayout>
#include <QtGui/QPushButton>

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  app.setOrganizationName("Numerical Rocks");
  app.setApplicationName("Application Example");
  QStyle* style;
  style = new QCleanlooksStyle();
  app.setStyle(style);

  QMainWindow mainWin;
  mainWin.setContentsMargins(0, 0, 0, 0);

  QWidget* w = new QWidget(&mainWin);
  mainWin.setCentralWidget(w);

  QLayout* layout = new QVBoxLayout(w);
  w->setLayout(layout);

  QDoubleRangeSlider* slider;
  slider = new QDoubleRangeSlider(Qt::Horizontal, w);
  slider->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding));
  slider->setCutoffRange(QPair<double, double>(0,0));
  layout->addWidget(slider);

  QSlider* slider2 = new QSlider(Qt::Horizontal);
  slider2->setRange(0,0);
  layout->addWidget(slider2);

  mainWin.show();
  return app.exec();

}
