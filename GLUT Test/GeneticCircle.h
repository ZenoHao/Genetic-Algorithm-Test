//
//  GeneticCircle.h
//  Genetic Algorithm Test
//
//  Created by Zeno Hao on 10/15/14.
//
//

#ifndef __Genetic_Algorithm_Test__GeneticCircle__
#define __Genetic_Algorithm_Test__GeneticCircle__

#include <stdio.h>
#include "Circle.h"
#include <vector>
#include <deque>

class GeneticCircle{
public:
    Circle* generate();
    ~GeneticCircle();
    GeneticCircle();
    GeneticCircle(int gen, std::vector<Circle*> circles);
private:
    int gen;
    std::vector<Circle*> circles;
    std::deque<Circle*> children;
    Circle* best;
    void morph();
    void eval();
    void mate();
};

#endif /* defined(__Genetic_Algorithm_Test__GeneticCircle__) */
