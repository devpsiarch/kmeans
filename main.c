#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <stdarg.h>

#define ASSERT_ALLOC(ptr) if(!result){                                      \
                        perror("failed to allocated memory for VectorR\n"); \
                        exit(0);                                            \
                        }                                                   \

/* i just had this though of this 'thing'*/
typedef struct TensorR TensorR;
struct TensorR {
    TensorR* values;
    size_t dimension;
};
TensorR* init_tensorR(unsigned int depth,...){
    (void)depth;
    return NULL;
}
/* i need to think more about the above */
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

/* init a VectorR with some values in verodic fasion , if dimention exeeds 
 * it ignores the rest , if they are less it also ignores (junk values) */
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
/* sets all values of said VectorR to 0 very usefull mind you...*/
void zeroVectorR(VectorR*const x){
    assert(x != NULL);
    assert(x->dimension != 0);
    for(size_t i = 0 ; i < x->dimension ; i++){
        x->values[i] = 0.f;
    }
}
/* frees a single VectorR and its content*/
void clean_VectorR(VectorR*const x){
    free(x->values);
    free(x);
}
/* copies a VectorR from anther*/ 
void VectorRcpy(VectorR*const dst,VectorR*const src){
    assert(src != NULL);
    assert(src->dimension == dst->dimension);
    for(size_t i = 0 ; i < dst->dimension ; i++){
        dst->values[i] = src->values[i];
    }
}
/* frees a array of VectorR */
void clean_bunch_VectorR(VectorR*const arr[],size_t n){
    for(size_t i = 0 ; i < n ; ++i){
        clean_VectorR(arr[i]);
    }
}
/* Gets distance of two points from any dimension */
double distanceR(const VectorR* a,const VectorR* b){
    assert(a->dimension == b->dimension);
    double sum = 0;
    for(size_t i = 0 ; i < a->dimension ; i++){
        sum += (a->values[i]-b->values[i])*(a->values[i]-b->values[i]);
    }
    return sqrt(sum);
}
/* prints a VectorR in the format (x1,...,xn)*/
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
/*Returns true of an array of a vectors are from the same size*/
bool validateVectorR(VectorR*const dataset[],size_t n,size_t dim){
    for(size_t i = 0 ; i < n ; i++){
        if(dataset[i]->dimension != dim) return false;
    }
    return true;
}
/* add up two matrices , perfomrs '+=' */
void addupcumVectorR(VectorR*const dst,VectorR*const src){
    assert(dst != NULL);
    assert(dst->dimension != 0);
    assert(dst->dimension == src->dimension);
    for(size_t i = 0 ; i < src->dimension ; i++){
        dst->values[i] += src->values[i];
    }
}
/* scales a VectorR by some scaler 'double' changes are applied to the vector itself*/
void scalVectorR(VectorR* const dst,double scaler){
    assert(dst != NULL);
    assert(dst->dimension != 0);
    for(size_t i = 0 ; i < dst->dimension ; i++){
        dst->values[i] *= scaler;
    }
}
/*Kmeans for any 'stable' dataset of the same dimension*/
void KmeansR(VectorR* dataset[],size_t n,size_t k){
    // assert that the dataset are of the same dimension
    assert(dataset != NULL);
    size_t dim = dataset[0]->dimension;
    assert(validateVectorR(dataset,n,dim));
    // create centroids as array of vectors (multi dimension).
    VectorR* centroids = malloc(sizeof(VectorR)*k);
    // init the dimentions of the centroids since they are not
    for(size_t i = 0 ; i < k; i++){
        centroids[i].values = malloc(sizeof(double) * dim);
        centroids[i].dimension = dim;
    }
    // init values to centroids
    for(size_t i = 0 ; i < k ; i++){
        VectorRcpy(&centroids[i],dataset[rand()%n]);
    }
    // iterating thought the times (before convergence).
    for(size_t iter = 0 ; iter < iterations ; iter++){
        /* ASSIGNEMENT STEP*/
        // for all points in the dataset
        for(size_t p = 0 ; p < n ; p++){
            double min_distance = FLT_MAX;
            size_t index_of_least_distance_centroid = 0;
            // for all centroids
            for(size_t c = 0 ; c < k ; c++){
                double distance_to_this_centroid = distanceR(&centroids[c],dataset[p]);
                if(distance_to_this_centroid < min_distance){
                    index_of_least_distance_centroid = c;
                    min_distance = distance_to_this_centroid;
                }
            }
            // assinging the centroid to the least distance one
            dataset[p]->centroid = index_of_least_distance_centroid;
        }
        /* UPDATE STEP */
        // getting the mean for each centroid
        for(size_t c = 0 ; c < k ; c++){
            VectorR* sum = init_VectorR(dim,0);
            zeroVectorR(sum);
            size_t count = 0;
            for(size_t p = 0 ; p < n ; p++){
                if(dataset[p]->centroid == c){
                    // add up the vectors in (as you do in math)
                    addupcumVectorR(sum,dataset[p]);
                    count ++;
                }
            }
            if (count > 0) {
                // scale the sum (new = 1/count * sum)
                scalVectorR(sum,(1.0f/count));
                VectorRcpy(sum,&centroids[c]); 
            } else {
                // Reinitialize or handle the empty cluster appropriately.
                VectorRcpy(&centroids[c],dataset[rand()%n]);
            }
            clean_VectorR(sum);
        }
    }
    clean_VectorR(centroids);
}

