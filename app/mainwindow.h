#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class TouchWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    TouchWidget *scribbleArea;
};

#endif // MAINWINDOW_H
