//  Answered and completed by Anh Vu Nguyen
#include <iostream>
#include "Image2D.hpp"
using namespace std;

int main()
{
    char* f2="lena24.bmp";
    Image2D* C = new Image2D(f2, 1, 1, true);

    /** Test RGB **//*
    cout << "-----Test RGB-----" << endl;
    C->EnregistrerImageRGB("RGB.bmp");
    cout << "-----End Test RGB-----" << endl;*/

    /** Test + **//*
    cout << "-----Test + -----" << endl;
    Image2D D = *C + *C;
    D.EnregistrerImageRGB("add.bmp");
    cout << "-----End Test + -----" << endl;*/

    /** Test - **//*
    cout << "-----Test - -----" << endl;
    Image2D E = *C - *C;
    E.EnregistrerImageRGB("sub.bmp");
    cout << "-----End Test - -----" << endl;*/

    /** Test == **//*
    cout << "-----Test == -----" << endl;
    bool egal = (*C == *C);
    if(egal) cout << "A == B" << endl;
    else cout << "A != B" << endl;
    cout << "-----End Test == -----" << endl;*/


    /** Test histogramme **//*
    cout << "-----Test histogramme-----" << endl;
    int* h;
    h = C->hist();
    for(int i = 0; i < 256; i++ ) {
      cout << i << " : " << h[i] << endl;
    }
    cout << "-----End Test histogramme-----" << endl;*/

    /** Test histogramme RGB**//*
    cout << "-----Test histogramme RGB-----" << endl;
    int** h;
    h = C->histRGB();
    for(int i = 0; i < 256; i++ ) {
      cout << "R[" << i << "]: " << h[0][i] << ", G[" << i << "]: " << h[1][i] << ", B[" << i << "]: " << h[2][i] << endl;
    }
    cout << "-----End Test histogramme RGB-----" << endl;*/

    /** Test saltAndPepper (Gray)**//*
    cout << "-----Test saltAndPepper (Gray)-----" << endl;
    C->saltAndPepper(1000, 2);
    C->EnregistrerImage("testSPGray.bmp");
    cout << "-----End Test saltAndPepper (Gray)-----" << endl;*/

    /** Test saltAndPepper (RGB)**//*
    cout << "-----Test saltAndPepper (RGB)-----" << endl;
    C->saltAndPepperRGB(1000, 2);
    C->EnregistrerImageRGB("testSPRGB.bmp");
    cout << "-----End Test saltAndPepper (RGB)-----" << endl;*/

    /** Test appliqueFiltre **//*
    cout << "-----Test appliqueFiltre -----" << endl;
    float** kernel;
    kernel = new float*[3];
    for(int i = 0; i <3; i++)
        kernel[i] = new float[3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            kernel[i][j] = 1.0/9.0;
        }
    }
    C->appliqueFiltre(kernel);
    C->EnregistrerImage("testKernelGray.bmp");
    cout << "-----End Test appliqueFiltre -----" << endl;*/

    /** Test filtreMoyenne **//*
    cout << "-----Test filtreMoyenne -----" << endl;
    C->saltAndPepper(1000, 2);
    C->filtreMoyenne();
    C->EnregistrerImage("testfiltreMoy.bmp");
    cout << "-----End Test filtreMoyenne -----" << endl;*/

    /** Test filtreMedian **//*
    cout << "-----Test filtreMedian -----" << endl;
    C->saltAndPepper(1000, 2);
    C->filtreMedian();
    C->EnregistrerImage("testfiltreMed.bmp");
    cout << "-----End Test filtreMedian -----" << endl;*/

    /** Test filtrePasseHaut **//*
    cout << "-----Test filtrePasseHaut -----" << endl;
    C->filtrePasseHaut();
    C->EnregistrerImage("testfilPasseHaut.bmp");
    cout << "-----End Test filtrePasseHaut -----" << endl;*/

    /** Test appliqueFiltre 2 **//*
    cout << "-----Test appliqueFiltre 2 -----" << endl;
    cout << "----- Noyau 5x5 gaussien -----" << endl;
    float** kernel;
    kernel = new float*[5];
    for(int i = 0; i<5; i++)
        kernel[i] = new float[5];
    kernel[0] = {new float[5]{1.0/331.0, 4.0/331.0, 7.0/331.0, 4.0/331.0, 1.0/331.0}};
    kernel[1] = {new float[5]{4.0/331.0, 20.0/331.0, 33.0/331.0, 20.0/331.0, 4.0/331.0}};
    kernel[2] = {new float[5]{7.0/331.0, 33.0/331.0, 55.0/331.0, 33.0/331.0, 7.0/331.0}};
    kernel[3] = {new float[5]{4.0/331.0, 20.0/331.0, 33.0/331.0, 20.0/331.0, 4.0/331.0}};
    kernel[4] = {new float[5]{1.0/331.0, 4.0/331.0, 7.0/331.0, 4.0/331.0, 1.0/331.0}};
    C->appliqueFiltre(kernel, 5);
    C->EnregistrerImage("testKernelGray2.bmp");
    cout << "-----End Test appliqueFiltre 2 -----" << endl;*/

    /** Test appliqueFiltre 3 **//*
    cout << "-----Test appliqueFiltre 3 -----" << endl;
    cout << "----- filtre moyenne 5x5 -----" << endl;
    float** kernel;
    kernel = new float*[5];
    for(int i = 0; i <5; i++)
        kernel[i] = new float[5];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            kernel[i][j] = 1.0/25.0;
        }
    }
    C->appliqueFiltre(kernel, 5);
    C->EnregistrerImage("testKernelGrayMoy2.bmp");
    cout << "-----End Test appliqueFiltre 3 -----" << endl;*/

    /** Test appliqueFiltreRGB **//*
    cout << "-----Test appliqueFiltreRGB -----" << endl;
    float** kernel;
    kernel = new float*[3];
    for(int i = 0; i <3; i++)
        kernel[i] = new float[3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            kernel[i][j] = 1.0/9.0;
        }
    }
    C->appliqueFiltreRGB(kernel);
    C->EnregistrerImageRGB("appliqueFiltreRGB.bmp");
    cout << "-----End Test appliqueFiltreRGB -----" << endl;*/

    /** Test filtreMoyenneRGB **//*
    cout << "-----Test filtreMoyenneRGB -----" << endl;
    C->saltAndPepperRGB(1000, 2);
    C->filtreMoyenneRGB();
    C->EnregistrerImageRGB("filtreMoyenneRGB.bmp");
    cout << "-----End Test filtreMoyenneRGB -----" << endl;*/

    /** Test filtreMedianRGB **//*
    cout << "-----Test filtreMedianRGB -----" << endl;
    C->saltAndPepperRGB(1000, 2);
    C->filtreMedianRGB();
    C->EnregistrerImageRGB("filtreMedianRGB.bmp");
    cout << "-----End Test filtreMedianRGB -----" << endl;*/

    /** Test filtrePasseHautRGB **//*
    cout << "-----Test filtrePasseHautRGB -----" << endl;
    C->filtrePasseHautRGB();
    C->EnregistrerImageRGB("filtrePasseHautRGB.bmp");
    cout << "-----End Test filtrePasseHautRGB -----" << endl;*/

    /** Test appliqueFiltreRGB 2 **//*
    cout << "-----Test appliqueFiltreRGB 2 -----" << endl;
    cout << "----- Noyau 5x5 gaussien -----" << endl;
    float** kernel;
    kernel = new float*[5];
    for(int i = 0; i<5; i++)
        kernel[i] = new float[5];
    kernel[0] = {new float[5]{1.0/331.0, 4.0/331.0, 7.0/331.0, 4.0/331.0, 1.0/331.0}};
    kernel[1] = {new float[5]{4.0/331.0, 20.0/331.0, 33.0/331.0, 20.0/331.0, 4.0/331.0}};
    kernel[2] = {new float[5]{7.0/331.0, 33.0/331.0, 55.0/331.0, 33.0/331.0, 7.0/331.0}};
    kernel[3] = {new float[5]{4.0/331.0, 20.0/331.0, 33.0/331.0, 20.0/331.0, 4.0/331.0}};
    kernel[4] = {new float[5]{1.0/331.0, 4.0/331.0, 7.0/331.0, 4.0/331.0, 1.0/331.0}};
    C->appliqueFiltreRGB(kernel, 5);
    C->EnregistrerImageRGB("appliqueFiltreRGB2.bmp");
    cout << "-----End Test appliqueFiltreRGB 2 -----" << endl;*/

    return 0;
}
