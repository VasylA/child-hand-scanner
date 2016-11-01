#include "ScanWidget.h"

#include <QPropertyAnimation>

ScanWidget::ScanWidget(QWidget *parent)
    : QWidget(parent),
      _scanLinePos(0),
      _scanAnimation(nullptr)
{
    const int FULL_SCAN_PERIOD = 10;

    _scanAnimation = new QPropertyAnimation(this, "scanLinePos");
    _scanAnimation->setDuration(FULL_SCAN_PERIOD / 2);
}

void ScanWidget::startScanAnimation()
{
    _scanAnimation->start();
}

qreal ScanWidget::scanLinePos() const
{
    return _scanLinePos;
}

void ScanWidget::setScanLinePos(const qreal &scanLinePos)
{
    _scanLinePos = scanLinePos;

//    setColor();
}
