#ifndef QDOUBLESLIDER_H
#define QDOUBLESLIDER_H

#include "qRangeSlider.h"
#include "RangeSliderUnitConverter.h"
#include <limits>

class QDoubleRangeSlider
: public QWidget,
  public RangeSliderUnitConverter
{
  Q_OBJECT
    public:
  typedef QPair<double,double> range_t;

  static double numericalLimitMax() {
    return std::numeric_limits<float>::max();
  }
  static double numericalLimitMin() {
    return -std::numeric_limits<float>::max();
  }
  static range_t numericalLimits() {
    return range_t(numericalLimitMin(),numericalLimitMax());
  }


  Q_PROPERTY(bool logaritmic READ isLogarithmic WRITE setLogarithmic)
  Q_PROPERTY(range_t range READ range WRITE setRange NOTIFY rangeChanged)
  Q_PROPERTY(range_t cutoffRange
             READ cutoffRange
             WRITE setCutoffRange
             NOTIFY cutoffRangeChanged)

  explicit QDoubleRangeSlider(QWidget* parent = 0);
  explicit QDoubleRangeSlider(Qt::Orientation orientation,
                              QWidget* parent = 0);

  range_t range() const;
  range_t cutoffRange() const;

  bool isLogarithmic() const;

 public slots:
  void setRange(QPair<double, double>);
  void setCutoffRange(QPair<double, double>);
  void setLogarithmic(bool logaritmic);

 signals:
  void rangeChanged(QPair<double, double>);
  void cutoffRangeChanged(QPair<double, double>);

  private slots:
  void rangeChanged(QPair<int,int>);

 private:
  void setup();
  void resetInternalCutoffRange();
  void resetInternalRange();



  QRangeSlider* slider_;

  QPair<double, double> cutoffRange_;
  QPair<double, double> range_;

  QPair<int,int> expectValue_;

  double convertFromBaseToDouble(int) const;
  QVariant convertFromBase(int) const;
  QPair<double,double> convertFromBase(QPair<int, int>) const;

  int convertToBase(QVariant value) const;
  int convertToBase(double value) const;
  QPair<int, int> convertToBase(QPair<double, double> value) const;

  static bool cmp(int a, int b, uint tolerance = 0);
  static bool cmp(const QPair<int, int>& a,
                  const QPair<int, int>& b,
                  uint tolerance = 0);

  static bool clamp(QPair<double,double>& value,
                    const QPair<double,double>& limits);
  static bool clamp(double& value, const QPair<double,double>& limits);

  bool isLogarithmic_;
};

#endif // QDOUBLESLIDER_H
