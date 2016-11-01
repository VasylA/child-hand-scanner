#ifndef TOUCHWIDGET_H
#define TOUCHWIDGET_H

#include <QWidget>

class QPropertyAnimation;

class TouchWidget : public QWidget
{
    Q_OBJECT

public:
    Q_PROPERTY(qreal scanLinePos READ scanLinePos WRITE setScanLinePos)

    TouchWidget(QWidget *parent = 0);

    qreal scanLinePos() const;
    void setScanLinePos(const qreal &scanLinePos); 

private:
    qreal _scanLinePos;
    QPropertyAnimation *_scanAnimation;
};

#endif // TOUCHWIDGET_H
