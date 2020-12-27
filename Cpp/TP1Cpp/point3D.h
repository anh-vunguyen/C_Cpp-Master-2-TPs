//  Answered and completed by Anh Vu Nguyen
#ifndef POINT3D_H
#define POINT3D_H

#include "point2D.h"

using namespace std;
class point3D : public point2D
{
public:
    point3D();
    point3D(const point3D &p2);
    point3D(double a, double b, double c);
    
    void print();
    ~point3D();
    
    
    /** méthodes à implémenter **/
    
    
    point3D & operator= (const point3D & p2);
    
    /** @brief Surcharge de l'opérateur +=.
     */
    
    point3D& operator+=( const point3D& p2 );
    
    /** @brief Surcharge de l'opérateur ==.
     */
    bool operator==( const point3D& p2 );
    
    
    /**   ------------------------------  **/
    
    friend  ostream& operator<<(ostream &stream, const point3D &p2)
    {
        return stream<<"Point "<<p2.x<<","<<p2.y<<","<<p2.z<<endl;
    }
    
    
protected:
    double z;
    
private:
};

#endif // POINT3D_H
