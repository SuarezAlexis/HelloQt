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
	
	connect(mw, SIGNAL(cuboRequest()), glWidget, SLOT(cuboResponse()));
	connect(mw, SIGNAL(esferaRequest()), glWidget, SLOT(esferaResponse()));
	connect(mw, SIGNAL(cilindroRequest()), glWidget, SLOT(cilindroResponse()));
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