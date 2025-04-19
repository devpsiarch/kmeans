#include "./inc/vectorr.h"
#define VECTORR_IMPLI
#include "./inc/kmeans.h"
#define KMEANS_IMPLI
#include "./inc/vizdata.h"
#define vizdata_IMPLI

#include <raylib.h>


int main(void){
    srand(time(0));
    size_t data_size = 20;


    VectorR* test[data_size];
    test[0] = init_VectorR(2, 750.00f,  316.66f);  // Right cluster (prev 700.0 → 750.0)
    test[1] = init_VectorR(2,  50.00f,   50.00f);  // Leftmost point (prev 103.06 → 50.0)
    test[2] = init_VectorR(2, 269.50f,  263.54f);  // Left cluster stretched (prev 111.22 → 269.50)
    test[3] = init_VectorR(2, 165.40f,  550.00f);  // Left cluster stretched (prev 107.35 → 165.40)
    test[4] = init_VectorR(2, 300.00f,  253.13f);  // Edge of left cluster (prev 112.35 → 300.0)
    test[5] = init_VectorR(2, 181.80f,  536.98f);  // Left cluster stretched (prev 107.96 → 181.80)
    test[6] = init_VectorR(2,  88.50f,   60.41f);  // Left cluster stretched (prev 104.49 → 88.50)
    test[7] = init_VectorR(2, 500.00f,  320.31f);  // Right cluster start (prev 693.88 → 500.0)
    test[8] = init_VectorR(2, 400.0f, 100.0f);   // Top-center
    test[9] = init_VectorR(2, 600.0f, 500.0f);   // Bottom-right
    test[10] = init_VectorR(2, 200.0f, 400.0f);  // Mid-left
    test[11] = init_VectorR(2, 700.0f, 100.0f);  // Top-right
    test[12] = init_VectorR(2, 100.0f, 300.0f);  // Left-middle
    test[13] = init_VectorR(2, 450.0f, 200.0f);  // Center-right
    test[14] = init_VectorR(2, 550.0f, 580.0f); // Far right bottom
    test[15] = init_VectorR(2, 250.0f, 150.0f);  // Mid-left top
    test[16] = init_VectorR(2, 350.0f, 450.0f);  // Center-bottom
    test[17] = init_VectorR(2, 650.0f, 300.0f);  // Right-middle
    test[18] = init_VectorR(2, 150.0f, 200.0f);  // Left-center
    test[19] = init_VectorR(2, 750.0f, 550.0f); // Far right bottom-corner    

    InitWindow(800,600,"Kmeans");

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawDataset2D(test,data_size);
        EndDrawing();
    }   
    CloseWindow(); 
    return 0;
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
