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
	QDialog dialog(this);
	// Use a layout allowing to have a label next to each field
	QFormLayout form(&dialog);

	// Add some text above the fields
	form.addRow(new QLabel("Ingresa los parametros del cubo"));
	form.addRow(new QLabel(""));
	// Add the lineEdits with their respective labels
	QList<QDoubleSpinBox *> fields;
	QDoubleSpinBox *field = new QDoubleSpinBox(&dialog);
	QString label = QString("Lado ");
	form.addRow(label, field);
	fields << field;

	form.addRow(new QLabel(""));
	form.addRow(new QLabel("Posicion"));
	field = new QDoubleSpinBox(&dialog);
	label = *new QString("X ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Y ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Z ");
	form.addRow(label, field);
	fields << field;


	// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
		Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

	// Show the dialog as modal
	if (dialog.exec() == QDialog::Accepted) {
		// If the user didn't dismiss the dialog, do something with the fields
		float pos[3] = { (float)fields.value(1)->value(), (float)fields.value(2)->value(), (float)fields.value(3)->value() };
		emit cuboRequest((float)fields.value(0)->value(), pos);
	}
}

void MainWindow::Esfera()
{
	QDialog dialog(this);
	QFormLayout form(&dialog);

	form.addRow(new QLabel("Ingresa los parametros de la esfera"));
	form.addRow(new QLabel(""));

	QList<QDoubleSpinBox *> fields;
	QDoubleSpinBox *field = new QDoubleSpinBox(&dialog);
	QString label = QString("Radio ");
	form.addRow(label, field);
	fields << field;
	
	form.addRow(new QLabel(""));
	form.addRow(new QLabel("Posicion"));
	field = new QDoubleSpinBox(&dialog);
	label = *new QString("X ");
	form.addRow(label, field);
	fields << field;
	
	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Y ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Z ");
	form.addRow(label, field);
	fields << field;

	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,	Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

	if (dialog.exec() == QDialog::Accepted) {
		float pos[3] = { (float)fields.value(1)->value(), (float)fields.value(2)->value(), (float)fields.value(3)->value() };
		emit esferaRequest((float)fields.value(0)->value(), pos);
	}
}

void MainWindow::Cilindro()
{
	QDialog dialog(this);
	QFormLayout form(&dialog);

	form.addRow(new QLabel("Ingresa los parametros del cilindro"));
	form.addRow(new QLabel(""));

	QList<QDoubleSpinBox *> fields;
	QDoubleSpinBox *field = new QDoubleSpinBox(&dialog);
	QString label = QString("Altura ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Radio ");
	form.addRow(label, field);
	fields << field;

	form.addRow(new QLabel(""));
	form.addRow(new QLabel("Posicion"));
	field = new QDoubleSpinBox(&dialog);
	label = *new QString("X ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Y ");
	form.addRow(label, field);
	fields << field;

	field = new QDoubleSpinBox(&dialog);
	label = *new QString("Z ");
	form.addRow(label, field);
	fields << field;

	QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
	form.addRow(&buttonBox);
	QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
	QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

	if (dialog.exec() == QDialog::Accepted) {
		float pos[3] = { (float)fields.value(2)->value(), (float)fields.value(3)->value(), (float)fields.value(4)->value() };
		emit cilindroRequest((float)fields.value(0)->value(), (float)fields.value(1)->value(), pos);
	}
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