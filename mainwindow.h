#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
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

	private:
		void createMenus();
        void createActions();
        void createTools();

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


};
#endif
