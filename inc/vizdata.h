// this will provide a lot of ways to visulize the dataset
// for now it will handle only 2D datasets more up to 4D are gonna be provided
#ifndef VIZDATA_H
#define VIZDATA_H
// header part
#include <raylib.h> 
#include "./vectorr.h"
#define DOT_RADIOUS 10 
static const Color COLOR_WHEEL[4] = {RED,BLUE,GREEN,YELLOW};

#define SELECT_COLOR(centroid) (centroid < 4) ? COLOR_WHEEL[centroid] : BLACK

void DrawDataset2D(VectorR* dataset[],size_t n);

#endif
#ifndef VIZDATA_IMPLI 
#define VIZDATA_IMPLI
// C Part
//
void DrawDataset2D(VectorR* dataset[],size_t n){
    assert(dataset != NULL);
    assert(validateVectorR(dataset,n,2));
    for(size_t i = 0 ; i < n ; i++){
       
       DrawCircle(dataset[i]->values[0],dataset[i]->values[1],DOT_RADIOUS,SELECT_COLOR(dataset[i]->centroid)); 
    }
}

#endif
