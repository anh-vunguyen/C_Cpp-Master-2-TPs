//
//  Image2D.hpp
//  TP1C++
//
//  TP created by Gustavo Guerrero on 15/09/2019.
//  Answered and completed by Anh Vu Nguyen

#ifndef Image2D_hpp
#define Image2D_hpp
#include <stdio.h>
#include <iostream>
#include <tgmath.h>
#define LONGUEUR_ENTETE 54
class Image2D
{
public:
    //Constructeur
    Image2D();
    Image2D(int nx, int ny, int ngl, double milx, double mily, int p0);
    Image2D(char* path,double milx, double mily);
    //M�thodes
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

protected:
    int** ptr = NULL;//. Tels que ptr[i] repr�sente un pointeur sur les valeurs des pixels de la ligne i et ptr[i][j] repr�sente la valeur du pixel i,j.
    void alloue_partie_dynamique(int dimx, int dimy);// : fonction d�allocation dynamique prenant en argument le nombre de pixels en x et en y. Utilisez new.
    void libere_partie_dynamique();// : fonction permettant lib�rer la m�moire dynamique. Utilisez delete.
    void init(int valeur_init);// : fonction permettant d�initialiser les valeurs des pixels � la valeur valeur_init.
    // Entete
    unsigned char en_tete[LONGUEUR_ENTETE];
private:

    int nbx;/////nombre de pixels sur l'axe x.
    int nby;/////nombre de pixels sur l'axe y.
    int number_grey_level;/////nombre de niveaux de gris.
    long int size;/////nombre total de pixels dans l'image.
    double dx;/////taille d'un pixel en millim�tres sur l'axe x.
    double dy;/////taille d'un pixel en millim�tres sur l'axe y.
};
#endif /* Image2D_hpp */
