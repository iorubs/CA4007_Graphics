/*
Ruben Vasconcelos 11337151

BASIC SYSTEM
•	Right click on the drawing window, select "Shape" then pick a shape.
•	Right click on the drawing window, select "Color" then pick a color.
•	Right click on the drawing window and select Reset from the menu.

ADVANCED SYSTEM
• To pick a color, left click the color in the color pallet.
• To change Brightness, right click the color window, select "Brightness",
  and pick a value for the Brightness.

SUPER-ADVANCED SYSTEM
• To change Transparency, right click the color window, select "Transparency",
  and pick a value for the Transparency.
*/

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <math.h>

GLfloat vertices_x [100];
GLfloat vertices_y [100];
GLfloat hh_draw, hh_color;
GLfloat b_ness = 0.0f;
GLfloat t_ness = 1.0f;
GLfloat point_size = 5.0f;
GLfloat line_width = 1.0f;
int shape = 1;
int draw = 1;
int rectangle = 0;
int vertice_count = 0;

GLfloat s_color [3] = {0.0, 0.0, 1.0};

void drawPoint(){
  glPointSize(point_size);
  glBegin(GL_POINTS);
    glVertex3f(vertices_x[0], vertices_y[0], 0.0f); //point cordinates
  glEnd();
}

void drawLine(){
  glLineWidth(line_width);
  glBegin(GL_LINES);
    glVertex3f(vertices_x[0], vertices_y[0], 0.0f); // origin of the line
    glVertex3f(vertices_x[1], vertices_y[1], 0.0f); // ending point of the line
  glEnd();
}

void drawRectangle(){
  glBegin(GL_POLYGON);
		glVertex2f(vertices_x[0], vertices_y[0]);
		glVertex2f(vertices_x[0], vertices_y[1]);
		glVertex2f(vertices_x[1], vertices_y[1]);
		glVertex2f(vertices_x[1], vertices_y[0]);
	glEnd();
}

void drawPolygon(){
  glBegin(GL_POLYGON);
    int i=0;
    for(i; i<shape; i++)
      glVertex2f(vertices_x[i], vertices_y[i]);
	glEnd();
}

void clear(){
  shape = 1;
  vertice_count = 0;
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

void drawDisplay(void){
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
	glColor4f(s_color[0], s_color[1], s_color[2], t_ness);

  if(draw){
    if(shape == 1)
      drawPoint();
    else if(shape == 2)
      drawLine();
    else if(shape == 4 && rectangle)
      drawRectangle();
    else if (shape != 0)
      drawPolygon();

    draw = 0;
  }

	glFlush();
	return;
}

void drawMouse(GLint button, GLint state, GLint x, GLint y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && shape != 0){
    vertices_x[vertice_count] = x;
    vertices_y[vertice_count] = hh_draw-y;

    vertice_count++;

    if((rectangle && vertice_count == 2) || (!rectangle && vertice_count == shape)){
      draw = 1;
      glutPostRedisplay();
      vertice_count = 0;
    }
	}
	return;
}

void drawReshape(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLfloat)w,0.0,(GLfloat)h);
	glViewport(0,0,w,h);
	hh_draw=h;
	return;
}

void processMenuEvents(int option) {
  switch (option) {
		case 1:
      clear();
			break;
    case 2:
      exit(0);
	}
}

void processPointMenuEvents(int option) {
  vertice_count = 0;
  rectangle = 0;
  shape = 1;
  point_size = (GLfloat) option*1.0;
}

void processLineMenuEvents(int option) {
  vertice_count = 0;
  rectangle = 0;
  shape = 2;
  line_width = (GLfloat) option*1.0;
}

void processPolygonMenuEvents(int option) {
  vertice_count = 0;
  rectangle = 0;
  shape = option+2;
}

void processShapeMenuEvents(int option) {
  vertice_count = 0;
  rectangle = 0;

  if(option == 3){
      shape = 4;
      rectangle = 1;
  }
}

void processBasicColourMenuEvents(int option) {
  switch (option) {
    case 1:
      s_color[0] = 1.0;
      s_color[1] = 0.0;
      s_color[2] = 0.0;
      break;
    case 2:
      s_color[0] = 0.0;
      s_color[1] = 1.0;
      s_color[2] = 0.0;
      break;
    case 3:
      s_color[0] = 0.0;
      s_color[1] = 0.0;
      s_color[2] = 1.0;
      break;
    case 4:
      s_color[0] = 1.0;
      s_color[1] = 1.0;
      s_color[2] = 1.0;
      break;
    case 5:
      s_color[0] = 0.0;
      s_color[1] = 0.0;
      s_color[2] = 0.0;
  }
}

