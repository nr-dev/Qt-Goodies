#include "qDoubleSlider.h"
#include <QtGui/QHBoxLayout>

QDoubleSlider::QDoubleSlider(QWidget * parent)
  : QWidget(parent),
    slider_(new QRangeSlider(this))
{
  setup();
}

QDoubleSlider::QDoubleSlider(Qt::Orientation orientation, QWidget *parent)
  : QWidget(parent),
    slider_(new QRangeSlider(orientation, this))
{
  setup();
}

void
QDoubleSlider::setup()
{
  QLayout * layout=new QHBoxLayout(this);
  setLayout(layout);
  layout->addWidget(slider_);
}
