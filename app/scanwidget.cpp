#include "scanwidget.h"

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

    updateUi();
}

void ScanWidget::updateUi()
{
    QPalette colorScheme(palette());

    QLinearGradient linearGradient;
    linearGradient.setStart(0, 0);
    linearGradient.setFinalStop(0, 1);
    linearGradient.setColorAt(0, Qt::green);
    linearGradient.setColorAt(_scanLinePos - 0.1,  Qt::green);
    linearGradient.setColorAt(_scanLinePos, Qt::white);
    linearGradient.setColorAt(_scanLinePos + 0.1, Qt::green);
    linearGradient.setColorAt(1, Qt::green);
    linearGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    colorScheme.setBrush(QPalette::Background, linearGradient);

    setAutoFillBackground(true);
    setPalette(colorScheme);
}
