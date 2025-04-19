// this will only have the algorithms that do data mining 
#ifndef KMEANS_H
#define KMEANS_H
// the header part
#include "./vectorr.h"
/*Kmeans for any 'stable' dataset of the same dimension
 * created centroids and deleted them when done + used for 
 * work not to visulize*/
void KmeansR(VectorR* dataset[],size_t n,size_t k);
// when provided a array of centroirs, this will apply kmeans on said 
// dataset once
// mainly used to visulize data 
// expects values to be allocated too
void KmeansROnce(VectorR* dataset[],size_t n,size_t k,VectorR* centroids);

#endif
#ifndef KMEANS_IMPLI
#define KMEANS_IMPLI 
// the C part (implimentation)

void KmeansROnce(VectorR* dataset[],size_t n,size_t k,VectorR* centroids){
    // assert that the dataset are of the same dimension
    assert(dataset != NULL);
    size_t dim = dataset[0]->dimension;
    assert(validateVectorR(dataset,n,dim));
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
        // updating centriods
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
        KmeansROnce(dataset,n,k,centroids);
    }
    clean_VectorR(centroids);
}

#endif
