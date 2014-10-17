//
//  Circle.cpp
//  Genetic Algorithm Test
//
//  Created by Zeno Hao on 10/15/14.
//
//

#include "Circle.h"
#include <iostream>

void Circle::draw(){
    glColor3f(0,1,1);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i <= 180; i++){
        glVertex2d(cos(i*2./180.*M_PI)*radius + x,sin(i*2./180.*M_PI)*radius + y);
    }
    glEnd();
}

Circle::~Circle(){}
Circle::Circle(double x, double y, double radius):x(x),y(y),radius(radius),GraphicsObject(){
}

void Circle::setX(double x){
    this->x = x;
}
void Circle::setY(double y){
    this->y = y;
}
void Circle::setRadius(double radius){
    this->radius = radius;
}