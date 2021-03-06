// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h" //ayuda a que compile mas rapido
#include <stdio.h> // esta cosa para librerias incluidas en c#
#include <stdlib.h>

#define GLEW_STATIC 

#include "GL/glew.h" //comillas para librerias personalizadas
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std; //aqui esta lo de c++

float posicionXTriangulo = 0;
float posicionYTriangulo = 0;
float angulo = 0;
enum Direccion {Izquierda,Derecha,Arriba,Abajo};
Direccion direccionHorizontalTriangulo=Direccion::Izquierda; //significa que es un miembro estatico
Direccion direccionVerticalTriangulo = Direccion::Arriba;

void dibujarTriangulo3D() {

	//Utilizar matriz identidad (una matriz nueva)
	glPushMatrix();
	//transformaciones estandar: translacion, rotacion,escala en este orden
	glTranslatef(posicionXTriangulo,posicionYTriangulo,0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	
	//el primero es el angulo y lo demas es que tanto afecta a cada uno de los ejes x,y,z
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

	//dibujar vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0.0f);
	glVertex3f(0.4f, -0.4f, 0.0f);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glEnd();

	//soltar la matriz
	glPopMatrix();
}

void dibujar() {
	dibujarTriangulo3D();
}

void actualizar() {
	
	if (angulo >= 360) {
		angulo =0.0f;
	}
		angulo += 0.03f;

	

	if (direccionHorizontalTriangulo == Direccion::Izquierda) 
	{
		if (posicionXTriangulo > -0.9f)
		{
			posicionXTriangulo -= 0.001f;
		}
		else 
		{
			direccionHorizontalTriangulo = Direccion::Derecha;
		}
	}
	if (direccionHorizontalTriangulo == Direccion::Derecha)
	{
		if (posicionXTriangulo < 0.9f) 
		{
			posicionXTriangulo += 0.001f;
		}
		else 
		{
			direccionHorizontalTriangulo = Direccion::Izquierda;
		}
	}	
	if (direccionVerticalTriangulo == Direccion::Arriba)
	{
		if (posicionYTriangulo > -0.9f)
		{
			posicionYTriangulo -= 0.0005f;
		}
		else
		{
			direccionVerticalTriangulo = Direccion::Abajo;
		}
	}
	if (direccionVerticalTriangulo == Direccion::Abajo)
	{
		if (posicionYTriangulo < 0.9f)
		{
			posicionYTriangulo += 0.0005f;
		}
		else
		{
			direccionVerticalTriangulo = Direccion::Arriba;
		}
	}

}

int main()
{
	//Declaramos apuntador de ventana

	GLFWwindow *window;

	//Si no se pudo iniciar glfw terminamos ejecución

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo iniciar GLFW entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido e contexto activamos funciones modernas
	glewExperimental = true; //permite trabajar con gpu y cpu al mismo tiempo,solo va a funcionar si ya esta establecido el contexto

	//en caso de haber error se guarda en la variable errorGlew que es tipo GLenum 
	GLenum errorGlew = glewInit(); //inicializa glew

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	//se obtiene la version de OpenGL y se imprime
	const GLubyte *versionGL = glGetString(GL_VERSION); 
	cout << "Version OpenGL: " << versionGL; 

	//ciclo de dibujo (draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768); //dice donde va a empezar a renderear y donde va a terminar
		//Establecer color de borrado
		glClearColor(1, 0,0, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffer
		glfwSwapBuffers(window); //cambia el buffer de la pantalla por el otro que se lleno
		//reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window); //terminamos los procesos y eliminamos la ventana
	glfwTerminate();
	return 0;
}



