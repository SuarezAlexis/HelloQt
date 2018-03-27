#include "openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QKeyEvent>
#include <QtCore/qmath.h>

//Clase TriangleWindow es la ventana OpenGL
class TriangleWindow : public OpenGLWindow
{
public:
	TriangleWindow(); //Constructor de la clase

	void initialize() override;	//M�todos para inicializar y renderizar ventana,
	void render() override;		// heredados de supercalsse. Se implementan m�s abajo.
	void keyPressEvent(QKeyEvent* ev) override;

private:
	GLuint m_posAttr;		// Variables que usar�n los programas de shader
	GLuint m_colAttr;		// guardan la ubicaci�n de los atributos
	GLuint m_matrixUniform;	// color y posici�n.

	QOpenGLShaderProgram *m_program; //Variable que apunta al programa shader
	int m_frame; //Contador de frames para regular animaci�n del tri�ngulo
	int rotating; //Bandera que define si el objeto rota o no
	float red, green, blue;
	float camara;
};

TriangleWindow::TriangleWindow()
	: m_program(0)
	, m_frame(0)
	, rotating(0)
	, red(1)
	, green(0)
	, blue(0)
	, camara(0)
{
}

int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv); //inicializar aplicaci�n

	QSurfaceFormat format; // Formato para definir antialiasing multi-muestra
	format.setSamples(16); // de 4 muestras

	TriangleWindow window; //Instancia de la ventana OpenGL
	window.setFormat(format);
	window.resize(640, 480);
	window.show();

	window.setAnimating(true); //Se habilita animaci�n

	return app.exec();
}

//Programas shader, son constantes globales tipo cadena
static const char *vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"attribute lowp vec4 colAttr;\n"
"varying lowp vec4 col;\n"
"uniform highp mat4 matrix;\n"
"void main() {\n"
"   col = colAttr;\n"
"   gl_Position = matrix * posAttr;\n"
"}\n";

static const char *fragmentShaderSource =
"varying lowp vec4 col;\n"
"void main() {\n"
"   gl_FragColor = col;\n"
"}\n";

void TriangleWindow::initialize() //Implementaci�n del m�todo heredado de OpenGLWindow
{ //Carga los programas de shader y guarda la ubicaci�n de los atributos posici�n y color y de la matriz uniforme
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	m_program->link();
	m_posAttr = m_program->attributeLocation("posAttr");
	m_colAttr = m_program->attributeLocation("colAttr");
	m_matrixUniform = m_program->uniformLocation("matrix");
}

void TriangleWindow::render() //Implementaci�n del m�todo heredado de OpenGLWindow.
{ //Aqu� se hace el renderizado, es donde se ocupa OpenGL.
	const qreal retinaScale = devicePixelRatio(); //Se obtiene la relaci�n entre 
												  //las coordenadas utiles est�ndar y 
												  //los pixeles reales de la pantalla.
	glViewport(0, 0, width() * retinaScale, height() * retinaScale); //Se establece el viewport.

	glClear(GL_COLOR_BUFFER_BIT); //Se limpia el color de fondo.

	m_program->bind(); // Se ligan los programas de shader.

	QMatrix4x4 matrix;
	matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f); //Matriz de perspectiva.
	matrix.translate(0, 0, -2 + camara); // Se aplica traslaci�n
	matrix.rotate( 100.0f * m_frame / screen()->refreshRate(), 0, 1, 0); //Se aplica rotaci�n variable (eje y)
																		//en funci�n de la tasa de refresco
																		//de la pantalla.
	//Se asigna valor uniforme obtenido en el shader de vertices.
	m_program->setUniformValue(m_matrixUniform, matrix);

	//Los tres v�rtices del tri�ngulo.
	GLfloat vertices[] = {
		0.5f,0.5f,-0.5,
		-0.5f, 0.5f,-0.5,
		-0.5f, -0.5f,-0.5,
		0.5f, -0.5f, -0.5,
		0.5f,0.5f, 0.5,
		-0.5f, 0.5f, 0.5,
		-0.5f, -0.5f, 0.5,
		0.5f, -0.5f, 0.5,
		0.5f,-0.5f, -0.5,
		0.5f, -0.5f, 0.5,
		-0.5f, -0.5f, 0.5,
		-0.5f, -0.5f, -0.5,
		0.5f,0.5f, -0.5,
		0.5f, 0.5f, 0.5,
		-0.5f, 0.5f, 0.5,
		-0.5f, 0.5f, -0.5
	};

	//Los colores para cada v�rtice.
	GLfloat colors[] = {
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue
	};

	// Especifica qu� atributo del v�rtice se modificar� (en este caso la posici�n y abajo el color),
	// el n�mero de componentes por atributo, el tipo de dato de cada elemento del arreglo,
	// si se deben o no normalizar los datos de punto fijo,
	// el espacio en bytes entre el inicio de cada atributo de v�rtice consecutivo (0 significa que son contiguos),
	// y el apuntador al arreglo de datos.
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

	glEnableVertexAttribArray(0); //Habilita los arreglos de atributos de v�rtice 0 y 1
	glEnableVertexAttribArray(1); //para el color y la posici�n.

	glDrawArrays(GL_QUADS, 0, 16); //Dibuja los arreglos de atributos de v�rtice habilitados 
								  //desde el indice 0, una determinada cantidad de elementos (8 en este caso).

	glDisableVertexAttribArray(1); //Deshabilita los arreglos de atrbutos de v�rtice.
	glDisableVertexAttribArray(0);

	m_program->release(); //Libera los programas de shader.
	
	m_frame += rotating; //Se incrementa el contador que controla el giro del tri�ngulo.
}

void TriangleWindow::keyPressEvent(QKeyEvent* ev)
{
	switch (ev->key())
	{
		case Qt::Key_Left:
			rotating--;
			return;
		case Qt::Key_Right:
			rotating++;
			return;
		case Qt::Key_F3:
			camara += 0.5f;
			return;
		case Qt::Key_F2:
			camara -= 0.5f;
			return;
		case Qt::Key_R:
			if (ev->modifiers() && Qt::ShiftModifier && red >= 0)
				red -= 0.1;
			else
				if (red <= 1)
					red += 0.1;
			return;
		case Qt::Key_G:
			if (ev->modifiers() && Qt::ShiftModifier && green >= 0)
				green -= 0.1;
			else
				if (green <= 1)
					green += 0.1;
			return;
		case Qt::Key_B:
			if (ev->modifiers() && Qt::ShiftModifier && blue >= 0)
				blue -= 0.1;
			else
				if (blue <= 1)
					blue += 0.1;
			return;
	}
}