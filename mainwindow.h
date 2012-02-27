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

	private:
		void createMenus();
        void createActions();
		QMenu* fileMenu;
		QMenu* editMenu;
		QMenu* helpMenu;
		QAction* newAct;
		QAction* openAct;
		QAction* saveAct;
};
#endif
