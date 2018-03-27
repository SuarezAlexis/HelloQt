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
	/*
	connect(xSlider , &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
	connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
	connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
	connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
	connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
	connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);
	*/
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *container = new QHBoxLayout;
	container->addWidget(glWidget);

	QWidget *w = new QWidget;
	w->setLayout(container);
	mainLayout->addWidget(w);

	setLayout(mainLayout);

	setWindowTitle(tr("Hello GL"));
}