/*!
	Geometria.cpp

	Programa para dibujar un pentagono con listas

	@author		Roberto Vivo' <rvivo@upv.es>
	@date		Feb,2024
 */

#define PROYECTO "IGR::S#02::Listas de dibujo"
#define NDEBUG = true
#pragma warning(disable: 4305) 

#include <iostream>	
#include <sstream>
#include <codebase.h>

using namespace std;
using namespace cb;

// Variables globales
static const int tasaFPS = 60;
static float gradosCamara = -90.0;
static float desfase = PI / 2;

/*
 * Parámetros para el reloj.
 */
static GLuint diente, cara, junta, engranaje, offset, offset1, face, quarters, mins, seg, aguja_min, aguja_seg, corona, axe;
static GLuint junta1, junta2, junta3, junta4, junta5, junta6, junta7;
static GLuint engranaje1, engranaje2, engranaje3, engranaje4, engranaje5, engranaje6, engranaje7;
/*
 * Parámetros para las velocidades.
 */
static float gE1 = 0.0, gE2 = 0.0, gE3 = 0.0, gE4 = 0.0, gE5 = 0.0, gE6 = 0.0, gE7 = 0.0;
/*
 * Funcion para crear un engranaje.
 */
static GLuint create_engranaje(GLfloat RP, GLfloat REJ, GLfloat REX, GLfloat ND, GLfloat A)
{
	GLfloat radio_primitivo = RP;
	GLfloat radio_eje = REJ;
	GLfloat radio_ext = REX;
	GLfloat num_dientes = ND;
	GLfloat desfase = PI / num_dientes;
	GLfloat ancho = A;

	/* Inicio del código para crear el diente del engranaje */

	diente = glGenLists(1);

	glNewList(diente, GL_COMPILE);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(radio_eje * cosf((float(0) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(0) / 2) * 2 * PI / num_dientes - desfase), 0);
	glVertex3f(radio_ext * cosf((float(0) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(0) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_primitivo * cosf((float(0) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(0) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_eje * cosf((float(1) / 2) * 2 * PI / num_dientes), radio_eje * sinf((float(1) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_primitivo * cosf((float(2) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(2) / 2) * 2 * PI / num_dientes), 0);

	glEnd();
	glEndList();

	/* Fin del código para crear el diente del engranaje */

	/* Inicio del código para crear la junta del engranaje */

	junta = glGenLists(1);
	glNewList(junta, GL_COMPILE);

	/* Junta de la parte de los dientes */
	glBegin(GL_QUAD_STRIP);

	for (int i = 0; i < (int)num_dientes * 2; i += 2)
	{

		glVertex3f(radio_eje * cosf((float(i) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(i) / 2) * 2 * PI / num_dientes - desfase), 0);
		glVertex3f(radio_eje * cosf((float(i) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(i) / 2) * 2 * PI / num_dientes - desfase), ancho);
		glVertex3f(radio_ext * cosf((float(i) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(i) / 2) * 2 * PI / num_dientes), 0);
		glVertex3f(radio_ext * cosf((float(i) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(i) / 2) * 2 * PI / num_dientes), ancho);

	}

	glVertex3f(radio_eje * cosf((float(0) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(0) / 2) * 2 * PI / num_dientes - desfase), 0);
	glVertex3f(radio_eje * cosf((float(0) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(0) / 2) * 2 * PI / num_dientes - desfase), ancho);
	glVertex3f(radio_ext * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_ext * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), ancho);

	for (int i = (int)num_dientes * 2; i > 0; i -= 2)
	{

		glVertex3f(radio_ext * cosf((float(i) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(i) / 2) * 2 * PI / num_dientes), 0);
		glVertex3f(radio_ext * cosf((float(i) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(i) / 2) * 2 * PI / num_dientes), ancho);
		glVertex3f(radio_eje * cosf((float(i) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(i) / 2) * 2 * PI / num_dientes - desfase), 0);
		glVertex3f(radio_eje * cosf((float(i) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(i) / 2) * 2 * PI / num_dientes - desfase), ancho);

	}

	glVertex3f(radio_ext * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_ext * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_ext * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), ancho);
	glVertex3f(radio_eje * cosf((float(0) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(0) / 2) * 2 * PI / num_dientes - desfase), 0);
	glVertex3f(radio_eje * cosf((float(0) / 2) * 2 * PI / num_dientes - desfase), radio_eje * sinf((float(0) / 2) * 2 * PI / num_dientes - desfase), ancho);



	glEnd();

	//Junta de la base
	glBegin(GL_QUAD_STRIP);

	for (int j = 0; j < (int)num_dientes * 2; j += 2)
	{

		glVertex3f(radio_primitivo * cosf((float(j) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(j) / 2) * 2 * PI / num_dientes), 0);
		glVertex3f(radio_primitivo * cosf((float(j) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(j) / 2) * 2 * PI / num_dientes), ancho);

	}

	glVertex3f(radio_primitivo * cosf((float(0) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(0) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_primitivo * cosf((float(0) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(0) / 2) * 2 * PI / num_dientes), ancho);

	for (int j = (int)num_dientes * 2; j > 0; j -= 2)
	{

		glVertex3f(radio_primitivo * cosf((float(j) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(j) / 2) * 2 * PI / num_dientes), 0);
		glVertex3f(radio_primitivo * cosf((float(j) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(j) / 2) * 2 * PI / num_dientes), ancho);

	}

	glVertex3f(radio_primitivo * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), 0);
	glVertex3f(radio_primitivo * cosf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), radio_primitivo * sinf((float(num_dientes * 2) / 2) * 2 * PI / num_dientes), ancho);

	glEnd();

	glEndList();

	/* Fin del código para crear la junta del engranaje */

	/* Inicio del código para crear la cara del engranaje */

	cara = glGenLists(1);
	glNewList(cara, GL_COMPILE);

	for (int i = 0; i < num_dientes; i++) {
		glPushMatrix();
		glRotatef(360 / num_dientes * i, 0, 0, 1);
		glCallList(diente);
		glPopMatrix();

	}

	glEndList();

	/* Fin del código para crear la cara del engranaje */

	/* Inicio del código para crear el engranaje completo */

	engranaje = glGenLists(1);
	glNewList(engranaje, GL_COMPILE);

	glCallList(cara);
	glPushMatrix();
	glTranslatef(0, 0, ancho);
	glRotatef(180, 0, 1, 0);
	glCallList(cara);
	glPopMatrix();
	glCallList(junta);

	glEndList();

	/* Fin del código para crear el engranaje completo */

	return engranaje;
}
/*
 * Funcion para crear la aguja del reloj.
 */
static GLuint create_aguja(GLfloat RP,  GLfloat ND, GLfloat REJ, GLfloat REX, GLfloat A)
{
	// Código para crear la aguja del reloj
	GLuint aguja = glGenLists(1);
	glNewList(aguja, GL_COMPILE);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(REJ * cosf((float(0) / 2) * 2 * PI / ND - A), REJ * sinf((float(0) / 2) * 2 * PI / ND - A), 0);
	glVertex3f(REX * cosf((float(0) / 2) * 2 * PI / ND), REX * sinf((float(0) / 2) * 2 * PI / ND), 0);
	glVertex3f(RP * cosf((float(0) / 2) * 2 * PI / ND), RP * sinf((float(0) / 2) * 2 * PI / ND), 0);
	glVertex3f(REJ * cosf((float(1) / 2) * 2 * PI / ND + A), REJ * sinf((float(1) / 2) * 2 * PI / ND + A), 0);

	glEnd();

	glEndList();
	
	// Fin del código para crear la aguja del reloj
	return aguja;
}	
/*
 * Funcion para crear el reloj.
 */
static void create_reloj()
{
	// Código para crear el reloj
	face = glGenLists(1);

	glNewList(face, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		glVertex3f(2.5 * cosf((float(i) / 2) * 2 * PI / 50 + desfase), 2.5 * sinf((float(i) / 2) * 2 * PI / 50 + desfase), 0.01);
	}
	glEnd();
	glEndList();

	quarters = glGenLists(1);
	glNewList(quarters, GL_COMPILE);
	glBegin(GL_LINES);
	glVertex3f(2, 0, 0.02);
	glVertex3f(2.4, 0, 0.02);
	glVertex3f(0, 2, 0.02);
	glVertex3f(0, 2.4, 0.02);
	glVertex3f(-2, 0, 0.02);
	glVertex3f(-2.4, 0, 0.02);
	glVertex3f(0, -2, 0.02);
	glVertex3f(0, -2.4, 0.02);
	glEnd();
	glEndList();

	mins = glGenLists(1);
	glNewList(mins, GL_COMPILE);
	glBegin(GL_LINES);
	float grad = 0.523599;
	for (int i = 0; i < 12; i++) {
		glVertex3f(2.2 * cosf(PI / 2 - (i * grad)), 2.2 * sinf(PI / 2 - (i * grad)), 0.02);
		glVertex3f(2.4 * cosf(PI / 2 - (i * grad)), 2.4 * sinf(PI / 2 - (i * grad)), 0.02);
	}
	glEnd();
	glEndList();

	corona = glGenLists(1);
	glNewList(corona, GL_COMPILE);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 100; i++) {
		glVertex3f(2.5 * cosf((float(i) / 2) * 2 * PI / 50 + desfase), 2.5 * sinf((float(i) / 2) * 2 * PI / 50 + desfase), 0.01);
		glVertex3f(3 * cosf((float(i) / 2) * 2 * PI / 50 + desfase), 3 * sinf((float(i) / 2) * 2 * PI / 50 + desfase), 0.01);
	}
	glEnd();
	glEndList();

	seg = glGenLists(1);
	glNewList(seg, GL_COMPILE);
	glBegin(GL_LINES);
	float grad_seg = 0.104720;
	for (int i = 0; i < 60; i++) {
		glVertex3f(2.3 * cosf(PI / 2 - (i * grad_seg)), 2.3 * sinf(PI / 2 - (i * grad_seg)), 0.02);
		glVertex3f(2.4 * cosf(PI / 2 - (i * grad_seg)), 2.4 * sinf(PI / 2 - (i * grad_seg)), 0.02);
	}
	glEnd();
	glEndList();

	axe = glGenLists(1);
	glNewList(axe, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		glVertex3f(0.05 * cosf((float(i) / 2) * 2 * PI / 50 + desfase), 0.05 * sinf((float(i) / 2) * 2 * PI / 50 + desfase), 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++) {
		glVertex3f(0.05 * cosf((float(i) / 2) * 2 * PI / 50 + desfase), 0.05 * sinf((float(i) / 2) * 2 * PI / 50 + desfase), -0.3);
	}
	glEnd();
	glEndList();
}

void init()
// Inicializaciones
{
	cout << "GL version " << glGetString(GL_VERSION) << endl;
	glClearColor(0.8f, 0.8f, 0.8f, 0.5f);
	glEnable(GL_DEPTH_TEST);

	//Desabilitar culling para que se vean los objetos por detrás.
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	
	//Comentar como se han calculado los módulos, offsets, velocidades.

	//Funciones para crear engranaje1.
	engranaje1 = create_engranaje(0.5f, 1.0f, 1.05f, 60.0f, -0.12f);
	junta1 = junta;
	//Funciones para crear engranaje2.
	engranaje2 = create_engranaje(0.05f, 0.2f, 0.25f, 12.0f, -0.18f);
	junta2 = junta;
	//Funciones para crear engranaje3.
	engranaje3 = create_engranaje(0.05f, 1.0f, 1.05f, 48.0f, -0.12f);
	junta3 = junta;
	//Funciones para crear engranaje4.
	engranaje4 = create_engranaje(0.05f, 0.25f, 0.3f, 12.0f, -0.18f);
	junta4 = junta;
	//Funciones para crear engranaje5.
	engranaje5 = create_engranaje(0.05f, 0.6f, 0.65f, 36.0f, -0.12f);
	junta5 = junta;
	//Funciones para crear engranaje6.
	engranaje6 = create_engranaje(0.05f, 0.2f, 0.25f, 12.0f, -0.12f);
	junta6 = junta;
	//Funciones para crear engranaje7.
	engranaje7 = create_engranaje(0.05f, 0.2f, 0.25f, 12.0f, -0.12f);
	junta7 = junta;
	//Cálculo del offset
	// ofsset = 180 / num_dientes
	offset = 180.0 / 12.0;
	offset1 = 180.0 / 36.0;
	//Creación de la aguja
	aguja_min = create_aguja(0, 60.0, 0.2, 1.8, 0.4);
	aguja_seg = create_aguja(0, 60.0, 0.2, 1, 0.2);
	//Creación del reloj
	create_reloj();
}

void muestraFPS()
{
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;
	int ahora, tiempo_transcurrido;

	// Cada que pase por aqui incremento los fotogramas
	fotogramas++;

	// Calculo el tiempo transcurrido
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	// si ha transcurrido un segundo, mostrar los fotogramas
	if (tiempo_transcurrido > 1000) {
		// modificar la barra de titulo
		stringstream titulo;
		titulo << "FPS= " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		// reinicio a cuenta
		fotogramas = 0;
		antes = ahora;
	}

}

void display()
// Funcion de atencion al dibujo
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Cálculo de la posición de la cámara
	Vec3 camPosition(5.5 * cosf(rad(gradosCamara)), cosf(rad(5.5 * gradosCamara)), -5.5 * sinf(rad(gradosCamara)));

	// Posicion de la camara
	gluLookAt(camPosition.x, camPosition.y, camPosition.z, 0, 0, 0, 0, 1, 0); // --> Vista perspectiva (general)
	//gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);  --> Comprobación frontal

	// Uso de Display Lists
	// Dibujar el engranaje relleno
	// Formato de dibujo para el reloj
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/* Cara */
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glColor3f(1, 1, 1);
	glCallList(face);
	glPopMatrix();

	/* Color Primario */
	glColor3f(0.83, 0.69, 0.22);

	/* Corona */
	glPushMatrix();
	glTranslatef(0, 0, 0.05);
	glCallList(corona);
	glPopMatrix();

	// Formato de dibujo para los engranajes
	glPolygonMode(GL_FRONT, GL_FILL);

	/* Aguja_min */
	glPushMatrix();
	glTranslatef(0, 0, 0.07);
	glRotatef(90.0 - gE1, 0, 0, 1);
	glCallList(aguja_min);
	glPopMatrix();

	/* Aguja_seg */
	glPushMatrix();
	glTranslatef(0, 0, 0.09);
	glRotatef(90.0 - gE7, 0, 0, 1);
	glCallList(aguja_seg);
	glPopMatrix();


	/* Engranaje 1 */
	glPushMatrix();
	glTranslatef(0, 0, -0.48);
	glRotatef(gE1, 0, 0, 1);
	glCallList(engranaje1);
	glPopMatrix();

	/* Engranaje 2 */
	glPushMatrix();
	glTranslatef(0.8855, 0.8855, -0.364);
	glRotatef(gE2 + offset, 0, 0, -1);
	glCallList(engranaje2);
	glPopMatrix();
	
	/* Engranaje 3 */
	glPushMatrix();
	glTranslatef(0.8855, 0.8855, -0.242);
	glRotatef(gE3, 0, 0, -1);
	glCallList(engranaje3);
	glPopMatrix();
	
	/* Engranaje 4 */
	glPushMatrix();
	glTranslatef(-0.416, 0.8855, -0.122);
	glRotatef(gE4 + offset, 0, 0, 1);
	glCallList(engranaje4);
	glPopMatrix();

	/* Engranaje 5 */
	glPushMatrix();
	glTranslatef(-0.416, 0.8855, 0);
	glRotatef(gE5 + offset1, 0, 0, 1);
	glCallList(engranaje5);
	glPopMatrix();

	/* Engranaje 6 */
	glPushMatrix();
	glTranslatef(0.2585, 0.367,0);
	glRotatef(gE6, 0, 0, -1);
	glCallList(engranaje6);
	glPopMatrix();

	/* Engranaje 7 */
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(gE7 + offset1, 0, 0, 1);
	glCallList(engranaje7);
	glPopMatrix();
	
	/* Eje 1 */
	glPushMatrix();
	glTranslatef(0.8855, 0.8855, -0.242);
	glColor3f(0.4, 0.4, 0.4);
	glRotatef(gE3, 0, 0, -1);
	glCallList(axe);
	glPopMatrix();

	/* Eje 2 */
	glPushMatrix();
	glTranslatef(-0.416, 0.8855, 0);
	glColor3f(0.4, 0.4, 0.4);
	glRotatef(gE5 + offset1, 0, 0, 1);
	glCallList(axe);
	glPopMatrix();

	// Dibujar el engranaje en modo alambrico
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	glLineWidth(2);
	glPolygonMode(GL_FRONT, GL_LINE);
	glColor3f(0, 0, 0);

	/* Quarters */
	glPushMatrix();
	glTranslatef(0, 0, 0.07);
	glCallList(quarters);
	glCallList(mins);
	glCallList(seg);
	glPopMatrix();

	/* Aguja_min */
	glPushMatrix();
	glTranslatef(0, 0, 0.07);
	glRotatef(90.0 - gE1, 0, 0, 1);
	glCallList(aguja_min);
	glPopMatrix();

	/* Aguja_seg */
	glPushMatrix();
	glTranslatef(0, 0, 0.09);
	glRotatef(90.0 - gE7, 0, 0, 1);
	glCallList(aguja_seg);
	glPopMatrix();

	/* Junta 1 */
	glPushMatrix();
	glTranslatef(0, 0, -0.48);
	glRotatef(gE1, 0, 0, 1);
	glCallList(junta1);
	glPopMatrix();

	/* Junta 2 */
	glPushMatrix();
	glTranslatef(0.8855, 0.8855, -0.364);
	glRotatef(gE2 + offset, 0, 0, -1);
	glCallList(junta2);
	glPopMatrix();

	/* Junta 3 */
	glPushMatrix();
	glTranslatef(0.8855, 0.8855, -0.242);
	glRotatef(gE3, 0, 0, -1);
	glCallList(junta3);
	glPopMatrix();

	/* Junta 4  */
	glPushMatrix();
	glTranslatef(-0.416, 0.8855, -0.122);
	glRotatef(gE4 + offset, 0, 0, 1);
	glCallList(junta4);
	glPopMatrix();

	/* Junta 5 */
	glPushMatrix();
	glTranslatef(-0.416, 0.8855, 0);
	glRotatef(gE5 + offset1, 0, 0, 1);
	glCallList(junta5);
	glPopMatrix();
	
	/* Junta 6 */
	glPushMatrix();
	glTranslatef(0.2585, 0.367, 0);
	glRotatef(gE6, 0, 0, -1);
	glCallList(junta6);
	glPopMatrix();

	/* Junta 7 */
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(gE7 + offset1, 0, 0, 1);
	glCallList(junta7);
	glPopMatrix();
	
	glPopAttrib();

	muestraFPS();

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	// Marco dentro del area de dibujo
	glViewport(0, 0, w, h);
	float razon = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, razon, 0.1, 20);

}

void update()
{

	// Animacion coherente con el tiempo transcurrido
	static const float omega = 1;	// vueltas por segundo

	// Incialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	gE1 += omega / 60 * 360 * tiempo_transcurrido;
	gE2 = gE1 * 5;
	gE3 = gE2;
	gE4 = gE3 * 4;
	gE5 = gE4;
	gE6 = gE5 * 3;
	gE7 = gE6;
	gradosCamara += omega / 60 * 360 * tiempo_transcurrido;
	antes = ahora;

	// Encolar un evento de redibujo
	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	// Sirve para re-arrancar el reloj de cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);

	update();
}

int main(int argc, char** argv)
// Programa principal
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(2000, onTimer, 1000 / tasaFPS);

	// Bucle de atencion a eventos
	glutMainLoop();
}