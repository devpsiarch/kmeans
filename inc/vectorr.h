// The headers part of the code
#ifndef VECTORR_H
#define VECTORR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdarg.h>

// use to assert pointer returned by malloc is not NULL
#define ASSERT_ALLOC(ptr) if(!result){                                      \
                        perror("failed to allocated memory for VectorR\n"); \
                        exit(0);                                            \
                        }                                                   \

static const int iterations = 10000;
// UNSIGNED_CENTROID is the max size_t that signifies that it is not assigned 
// to any centroid , mostly safe .... 
#define UNSIGNED_CENTROID (size_t)-1
/* I want to make an abtract data */
typedef struct VectorR VectorR;
struct VectorR {
    double* values;
    size_t dimension;
    size_t centroid;
};
/*
 * values describe the values that the vector holds here its from |R
 * Dimension describes the size and how many specialties does a 'point' has
 * */

// IMPLIMENED functionlity

/* init a VectorR with some values in verodic fasion , if dimention exeeds 
 * it ignores the rest , if they are less it also ignores (junk values) */
VectorR* init_VectorR(const unsigned int dim,...);
/* sets all values of said VectorR to 0 very usefull mind you...*/
void zeroVectorR(VectorR*const x);
/* frees a single VectorR and its content*/
void clean_VectorR(VectorR*const x);
/* copies a VectorR from anther*/ 
void VectorRcpy(VectorR*const dst,VectorR*const src);
/* frees a array of VectorR */
void clean_bunch_VectorR(VectorR*const arr[],size_t n);
/* Gets distance of two points from any dimension */
double distanceR(const VectorR* a,const VectorR* b);
/* prints a VectorR in the format (x1,...,xn)*/
void printVectorR(const VectorR*const x);
/*Returns true of an array of a vectors are from the same size*/
bool validateVectorR(VectorR*const dataset[],size_t n,size_t dim);
/* add up two matrices , perfomrs '+=' */
void addupcumVectorR(VectorR*const dst,VectorR*const src);
/* scales a VectorR by some scaler 'double' changes are applied to the vector itself*/
void scalVectorR(VectorR* const dst,double scaler);

#endif 

// The C part of the code
#ifndef VECTORR_IMPLI
#define VECTORR_IMPLI

// here will provide the implimentation for said functionlity
VectorR* init_VectorR(const unsigned int dim,...){
    VectorR* result = (VectorR*)malloc(sizeof(VectorR));
    ASSERT_ALLOC(result);
    result->values = malloc(sizeof(double)*dim);
    ASSERT_ALLOC(result->values);
    result->dimension = dim;
    result->centroid = UNSIGNED_CENTROID;
    
    va_list args;
    va_start(args,dim);
    for(size_t i = 0 ; i < dim ;i++){
        double next = va_arg(args,double);
        result->values[i] = next;
    }
    va_end(args);
    return result;
}
void zeroVectorR(VectorR*const x){
    assert(x != NULL);
    assert(x->dimension != 0);
    for(size_t i = 0 ; i < x->dimension ; i++){
        x->values[i] = 0.f;
    }
}
void clean_VectorR(VectorR*const x){
    free(x->values);
    free(x);
}
void VectorRcpy(VectorR*const dst,VectorR*const src){
    assert(src != NULL);
    assert(src->dimension == dst->dimension);
    for(size_t i = 0 ; i < dst->dimension ; i++){
        dst->values[i] = src->values[i];
    }
}
void clean_bunch_VectorR(VectorR*const arr[],size_t n){
    for(size_t i = 0 ; i < n ; ++i){
        clean_VectorR(arr[i]);
    }
}
double distanceR(const VectorR* a,const VectorR* b){
    assert(a->dimension == b->dimension);
    double sum = 0;
    for(size_t i = 0 ; i < a->dimension ; i++){
        sum += (a->values[i]-b->values[i])*(a->values[i]-b->values[i]);
    }
    return sqrt(sum);
}
void printVectorR(const VectorR*const x){
    printf("dim (%zu) ",x->dimension);
    if(x->centroid == UNSIGNED_CENTROID) printf("cen (unsigned) [");
    else printf("cen (%zu) [",x->centroid);
    for(size_t i = 0 ; i < x->dimension ;++i){
        printf("%lf",x->values[i]);
        if(i != x->dimension-1) printf(",");
    }
    printf("]\n");
}
bool validateVectorR(VectorR*const dataset[],size_t n,size_t dim){
    for(size_t i = 0 ; i < n ; i++){
        if(dataset[i]->dimension != dim) return false;
    }
    return true;
}
void addupcumVectorR(VectorR*const dst,VectorR*const src){
    assert(dst != NULL);
    assert(dst->dimension != 0);
    assert(dst->dimension == src->dimension);
    for(size_t i = 0 ; i < src->dimension ; i++){
        dst->values[i] += src->values[i];
    }
}
void scalVectorR(VectorR* const dst,double scaler){
    assert(dst != NULL);
    assert(dst->dimension != 0);
    for(size_t i = 0 ; i < dst->dimension ; i++){
        dst->values[i] *= scaler;
    }
}


#endif 
