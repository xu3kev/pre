#include<QtGui>

#include"mainwindow.h"
#include"paintarea.h"
MainWindow::MainWindow()
{
    //QWidget* widget = new QWidget;
    paintArea=new PaintArea;
    setCentralWidget(paintArea);

    //QWidget* top=new QWidget;
    //top->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //QWidget* bottom=new QWidget;
    //bottom->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    /*
	QVBoxLayout* layout=new QVBoxLayout;
	layout->setMargin(5);
    layout->addWidget(top);
    layout->addWidget(paintArea);
	layout->addWidget(bottom);
    widget->setLayout(layout);
    */
    createActions();
	createMenus();

    createTools();

    setWindowTitle("MENU");
    statusBar();

    resize(1000,600);
}
void MainWindow::createTools(){

    tools=new QToolBar("toolbar");

    toolGroup=new QActionGroup(this);
    toolGroup->setExclusive(true);

    penAct=new QAction("Pen",this);
    penAct->setCheckable(true);
    connect(penAct,SIGNAL(triggered()),this,SLOT(pen()));

    paintAct=new QAction("Paint",this);
    paintAct->setCheckable(true);
    connect(paintAct,SIGNAL(triggered()),this,SLOT(paint()));

    recAct=new QAction("rec",this);
    recAct->setCheckable(true);
    connect(recAct,SIGNAL(triggered()),this,SLOT(rec()));

    eclAct=new QAction("ecl",this);
    eclAct->setCheckable(true);
    connect(eclAct,SIGNAL(triggered()),this,SLOT(ecl()));

    addToolBar(tools);
    toolGroup->addAction(penAct);
    toolGroup->addAction(paintAct);
    toolGroup->addAction(recAct);
    toolGroup->addAction(eclAct);
    tools->addActions(toolGroup->actions());

}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

	editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(copyAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(aboutAct);
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

    copyAct = new QAction("Copy",this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setStatusTip("Copy");//TODO
    connect(copyAct,SIGNAL(triggered()),this,SLOT(copy()));

    pasteAct = new QAction("Paste",this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setStatusTip("Paste");//TODO
    connect(pasteAct,SIGNAL(triggered()),this,SLOT(paste()));

    cutAct = new QAction("Cut",this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setStatusTip("Cut");//TODO
    connect(cutAct,SIGNAL(triggered()),this,SLOT(cut()));

    undoAct = new QAction("Undo",this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setStatusTip("Undo");
    connect(undoAct,SIGNAL(triggered()),this,SLOT(undo()));

    redoAct = new QAction("Redo",this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setStatusTip("Redo");
    connect(redoAct,SIGNAL(triggered()),this,SLOT(redo()));

    aboutAct = new QAction("About",this);
    aboutAct->setStatusTip("Show about box");
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

}
void MainWindow::newFile(){

}
void MainWindow::open(){

}
void MainWindow::save(){


}
void MainWindow::copy(){

}
void MainWindow::paste(){

}
void MainWindow::cut(){

}
void MainWindow::undo(){

}
void MainWindow::redo(){

}
void MainWindow::about(){

}
void MainWindow::pen(){
    paintArea->setState(0);
}
void MainWindow::rec(){
    paintArea->setState(3);
}
void MainWindow::paint(){
    paintArea->setState(2);
}
void MainWindow::ecl(){
    paintArea->setState(4);
}
