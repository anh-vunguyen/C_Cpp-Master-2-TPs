//  Answered and completed by Anh Vu Nguyen
#include <iostream>
#include "Image2D.hpp"
#include <vector>
#include <algorithm>
#include <string>
//TP5 c++
#include "recalage.hpp"

using namespace std;

int main()
{
    /** Test RGB **//*
    char* f2="lena24.bmp";
    Image2D* C = new Image2D(f2, 1, 1);
    cout << "-----Test-----" << endl;
    C->EnregistrerImage("lena24Gray.bmp");
    cout << "-----End Test-----" << endl;
    */

    /** Test SSD **//*
    char* fimg1="lena24.bmp";
    Image2D* img1 = new Image2D(fimg1, 1, 1);
    char* fimg2="test.bmp";
    Image2D* img2 = new Image2D(fimg2, 1, 1);
    cout << "-----Test-----" << endl;
    cout << "la somme des differences pixel a pixel" << endl;
    cout << "SSD = " << SSD(*img1, *img2) << endl;
    cout << "-----End Test-----" << endl;*/


    /** Test joint_histogram **//*
    char* fimg1="lena24.bmp";
    Image2D* img1 = new Image2D(fimg1, 1, 1);
    char* fimg2="lena24.bmp";
    Image2D* img2 = new Image2D(fimg2, 1, 1);
    cout << "-----Test joint_histogram-----" << endl;
    int** test_jh;
    test_jh = joint_histogram(*img1, *img2);
    int test_sum = 0;
    for(int i=0; i<256; i++){
        cout << test_jh[i][i] << " ";
        test_sum += test_jh[i][i];
    }
    cout << "\n" << test_sum << endl;
    cout << "-----End Test-----" << endl;
    */

    /** Test EntropieConjointe **//*
    char* fimg1="lena24.bmp";
    Image2D* img1 = new Image2D(fimg1, 1, 1);
    char* fimg2="lena24.bmp";
    Image2D* img2 = new Image2D(fimg2, 1, 1);
    cout << "-----Test EntropieConjointe-----" << endl;
    double test_H;
    test_H = EntropieConjointe(*img1, *img2);
    cout << test_H << endl;
    cout << "-----End Test-----" << endl;
    */

    /** Test mutual_information **//*
    cout << "-----Test mutual_information -----" << endl;
    char* f1="lena24.bmp";
    Image2D* img = new Image2D(f1, 1, 1);
    char* f2="lena24ref.bmp";
    Image2D* imgref = new Image2D(f2, 1, 1);
    double MI = 0;
    MI = mutual_information(img, imgref);
    cout << " Mutual Information MI = " << MI << endl;
    cout << "-----End Test mutual_information -----" << endl;*/

    /** Test inverse matrix **//*
    double A[3][3] = { {1.0, 2.0, -1.0},
                    {-2.0, 0.0, 1.0},
                    {1.0, -1.0, 0.0}};
    cout << determinant(A, 3) << endl;
    double inv[3][3];
    if (inverse(A, inv)){
         for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
                cout << A[i][j] << " ";
                cout << endl;
        }
        cout << "-------------" <<  endl;
        for (int i=0; i<3; i++)
        {
            for (int j=0; j<3; j++)
                cout << inv[i][j] << " ";
                cout << endl;
        }
    }
    */

    /** Test rotation **//*
    cout << "-----Test rotation -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    rotation(img, 60.0);
    cout << "-----End Test rotation -----" << endl;*/



    /** Test identity **//*
    cout << "-----Test identity -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    identity(*img);
    cout << "-----End Test identity -----" << endl;
    */


    /** Test scaling **//*
    cout << "-----Test scaling -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    scaling(img, 4, 4);
    cout << "-----End Test scaling -----" << endl;
    */

    /** Test translation **//*
    cout << "-----Test translation -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    translation(img, 10, 20);
    cout << "-----End Test translation -----" << endl;
    */

    /** Test shear_vert **//*
    cout << "-----Test shear_vert -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    shear_vert(img, 0.5);
    cout << "-----End Test shear_vert -----" << endl;
    */

    /** Test shear_horiz **//*
    cout << "-----Test shear_horiz -----" << endl;
    char* f2="lena24.bmp";
    Image2D* img = new Image2D(f2, 1, 1);
    shear_horiz(img,0.5);
    cout << "-----End Test shear_horiz -----" << endl;
    */

    /** Test recalage **//*
    cout << "-----Test recalage -----" << endl;
    char* f1="lena24distorted.bmp";
    Image2D* img = new Image2D(f1, 1, 1);
    char* f2="lena24ref.bmp";
    Image2D* imgref = new Image2D(f2, 1, 1);
    recalage(img, imgref, 10.0);
    cout << "-----End Test recalage -----" << endl;
    */

    return 0;
}
