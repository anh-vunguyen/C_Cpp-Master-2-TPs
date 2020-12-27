//  Answered and completed by Anh Vu Nguyen
#include <iostream>
#include "Image2D.hpp"
//TP4 c++
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

int main()
{
    /** Test RGB **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1, true);
    cout << "-----Test-----" << endl;
    C->EnregistrerImage("imageTestGray.bmp");
    cout << "-----End Test-----" << endl;*/

    /** Test RGB **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1, true);
    cout << "-----Test-----" << endl;
    C->EnregistrerImageRGB("imageTest333.bmp");
    cout << "-----End Test-----" << endl;*/

    /** Test histogramme **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1);
    cout << "-----Test histogramme-----" << endl;
    int* h;
    h = C->hist();
    for(int i = 0; i < 256; i++ ) {
      cout << i << " : " << h[i] << endl;
    }
    cout << "-----End Test histogramme-----" << endl;*/

    /** Test find_peaks **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1);
    cout << "-----Test find_peaks-----" << endl;
    int* h;
    h = C->hist();
    vector<int> res = C->find_peaks(h);
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << endl;
    cout << "-----End Test find_peaks-----" << endl;*/

    /** Test segmentation_avec_histogramme **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1);
    cout << "-----Test segmentation_avec_histogramme-----" << endl;
    C->segmentation_avec_histogramme();
    cout << "-----End Test segmentation_avec_histogramme-----" << endl;*/

    /** Test segmentation_avec_histogrammeRGB **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1, true);
    cout << "-----Test segmentation_avec_histogrammeRGB-----" << endl;
    C->segmentation_avec_histogrammeRGB();
    cout << "-----End Test segmentation_avec_histogrammeRGB-----" << endl;*/

    /** Test segmentation_ligne **//*
    char* f2="imageTest.bmp";
    Image2D* C = new Image2D(f2, 1, 1);
    cout << "-----Test segmentation_ligne-----" << endl;
    C->segmentation_ligne();
    cout << "-----End Test segmentation_ligne-----" << endl;*/

    /** Test Image2D with padding **//*
    char* f2="linescolor.bmp";
    Image2D* C = new Image2D(f2, 1, 1, true, true);
    cout << "-----Test-----" << endl;
    C->EnregistrerImage("linescolorGray.bmp", true);
    cout << "-----End Test-----" << endl;*/

    return 0;
}
