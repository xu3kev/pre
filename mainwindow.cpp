#include<QtGui>

#include"mainwindow.h"
#include"paintarea.h"
MainWindow::MainWindow()
{
    //QWidget* widget = new QWidget;

    paintArea=new PaintArea;
    scrollArea=new QScrollArea;
    scrollArea->setWidget(paintArea);
    //scrollArea->setBackgroundRole(QPalette::Dark);
    setCentralWidget(scrollArea);
//    setCentralWidget(paintArea);

 //   QWidget* top=new QWidget;
 //   top->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
 //   QWidget* bottom=new QWidget;
 //   bottom->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


//	QVBoxLayout* layout=new QVBoxLayout;
//    QHBoxLayout* layout2=new QHBoxLayout;


    //layout->setMargin(5);
    //layout->addWidget(top);
    //layout->addWidget(paintArea);
//    layout->addWidget(colorPick);
    //layout->addWidget(bottom);
    //widget->setLayout(layout);
    //paintArea->setLayout(layout);
    createActions();
	createMenus();


    createTools();
    createColors();
    paintArea->setColorPick(colorPick);
    setWindowTitle("MENU");
    statusBar();

    resize(1000,600);
    penAct->setChecked(true);
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


    chooseAct=new QAction("choose",this);
    chooseAct->setCheckable(true);
    connect(chooseAct,SIGNAL(triggered()),this,SLOT(choose()));

    lineAct=new QAction("line",this);
    lineAct->setCheckable(true);
    connect(lineAct,SIGNAL(triggered()),this,SLOT(line()));

    getColorAct=new QAction("getColor",this);
    getColorAct->setCheckable(true);
    connect(getColorAct,SIGNAL(triggered()),this,SLOT(getColor()));


    addToolBar(Qt::LeftToolBarArea,tools);
    toolGroup->addAction(penAct);
    toolGroup->addAction(paintAct);
    toolGroup->addAction(recAct);
    toolGroup->addAction(eclAct);
    toolGroup->addAction(chooseAct);
    toolGroup->addAction(lineAct);
    toolGroup->addAction(getColorAct);
    tools->addActions(toolGroup->actions());
    QCheckBox* tmp = new QCheckBox ;
    //QPixmap* tmp4=new QPixmap(150,150);
    //tmp4->fill(QColor(0,0,0));
    //QIcon* tmp3=new QIcon(*tmp4);
    //tmp->setIcon(*tmp3);

    connect(tmp,SIGNAL(clicked(bool)),this,SLOT(check(bool)));
    QSpinBox* tmp2=new QSpinBox;
    connect(tmp2,SIGNAL(valueChanged(int)),this,SLOT(pen(int)));
    tmp2->setValue(1);
    tmp2->setMinimum(1);
    tools->addWidget(tmp);
    tools->addWidget(tmp2);

}

void MainWindow::createColors(){

    colorPick=new ColorPick(this,paintArea->getPainter());
    //colorPick->addAction("red");
//    colorPick->setBackgroundRole(QPalette::Light);
    addToolBar(Qt::LeftToolBarArea,colorPick);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

	editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addAction(resizeAct);

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

    resizeAct = new QAction("resize",this);
    connect(resizeAct,SIGNAL(triggered()),this,SLOT(resizeImage()));

    aboutAct = new QAction("About",this);
    aboutAct->setStatusTip("Show about box");
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(about()));

}
void MainWindow::newFile(){
    paintArea->newImage(QInputDialog::getInt(this,"New","width",800),
                        QInputDialog::getInt(this,"New","height",500));

}
void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath());
    if(!fileName.isEmpty()){
        paintArea->setImage(fileName);
    }
}
void MainWindow::save(){
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"),
                                                    QDir::currentPath().append("/untitle.png"));

    if(!fileName.isEmpty()){
        cerr<<"!";
        paintArea->saveImage(fileName);
    }
}
void MainWindow::copy(){
paintArea->copyImage();
}
void MainWindow::paste(){
if(paintArea->paste()){
    chooseAct->setChecked(true);
}
}
void MainWindow::cut(){
paintArea->cut();
}
void MainWindow::undo(){
    paintArea->undo();
}
void MainWindow::redo(){
    paintArea->redo();
}
void MainWindow::about(){
    QMessageBox::about(this,"About","paint");
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
    paintArea->setState(5);
}
void MainWindow::choose(){
    paintArea->setState(7);
}
void MainWindow::line(){
    paintArea->setState(10);
}
void MainWindow::getColor(){
    paintArea->setState(12);
}
void MainWindow::check(bool g){
    paintArea->setCheck(g);
    if(g){
        paintArea->getPainter()->setBrush(colorPick->getColor2());
    }
    else{
        paintArea->getPainter()->setBrush(Qt::NoBrush);
    }
}
void MainWindow::resizeImage(){
    paintArea->resizeImage(QInputDialog::getInt(this,"New","width",paintArea->getWidth()),
                           QInputDialog::getInt(this,"New","height",paintArea->getHeight()));
}
void MainWindow::pen(int x){
    cerr<<x;
    QPen tmp=paintArea->getPainter()->pen();
    tmp.setWidth(x);
    paintArea->getPainter()->setPen(tmp);
}
