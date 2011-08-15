#ifndef QDOUBLESLIDER_H
#define QDOUBLESLIDER_H

#include "qRangeSlider.h"

class QDoubleSlider : public QWidget
{
  Q_OBJECT
    public:
  typedef QPair<double,double> range_t;

  Q_PROPERTY(range_t range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(range_t maxRange READ maxRange WRITE setMaxRange NOTIFY maxRangeChanged)

  explicit QDoubleSlider(QWidget * = 0);
  explicit QDoubleSlider(Qt::Orientation orientation, QWidget *parent = 0);

  range_t range() const;
  range_t maxRange() const;

 public slots:
  void setRange(QPair<double,double>);
  void setMaxRange(QPair<double,double>);

 signals:
  void rangeChanged(QPair<double,double>);
  void maxRangeChanged(QPair<double,double>);

  private slots:
  void rangeChanged(QPair<int,int>);

 private:
  void setup();
  QRangeSlider * slider_;
  QPair<double,double> maxRange_;
  QPair<double,double> range_;

  double convertFromRangeSlider(int) const;
  QPair<double,double> convertFromRangeSlider(QPair<int,int>) const;
  int convertToRangeSlider(double value) const;
  QPair<int,int> convertToRangeSlider(QPair<double,double> value) const;

  static bool cmp(int, int, uint = 0);
  static bool cmp(const QPair<int,int> &, const QPair<int,int> &, uint = 0);
};

#endif // QDOUBLESLIDER_H
