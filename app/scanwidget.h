#ifndef SCANWIDGET_H
#define SCANWIDGET_H

#include <QWidget>

class QPropertyAnimation;

class ScanWidget : public QWidget
{
    Q_OBJECT

public:
    Q_PROPERTY(qreal scanLinePos READ scanLinePos WRITE setScanLinePos)

    explicit ScanWidget(QWidget *parent = 0);

    void startScanAnimation();

    qreal scanLinePos() const;
    void setScanLinePos(const qreal &scanLinePos); 

private:
    qreal _scanLinePos;
    QPropertyAnimation *_scanAnimation;
};

#endif // SCANWIDGET_H