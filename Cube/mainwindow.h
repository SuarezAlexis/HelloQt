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
/*
protected:
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU
*/

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

	QAction *cuboAction;
	QAction *esferaAction;
	QAction *cilindroAction;
	QAction *rojoAction;
	QAction *verdeAction;
	QAction *azulAction;
	QAction *cerrarAction;
};

#endif