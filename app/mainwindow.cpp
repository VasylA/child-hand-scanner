#include "mainwindow.h"
#include "touchwidget.h"

#include <QPropertyAnimation>
#include <QTouchEvent>
#include <QPalette>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _scanState(SS_None)
{
    setupWidgets();

    _scanTimer.setInterval(FULL_SCAN_PERIOD);
    _scanTimer.setSingleShot(true);

    connect(&_scanTimer, SIGNAL(timeout()), SLOT(checkTouchState()));

    setScanState(SS_None);
}

MainWindow::ScanState MainWindow::scanState() const
{
    return _scanState;
}

void MainWindow::setScanState(const MainWindow::ScanState &scanState)
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

        QTimer::singleShot(RESET_SCAN_PERIOD , this, SLOT(resetTouchState()));
        break;

    case SS_Interrupted:
        setColor(Qt::red);
        emit scanInterrupted();

        QTimer::singleShot(RESET_SCAN_PERIOD , this, SLOT(resetTouchState()));
        break;

    default:
        setColor(Qt::white);
        break;
    }
}

bool MainWindow::event(QEvent *event)
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

        if (staticPointsCount > MIN_TOUCH_POINTS_COUNT - 2)
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

void MainWindow::setupWidgets()
{
//    _touchWidget = new TouchWidget;
//    setCentralWidget(_touchWidget);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
//    setWindowState(Qt::WindowFullScreen);
    setWindowTitle(tr("Hand Scanner"));

    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
}

void MainWindow::setColor(QColor color)
{
    QPalette colorScheme(palette());

    QLinearGradient linearGradient;
    linearGradient.setStart(0, 0);
    linearGradient.setFinalStop(0, 1);
    linearGradient.setColorAt(0, Qt::green);
    linearGradient.setColorAt(0.4, Qt::green);
    linearGradient.setColorAt(0.5, Qt::white);
    linearGradient.setColorAt(0.6, Qt::green);
    linearGradient.setColorAt(1, Qt::green);
    linearGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

//    colorScheme.setColor(QPalette::Background, color);
    colorScheme.setBrush(QPalette::Background, linearGradient);

    setAutoFillBackground(true);
    setPalette(colorScheme);
}

void MainWindow::checkStateForEnoughPoints()
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

void MainWindow::checkStateForNotEnoughPoints()
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

void MainWindow::resetTouchState()
{
    setScanState(SS_None);
}

void MainWindow::checkTouchState()
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
