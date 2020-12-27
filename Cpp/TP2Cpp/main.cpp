//  Answered and completed by Anh Vu Nguyen
#include <iostream>
#include "Image2D.hpp"
using namespace std;

int main()
{
    char* f2="lena24.bmp";
    Image2D C(f2,1,1);

    /** Test EnregistrerImage **//*
    cout << "-----Test EnregistrerImage-----" << endl;
    C.EnregistrerImage("lena_save.bmp");
    cout << "-----End Test EnregistrerImage-----" << endl;
    */

    /** Test Seuillage **//*
    cout << "-----Test Seuillage-----" << endl;
    int threshold = 100;
    C.seuillageImage(threshold);
    cout << "-----End Test Seuillage-----" << endl;
    */

    /** Test Masque **//*
    cout << "-----Test Masque-----" << endl;
    C.applyBinaryMask("mask.bmp", "lena_masque.bmp");
    cout << "-----End Test Masque-----" << endl;
    */

    /** Test pixel_is_in_image **//*
    cout << "-----Test pixel_is_in_image-----" << endl;
    bool test = C.pixel_is_in_image(511,511);
    cout << test << endl;
    cout << "-----End Test pixel_is_in_image-----" << endl;
    */

    /** Test interpolation_nn_x **//*
    cout << "-----Test interpolation_nn_x-----" << endl;
    int test = C.interpolation_nn_x(1.4);
    cout << test << endl;
    cout << "-----End Test interpolation_nn_x-----" << endl;
    */

    /** Test interpolation_nn_y **//*
    cout << "-----Test interpolation_nn_y-----" << endl;
    int test = C.interpolation_nn_y(1.6);
    cout << test << endl;
    cout << "-----End Test interpolation_nn_y-----" << endl;
    */

    /** Test translation 1 **//*
    cout << "-----Test translation 1-----" << endl;
    C.translation(50, 50, "transout.bmp");
    cout << "-----End Test translation 1-----" << endl;
    */

    /** Test translation 2 **//*
    cout << "-----Test translation 2-----" << endl;
    Image2D Sout = C.translation(50, 100);
    Sout.EnregistrerImage("sout.bmp");
    cout << "-----End Test translation 2-----" << endl;
    */

    /** Test rotation 1 **//*
    cout << "-----Test rotation 1-----" << endl;
    C.rotation(45, "rotout1.bmp");
    cout << "-----End rotation 1-----" << endl;
    */

    /** Test rotation 2 **//*
    cout << "-----Test rotation 2-----" << endl;
    Image2D Sout = C.rotation(90);
    Sout.EnregistrerImage("rotout2.bmp");
    cout << "-----End rotation 2-----" << endl;
    */

    return 0;
}
