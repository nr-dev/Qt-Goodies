#include "qDoubleSlider.h"

#include <QtGui/QHBoxLayout>
#include <cassert>


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
  layout->setContentsMargins(0,0,0,0);
  maxRange_ = numericalLimits();
  range_ = maxRange_;
  slider_->setMaxRange(QPair<int,int>(0,10000));
  slider_->setRange(QPair<int,int>(0,10000));
  bool ok = true;
  ok &= connect(slider_,SIGNAL(rangeChanged(QPair<int,int>)),
		this,SLOT(rangeChanged(QPair<int,int>)));
  assert(ok);
}

bool
QDoubleSlider::cmp(int a, int b, uint offset)
{
  return ((a+int(offset))>=b)
    && ((a-int(offset))<=b);
}

bool
QDoubleSlider::cmp(const QPair<int,int> & a, const QPair<int,int> & b, uint offset) {
  return cmp(a.first, b.first, offset) &&
    cmp(a.second, b.second, offset);
}

void
QDoubleSlider::setRange(QPair<double,double> range)
{
  clamp(range,maxRange());
  range_ = range;

  //Need to allow for perfect values
  QPair<int,int> nRange = convertToRangeSlider(range);
  QPair<int,int> oRange = slider_->range();

  expectValue_ = nRange;

  if (!cmp(oRange,nRange,1)) {
    slider_->setRange(nRange);
  }
}

void
QDoubleSlider::setMaxRange(QPair<double,double> maxRange)
{
  clamp(maxRange, numericalLimits());
  QPair<double,double> oRange = range();

  maxRange_ = maxRange;

  setRange(oRange);
  emit maxRangeChanged(maxRange_);
}

QDoubleSlider::range_t
QDoubleSlider::range() const
{
  return range_;
}

QDoubleSlider::range_t
QDoubleSlider::maxRange() const
{
  return maxRange_;
}

double
QDoubleSlider::convertFromRangeSlider(int value) const
{

  QPair<int,int> sliderMaxRange = slider_->maxRange();

  double retVal=(value-sliderMaxRange.first)/double(sliderMaxRange.second-sliderMaxRange.first);

  return retVal*(maxRange_.second-maxRange_.first)+maxRange_.first;
}

QPair<double,double>
QDoubleSlider::convertFromRangeSlider(QPair<int,int> value) const
{

  return QPair<double,double>(convertFromRangeSlider(value.first),convertFromRangeSlider(value.second));
}

int
QDoubleSlider::convertToRangeSlider(double value) const
{

  double retVal=(value-maxRange_.first)/(maxRange_.second-maxRange_.first);

  QPair<int,int> sliderMaxRange = slider_->maxRange();

  return int(retVal*(sliderMaxRange.second-sliderMaxRange.first)+sliderMaxRange.first);
}


void
QDoubleSlider::rangeChanged(QPair<int,int> value)
{
  QPair<double,double> range = convertFromRangeSlider(value);

  if (!cmp(value,expectValue_,1)) {
    range_ = range;
    emit rangeChanged(range);
  }
}

QPair<int,int>
QDoubleSlider::convertToRangeSlider(QPair<double,double> value) const
{

  return QPair<int,int>(convertToRangeSlider(value.first),
			convertToRangeSlider(value.second));
}

bool QDoubleSlider::clamp(QPair<double,double> & value,
			  const QPair<double,double> & limits)
{
  bool changed = false;
  changed |= clamp(value.first, limits);
  changed |= clamp(value.second, limits);
  return changed;
}

bool QDoubleSlider::clamp(double & value, const QPair<double,double> & limits)
{
  assert(limits.first <= limits.second);
  if (value < limits.first) {
    value = limits.first;
    return true;
  }
  if (value > limits.second) {
    value = limits.second;
    return true;
  }
  return false;
}
