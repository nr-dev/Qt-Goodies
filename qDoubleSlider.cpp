/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/


#include "qDoubleSlider.h"
#ifndef QT_NO_SLIDER
#ifndef QT_NO_ACCESSIBILITY
#include <QtGui/QAccessible>
#endif
#include <QtGui/QApplication>
#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QStyle>
#include <QtGui/QStyleOption>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    Initialize \a option with the values from this QDoubleSlider. This method
    is useful for subclasses when they need a QStyleOptionSlider, but don't want
    to fill in all the information themselves.

    \sa QStyleOption::initFrom()
*/
void QDoubleSlider::initStyleOption(QStyleOptionSlider *option) const
{
  
    if (!option)
        return;

    //    Q_D(const QDoubleSlider);
    option->initFrom(this);
    option->subControls = QStyle::SC_None;
    option->activeSubControls = QStyle::SC_None;
}


/*!
    \class QDoubleSlider
    \brief The QDoubleSlider widget provides a vertical or horizontal slider.

    \ingroup basicwidgets


    The slider is the classic widget for controlling a bounded value.
    It lets the user move a slider handle along a horizontal or vertical
    groove and translates the handle's position into an integer value
    within the legal range.

    QDoubleSlider has very few of its own functions; most of the functionality is in
    QAbstractSlider. The most useful functions are setValue() to set
    the slider directly to some value; triggerAction() to simulate
    the effects of clicking (useful for shortcut keys);
    setSingleStep(), setPageStep() to set the steps; and setMinimum()
    and setMaximum() to define the range of the scroll bar.

    QDoubleSlider provides methods for controlling tickmarks.  You can use
    setTickPosition() to indicate where you want the tickmarks to be,
    setTickInterval() to indicate how many of them you want. the
    currently set tick position and interval can be queried using the
    tickPosition() and tickInterval() functions, respectively.

    QDoubleSlider inherits a comprehensive set of signals:
    \table
    \header \o Signal \o Description
    \row \o \l valueChanged()
    \o Emitted when the slider's value has changed. The tracking()
       determines whether this signal is emitted during user
       interaction.
    \row \o \l sliderPressed()
    \o Emitted when the user starts to drag the slider.
    \row \o \l sliderMoved()
    \o Emitted when the user drags the slider.
    \row \o \l sliderReleased()
    \o Emitted when the user releases the slider.
    \endtable

    QDoubleSlider only provides integer ranges. Note that although
    QDoubleSlider handles very large numbers, it becomes difficult for users
    to use a slider accurately for very large ranges.

    A slider accepts focus on Tab and provides both a mouse wheel and a
    keyboard interface. The keyboard interface is the following:

    \list
        \o Left/Right move a horizontal slider by one single step.
        \o Up/Down move a vertical slider by one single step.
        \o PageUp moves up one page.
        \o PageDown moves down one page.
        \o Home moves to the start (mininum).
        \o End moves to the end (maximum).
    \endlist

    \table 100%
    \row \o \inlineimage macintosh-slider.png Screenshot of a Macintosh slider
         \o A slider shown in the \l{Macintosh Style Widget Gallery}{Macintosh widget style}.
    \row \o \inlineimage windows-slider.png Screenshot of a Windows XP slider
         \o A slider shown in the \l{Windows XP Style Widget Gallery}{Windows XP widget style}.
    \row \o \inlineimage plastique-slider.png Screenshot of a Plastique slider
         \o A slider shown in the \l{Plastique Style Widget Gallery}{Plastique widget style}.
    \endtable

    \sa QScrollBar, QSpinBox, QDial, {fowler}{GUI Design Handbook: Slider}, {Sliders Example}
*/


/*!
    \enum QDoubleSlider::TickPosition

    This enum specifies where the tick marks are to be drawn relative
    to the slider's groove and the handle the user moves.

    \value NoTicks Do not draw any tick marks.
    \value TicksBothSides Draw tick marks on both sides of the groove.
    \value TicksAbove Draw tick marks above the (horizontal) slider
    \value TicksBelow Draw tick marks below the (horizontal) slider
    \value TicksLeft Draw tick marks to the left of the (vertical) slider
    \value TicksRight Draw tick marks to the right of the (vertical) slider

    \omitvalue NoMarks
    \omitvalue Above
    \omitvalue Left
    \omitvalue Below
    \omitvalue Right
    \omitvalue Both
*/


/*!
    Constructs a vertical slider with the given \a parent.
*/
QDoubleSlider::QDoubleSlider(QWidget *parent)
    : QWidget(parent)
{
  init();
}

/*!
    Constructs a slider with the given \a parent. The \a orientation
    parameter determines whether the slider is horizontal or vertical;
    the valid values are Qt::Vertical and Qt::Horizontal.
*/

