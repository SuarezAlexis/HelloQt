/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "openglwindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include <QtCore/qmath.h>

//Clase TriangleWindow es la ventana OpenGL
class TriangleWindow : public OpenGLWindow
{
public:
	TriangleWindow(); //Constructor de la clase

	void initialize() override;	//Métodos para inicializar y renderizar ventana,
	void render() override;		// heredados de superclase. Se implementan más abajo.

private:
	GLuint m_posAttr;		// Variables que usarán los programas de shader
	GLuint m_colAttr;		// guardan la ubicación de los atributos
	GLuint m_matrixUniform;	// color y posición.

	QOpenGLShaderProgram *m_program; //Variable que apunta al programa shader
	int m_frame; //Contador de frames para regular animación del triángulo
};

TriangleWindow::TriangleWindow() 
	: m_program(0)
	, m_frame(0)
{
}

int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv); //inicializar aplicación

	QSurfaceFormat format; // Formato para definir antialiasing multi-muestra
	format.setSamples(16); // de 4 muestras

	TriangleWindow window; //Instancia de la ventana OpenGL
	window.setFormat(format); 
	window.resize(640, 480);
	window.show();

	window.setAnimating(true); //Se habilita animación

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

void TriangleWindow::initialize() //Implementación del método heredado de OpenGLWindow
{ //Carga los programas de shader y guarda la ubicación de los atributos posición y color y de la matriz uniforme
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	m_program->link();
	m_posAttr = m_program->attributeLocation("posAttr");
	m_colAttr = m_program->attributeLocation("colAttr");
	m_matrixUniform = m_program->uniformLocation("matrix");
}

void TriangleWindow::render() //Implementación del método heredado de OpenGLWindow.
{ //Aquí se hace el renderizado, es donde se ocupa OpenGL.
	const qreal retinaScale = devicePixelRatio(); //Se obtiene la relación entre 
												  //las coordenadas utiles estándar y 
												  //los pixeles reales de la pantalla.
	glViewport(0, 0, width() * retinaScale, height() * retinaScale); //Se establece el viewport.

	glClear(GL_COLOR_BUFFER_BIT); //Se limpia el color de fondo.

	m_program->bind(); // Se ligan los programas de shader.

	QMatrix4x4 matrix;
	matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f); //Matriz de perspectiva.
	matrix.translate(0, 0, -2); // Se aplica traslación
	matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0); //Se aplica rotación variable (eje y)
																		//en función de la tasa de refresco
																		//de la pantalla.
	//Se asigna valor uniforme obtenido en el shader de vertices.
	m_program->setUniformValue(m_matrixUniform, matrix); 

	//Los tres vértices del triángulo.
	GLfloat vertices[] = {
		0.5f,0.5f,-0.5,
		-0.5f, 0.5f,-0.5,
		-0.5f, -0.5f,-0.5,
		0.5f, -0.5f,-0.5,
		0.5f,0.5f,0.5,
		-0.5f, 0.5f,0.5,
		-0.5f, -0.5f,0.5,
		0.5f, -0.5f, 0.5,
	};

	//Los colores para cada vértice.
	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	// Especifica qué atributo del vértice se modificará (en este caso la posición y abajo el color),
	// el número de componentes por atributo, el tipo de dato de cada elemento del arreglo,
	// si se deben o no normalizar los datos de punto fijo,
	// el espacio en bytes entre el inicio de cada atributo de vértice consecutivo (0 significa que son contiguos),
	// y el apuntador al arreglo de datos.
	glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

	glEnableVertexAttribArray(0); //Habilita los arreglos de atributos de vértice 0 y 1
	glEnableVertexAttribArray(1); //para el color y la posición.

	glDrawArrays(GL_QUADS, 0, 8); //Dibuja los arreglos de atributos de vértice habilitados 
									  //desde el indice 0, una determinada cantidad de elementos (8 en este caso).

	glDisableVertexAttribArray(1); //Deshabilita los arreglos de atrbutos de vértice.
	glDisableVertexAttribArray(0);

	m_program->release(); //Libera los programas de shader.

	++m_frame; //Se incrementa el contador que controla el giro del triángulo.
}