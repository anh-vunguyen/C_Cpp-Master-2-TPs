//  Answered and completed by Anh Vu Nguyen
#ifndef RECALAGE_HPP_INCLUDED
#define RECALAGE_HPP_INCLUDED

#include <stdio.h>
#include <iostream>
#include <tgmath.h>
#include "Image2D.hpp"

// Les mesures de similarite
double SSD(Image2D img1, Image2D img2);
int** joint_histogram(Image2D img1, Image2D img2);
double EntropieConjointe(Image2D img1, Image2D img2);
double mutual_information(Image2D* img, Image2D* img2);

// Rigide/Affine
void affine(Image2D img, double kernel[3][3]);
void rotation(Image2D* img, double theta);
void identity(Image2D* img);
void scaling(Image2D* img, double cx, double cy);
void translation(Image2D* img, double tx, double ty);
void shear_vert(Image2D* img, double sv);
void shear_horiz(Image2D* img, double sh);

// Chercher la matrice inverse
void getCofactor(double A[3][3], double temp[3][3], int p, int q, int n);
double determinant(double A[3][3], int n);
void adjoint(double A[3][3],double adj[3][3]);
bool inverse(double A[3][3], double inverse[3][3]);

// Recalage de deux image
void recalage(Image2D* img, Image2D* imgref, double pas);




#endif // RECALAGE_HPP_INCLUDED
