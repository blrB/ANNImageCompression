#ifndef RECTANGLEMODEL_H
#define RECTANGLEMODEL_H

#include <armadillo>
#include <vector>

using namespace std;
using namespace arma;

class RectangleModel
{
private:
    int startX;
    int startY;
    vector<double> vectorX;
    mat X;
public:
    RectangleModel(int startX, int startY);
    void createMatrixX();
    void addElement(double newElement);
    int getStartX();
    void setStartX(int start);
    int getStartY();
    void setStartY(int start);
    vector<double> getVectorX();
    void setVectorX(vector<double> vector);
    mat getX();
    void setX(mat x);
};

#endif // RECTANGLEMODEL_H
