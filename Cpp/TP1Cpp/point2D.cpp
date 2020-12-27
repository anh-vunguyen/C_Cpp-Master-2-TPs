//
//  point2D.cpp
//  TP1C++
//  Answered and completed by Anh Vu Nguyen
//

#include "point2D.h"
#include <math.h>
using namespace std;

// Constructeur
point2D::point2D(){}

point2D::point2D(double a, double b){
    x = a;
    y = b;
}

// Norme
double point2D::CalculeNorme(){
    return sqrt((x*x) + (y*y));
}

// Afficheur
void point2D::print(){
    cout << "x: " << x << ", y: " << y << endl;
}

// Setters
double point2D::get_x(){
    return x;
}
double point2D::get_y(){
    return y;
}

// Setters
void point2D::set_x(double a){
    x = a;
}
void point2D::set_y(double b){
    y = b;
}

// Operateur = (assignment)
point2D & point2D::operator=(const point2D &Px)
{
    (*this).x = Px.x;
    (*this).y = Px.y;
    return *this;
}

// Operateur += (l'increment)
point2D & point2D::operator+=(const point2D &Px)
{
    (*this).x += Px.x;
    (*this).y += Px.y;
    return *this;
}

// Operateur == (egal)
bool point2D::operator==(const point2D &Px)
{
    if(((*this).x == Px.x) && ((*this).y == Px.y)){
        return 1;
    }else{
        return 0;
    }
}

// Operateur != (different)
bool point2D::operator!=(const point2D &Px){
    if(((*this).x == Px.x) && ((*this).y == Px.y)){
        return 0;
    }else{
        return 1;
    }
}

// Operateur + (addition)
point2D point2D::operator+(const point2D &Px){
    point2D res;
    res.x = x + Px.x;
    res.y = y + Px.y;
    return res;
}

// Destructeur
point2D::~point2D()
{
    //cout << "Object Destroyed" << endl;
}

