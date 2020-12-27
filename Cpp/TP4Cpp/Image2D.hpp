//
//  Image2D.hpp
//  TP1C++
//
//  Created by Gustavo Guerrero on 15/09/2019.
//  Answered and completed by Anh Vu Nguyen
#ifndef Image2D_hpp
#define Image2D_hpp
#include <stdio.h>
#include <iostream>
#include <tgmath.h>

//TP4 c++
#include <vector>
#include <algorithm>


#define LONGUEUR_ENTETE 54
class Image2D
{
public:
    //Constructeur
    Image2D();
    Image2D(int nx, int ny, int ngl, double milx, double mily, int p0);
    Image2D(char* path,double milx, double mily);
    // TP3 C++
    Image2D(char* path,double milx, double mily, bool rgb);
    //Méthodes
    ~Image2D();


    int getNbx();
    void setNbx(int a);
    int getNby();
    void setNby(int a);
    int getNgl();
    void setNgl(int a);
    long int getSize();
    double getDx();
    void setDx(double a);
    double getDy();
    void setDy(double a);

    int getPixelValue(int i,int j);
    void setPixelValue(int i,int j, int a);

    // TP2 C++
    void EnregistrerImage(char* path);
    void seuillageImage(int seuil);
    void applyBinaryMask(char* path_mask, char* path_result);
    bool pixel_is_in_image(int x, int y);
    int interpolation_nn_x(float x);
    int interpolation_nn_y(float y);
    void translation(float t_x, float t_y, const char* filename);
    Image2D translation(float t_x, float t_y);
    void rotation(float theta, const char* filename);
    Image2D rotation(float theta);


    //TP3 C++
    void EnregistrerImageRGB(char* path);
    int* hist(); // histogramme en niveau de gris
    int** histRGB(); // histogramme RGB
    void saltAndPepper(int nbNoise, int sizeNoise); // ajoute du bruit "sel et poivre" dans l'image de niveau de gris
    void saltAndPepperRGB(int nbNoise, int sizeNoise); // ajoute du bruit "sel et poivre" dans l'image RGB

    // En niveau de gris
    void appliqueFiltre(float** kernel);
    void appliqueFiltre(float** kernel, int size);
    void filtreMoyenne();
    void filtreMedian();
    void filtrePasseHaut();

    // En RGB
    void appliqueFiltreRGB(float** kernel);
    void appliqueFiltreRGB(float** kernel, int size);
    void filtreMoyenneRGB();
    void filtreMedianRGB();
    void filtrePasseHautRGB();

    // Operateurs surcharges
    Image2D operator+(const Image2D& B);
    Image2D operator-(const Image2D& B);
    bool operator==(const Image2D& B);

    // TP4 C++
    std::vector<int> find_peaks(int* h);
    void segmentation_avec_histogramme();
    void segmentation_avec_histogrammeRGB();
    void segmentation_ligne();
    // TP3 C++
    Image2D(char* path,double milx, double mily, bool rgb, bool padding);
    void EnregistrerImage(char* path, bool padding);
    //void EnregistrerImageRGB(char* path, bool padding);


protected:
    int** ptr = NULL;//. Tels que ptr[i] représente un pointeur sur les valeurs des pixels de la ligne i et ptr[i][j] représente la valeur du pixel i,j.
    void alloue_partie_dynamique(int dimx, int dimy);// : fonction d’allocation dynamique prenant en argument le nombre de pixels en x et en y. Utilisez new.
    void libere_partie_dynamique();// : fonction permettant libérer la mémoire dynamique. Utilisez delete.
    void init(int valeur_init);// : fonction permettant d’initialiser les valeurs des pixels à la valeur valeur_init.
    // Entete
    unsigned char en_tete[LONGUEUR_ENTETE];
    // TP3 C++
    int** R = NULL;
    int** G = NULL;
    int** B = NULL;
    void alloue_partie_dynamique_R(int dimx, int dimy);// : fonction d’allocation dynamique prenant en argument le nombre de pixels en x et en y. Utilisez new.
    void libere_partie_dynamique_R();// : fonction permettant libérer la mémoire dynamique. Utilisez delete.
    void alloue_partie_dynamique_G(int dimx, int dimy);// : fonction d’allocation dynamique prenant en argument le nombre de pixels en x et en y. Utilisez new.
    void libere_partie_dynamique_G();// : fonction permettant libérer la mémoire dynamique. Utilisez delete.
    void alloue_partie_dynamique_B(int dimx, int dimy);// : fonction d’allocation dynamique prenant en argument le nombre de pixels en x et en y. Utilisez new.
    void libere_partie_dynamique_B();// : fonction permettant libérer la mémoire dynamique. Utilisez delete.


private:

    int nbx;/////nombre de pixels sur l'axe x.
    int nby;/////nombre de pixels sur l'axe y.
    int number_grey_level;/////nombre de niveaux de gris.
    long int size;/////nombre total de pixels dans l'image.
    double dx;/////taille d'un pixel en millimètres sur l'axe x.
    double dy;/////taille d'un pixel en millimètres sur l'axe y.
};
#endif /* Image2D_hpp */
