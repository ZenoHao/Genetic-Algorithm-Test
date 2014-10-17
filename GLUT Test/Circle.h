//
//  Circle.h
//  Genetic Algorithm Test
//
//  Created by Zeno Hao on 10/15/14.
//
//

#ifndef __Genetic_Algorithm_Test__Circle__
#define __Genetic_Algorithm_Test__Circle__

#include <stdio.h>
#include "GraphicsObject.h"
#include <GLUT/glut.h>
#include <math.h>

class Circle: virtual public GraphicsObject{
private:
    double x;
    double y;
    double radius;
public:
    virtual ~Circle();
    Circle( const Circle& o ): GraphicsObject(){x = o.x; y = o.y; radius = o.radius;}
    Circle(double x = 0, double y = 0, double radius = 0);
    double getX(){return this->x;}
    double getY(){return this->y;}
    double getRadius(){return this->radius;}
    
    void setX(double x);
    void setY(double y);
    void setRadius(double radius);
    virtual void draw();
};

#endif /* defined(__Genetic_Algorithm_Test__Circle__) */
