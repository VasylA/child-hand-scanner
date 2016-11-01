#include "touchwidget.h"

#include <QPropertyAnimation>

TouchWidget::TouchWidget(QWidget *parent)
    : QWidget(parent),
      _scanLinePos(0),
      _scanAnimation(nullptr)
{
    const int FULL_SCAN_PERIOD = 10;

    _scanAnimation = new QPropertyAnimation(this, "scanLinePos");
    _scanAnimation->setDuration(FULL_SCAN_PERIOD / 2);
}

qreal TouchWidget::scanLinePos() const
{
    return _scanLinePos;
}

void TouchWidget::setScanLinePos(const qreal &scanLinePos)
{
    _scanLinePos = scanLinePos;

//    setColor();
}
