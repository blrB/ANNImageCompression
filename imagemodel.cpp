#include <iostream>
#include <CImg.h>
#include <vector>
#include <armadillo>
#include <cmath>
#include <float.h>

#include "imagemodel.h"
#include "rectanglemodel.h"

using namespace std;
using namespace cimg_library;
using namespace arma;

ImageModel::ImageModel(char const * patch){
    CImg<unsigned char> src(patch);
    initANN();
    imageWidth = src.width();
    imageHight = src.height();
    for (int indexW = 0; indexW < imageWidth; indexW +=m){
        for (int indexH = 0; indexH < imageHight; indexH +=n){
            RectangleModel bufferRectangle(indexW,indexH);
            for (int i = indexW; i < indexW + m; i++){
                for (int j = indexH; j < indexH + n; j++) {
                    if (i < imageWidth && j < imageHight){
                        bufferRectangle.addElement(convertColor((int)src(i,j,0,0)));
                        bufferRectangle.addElement(convertColor((int)src(i,j,0,1)));
                        bufferRectangle.addElement(convertColor((int)src(i,j,0,2)));
                    } else {
                        bufferRectangle.addElement(-1);
                        bufferRectangle.addElement(-1);
                        bufferRectangle.addElement(-1);
                    }
                }
            }
            bufferRectangle.createMatrixX();
            rectangleModelList.push_back(bufferRectangle);
        }
    }
    L = rectangleModelList.size();
    nmRGB = n * m * RGB;
    createWeightMatrix();
    run();
}

void ImageModel::initANN(){
    cout << "Enter hight of rectangle(n):" << endl;
    cin >> n;
    cout << "Enter width of rectangle(m):" << endl;
    cin >> m;
    cout << "Enter number of neuron for second layer(p):" << endl;
    cin >> p;
    cout << "Enter error degree(e):" << endl;
    cin >> e;
    cout << "Enter step(a) (Enter 0 for adaptive learnin step):" << endl;
    cin >> a;
}

void ImageModel::run(){
    double step;
    double step_;
    double E;
    //normalizeMatrixs(); // uncomment if necessary normalization
    int iteration = 0;
    do {
        E = 0;
        for (int index = 0; index < L; index++){
            mat X = rectangleModelList[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            if (a){
                step_ = step = a;
            } else {
                step_ = adaptiveLearningStep(Y);
                step = adaptiveLearningStep(X);
            }
            W = W - (step * X.t() * deltaX * W_.t());
            W_ = W_ - (step_ * Y.t() * deltaX);
            //normalizeMatrixs(); // uncomment if necessary normalization
        }
        // count error after correction
        for (int index = 0; index < L; index++){
            mat X = rectangleModelList[index].getX();
            mat Y = X * W;
            mat X_ = Y * W_;
            mat deltaX = X_ - X;
            E += getErrorDegree(deltaX);
        }
        iteration++;
        cout << "Iteration: " << iteration << " Error: " << E << endl;
    } while (E > e);
    double z = (1.0 * n * m * RGB * L) / ((n * m * RGB + L) * p + 2);
    cout << "Z = " << z << endl;;
}

void ImageModel::normalizeMatrixs(){
    normalizeMatrix(W);
    normalizeMatrix(W_);
}

void ImageModel::normalizeMatrix(mat matrix){
    for (unsigned int i = 0; i < matrix.n_cols; i++) {
        double sum = 0;
        for (unsigned int j = 0; j < matrix.n_rows; j++) {
            sum += pow(matrix(j, i), 2);
        }
        sum = sqrt(sum);
        for (unsigned int j = 0; j < matrix.n_rows; j++) {
            matrix(j, i) = matrix(j, i) / sum;
        }
    }
}

double ImageModel::adaptiveLearningStep(mat matrix){
    int FACTOR = 10;
    mat temp = (matrix * matrix.t());
    return 1.0 / (temp(0,0) + FACTOR);
}

void ImageModel::createOutputImage(){
    CImg<float> image(imageWidth,imageHight,1,3,0);
    float color[3];
    for (int index = 0; index < L; index++){
        int startX = rectangleModelList[index].getStartX();
        int startY = rectangleModelList[index].getStartY();
        mat X = rectangleModelList[index].getX();
        mat Y = X * W;
        mat X_ = Y * W_;
        int pixel = 0;
        for (int i = startX; i < m + startX; i++) {
            for (int j = startY; j < n + startY; j++) {
                color[0] = convertRGBToOutput(X_(0, pixel++));
                color[1] = convertRGBToOutput(X_(0, pixel++));
                color[2] = convertRGBToOutput(X_(0, pixel++));
                if (i < imageWidth && j < imageHight){
                    image.draw_point(i,j,color);
                }
            }
        }
    }
    image.save("output.png");
}

int ImageModel::convertRGBToOutput(double color){
    double ans = (255 * (color + 1) / 2);
    if (ans < 0){
        ans = 0;
    }
    if (ans > 255){
        ans = 255;
    }
    return (int)ans;
}

double ImageModel::getErrorDegree(mat deltaX){
    double e=0;
    for (int i = 0; i < nmRGB; i++) {
        e += pow(deltaX(0, i), 2);
    }
    return e;
}

void ImageModel::createWeightMatrix(){
    srand (time(NULL));
    W = randu<mat>(nmRGB,p);
    for (int i = 0; i < nmRGB; i++){
        for (int j = 0; j < p; j++)
            W(i,j) = (((double)rand() / RAND_MAX)*2 - 1 )*0.1;;
    }
    W_ = W.t();
}

double ImageModel::convertColor(int color){
    return ((2.0 * color / 255) - 1);
}