QDoubleSlider::QDoubleSlider(Qt::Orientation orientation, QWidget *parent)
    : QWidget(parent)
{
  init();
}

void QDoubleSlider::init() 
{
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed));
  _range=range_t(40,60);
  tracking = NONE;
}

/*!
    Destroys this slider.
*/
QDoubleSlider::~QDoubleSlider()
{
}
#include <iostream>

class SliderProperties {
  static const float factor = 0.5;
  
public:
  enum WHICH { NONE=0, FIRST=0x1, SECOND=0x2, BOTH=FIRST|SECOND };

  static QPolygon getMarkerArea(const QRect & bbox, const QPair<int,int> & range, SliderProperties::WHICH which);

  static int getGrooveX(const QRect & bbox) {
    return bbox.x()+factor*.5*bbox.width();
  }
  static int getGrooveY(const QRect & bbox) {
    return bbox.y()+factor*.5*bbox.height();
  }
  static int getGrooveWidth(const QRect & bbox) {
    return (1.0-factor)*bbox.width();
  }
  static int getGrooveHeight(const QRect & bbox) {
    return (1.0-factor)*bbox.height();
  }
  static int getPosMin(const QRect & bbox, int min) {
    return SliderProperties::getGrooveX(bbox)+0.01*min*SliderProperties::getGrooveWidth(bbox);
  }
  static int getPosMax(const QRect & bbox, int max) {
    return SliderProperties::getGrooveX(bbox)+0.01*max*SliderProperties::getGrooveWidth(bbox);
  }

  static void ppoint(const QPoint & p) {
    std::cout<<"("<<p.x()<<","<<p.y()<<")";
  }


  static QDoubleSlider::ELEMENT getElement(const QRect & bbox, const QPair<int, int> & range, const QPoint & pos) {
    QPolygon p = getMarkerArea(bbox, range, SliderProperties::FIRST);
    if (p.containsPoint(pos,Qt::OddEvenFill))
      return QDoubleSlider::FIRST;
    p = getMarkerArea(bbox, range, SliderProperties::SECOND);
    if (p.containsPoint(pos,Qt::OddEvenFill))
      return QDoubleSlider::SECOND;
   
    return QDoubleSlider::NONE;
  }
};

#include <cassert>

QPolygon SliderProperties::getMarkerArea(const QRect & bbox, const QPair<int,int> & range, SliderProperties::WHICH which)
{

  QPolygon paintArea;

  int width=10;
    
  int pos;
  if (which&SliderProperties::FIRST) {
    pos = SliderProperties::getPosMin(bbox,range.first);
    width=-width;
  }
  else {
    assert(which&SliderProperties::SECOND);
    pos = SliderProperties::getPosMin(bbox,range.second);
  }

  int y=SliderProperties::getGrooveY(bbox);
  int base=y+SliderProperties::getGrooveHeight(bbox);
  int tip=base+0.1*bbox.height();

  paintArea.push_back(QPoint(pos,y));
  paintArea.push_back(QPoint(pos,tip));
  paintArea.push_back(QPoint(pos+width,base));
  paintArea.push_back(QPoint(pos+width,y));
  paintArea.push_back(paintArea[0]);

  return paintArea;
}

void cubic_average(QPolygonF & p, size_t j) {
  p[j]=(p[j-1]+4*p[j]+p[j+1])*(1.0/6.0);  
}

void point_insert(QPolygonF & p, size_t j, float l=0.5) {
  size_t prev = j-1;
  if(j==0) {
    assert(p[p.size()-1]==p[0]);
    prev=p.size()-2;
  }
    
  QPointF newPoint=(1-l)*p[prev]+l*p[j];
  p.insert(j,1,newPoint);

  if(j==0) {
    p[p.size()-1]=p[0];
  }
}

void cubic_subdivide(QPolygonF & p, size_t j, int recurse=1) {
  assert(j>0);
  assert(j<p.size()-1);

  
  cubic_average(p,j);

  if(--recurse>=0) {
    point_insert(p,j+1);
    point_insert(p,j);
    cubic_subdivide(p,j+1,recurse);
    cubic_subdivide(p,j,recurse);
  }

}

