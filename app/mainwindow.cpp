#include <QtGui>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "touchwidget.h"

MainWindow::MainWindow()
{
    scribbleArea = new TouchWidget;
    setCentralWidget(scribbleArea);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setWindowState(Qt::WindowFullScreen);
    setWindowTitle(tr("Hand Scanner"));
}
