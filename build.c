#include <stdbool.h>
#include "ouroc.h"
#define OUROC_IMPLI

int main(int argc,char*argv[]){
    bool run = false;
    if(argc >= 2){
        if(strcmp(argv[1],"run") == 0) run = true;
    }
    Builder tester = {
        .bdir = NULL,
        .buffer_used = 0,
        .buffer_max = 256
    };
    initbuilder(&tester);

    tester.appendcc(&tester,"clang");
    tester.appendtarget(&tester,"kmeans");
    tester.appendsrcs(&tester,"main.c");

    tester.appendflags(&tester,"-Wall");
    tester.appendflags(&tester,"-Wextra");
    tester.appendflags(&tester,"-lraylib");
    tester.appendflags(&tester,"-lGL");
    tester.appendflags(&tester,"-lm");
    tester.appendflags(&tester,"-lpthread");
    tester.appendflags(&tester,"-ldl");
    tester.appendflags(&tester,"-lrt");
    tester.appendflags(&tester,"-lX11");
    tester.appendflags(&tester,"-o");

    tester.construct(&tester);
    SHOWCOMMAND(tester);
    tester.execute(&tester);
    tester.clean_up(&tester);
    
    if(run) system("./kmeans");
    
    return 0;
}
