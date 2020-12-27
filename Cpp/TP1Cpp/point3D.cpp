//  Answered and completed by Anh Vu Nguyen
#include "point3D.h"

point3D::point3D():point2D(),z(0.0){}

point3D::point3D(const point3D &p2){
    x = p2.x;
    y = p2.y;
    z = p2.z;
}

point3D::point3D(double a, double b, double c):point2D(a,b),z(c){}

void point3D::print()
{
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
}

point3D & point3D::operator= (const point3D & p2){
    (*this).x = p2.x;
    (*this).y = p2.y;
    (*this).z = p2.z;
    return *this;
}

/** @brief Surcharge de l'opérateur +=.
 */
point3D& point3D::operator+=( const point3D& p2 ){
    (*this).x += p2.x;
    (*this).y += p2.y;
    (*this).z += p2.z;
    return *this;
}

/** @brief Surcharge de l'opérateur ==.
 */
bool point3D::operator==( const point3D& p2 ){
    if(((*this).x == p2.x) && ((*this).y == p2.y) && ((*this).z == p2.z)){
        return 1;
    }else{
        return 0;
    }
}

point3D::~point3D()
{
    cout << "point3D object destroyed." << endl;
}
