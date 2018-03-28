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
	QAction *cuboAction;
	QAction *esferaAction;
	QAction *cilindroAction;
	QAction *rojoAction;
	QAction *verdeAction;
	QAction *azulAction;
	QAction *cerrarAction;

signals:
	void cuboRequest(float size, float *pos);
	void esferaRequest(float radius, float *pos);
	void cilindroRequest(float height, float radius, float *pos);
	void rojoRequest();
	void verdeRequest();
	void azulRequest();

private slots:
	void Cubo();
	void Esfera();
	void Cilindro();
	void Rojo();
	void Verde();
	void Azul();
	void Cerrar();

private:
	void createActions();
	void createMenus();

	QMenu *objetoMenu;
	QMenu *colorMenu;
	QMenu *dimrvMenu;


};

#endif