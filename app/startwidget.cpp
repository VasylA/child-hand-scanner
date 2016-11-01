#include "startwidget.h"

#include <QLabel>
#include <QLayout>
#include <QPalette>
#include <QRadialGradient>
#include <QPropertyAnimation>

const QString StartWidget::labelText = "Пройти рівень";

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent),
      _accessLabel(new QLabel),
      _backgroundAnimation(new QPropertyAnimation(this, "COLOR")),
      _colorChannel(150),
      _textSize(120)
{
    initUi();

    connect(_backgroundAnimation, SIGNAL(finished()), SLOT(runAnimation()));
    runAnimation();
}

void StartWidget::initUi()
{
    _accessLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _accessLabel->setAlignment(Qt::AlignCenter);
    _accessLabel->setWordWrap(true);

    QLayout *centralLayout = new QHBoxLayout;
    centralLayout->addWidget(_accessLabel);
    setLayout(centralLayout);

    updateUi();
}

void StartWidget::runAnimation()
{
    if(_backgroundAnimation->state() == QAbstractAnimation::Running)
    {
        _backgroundAnimation->stop();
        return;
    }

    _backgroundAnimation->setStartValue(100);
    _backgroundAnimation->setDuration(2000);
    _backgroundAnimation->setEndValue(250);

    QAbstractAnimation::Direction newDirection = (_backgroundAnimation->direction() == QAbstractAnimation::Forward) ? QAbstractAnimation::Backward
                                                                                                                    : QAbstractAnimation::Forward;
    _backgroundAnimation->setDirection(newDirection);

    _backgroundAnimation->start();
}

int StartWidget::textSize() const
{
    return _textSize;
}

void StartWidget::setTextSize(int textSize)
{
    _textSize = textSize;

    updateLabel();
}

void StartWidget::updateUi()
{
    QPoint widgetCenter(width() / 2, height() / 2);

    QRadialGradient bgGradient;
    bgGradient.setColorAt(1, QColor(0, 20,_colorChannel, 255));
    bgGradient.setColorAt(0, QColor(180, 180, 180, 255));
    bgGradient.setRadius(width() / 2.0);
    bgGradient.setCenter(widgetCenter);
    bgGradient.setFocalPoint(widgetCenter);

    QColor textColor = QColor(0, 20, 255 - _colorChannel, 255);

    QPalette colorScheme(palette());
    colorScheme.setBrush(QPalette::Background, bgGradient);
    colorScheme.setBrush(QPalette::WindowText, textColor);

    setAutoFillBackground(true);
    setPalette(colorScheme);

    _accessLabel->setAutoFillBackground(true);
    _accessLabel->setPalette(colorScheme);

    updateLabel();
}

void StartWidget::updateLabel()
{
    QString htmlText = QString("<p style='font-size:%0px; font-family:verdana'><b>%1</b></p>")
            .arg(_textSize)
            .arg(labelText);

    _accessLabel->setText(htmlText);
}

int StartWidget::colorChannel() const
{
    return _colorChannel;
}

void StartWidget::setColorChannel(int colorChannel)
{
    _colorChannel = colorChannel;

    updateUi();
}
