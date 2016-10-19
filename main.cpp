#include <iostream>
#include <CImg.h>
#include <vector>
#include <armadillo>

#define ARMA_DONT_USE_WRAPPER

#include "rectanglemodel.h"
#include "imagemodel.h"

using namespace std;
using namespace cimg_library;
using namespace arma;

// path to image
char const *srcImg;

int main(int argc , char *argv[]){
    if (argc != 2) {
        printf("Not correct argument\n");
        exit(1);
    }
    srcImg = strdup(argv[1]);
    ImageModel model(srcImg);
    model.run();
    model.createOutputImage();
    return 0;
}

