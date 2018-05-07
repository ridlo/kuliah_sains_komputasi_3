#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float year = 0.0, day = 0.0, month = 0.0;
double boxsize = 10.0;
bool fullscreen = false;
bool mouseDown = false;

float x_rot = 0.0f;
float y_rot = 0.0f;
float x_diff = 0.0f;
float y_diff = 0.0f;

float rm = 4.0f;
float xm = 0.0f;
float ym = 0.0f;
float zm = 4.0f;
float inc = 0.349065; // 20 deg

float rs = 1.0f;
float xs = 1.0f;
float ys = 0.0f;
float zs = 0.0f;


void putarBulan(){
    float mon = month*M_PI/180.;
    xm = rm * cos(inc) * sin(mon);
    ym = rm * sin(inc) * sin(mon);
    zm = rm * cos(mon);
    glutPostRedisplay();
}

void putarCahaya(){
    float yr = year*M_PI/180.;
    xs = rs * cos(yr);
    zs = rs * sin(yr);
    glutPostRedisplay();
}

void init(void){
    GLfloat mat_specular[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat mat_shininess[] = {5.0};

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 2*boxsize, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { xs, ys, zs, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glColor3f(1.0, 1.0, 1.0);
    glutWireCube(boxsize); // boxsize

    glPushMatrix();
    glColor3f(0.5, 0.5, 1.0);
    glutSolidSphere(0.8, 20, 16); // earth
    glTranslatef(xm, ym, zm);
    glColor3f(1.0, 1.0, 0.9);
    glutSolidSphere(0.4, 20, 16); // moon
    glPopMatrix();
    glutSwapBuffers();
}

/* "smoothing" when resize the screen display */
void resize(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
    if (key == 'm'){
        month += 5;
        if (month > 360){
            month -= 360;
        }
        putarBulan();
    }
    else if (key == 'M'){
        month -= 5;
        if (month < 0){
            month += 360;
        }
        putarBulan();
    }
    else if (key == 'y'){
        year -= 5;
        if (year < 0){
            year += 360;
        }
        putarCahaya();
    }
    else if (key == 'Y'){
        year += 5;
        if (year > 360){
            year -= 360;
        }
        putarCahaya();
    }
}

void specialKeyboard(int key, int x, int y){
    if (key == GLUT_KEY_F1){
        fullscreen = !fullscreen;
        if (fullscreen){
            glutFullScreen();
        } 
        else {
            glutPositionWindow(25, 25);
            glutReshapeWindow(700, 700);
        }
    }
}

/* rotate using mouse pointer */
void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseDown = true;
        x_diff = x - y_rot;
        y_diff = -y + x_rot;
    }
    else{
        mouseDown = false;
    }
}

void mouseMotion(int x, int y){
    if (mouseDown){
        y_rot = x - x_diff;
        x_rot = y + y_diff;
        glutPostRedisplay();
    }
}

int main(int argc,  char *argv[]){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(25, 25);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Earth-Moon System");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();

    return 0;
}
