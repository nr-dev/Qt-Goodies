#include "qDoubleRangeSlider.h"

#include <QtGui/QHBoxLayout>
#include <cassert>


QDoubleRangeSlider::QDoubleRangeSlider(QWidget* parent)
  : QWidget(parent),
    slider_(new QRangeSlider(this))
{
  setup();
}

QDoubleRangeSlider::QDoubleRangeSlider(Qt::Orientation orientation,
                                       QWidget* parent)
  : QWidget(parent),
    slider_(new QRangeSlider(orientation, this))
{
  setup();
}

void
QDoubleRangeSlider::setup()
{
  QLayout* layout = new QHBoxLayout(this);
  setLayout(layout);
  layout->addWidget(slider_);
  layout->setContentsMargins(0,0,0,0);
  cutoffRange_ = numericalLimits();
  range_ = cutoffRange_;
  resetInternalCutoffRange();
  resetInternalRange();
  bool ok = true;
  ok &= connect(slider_,SIGNAL(rangeChanged(QPair<int,int>)),
                this,SLOT(rangeChanged(QPair<int,int>)));
  assert(ok);
}


void QDoubleRangeSlider::resetInternalCutoffRange()
{
  slider_->setCutoffRange(QPair<int, int>(0,10000));
}

void QDoubleRangeSlider::resetInternalRange()
{
  slider_->setRange(QPair<int, int>(0,10000));
}


bool
QDoubleRangeSlider::cmp(int a, int b, uint offset)
{
  return ((a+int(offset))>=b)
    && ((a-int(offset))<=b);
}

bool
QDoubleRangeSlider::cmp(const QPair<int, int>& a,
                   const QPair<int, int>& b,
                   uint offset) {
  return cmp(a.first, b.first, offset)&&
    cmp(a.second, b.second, offset);
}

void
QDoubleRangeSlider::setRange(QPair<double, double> range)
{
  clamp(range,cutoffRange());
  if (range_ == range)
    return;

  range_ = range;

  //Need to allow for perfect values
  QPair<int, int> nRange = convertToRangeSlider(range);
  QPair<int, int> oRange = slider_->range();

  expectValue_ = nRange;

  if (!cmp(oRange,nRange,1)) {
    slider_->setRange(nRange);
  }
}

void
QDoubleRangeSlider::setCutoffRange(QPair<double, double> cutoffRange)
{
  clamp(cutoffRange, numericalLimits());
  if (cutoffRange_ == cutoffRange)
    return;

  if (cutoffRange.first == cutoffRange.second) {
    slider_->setCutoffRange(QPair<int,int>(0, 0));
  }
  else {
    resetInternalCutoffRange();
    resetInternalRange();
  }

  QPair<double, double> oRange = range();

  cutoffRange_ = cutoffRange;

  setRange(oRange);
  emit cutoffRangeChanged(cutoffRange_);
}


QDoubleRangeSlider::range_t
QDoubleRangeSlider::range() const
{
  return range_;
}


QDoubleRangeSlider::range_t
QDoubleRangeSlider::cutoffRange() const
{
  return cutoffRange_;
}


double
QDoubleRangeSlider::convertFromRangeSlider(int value) const
{

  QPair<int, int> sliderMaxRange = slider_->cutoffRange();

  double retVal=(value-sliderMaxRange.first) /
    double(sliderMaxRange.second-sliderMaxRange.first);

  return retVal * (cutoffRange_.second - cutoffRange_.first) +
    cutoffRange_.first;
}


QPair<double, double>
QDoubleRangeSlider::convertFromRangeSlider(QPair<int, int> value) const
{

  return QPair<double, double>(convertFromRangeSlider(value.first),
                              convertFromRangeSlider(value.second));
}


int QDoubleRangeSlider::convertToRangeSlider(double value) const
{

  double retVal = (value-cutoffRange_.first)/
    (cutoffRange_.second-cutoffRange_.first);

  QPair<int, int> sliderMaxRange = slider_->cutoffRange();

  return int(retVal * (sliderMaxRange.second - sliderMaxRange.first) +
             sliderMaxRange.first);
}


void
QDoubleRangeSlider::rangeChanged(QPair<int, int> value)
{
  QPair<double, double> range = convertFromRangeSlider(value);

  if (!cmp(value,expectValue_,1)) {
    range_ = range;
    emit rangeChanged(range);
  }
}

QPair<int, int>
QDoubleRangeSlider::convertToRangeSlider(QPair<double, double> value) const
{

  return QPair<int, int>(convertToRangeSlider(value.first),
                        convertToRangeSlider(value.second));
}

bool QDoubleRangeSlider::clamp(QPair<double, double>& value,
                          const QPair<double, double>& limits)
{
  bool changed = false;
  changed |= clamp(value.first, limits);
  changed |= clamp(value.second, limits);
  return changed;
}

bool QDoubleRangeSlider::clamp(double& value,
                               const QPair<double, double>& limits)
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
