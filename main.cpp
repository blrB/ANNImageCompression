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
char const *srcImg = "../ANNImageCompression/256px-Lenna.png";

int main(){
    ImageModel model(srcImg);
    model.createOutputImage();
    return 0;
}

