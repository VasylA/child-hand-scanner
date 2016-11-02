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

    qreal scanLinePos() const;
    void setScanLinePos(const qreal &scanLinePos); 

    QColor baseColor() const;
    void setBaseColor(const QColor &baseColor);

    int fullScanPeriod() const;
    void setFullScanPeriod(int fullScanPeriod);

public slots:
    void startScanAnimation();
    void stopScanAnimation();


private:
    void updateUi();

private:
    int _fullScanPeriod;
    qreal _scanLinePos;
    QColor _baseColor;
    QPropertyAnimation *_scanAnimation;
};

#endif // SCANWIDGET_H
