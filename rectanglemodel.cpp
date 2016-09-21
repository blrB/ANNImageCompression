#include "rectanglemodel.h"
#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

RectangleModel::RectangleModel(int startX, int startY){
    this->startX = startX;
    this->startY = startY;
}

void RectangleModel::createMatrixX(){
    X = mat(vectorX).t();
}

void RectangleModel::addElement(double newElement){
    vectorX.push_back(newElement);
}

int RectangleModel::getStartX(){
    return startX;
}

void RectangleModel::setStartX(int startX){
    this->startX = startX;
}

int RectangleModel::getStartY(){
    return startY;
}

void RectangleModel::setStartY(int startY){
    this->startY = startY;
}

vector<double> RectangleModel::getVectorX(){
    return vectorX;
}

void RectangleModel::setVectorX(vector<double> vectorX){
    this->vectorX = vectorX;
}

mat RectangleModel::getX(){
    return X;
}

void RectangleModel::setX(mat X){
    this->X = X;
}

