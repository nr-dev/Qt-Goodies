#ifndef QDOUBLESLIDER_H
#define QDOUBLESLIDER_H

#include "qRangeSlider.h"
#include <limits>

class QDoubleSlider : public QWidget
{
  Q_OBJECT
    public:
  typedef QPair<double,double> range_t;

  static const double numericalLimitMax() {
    return std::numeric_limits<float>::max();
  }
  static const double numericalLimitMin() {
    return -std::numeric_limits<float>::max();
  }
  static range_t numericalLimits() {
    return range_t(numericalLimitMin(),numericalLimitMax());
  }


  Q_PROPERTY(range_t range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(range_t cutoffRange
             READ cutoffRange
             WRITE setCutoffRange
             NOTIFY maxRangeChanged)

  explicit QDoubleSlider(QWidget* parent = 0);
  explicit QDoubleSlider(Qt::Orientation orientation, QWidget* parent = 0);

  range_t range() const;
  range_t cutoffRange() const;

 public slots:
  void setRange(QPair<double, double>);
  void setCutoffRange(QPair<double, double>);

 signals:
  void rangeChanged(QPair<double, double>);
  void cutoffRangeChanged(QPair<double, double>);

  private slots:
  void rangeChanged(QPair<int,int>);

 private:
  void setup();

  QRangeSlider* slider_;

  QPair<double, double> cutoffRange_;
  QPair<double, double> range_;

  QPair<int,int> expectValue_;

  double convertFromRangeSlider(int) const;
  QPair<double,double> convertFromRangeSlider(QPair<int, int>) const;

  int convertToRangeSlider(double value) const;
  QPair<int, int> convertToRangeSlider(QPair<double, double> value) const;

  static bool cmp(int a, int b, uint tolerance = 0);
  static bool cmp(const QPair<int, int>& a,
                  const QPair<int, int>& b,
                  uint tolerance = 0);

  static bool clamp(QPair<double,double>& value,
                    const QPair<double,double>& limits);
  static bool clamp(double& value, const QPair<double,double>& limits);
};

#endif // QDOUBLESLIDER_H
