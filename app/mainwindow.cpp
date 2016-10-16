#include "mainwindow.h"
#include "touchwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _touchWidget = new TouchWidget;
    setCentralWidget(_touchWidget);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowState(Qt::WindowFullScreen);
    setWindowTitle(tr("Hand Scanner"));
}
