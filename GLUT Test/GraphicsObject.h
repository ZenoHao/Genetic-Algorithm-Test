//
//  GraphicsObject.h
//  Genetic Algorithm Test
//
//  Created by Zeno Hao on 10/15/14.
//
//

#ifndef __Genetic_Algorithm_Test__GraphicsObject__
#define __Genetic_Algorithm_Test__GraphicsObject__

#include <stdio.h>

class GraphicsObject{
private:
public:
    GraphicsObject();
    virtual void draw() = 0;
    virtual ~GraphicsObject();
};

#endif /* defined(__Genetic_Algorithm_Test__GraphicsObject__) */
