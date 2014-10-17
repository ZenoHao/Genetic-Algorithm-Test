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

int compare(Circle* i, Circle* j){return i->getRadius() < j->getRadius();}

GeneticCircle::GeneticCircle(){}
GeneticCircle::~GeneticCircle(){}
GeneticCircle::GeneticCircle(int gen, std::vector<Circle*> circles){
    // Deep copy. Not sure if necessary
    for(int i = 0; i < circles.size(); i ++){
        this->circles.push_back(new Circle(circles.at(i)->getX(),
                                           circles.at(i)->getY(),
                                           circles.at(i)->getRadius()));
    }
    this->gen = gen;
    srand(time(0));
    for(int i = 0; i < NUM_CHILD; i ++){
        children.push_back(new Circle((static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5),
                                      (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5),
                                      static_cast <float> (rand()) / static_cast <float> (RAND_MAX)));
    }
}

void GeneticCircle::morph(){
    std::cout << "mutating" << std::endl;
    srand(time(NULL));
    int num = 0;
    for(int i = 0; i < children.size(); i++){
        num = rand()%3 + 1;
        switch(num){
            case 1:
                std::cout << "Mutating X value of child " << i << std::endl;
                while(children.at(i)->getX() < -1 || children.at(i)->getX() > 1)
                    children.at(i)->setX(children.at(i)->getX() +
                                         (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5)/10.);
                break;
            case 2:
                std::cout << "Mutating Y value of child " << i << std::endl;
                while(children.at(i)->getY() < -1 || children.at(i)->getY() > 1)
                    children.at(i)->setY(children.at(i)->getY() +
                                         (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5)/10.);
                break;
            case 3:
                std::cout << "Mutating Radius value of child " << i << std::endl;
                while(children.at(i)->getRadius() < 0)
                    children.at(i)->setRadius(children.at(i)->getRadius() +
                                              (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5)/10.);
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
    std::deque<Circle*>temp = children;
    bool unfit = true;
    for(int i = 0; children.size() > 0; i ++)
        children.pop_front();
    std::cout << "Size is:\t" << children.size() << std::endl;
    for(int i = 0; i < temp.size(); i ++){
        unfit = false;
        // if the circle touches an existing circle, then push it to the end of deque
        // check this by comparing their straight line distance ot their radii
        // if combined radii greater than distance, then the circle is unfit.
        for(int j = 0; j < circles.size(); j++){
            if(temp.at(i)->getRadius() + circles.at(j)->getRadius() >
               sqrt(pow(temp.at(i)->getX() - circles.at(j)->getX(),2) +
                    pow(temp.at(i)->getY() - circles.at(j)->getY(),2))){
                   break;
               }
            else
                children.push_back(temp.at(i));
        }
    }
    std::cout << "Size is:\t" << children.size() << std::endl;
    for(int i = 0; temp.size() > 0; i ++)
        temp.pop_front();
    // after sorting unfit candidates to the end of deque, sort by radius
    std::sort(children.begin(), children.end(), compare);
}
void GeneticCircle::mate(){
    Circle* child1;
    Circle* child2;
    // get fittest children and combine their attributes
    std::cout << "mating" << std::endl;
    srand(time(0));
    int swap = 0;
    double temp = 0;
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
    for(int i = 0; i < gen; i ++){
        std::cout << "-----------GENERATION " << i << "--------------" << std::endl;
        morph();
        eval();
        mate();
        if(children.size() > 0){
            std::cout << "Child stats" << std::endl;
            std::cout << "X:\t" << children.at(0)->getX() << std::endl;
            std::cout << "Y:\t" << children.at(0)->getY()<< std::endl;
            std::cout << "RADIUS:\t" << children.at(0)->getRadius() << std::endl;
        }
        else{
        }
    }
    std::cout << "Child stats" << std::endl;
    std::cout << "X:\t" << children.at(0)->getX() << std::endl;
    std::cout << "Y:\t" << children.at(0)->getY()<< std::endl;
    std::cout << "RADIUS:\t" << children.at(0)->getRadius() << std::endl;
    std::cout << "num Children:\t" << children.size() << std::endl;
    return children.at(0);
}
