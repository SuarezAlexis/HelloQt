#include <QtWidgets>
#include <QMessageBox>

#include "mainwindow.h"
#include "window.h"

MainWindow::MainWindow()
{
	setCentralWidget(new Window(this));

	QVBoxLayout *layout = new QVBoxLayout;
	layout->setMargin(1);

	createActions();
	createMenus();

	setWindowTitle(tr("Practica 1  [DIMyRV]"));
	setMinimumSize(160, 160);
	resize(800, 600);
}

void MainWindow::Cerrar()
{
	QMessageBox::information(0, tr("Mensaje"), tr("Este programa dice:\n\"return EXIT_SUCCESS;\""));
	QApplication::quit();
}

void MainWindow::createActions()
{
	cuboAction = new QAction(tr("&Cubo"), this);
	cuboAction->setShortcut(QKeySequence::Cut);
	cuboAction->setStatusTip(tr("Crear un nuevo cubo"));
	connect(cuboAction, &QAction::triggered, this, &MainWindow::Cubo);

	esferaAction = new QAction(tr("&Esfera"), this);
	//esferaAction->setShortcut(QKeySequence::New);
	esferaAction->setStatusTip(tr("Crear un nueva esfera"));
	connect(esferaAction, &QAction::triggered, this, &MainWindow::Esfera);

	cilindroAction = new QAction(tr("&Cilindro"), this);
	//cilindroAction->setShortcut(QKeySequence::New);
	cilindroAction->setStatusTip(tr("Crear un nuevo cilindro"));
	connect(cilindroAction, &QAction::triggered, this, &MainWindow::Cilindro);

	rojoAction = new QAction(tr("&Rojo"), this);
	//rojoAction->setShortcut(QKeySequence::New);
	rojoAction->setStatusTip(tr("Hace todos los objetos color rojo"));
	connect(rojoAction, &QAction::triggered, this, &MainWindow::Rojo);

	verdeAction = new QAction(tr("&Verde"), this);
	//verdeAction->setShortcut(QKeySequence::New);
	verdeAction->setStatusTip(tr("Hace todos los objetos color verde"));
	connect(verdeAction, &QAction::triggered, this, &MainWindow::Verde);

	azulAction = new QAction(tr("&Azul"), this);
	//azulAction->setShortcut(QKeySequence::New);
	azulAction->setStatusTip(tr("Hace todos los objetos color azul"));
	connect(azulAction, &QAction::triggered, this, &MainWindow::Azul);

	cerrarAction = new QAction(tr("&Cerrar programa"), this);
	//cerrarAction->setShortcut(QKeySequence::New);
	cerrarAction->setStatusTip(tr("Cierra el programa :)"));
	connect(cerrarAction, &QAction::triggered, this, &MainWindow::Cerrar);
}

void MainWindow::createMenus()
{
	dimrvMenu = menuBar()->addMenu(tr("&Programa"));
	dimrvMenu->addAction(cerrarAction);

	objetoMenu = menuBar()->addMenu(tr("&Objetos"));
	objetoMenu->addAction(cuboAction);
	objetoMenu->addAction(esferaAction);
	objetoMenu->addAction(cilindroAction);

	colorMenu = menuBar()->addMenu(tr("&Colores"));
	colorMenu->addAction(rojoAction);
	colorMenu->addAction(verdeAction);
	colorMenu->addAction(azulAction);	
}


void MainWindow::Cubo()
{
	emit cuboRequest();
}

void MainWindow::Esfera()
{
	emit esferaRequest();
}

void MainWindow::Cilindro()
{
	emit cilindroRequest();
}

void MainWindow::Rojo()
{
	emit rojoRequest();
}

void MainWindow::Verde()
{
	emit verdeRequest();
}

void MainWindow::Azul()
{
	emit azulRequest();
}