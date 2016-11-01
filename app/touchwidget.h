#ifndef TOUCHWIDGET_H
#define TOUCHWIDGET_H

#include <QWidget>
#include <QTimer>

class QPropertyAnimation;

class TouchWidget : public QWidget
{
    Q_OBJECT

public:
    Q_PROPERTY(qreal scanLinePos READ scanLinePos WRITE setScanLinePos)

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

    qreal scanLinePos() const;
    void setScanLinePos(const qreal &scanLinePos);

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
    QColor colorForState(const ScanState &scanState);

private slots:
    void resetTouchState();
    void checkTouchState();

private:
    static const int MIN_TOUCH_POINTS_COUNT = 2;
    static const int RESET_SCAN_PERIOD = 5000;
    static const int FULL_SCAN_PERIOD = 8000;

    ScanState _scanState;

    QTimer _scanTimer;
    qreal _scanLinePos;
    QPropertyAnimation *_scanAnimation;
};

#endif // TOUCHWIDGET_H
