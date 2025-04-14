#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <float.h>

struct multi_dem_point {
    size_t dimension;
    // should be any type here
    float* point;
};

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

static const int iterations = 500;
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
    point dataset[5] = {
        {150,0},
        {200,0},
        {250,0},
        {-570,0},
        {-600,0}
    };
    print_data(&dataset,5);
    printf("-------------------------------\n");
    kmeans(dataset,5,2);
    print_data(&dataset,5);
    return 0;
}
