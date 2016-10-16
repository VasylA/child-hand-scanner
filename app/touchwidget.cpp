#include "touchwidget.h"

#include <QTouchEvent>
#include <QPalette>
#include <QColor>

TouchWidget::TouchWidget(QWidget *parent)
    : QWidget(parent),
      _scanState(SS_None)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);

    _scanTimer.setInterval(FULL_SCAN_PERIOD);
    _scanTimer.setSingleShot(true);

    connect(&_scanTimer, SIGNAL(timeout()), SLOT(checkTouchState()));

    setScanState(SS_None);
}

bool TouchWidget::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        int staticPointsCount = 0;
        QList<QTouchEvent::TouchPoint> touchPoints = static_cast<QTouchEvent *>(event)->touchPoints();
        foreach (const QTouchEvent::TouchPoint &touchPoint, touchPoints)
        {
            if (touchPoint.state() == Qt::TouchPointStationary)
                staticPointsCount++;
        }

        if (staticPointsCount > 1)
            checkStateForEnoughPoints();
        else
            checkStateForNotEnoughPoints();
    }
        break;

    default:
        return QWidget::event(event);
    }
    return true;
}

void TouchWidget::setColor(QColor color)
{
    QPalette colorScheme(palette());
    colorScheme.setColor(QPalette::Background, color);

    setAutoFillBackground(true);
    setPalette(colorScheme);
}

void TouchWidget::checkStateForEnoughPoints()
{
    switch (_scanState)
    {
    case SS_None:
        if (_scanTimer.isActive())
        {
            _scanTimer.stop();
            break;
        }
        _scanTimer.start();

        setScanState(SS_Started);
        break;

    case SS_Started:
        if (_scanTimer.isActive())
        {
            if (_scanTimer.remainingTime() > 0)
                break;

            setScanState(SS_Finished);
            break;
        }
        break;

    default:
        break;
    }
}

void TouchWidget::checkStateForNotEnoughPoints()
{
    switch (_scanState)
    {
    case SS_None:
        if (_scanTimer.isActive())
            _scanTimer.stop();
        break;

    case SS_Started:
        if (_scanTimer.isActive())
        {
            _scanTimer.stop();
            setScanState(SS_Interrupted);
        }
        break;

    default:
        break;
    }
}

void TouchWidget::resetTouchState()
{
    setScanState(SS_None);
}

void TouchWidget::checkTouchState()
{
    switch (_scanState)
    {
    case SS_Started:
        if (_scanTimer.isActive())
            break;

        setScanState(SS_Finished);
        break;

    default:
        break;
    }
}

TouchWidget::ScanState TouchWidget::scanState() const
{
    return _scanState;
}

void TouchWidget::setScanState(const ScanState &scanState)
{
    _scanState = scanState;

    switch (_scanState)
    {
    case SS_Started:
        setColor(Qt::blue);
        emit scanStarted();
        break;

    case SS_Finished:
        setColor(Qt::green);
        emit scanFinished();

        QTimer::singleShot(3000, this, SLOT(resetTouchState()));
        break;

    case SS_Interrupted:
        setColor(Qt::red);
        emit scanInterrupted();

        QTimer::singleShot(3000, this, SLOT(resetTouchState()));
        break;

    default:
        setColor(Qt::white);
        break;
    }
}

