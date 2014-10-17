//
//  main.cpp
//  Genetic Circles
//
//  Created by Zeno Hao on 10/15/14.
//
//
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <deque>
#include "Circle.h"

class A{
    public:
    int x;
    A(const A& a){x = a.x;}
    A(){x = 0;}
    A(int x){this->x = x;}
};
int main(int argc, const char * argv[]) {
    std::deque<A*> container = std::deque<A*>();
    for(int i = 0; i < 10; i ++){
        container.push_back(new A(i));
        std::cout << container.at(i)->x << std::endl;
    }
    A* copy;
    for(int i = 0; i < 5; i++){
        copy = new A(*container.front());
        container.pop_front();
        container.push_back(copy);
    }
    free(copy);
    std::cout << "\n\n\n\n";
    for(A* t: container)
        std::cout << t->x << std::endl;
}