void createGLUTShapeMenus() {
  int colourMenu = glutCreateMenu(processBasicColourMenuEvents);
  glutAddMenuEntry("Red", 1);
  glutAddMenuEntry("Green", 2);
  glutAddMenuEntry("Blue", 3);
  glutAddMenuEntry("White", 4);
  glutAddMenuEntry("Black", 5);

  int pointMenu = glutCreateMenu(processPointMenuEvents);
	glutAddMenuEntry("Small", 1);
	glutAddMenuEntry("Medium", 5);
	glutAddMenuEntry("Large", 10);

  int lineMenu = glutCreateMenu(processLineMenuEvents);
	glutAddMenuEntry("Small", 1);
	glutAddMenuEntry("Medium", 5);
	glutAddMenuEntry("Large", 10);

  int poligonMenu = glutCreateMenu(processPolygonMenuEvents);
	glutAddMenuEntry("3", 1);
	glutAddMenuEntry("4", 2);
  glutAddMenuEntry("5", 3);
	glutAddMenuEntry("6", 4);
  glutAddMenuEntry("7", 5);
	glutAddMenuEntry("8", 6);
  glutAddMenuEntry("9", 7);
	glutAddMenuEntry("10", 8);

  int shapeMenu = glutCreateMenu(processShapeMenuEvents);
	glutAddSubMenu("Point", pointMenu);
	glutAddSubMenu("Line", lineMenu);
  glutAddMenuEntry("Rectangle", 3);
	glutAddSubMenu("Polygon", poligonMenu);

  int menu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Reset", 1);
  glutAddSubMenu("Shape", shapeMenu);
  glutAddSubMenu("Color", colourMenu);
  glutAddMenuEntry("Quit", 2);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawOutLine(){
  glColor4f(1.0,1.0,1.0,1.0);

  //add outline to make palet easier to destinguish
  glLineWidth(2.0f);
  glBegin(GL_LINES);
    int i=0;
    for(i; i<6; i++){
      glVertex3f(sin(i/6.0*2*M_PI), cos(i/6.0*2*M_PI), 0.0f); // origin of the line
      glVertex3f(sin((i+1)/6.0*2*M_PI), cos((i+1)/6.0*2*M_PI), 0.0f); // ending point of the line
    }
  glEnd();
}

void drawPallet(){
  glBegin(GL_POLYGON);
    glColor3f(1.0f+b_ness, 0.0f+b_ness, 0.0f+b_ness); // make this vertex red
    glVertex2d(sin(0/6.0*2*M_PI), cos(0/6.0*2*M_PI));
    glColor3f(1.0f+b_ness, 1.0f+b_ness, 0.0f+b_ness); // make this vertex red/green
    glVertex2d(sin(1/6.0*2*M_PI), cos(1/6.0*2*M_PI));
    glColor3f(0.0f+b_ness, 1.0f+b_ness, 0.0f+b_ness); // make this vertex green
    glVertex2d(sin(2/6.0*2*M_PI), cos(2/6.0*2*M_PI));
    glColor3f(0.0f+b_ness, 1.0f+b_ness, 1.0f+b_ness); // make this vertex green/blue
    glVertex2d(sin(3/6.0*2*M_PI), cos(3/6.0*2*M_PI));
    glColor3f(0.0f+b_ness, 0.0f+b_ness, 1.0f+b_ness); // make this vertex blue
    glVertex2d(sin(4/6.0*2*M_PI), cos(4/6.0*2*M_PI));
    glColor3f(1.0f+b_ness, 0.0f+b_ness, 1.0f+b_ness); // make this vertex blue/red
    glVertex2d(sin(5/6.0*2*M_PI), cos(5/6.0*2*M_PI));
  glEnd();
}

void colorDisplay() {
  glClearColor(s_color[0],s_color[1],s_color[2],t_ness);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  drawOutLine();
  drawPallet();
  glFlush();
}

void colorMouse(GLint button, GLint state, GLint x, GLint y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
    glReadPixels(x, hh_color-y, 1, 1, GL_RGB, GL_FLOAT, &s_color);
    glutPostRedisplay();
	}
	return;
}

void processBrightnessMenuEvents(int option) {
  b_ness = (GLfloat) option/100;
  glutPostRedisplay();
}

void processTransparencyMenuEvents(int option) {
  t_ness = (GLfloat) option/100;
}

void processAdvancedColorMenuEvents(int option) {
  switch (option) {
    case 1:
      exit(0);
  }
}

void colorReshape(GLsizei w, GLsizei h){
	hh_color=h;
	return;
}

void createGLUTColorMenus() {
  int brightMenu = glutCreateMenu(processBrightnessMenuEvents);
	glutAddMenuEntry("100% (White)", 100);
	glutAddMenuEntry("90%", 80);
  glutAddMenuEntry("80%", 60);
  glutAddMenuEntry("70%", 40);
  glutAddMenuEntry("60%", 20);
	glutAddMenuEntry("50%", 0);
  glutAddMenuEntry("40%", -20);
  glutAddMenuEntry("30%", -40);
  glutAddMenuEntry("20%", -60);
  glutAddMenuEntry("10%", -80);
  glutAddMenuEntry("0% (Black)", -100);

  int transpMenu = glutCreateMenu(processTransparencyMenuEvents);
  glutAddMenuEntry("90%", 10);
  glutAddMenuEntry("80%", 20);
  glutAddMenuEntry("70%", 30);
  glutAddMenuEntry("60%", 40);
  glutAddMenuEntry("50%", 50);
  glutAddMenuEntry("40%", 60);
  glutAddMenuEntry("30%", 70);
  glutAddMenuEntry("20%", 80);
  glutAddMenuEntry("10%", 90);
  glutAddMenuEntry("Off", 100);

  int menu = glutCreateMenu(processAdvancedColorMenuEvents);
  glutAddSubMenu("Brightness", brightMenu);
  glutAddSubMenu("Transparency", transpMenu);
  glutAddMenuEntry("Quit", 1);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);

  //color window
  glutInitWindowSize(400,400);
	glutInitWindowPosition(0,0);
	glutCreateWindow("color");
  createGLUTColorMenus();
  glutDisplayFunc(colorDisplay);
  glutReshapeFunc(colorReshape);
  glutMouseFunc(colorMouse);

  //drawing window
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("drawing");
  createGLUTShapeMenus();
  glutDisplayFunc(drawDisplay);
	glutReshapeFunc(drawReshape);
	glutMouseFunc(drawMouse);
  clear();

	glutMainLoop();
}
