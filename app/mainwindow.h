#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class TouchWidget;

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

signals:
    void scanStarted();
    void scanFinished();
    void scanInterrupted();


protected:
    bool event(QEvent *event) override;


private:
    void setupWidgets();
    void setColor(QColor color);
    void checkStateForEnoughPoints();
    void checkStateForNotEnoughPoints();

private slots:
    void resetTouchState();
    void checkTouchState();

private:
    static const int MIN_TOUCH_POINTS_COUNT = 2;
    static const int RESET_SCAN_PERIOD = 5000;
    static const int FULL_SCAN_PERIOD = 8000;

    ScanState _scanState;
    QTimer _scanTimer;

    TouchWidget *_touchWidget;
};

#endif // MAINWINDOW_H
