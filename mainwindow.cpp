#include<QtGui>

#include"mainwindow.h"
MainWindow::MainWindow()
{
    QWidget* widget = new QWidget;
	setCentralWidget(widget);

	QWidget* top=new QWidget;
	top->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	QWidget* bottom=new QWidget;
	bottom->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	QVBoxLayout* layout=new QVBoxLayout;
	layout->setMargin(5);
    layout->addWidget(top);
	layout->addWidget(bottom);
	widget->setLayout(layout);

    createActions();
	createMenus();

    setWindowTitle("MENU");
    statusBar();

	resize(480,320);
}
void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

	editMenu = menuBar()->addMenu("Edit");
	helpMenu = menuBar()->addMenu("help");
}
void MainWindow::createActions()
{
    newAct= new QAction("New",this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip("Create a new file");
    connect(newAct,SIGNAL(triggered()),this,SLOT(newFile()));

    openAct= new QAction("Open",this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip("Open an existing file");
    connect(openAct,SIGNAL(triggered()),this,SLOT(open()));

    saveAct= new QAction("Save",this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip("Save to the disk");
    connect(saveAct,SIGNAL(triggered()),this,SLOT(save()));

}
void MainWindow::newFile(){

}
void MainWindow::open(){

}
void MainWindow::save(){


}
