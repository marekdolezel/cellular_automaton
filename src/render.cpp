/**
 * @file render.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-02
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <stdio.h>
#include <GL/glut.h>
#include "Grid.hpp"

void runSimulationLoop(void);

int winWidth, winHeight;
GLuint selectBuffer[64];

void draw_rectangle(double X, double Y, double size) {
  glVertex2f(X, Y);
  glVertex2f(X+size, Y);
  glVertex2f(X+size, Y+size);
  glVertex2f(X, Y+size);
}

double old_max = 0;
void colorMap(double min, double max,double D, int *r, int *g, int *b)
{
    /*
        Here we do the following:
            1. use 46 shades of green (yellow - low concentration, green - high concentration)
            2. max represents highest concentration at a time t (r,g,b) = (0, 255, 0)
            3. compute how much percent D is out of 'max' value (D/max)
            4. map (D/MAX)  to interval (0,230)
            5. return *r = 230 - I  

    */
    *g = 255;
    *b = 0;


    // //[a,b] -> [c,d]
    // double a = min;
    // double bb;
    // //if (old_max < max)
    // bb = max;
    
    // // bb = bb + 0.3*bb;
    // double c = 0;
    // double d = 230;

    // double x = c + ((d-c)/(bb-a))*(D-a);

    double c = 0;
    double d = 230;

    double I = c + (d-c)*(D/max);

    // x = 230 -x;
    // int x;
    // if (D > 0 && D < 5 )
    //     x = 5;
    // if (D > 5 && D < 10)
    //     x = 10;
    // if (D > 10 && D < 20)
    //     x = 15;
    // if (D > 30)
    //     x = 230;


    // if (D < 0.01)
    //     *r = 230;
    // else
        *r = 230 - I;
    //cout << "x " << x <<"D=" << D << endl;
}

void openGL_PrintGrid(Grid *grid)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);

    int gsize = grid->GetX();
    double max_cell_size = winHeight/gsize;

    double min = grid->GetMinState();
    double max = grid->GetMaxState();

    double coord = 0;
    for (int col = 0; col < gsize; col++) {  
        for (int i = 0; i < gsize; i++) {
            double state = grid->GetCellState(i, col);
            int r = 0;
            int g = 0;
            int b = 0;
            // int h = 120;
            // double s;
            // double v = 40;
            colorMap(min, max,state, &r, &g, &b);
            // HSV_RGB(h, s, v, &red, &green, &blue);
            glColor3ub((GLbyte)r, (GLbyte)g, (GLbyte)b);

            draw_rectangle(max_cell_size*col,max_cell_size*i, max_cell_size);
            coord += max_cell_size;
        }
    }
     
    glEnd();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  printf("%d %d\n", w,h);
  winWidth = w;
  winHeight = h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, winWidth, 0, winHeight, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void
keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    exit(0);
  }
}

void render_init(int argc, char* argv[]) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("CA");
    glutReshapeFunc(reshape);
    glutDisplayFunc(runSimulationLoop);
    glutKeyboardFunc(keyboard);
    glSelectBuffer(sizeof(selectBuffer), selectBuffer);
    glutMainLoop();

}
