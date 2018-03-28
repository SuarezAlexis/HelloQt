#include "mainwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

Window::Window(MainWindow *mw)
	: mainWindow(mw)
{
	glWidget = new MainWidget;
	
	connect(mw, SIGNAL(cuboRequest(float, float*)), glWidget, SLOT(cuboResponse(float, float*)));
	connect(mw, SIGNAL(esferaRequest(float, float*)), glWidget, SLOT(esferaResponse(float, float*)));
	connect(mw, SIGNAL(cilindroRequest(float, float, float*)), glWidget, SLOT(cilindroResponse(float, float, float*)));
	connect(mw, SIGNAL(rojoRequest()), glWidget, SLOT(rojoResponse()));
	connect(mw, SIGNAL(verdeRequest()), glWidget, SLOT(verdeResponse()));
	connect(mw, SIGNAL(azulRequest()), glWidget, SLOT(azulResponse()));

	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *container = new QHBoxLayout;
	container->addWidget(glWidget);

	QWidget *w = new QWidget;
	w->setLayout(container);
	mainLayout->addWidget(w);

	setLayout(mainLayout);

	setWindowTitle(tr("Hello GL"));
}