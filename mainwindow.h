#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <colorpick.h>

class ColorPick;
class QColorDialog;
class PaintArea;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QScrollArea;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow();
    private slots:
        void newFile();
        void open();
        void save();
        void copy();
        void paste();
        void cut();
        void undo();
        void redo();
        void about();
        void pen();
        void rec();
        void paint();
        void ecl();
        void choose();
        void line();
        void getColor();

	private:
		void createMenus();
        void createActions();
        void createTools();
        void createColors();

        PaintArea* paintArea;
        QScrollArea* scrollArea;

        //QColorDialog* colorPick;
        //QToolBar* colorPick;
        ColorPick* colorPick;
		QMenu* fileMenu;
		QMenu* editMenu;
		QMenu* helpMenu;
		QAction* newAct;
		QAction* openAct;
		QAction* saveAct;
        QAction* copyAct;
        QAction* pasteAct;
        QAction* cutAct;
        QAction* redoAct;
        QAction* undoAct;
        QAction* aboutAct;


        QToolBar* tools;
        QActionGroup* toolGroup;
        QAction* penAct;
        QAction* paintAct;
        QAction* recAct;
        QAction* eclAct;
        QAction* chooseAct;
        QAction* lineAct;
        QAction* getColorAct;

};
#endif
