#ifndef QDOUBLESLIDER_H
#define QDOUBLESLIDER_H

#include "qRangeSlider.h"

class QDoubleSlider : public QWidget
{
  Q_OBJECT
    public:
  explicit QDoubleSlider(QWidget * = 0);
  explicit QDoubleSlider(Qt::Orientation orientation, QWidget *parent = 0);

 private:
  void setup();
  QRangeSlider * slider_;
};

#endif // QDOUBLESLIDER_H
