#include "scanwidget.h"

#include <QPropertyAnimation>

ScanWidget::ScanWidget(QWidget *parent)
    : QWidget(parent),
      _fullScanPeriod(10000),
      _scanLinePos(0),
      _baseColor(100, 0, 150),
      _scanAnimation(nullptr)
{
    _scanAnimation = new QPropertyAnimation(this, "scanLinePos");
    _scanAnimation->setDirection(QAbstractAnimation::Backward);
    _scanAnimation->setDuration(_fullScanPeriod / 2);

    connect(_scanAnimation, SIGNAL(finished()), SLOT(startScanAnimation()));
}

void ScanWidget::startScanAnimation()
{
    if (_scanAnimation->state() == QAbstractAnimation::Running)
        _scanAnimation->stop();

    QAbstractAnimation::Direction newDirection = (_scanAnimation->direction() == QAbstractAnimation::Forward) ? QAbstractAnimation::Backward
                                                                                                              : QAbstractAnimation::Forward;
    _scanAnimation->setStartValue(0.0);
    _scanAnimation->setEndValue(1.0);
    _scanAnimation->setDirection(newDirection);
    _scanAnimation->setDuration(_fullScanPeriod / 2);

    _scanAnimation->start();
}

void ScanWidget::stopScanAnimation()
{
    if (_scanAnimation->state() == QAbstractAnimation::Running)
        _scanAnimation->stop();

    _scanAnimation->setDirection(QAbstractAnimation::Backward);
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

    linearGradient.setColorAt(0,   _baseColor);
    if (_scanLinePos >= 0.03)
        linearGradient.setColorAt(_scanLinePos - 0.03,   _baseColor);
    linearGradient.setColorAt(_scanLinePos, Qt::white);
    if (_scanLinePos <= 0.97)
        linearGradient.setColorAt(_scanLinePos + 0.03,   _baseColor);
    linearGradient.setColorAt(1,   _baseColor);

    linearGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    colorScheme.setBrush(QPalette::Background, linearGradient);

    setAutoFillBackground(true);
    setPalette(colorScheme);
}

int ScanWidget::fullScanPeriod() const
{
    return _fullScanPeriod;
}

void ScanWidget::setFullScanPeriod(int fullScanPeriod)
{
    _fullScanPeriod = fullScanPeriod;
}

QColor ScanWidget::baseColor() const
{
    return _baseColor;
}

void ScanWidget::setBaseColor(const QColor &baseColor)
{
    _baseColor = baseColor;
}
