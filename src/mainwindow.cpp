#include "mainwindow.h"
#include "splitterm.h"

#include <QHBoxLayout>

MainWindow::MainWindow() : QMainWindow()
{
    //TODO: Transparency like in Konsole
    setAutoFillBackground(false);
    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);

    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    widget->setLayout(layout);

    SplitTerm* t = new SplitTerm(widget);
    layout->addWidget(t);
    connect(t, SIGNAL(closed()), this, SLOT(close()));
}
 
MainWindow::~MainWindow()
{
}
