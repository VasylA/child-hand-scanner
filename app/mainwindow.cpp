#include "mainwindow.h"
#include "scanwidget.h"
#include "startwidget.h"
#include "accessdeniedwidget.h"
#include "accessgrantedwidget.h"

#include <QColor>
#include <QScreen>
#include <QPalette>
#include <QBoxLayout>
#include <QTouchEvent>
#include <QApplication>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _scanState(SS_None),
    _scanFrame(nullptr),
    _startFrame(nullptr),
    _loseFrame(nullptr),
    _winFrame(nullptr),
    _stackedWidget(nullptr)
{
    setupWidgets();

    initTimer();

    setInitialAppState();
}

MainWindow::ScanState MainWindow::scanState() const
{
    return _scanState;
}

void MainWindow::setScanState(const MainWindow::ScanState &scanState)
{
    _scanState = scanState;
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
            reactOnTouchIfEnoughPoints();
        else
            reactOnTouchIfNotEnoughPoints();
    }
        break;


    case QEvent::MouseButtonPress:
        reactOnTouchIfEnoughPoints();
        break;

    case QEvent::MouseButtonRelease:
        reactOnTouchIfNotEnoughPoints();
        break;

    default:
        return QWidget::event(event);
    }
    return true;
}

void MainWindow::initTimer()
{
    _scanTimer.setInterval(FULL_SCAN_PERIOD);
    _scanTimer.setSingleShot(true);

    connect(&_scanTimer, SIGNAL(timeout()), this, SLOT(checkScanStateOInTimeOut()));
}

void MainWindow::setupWidgets()
{
    setupGameFrames();

    _stackedWidget = new QStackedWidget;
    _stackedWidget->addWidget(_startFrame);
    _stackedWidget->addWidget(_scanFrame);
    _stackedWidget->addWidget(_loseFrame);
    _stackedWidget->addWidget(_winFrame);

    setCentralWidget(_stackedWidget);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
//    setWindowState(Qt::WindowFullScreen);
    setWindowTitle(tr("Hand Scanner"));

    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
}

void MainWindow::setupGameFrames()
{
    QSizeF availableScreenSize = size();//qApp->primaryScreen()->availableSize();

    const int TEXT_PIXEL_SIZE = availableScreenSize.height() / 5;

    _startFrame = new StartWidget;
    _startFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _startFrame->setTextSize(TEXT_PIXEL_SIZE);

    _scanFrame = new ScanWidget;
    _scanFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _scanFrame->setFullScanPeriod(FULL_SCAN_PERIOD);

    _winFrame = new AccessGrantedWidget;
    _winFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _winFrame->setTextSize(TEXT_PIXEL_SIZE);

    _loseFrame = new AccessDeniedWidget;
    _loseFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _loseFrame->setTextSize(TEXT_PIXEL_SIZE);
}

void MainWindow::setInitialAppState()
{
    if (_scanState == SS_None)
        return;

    if (_scanTimer.isActive())
        _scanTimer.stop();

    _scanState = SS_None;

    if (_stackedWidget->currentWidget() != _startFrame)
        _stackedWidget->setCurrentWidget(_startFrame);
}

void MainWindow::reactOnTouchIfEnoughPoints()
{
    if (_scanState != SS_None)
        return;

    if (_scanTimer.isActive())
        _scanTimer.stop();

    _scanState = SS_Started;

    if (_stackedWidget->currentWidget() != _scanFrame)
        _stackedWidget->setCurrentWidget(_scanFrame);

    _scanTimer.start(FULL_SCAN_PERIOD);
    _scanFrame->startScanAnimation();
}

void MainWindow::reactOnTouchIfNotEnoughPoints()
{
    if (_scanState != SS_Started)
        return;

    _scanFrame->stopScanAnimation();
    if (_scanTimer.isActive())
        _scanTimer.stop();

    _scanState = SS_Interrupted;

    _stackedWidget->setCurrentWidget(_loseFrame);

    QTimer::singleShot(RESET_SCAN_PERIOD, this, SLOT(setInitialAppState()));
}

void MainWindow::checkScanStateOInTimeOut()
{
    if (_scanState != SS_Started)
        return;

    _scanFrame->stopScanAnimation();
    if (_scanTimer.isActive())
        _scanTimer.stop();

    _scanState = SS_Finished;

    _stackedWidget->setCurrentWidget(_winFrame);

    QTimer::singleShot(RESET_SCAN_PERIOD, this, SLOT(setInitialAppState()));
}
