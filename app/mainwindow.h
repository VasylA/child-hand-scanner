#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class StartWidget;
class ScanWidget;
class AccessGrantedWidget;
class AccessDeniedWidget;

class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum ScanState
    {
        SS_None = 0,
        SS_Started,
        SS_Finished,
        SS_Interrupted
    };

public:
    MainWindow(QWidget *parent = 0);

    ScanState scanState() const;
    void setScanState(const ScanState &scanState);


protected:
    bool event(QEvent *event) override;


private:
    void initTimer();
//    void initSoundPlayer();
//    void initTestpointsController();

    void setupWidgets();
    void setupGameFrames();

private slots:
    // Game State slots
    void setInitialAppState();
    void reactOnTouchIfEnoughPoints();
    void reactOnTouchIfNotEnoughPoints();
    void checkScanStateOInTimeOut();

private:
    static const int MIN_TOUCH_POINTS_COUNT = 2;
    static const int RESET_SCAN_PERIOD = 5000;
    static const int FULL_SCAN_PERIOD = 8000;

    ScanState _scanState;
    QTimer _scanTimer;

    ScanWidget         *_scanFrame;
    StartWidget       *_startFrame;
    AccessDeniedWidget *_loseFrame;
    AccessGrantedWidget *_winFrame;
    QStackedWidget *_stackedWidget;

};

#endif // MAINWINDOW_H
