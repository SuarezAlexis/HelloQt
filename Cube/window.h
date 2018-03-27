#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QSlider;
class QPushButton;

class MainWidget;
class MainWindow;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(MainWindow *mw);

private:
	MainWidget *glWidget;
	MainWindow *mainWindow;
};

#endif