void paintGroove(QPainter & p, const QRect & bbox) {

  QRect paintBox;

  static const float factor = 0.5;

  paintBox.setX(SliderProperties::getGrooveX(bbox));
  paintBox.setY(SliderProperties::getGrooveY(bbox));
  paintBox.setWidth(SliderProperties::getGrooveWidth(bbox));
  paintBox.setHeight(SliderProperties::getGrooveHeight(bbox));


  QPolygonF paintArea=QPolygon(paintBox,true);

  float offset=0.025;
  float aspect=SliderProperties::getGrooveWidth(bbox)*1.0/SliderProperties::getGrooveHeight(bbox);
  offset=0.2;
  float offset2=offset/aspect;

  for (int i=4;i>0;--i) {
    if(i%2==0) {
      point_insert(paintArea,i,offset);
      point_insert(paintArea,i-1,1-offset2);
    }
    else {
      point_insert(paintArea,i,offset2);
      point_insert(paintArea,i-1,1-offset);
    }
    cubic_subdivide(paintArea,i,7);
  }

  QRectF pbbox=paintArea.boundingRect();

  QPointF p1=pbbox.topLeft();
  QPointF p2=pbbox.bottomRight();
  p2.setX(p1.x());

  QLinearGradient grad(p1,p2);
  grad.setColorAt(0,Qt::black);
  grad.setColorAt(0.15,Qt::gray);
  grad.setColorAt(0.85,Qt::gray);
  grad.setColorAt(1.0,Qt::white);

  p.fillRect(bbox,Qt::blue);
  p.save();
  //p.setRenderHint(QPainter::Antialiasing, true);
  p.setRenderHint(QPainter::HighQualityAntialiasing, true);
  p.setPen(Qt::NoPen);
  //p.drawPoints(paintArea);
  p.setBrush(QBrush(grad));
  p.drawPolygon(paintArea);
  p.restore();
}

void paintFilling(QPainter & p, const QRect & bbox, const QPair<int,int> & range) {

  QRect paintBox;

  int x = SliderProperties::getPosMin(bbox,range.first);
  int width = SliderProperties::getPosMax(bbox,range.second)-x;

  paintBox.setX(x);
  paintBox.setY(SliderProperties::getGrooveY(bbox));
  paintBox.setWidth(width);
  paintBox.setHeight(SliderProperties::getGrooveHeight(bbox));

  QPolygon paintArea=QPolygon(paintBox,true);

  QRectF pbbox=paintArea.boundingRect();

  QPointF p1=pbbox.topLeft();
  QPointF p2=pbbox.bottomRight();
  p2.setX(p1.x());

  QLinearGradient grad(p1,p2);
  grad.setColorAt(0,Qt::black);
  grad.setColorAt(0.15,Qt::red);
  grad.setColorAt(0.85,Qt::red);
  grad.setColorAt(1.0,Qt::white);

  p.save();
  //p.setRenderHint(QPainter::Antialiasing, true);
  p.setRenderHint(QPainter::HighQualityAntialiasing, true);
  p.setPen(Qt::NoPen);
  //p.drawPoints(paintArea);
  p.setBrush(QBrush(grad));
  p.drawPolygon(paintArea);
  p.restore();

}

void paintMarker(QPainter & p, const QRect & bbox, const QPair<int,int> & range, SliderProperties::WHICH which) {

  QRect paintBox;

  p.setBrush(Qt::lightGray);

  if (which&SliderProperties::FIRST) {
    QPolygon poly = SliderProperties::getMarkerArea(bbox, range, which);
    p.drawPolygon(poly);
  }
  if (which&SliderProperties::SECOND) {
    QPolygon poly = SliderProperties::getMarkerArea(bbox, range, which);
    p.drawPolygon(poly);
  }
}

void paintTicks(QPainter & p, const QRect & bbox) {
  int top = SliderProperties::getGrooveY(bbox)+SliderProperties::getGrooveHeight(bbox);
  int bottom = bbox.height();
  int height = bottom-top;

  bottom-=0.2*height;
  top+=0.2*top;
  
  int baseX = SliderProperties::getGrooveX(bbox);
  int width = SliderProperties::getGrooveWidth(bbox);

  for (int i=0;i<100; i+=5) {
    int x=baseX+i*width/100;
    p.drawLine(QPoint(x,top),QPoint(x,bottom));
  }

}



/*!
    \reimp
*/
void QDoubleSlider::paintEvent(QPaintEvent *)
{
  //    Q_D(QDoubleSlider);
    QPainter p(this);
    QStyleOptionSlider opt;

    QRect bbox = geometry();


    paintGroove(p, bbox);
    paintFilling(p, bbox, range());
    paintTicks(p,bbox);
    paintMarker(p, bbox, range(), SliderProperties::FIRST);
    paintMarker(p, bbox, range(), SliderProperties::SECOND);



}

/*!
    \reimp
*/

