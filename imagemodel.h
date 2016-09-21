#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <iostream>
#include <CImg.h>
#include <vector>
#include <armadillo>

#include "rectanglemodel.h"

using namespace std;
using namespace arma;

class ImageModel
{
private:
    int RGB = 3;
    int imageWidth;
    int imageHight;
    int n;
    int m;
    int p;
    double e;
    int L;
    int nmRGB;
    double a;
    vector<RectangleModel> rectangleModelList;
    mat W;
    mat W_;
public:
    ImageModel(char const * patch);
    void initANN();
    void run();
    void createOutputImage();
    int convertRGBToOutput(double rgb);
    double getErrorDegree(mat deltaX);
    void createWeightMatrix();
    double convertColor(int color);
    void normalizeMatrix(mat matrix);
    void normalizeMatrixs();
    double adaptiveLearningStep(mat matrix);
};

#endif // IMAGEMODEL_H
