//
//  GeneticCircle.cpp
//  Genetic Algorithm Test
//
//  Created by Zeno Hao on 10/15/14.
//
//

#include "GeneticCircle.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>

#define NUM_CHILD 8
#define MUT_RATE_X 0.1
#define MUT_RATE_Y 0.1
#define MUT_RATE_RAD 0.1

int compare(Circle* i, Circle* j){return i->getRadius() < j->getRadius();}

GeneticCircle::GeneticCircle(){}
GeneticCircle::~GeneticCircle(){}
GeneticCircle::GeneticCircle(int gen, std::vector<Circle*> circles){
    best = new Circle(0,0,0);
    // Deep copy. Not sure if necessary
    for(int i = 0; i < circles.size(); i ++){
        this->circles.push_back(new Circle(circles.at(i)->getX(),
                                           circles.at(i)->getY(),
                                           circles.at(i)->getRadius()));
    }
    this->gen = gen;
    srand(time(0));
    for(int i = 0; i < NUM_CHILD; i ++){
        children.push_back(new Circle(((float)rand()/(float)(RAND_MAX) - 0.5),
                                      ((float)rand()/(float)(RAND_MAX) - 0.5),
                                      0));
    }
}

void GeneticCircle::morph(){
    std::cout << "mutating" << std::endl;
    int num = 0;
    for(int i = 0; i < children.size(); i++){
        num = rand()%3 + 1;
        switch(num){
            case 1:
                std::cout << "Mutating X value of child " << i << std::endl;
                std::cout << "\tPrev X value:\t" << children.at(i)->getX() << std::endl;
                children.at(i)->setX(children.at(i)->getX() + ((float)rand()/(float)(RAND_MAX) - 0.5)*MUT_RATE_X);
                while(children.at(i)->getX() < -1 || children.at(i)->getX() > 1){
                    if(children.at(i)->getX() < -1){
                        children.at(i)->setX(children.at(i)->getX() + (float)rand()/(float)(RAND_MAX)*MUT_RATE_X);
                    }
                    else if(children.at(i)->getX() > 1){
                        children.at(i)->setX(children.at(i)->getX() - (float)rand()/(float)(RAND_MAX)*MUT_RATE_X);
                    }
                }
                std::cout << "\tNew X value:\t" << children.at(i)->getX() << std::endl;
                break;
            case 2:
                std::cout << "Mutating Y value of child " << i << std::endl;
                std::cout << "\tPrev Y value:\t" << children.at(i)->getY() << std::endl;
                children.at(i)->setY(children.at(i)->getY() + ((float)rand()/(float)(RAND_MAX) - 0.5)*MUT_RATE_Y);
                while(children.at(i)->getY() < -1 || children.at(i)->getY() > 1){
                    if(children.at(i)->getY() < -1){
                        children.at(i)->setY(children.at(i)->getY() + (float)rand()/(float)(RAND_MAX)*MUT_RATE_Y);
                    }
                    else if(children.at(i)->getY() > 1){
                        children.at(i)->setY(children.at(i)->getY() - (float)rand()/(float)(RAND_MAX)*MUT_RATE_Y);
                    }
                }
                std::cout << "\tNew Y value:\t" << children.at(i)->getY() << std::endl;
                break;
            case 3:
                std::cout << "Mutating Radius value of child " << i << std::endl;
                std::cout << "\tPrev radius:\t" << children.at(i)->getRadius() << std::endl;
                do{
                    children.at(i)->setRadius(children.at(i)->getRadius() + ((float)rand()/(float)(RAND_MAX))*MUT_RATE_RAD);
                }
                while(children.at(i)->getRadius() <= 0);
                std::cout << "\tNew radius:\t" << children.at(i)->getRadius() << std::endl;
                break;
            default:
                // oh god something went wrong;
                std::cout << "something is wrong" << std::endl;
                break;
        }
    }
}
void GeneticCircle::eval(){
    std::cout << "evaulating" << std::endl;
    // sort by largest radius that is within window and does not touch any other circle
    for(Circle* c: children){
        for(Circle* d: circles){
            if(d->getRadius() >
               sqrt(pow(c->getX() - d->getX(),2) + pow(c->getY() - d->getY(),2))){
                c->setRadius(0);
                std::cout << "Setting radius to zero" << std::endl;
                break;
            }
            else if(c->getRadius() + d->getRadius() >
                    sqrt(pow(c->getX() - d->getX(),2) + pow(c->getY() - d->getY(),2))){
                // if the circle is just touching another circle
                c->setRadius(d->getRadius() - sqrt(pow(c->getX() - d->getX(),2) + pow(c->getY() - d->getY(),2)));
                c->setRadius(0);
                std::cout << "Setting radius to zero" << std::endl;
                break;
            }
        }
        if(c->getRadius() + c->getX() > 1 || c->getX() - c->getRadius() < -1
           || c->getY() + c->getRadius() > 1 || c->getY() - c->getRadius() < -1){
            c->setRadius(0);
            std::cout << "Circle touching edge" << std::endl;
            std::cout << "Setting radius to zero" << std::endl;
        }
    }
    // after sorting unfit candidates to the end of deque, sort by radius
    std::sort(children.begin(), children.end(), compare);
}
void GeneticCircle::mate(){
    Circle* child1;
    Circle* child2;
    // get fittest children and combine their attributes
    std::cout << "mating" << std::endl;
    int swap = 0;
    double temp = 0;
    // Get rid of the weakest children to make room
    for(int i = children.size()/4 - 1; i < children.size(); i++){
        children.pop_back();
    }
    int size = children.size()/2;
    for(int i = 0; i < size; i++){
        // randomize for each attribute with 50% probability
        child1 = new Circle(*children.at(i*2));
        child2 = new Circle(*children.at(i*2+1));
        for(int j = 0; j < 3; j++){
            swap = rand()%2;
            switch(j){
                case 0:
                    if(swap == 1){
                        std::cout << "Swapping X of children " << i*2
                        << " and " << i*2 + 1 << ":\t" << children.at(i*2)->getX()
                        << "\t" << children.at(i*2+1)->getX() << std:: endl;
                        temp = children.at(i*2)->getX();
                        child1->setX(children.at(i*2+1)->getX());
                        child2->setX(temp);
                    }
                    break;
                case 1:
                    if(swap == 1){
                        std::cout << "Swapping Y of children " << i*2
                        << " and " << i*2 + 1 << ":\t" << children.at(i*2)->getY()
                        << "\t" << children.at(i*2+1)->getY() << std:: endl;
                        temp = children.at(i*2)->getY();
                        children.at(i*2)->setY(children.at(i*2+1)->getY());
                        children.at(i*2+1)->setY(temp);
                        child1->setY(children.at(i*2+1)->getY());
                        child2->setY(temp);
                    }
                    break;
                case 2:
                    if(swap == 1){
                        std::cout << "Swapping Radius of children " << i*2
                        << " and " << i*2 + 1 << ":\t" << children.at(i*2)->getRadius()
                        << "\t" << children.at(i*2+1)->getRadius() << std:: endl;
                        temp = children.at(i*2)->getRadius();
                        children.at(i*2)->setRadius(children.at(i*2+1)->getRadius());
                        children.at(i*2+1)->setRadius(temp);
                        child1->setRadius(children.at(i*2+1)->getRadius());
                        child2->setRadius(temp);
                    }
                    break;
                default:
                    // oh god something went wrong;
                    std::cout << "something is wrong" << std::endl;
                    break;
            }
        }
        children.push_back(child1);
        children.push_back(child2);
    }
}
Circle* GeneticCircle::generate(){
    Circle* winner = new Circle();
    for(int i = 0; i < gen; i++){
        std::cout << "-----------GENERATION " << i << "--------------" << std::endl;
        morph();
        eval();
        //mate();
        if(children.size() > 0){
            if(children.at(0)->getRadius() > best->getRadius()){
                best->setX(children.at(0)->getX());
                best->setY(children.at(0)->getY());
                best->setRadius(children.at(0)->getRadius());
            }
            else{
                children.at(0)->setX(best->getX());
                children.at(0)->setY(best->getY());
                children.at(0)->setRadius(best->getRadius());
            }
            std::cout << "Child stats" << std::endl;
            std::cout << "X:\t" << best->getX() << std::endl;
            std::cout << "Y:\t" << best->getY()<< std::endl;
            std::cout << "RADIUS:\t" << best->getRadius() << std::endl;
        }
        else{
        }
        if(best->getRadius() > 0.4)
            break;
    }
    std::cout << "Child stats" << std::endl;
    std::cout << "X:\t" << best->getX() << std::endl;
    std::cout << "Y:\t" << best->getY()<< std::endl;
    std::cout << "RADIUS:\t" << best->getRadius() << std::endl;
    std::cout << "num Children:\t" << children.size() << std::endl;
    return best;
}
