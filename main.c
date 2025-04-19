#include "./inc/vectorr.h"
#define VECTORR_IMPLI
#include "./inc/kmeans.h"
#define KMEANS_IMPLI


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