typedef struct point point;

float distance(float a,float b){
    return fabsf(b-a);
}

struct point{
    float value;
    // this is the index to which cluster 
    // a data belongs to
    size_t centroid;
};

void kmeans(point* data,size_t n,size_t k){
    assert(k <= n);
    // init the clusters randomly from the data
    float* centroids = (float*)malloc(sizeof(float)*k);
    for(size_t i = 0 ; i < k ; i++){
        centroids[i] = (float)data[rand()%n].value;
    } 
    // kmeans begins here
    // how many times we iterate thought tht proccess
    for(int iter = 0 ; iter < iterations ; ++iter){ 
        //printf("[iteration : %d]\n",iter);
        /* ASSIGNEMENT STEP */
        // go though all points (aka data)
        for(size_t p = 0 ; p < n ; p++){
            float distances_to_centroids[k];
            float min_distance = FLT_MAX;
            size_t index = 0;
            // finding the min distance for point 'p'
            for(size_t c = 0 ; c < k ; c++){
                distances_to_centroids[c] = distance(data[p].value,(float)centroids[c]);
                if(distances_to_centroids[c] < min_distance){
                    index = c;
                    min_distance = distances_to_centroids[c];
                }
            }
            // assinging said point 'p' with centroid 'c'
            data[p].centroid = index;
        }
        /* UPDATE STEP */
        // new centroid is the mean of the points in it 
        // new_centroid = 1/number_of_points_in*(sum(all_points_in))
        for(size_t c = 0 ; c < k ; c++){
            float sum = 0;
            size_t count = 0;
            for(size_t p = 0 ; p < n ; ++p){
                if(data[p].centroid == c){
                    sum += data[p].value;
                    count++;    
                }
            }
            if (count > 0) {
                centroids[c] = (1.0f / count) * sum;
            } else {
                // Reinitialize or handle the empty cluster appropriately.
                centroids[c] = data[rand() % n].value;
            }
        }
    }
    free(centroids);
}
void print_data(point* points,size_t n){
    for(size_t i = 0 ; i < n ; ++i){
        printf("(%f:%zu)\n",points[i].value,points[i].centroid);
    }
}
int main(void){
    srand(time(0));
    size_t data_size = 8;

    VectorR* test[8];
    test[0] = init_VectorR(2, -100.f, -20.f);
    test[1] = init_VectorR(2, -2.5f, -50.f);
    test[2] = init_VectorR(2, 5.f, 30.f);
    test[3] = init_VectorR(2, 4.f, 2.f);
    test[4] = init_VectorR(2, 5.2f, 31.f);
    test[5] = init_VectorR(2, 4.1f, 3.f);
    test[6] = init_VectorR(2, -3.f, -49.f);
    test[7] = init_VectorR(2, -99.f, -19.5f); 

    for (size_t i = 0 ; i < data_size;++i) {
        printVectorR(test[i]);
    }
    printf("---------------------------\n");
    KmeansR(test,data_size,3);
    for (size_t i = 0 ; i < data_size;++i) {
        printVectorR(test[i]);
    }
    clean_bunch_VectorR(test,data_size);
    return 0;
    // point dataset[5] = {
    //     {150,0},
    //     {200,0},
    //     {250,0},
    //     {-570,0},
    //     {-600,0}
    // };
    // print_data(&dataset,5);
    // printf("-------------------------------\n");
    // kmeans(dataset,5,2);
    // print_data(&dataset,5);
    return 0;
}
