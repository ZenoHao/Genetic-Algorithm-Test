#include <GLUT/glut.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include "Circle.h"
#include "GeneticCircle.h"
#include <iostream>

#define NUM_CIRCLES 10
#define WIN_DIM 500

std::vector<Circle*> circles;
Circle* result;
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    for(int i = 0; i < circles.size(); i ++)
        circles.at(i)->draw();
    result->draw();
    glColor3f(1,0,1);
    glBegin(GL_LINES);
    glVertex2d(result->getX()-0.05,result->getY());
    glVertex2d(result->getX()+0.05,result->getY());
    glVertex2d(result->getX(),result->getY()-0.05);
    glVertex2d(result->getX(),result->getY()+0.05);
    glEnd();
    std::cout << result->getX() << std::endl;
    glutSwapBuffers();
}

void reshape(int width, int height) {

}

void idle(void) {
}

int main(int argc, char **argv) {
    // credit to http://stackoverflow.com/questions/7879843/opengl-hello-world-on-mac-without-xcode
    
    //a basic set up...
    srand(time(0));
    circles = std::vector<Circle*>();
    for(int i = 0; i < NUM_CIRCLES; i++){
        circles.push_back(new Circle(2*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5),
                                     2*(static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/3));
    }
    GeneticCircle gen = GeneticCircle(100, circles);
    result = gen.generate();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIN_DIM, WIN_DIM);
    
    //create the window, the argument is the title
    glutCreateWindow("GLUT program");
    
    //pass the callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    
    //we never get here because glutMainLoop() is an infinite loop
    return 0;
    
}