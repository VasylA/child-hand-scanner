#ifndef TOUCHWIDGET_H
#define TOUCHWIDGET_H

#include <QWidget>
#include <QTimer>

class TouchWidget : public QWidget
{
    Q_OBJECT

public:
    enum ScanState
    {
        SS_None = 0,
        SS_Started,
        SS_Finished,
        SS_Interrupted
    };

    TouchWidget(QWidget *parent = 0);

    ScanState scanState() const;
    void setScanState(const ScanState &scanState);

signals:
    void scanStarted();
    void scanFinished();
    void scanInterrupted();

protected:
    bool event(QEvent *event) override;

private:
    void setColor(QColor color);
    void checkStateForEnoughPoints();
    void checkStateForNotEnoughPoints();

private slots:
    void resetTouchState();
    void checkTouchState();

private:
    static const int FULL_SCAN_PERIOD = 8000;

    ScanState _scanState;

    QTimer _scanTimer;
};

#endif // TOUCHWIDGET_H