bool QDoubleSlider::event(QEvent *event)
{
  //    Q_D(QDoubleSlider);

    switch(event->type()) {
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove:
      /*
        if (const QHoverEvent *he = static_cast<const QHoverEvent *>(event))
            d->updateHoverControl(he->pos());
      */
        break;
    case QEvent::StyleChange:
    case QEvent::MacSizeChange:
      //d->resetLayoutItemMargins();
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

/*!
    \reimp
*/
void QDoubleSlider::mousePressEvent(QMouseEvent *ev)
{
  //    Q_D(QDoubleSlider);
    ELEMENT elem = SliderProperties::getElement(geometry(),range(),ev->pos());

    if (elem != QDoubleSlider::NONE) {
      ev->accept();
      tracking = elem;
    }
    
    std::cout<<"Tracking ";

    switch(tracking) {
    case QDoubleSlider::NONE:
      std::cout<<"NONE";
      break;
    case QDoubleSlider::FIRST:
      std::cout<<"FIRST";
      break;
    case QDoubleSlider::SECOND:
      std::cout<<"SECOND";
      break;
    default:
      abort();
    }
    std::cout<<std::endl;
}

/*!
    \reimp
*/
void QDoubleSlider::mouseMoveEvent(QMouseEvent *ev)
{
  if (tracking!=NONE) {
    ev->accept();
    QRect bbox = geometry();
    int val=100*(ev->pos().x()-SliderProperties::getGrooveX(bbox))/SliderProperties::getGrooveWidth(bbox);
    if (val<0)
      val=0;
    if (val>99)
      val=99;
    
    range_t newRange=range();
    
    if (tracking==FIRST) {
      newRange.first=val;
      if (val>newRange.second)
	newRange.second=val;
    }
    else if(tracking==SECOND) {
      newRange.second=val;
      if (val<newRange.first)
	newRange.first=val;
    }
    setValue(newRange);
  }
}

void QDoubleSlider::setValue(const QPair<int,int> & range) {
  this->_range=range;
  update();
  emit valueChanged(range);
}

/*!
    \reimp
*/
void QDoubleSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    tracking=NONE;
}

/*!
    \reimp
*/
QSize QDoubleSlider::sizeHint() const
{
  //Q_D(const QDoubleSlider);
    ensurePolished();
    const int SliderLength = 84, TickSpace = 5;
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    int thick = style()->pixelMetric(QStyle::PM_SliderThickness, &opt, this);
    /*
    if (d->tickPosition & TicksAbove)
        thick += TickSpace;
    if (d->tickPosition & TicksBelow)
        thick += TickSpace;
    */
    int w = thick, h = SliderLength;
    /*
    if (d->orientation == Qt::Horizontal) {
        w = SliderLength;
        h = thick;
    }
    */
    return style()->sizeFromContents(QStyle::CT_Slider, &opt, QSize(w, h), this).expandedTo(QApplication::globalStrut());
}

/*!
    \reimp
*/
QSize QDoubleSlider::minimumSizeHint() const
{
  //    Q_D(const QDoubleSlider);
    QSize s = sizeHint();
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    int length = style()->pixelMetric(QStyle::PM_SliderLength, &opt, this);
    /*
    if (d->orientation == Qt::Horizontal)
        s.setWidth(length);
    else
        s.setHeight(length);
    return s;
    */
}

/*!
    \property QDoubleSlider::tickPosition
    \brief the tickmark position for this slider

    The valid values are described by the QDoubleSlider::TickPosition enum.

    The default value is \l QDoubleSlider::NoTicks.

    \sa tickInterval
*/

void QDoubleSlider::setTickPosition(QSlider::TickPosition position)
{
  //    Q_D(QDoubleSlider);
    //d->tickPosition = position;
    //d->resetLayoutItemMargins();
    update();
    updateGeometry();
}

QSlider::TickPosition QDoubleSlider::tickPosition() const
{
  //return d_func()->tickPosition;
}

/*!
    \fn TickPosition QDoubleSlider::tickmarks() const
    \compat

    Use tickPosition() instead.
*/

/*!
    \fn QDoubleSlider::setTickmarks(TickPosition position)
    \compat

    Use setTickPosition() instead.
*/

/*!
    \property QDoubleSlider::tickInterval
    \brief the interval between tickmarks

    This is a value interval, not a pixel interval. If it is 0, the
    slider will choose between lineStep() and pageStep().

    The default value is 0.

    \sa tickPosition, lineStep(), pageStep()
*/

void QDoubleSlider::setTickInterval(int ts)
{
  //    d_func()->tickInterval = qMax(0, ts);
    update();
}

int QDoubleSlider::tickInterval() const
{
  //    return d_func()->tickInterval;
  return 0;
}

/*!
    \fn void QDoubleSlider::addStep()

    Use setValue() instead.
*/

/*!
    \fn void QDoubleSlider::subtractStep()

    Use setValue() instead.
*/

/*! \internal
    Returns the style option for slider.
*/
Q_GUI_EXPORT QStyleOptionSlider qt_qsliderStyleOption(QDoubleSlider *slider)
{
    QStyleOptionSlider sliderOption;
    slider->initStyleOption(&sliderOption);
    return sliderOption;
}

#endif

QT_END_NAMESPACE
