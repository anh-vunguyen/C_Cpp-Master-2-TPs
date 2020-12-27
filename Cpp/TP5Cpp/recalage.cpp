//  Answered and completed by Anh Vu Nguyen
#include "Image2D.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <tgmath.h>
#define PI 3.14159265
using namespace std;


// Les mesures de similarite
double SSD(Image2D img1, Image2D img2){
    double res = 0.0;
    if((img1.getNbx() == img2.getNbx()) && (img1.getNby() == img2.getNby())){
        int** ptr1 = img1.getPtr();
        int** ptr2 = img2.getPtr();
        for (int i=0; i< img1.getNby(); i++) {
            for (int j=0; j < img1.getNbx(); j++) {
                res += pow(ptr1[i][j] - ptr2[i][j], 2);
            }
        }
        res = res/(img1.getNbx()*img1.getNby());
        return res;
    }else{
        cout << "Les images n'ont pas la meme taille." << endl;
        return res;
    }
}

int** joint_histogram(Image2D img1, Image2D img2){
    if((img1.getNbx() == img2.getNbx()) && (img1.getNby() == img2.getNby())){
        int LIG = img1.getNby();
        int COL = img1.getNbx();
        int N = 256; // 256 valeurs du niveau gris
        int** ptr1 = img1.getPtr();
        int** ptr2 = img2.getPtr();
        int** jh = new int* [N];
        for (int i=0; i<N ; i++){
            jh[i] = new int[N];
        }
        for (int i=0; i<N ; i++){
            for (int j=0; j<N ; j++){
                jh[i][j] = 0;
            }
        }
        for (int i=0; i< img1.getNby(); i++) {
            for (int j=0; j < img1.getNbx(); j++) {
                jh[ptr1[i][j]][ptr2[i][j]] = jh[ptr1[i][j]][ptr2[i][j]] +1;
            }
        }
        return jh;
    }else{
        cout << "Les images n'ont pas la meme taille." << endl;
        return NULL;
    }
}

double EntropieConjointe(Image2D img1, Image2D img2){
    double H = -1;
    if((img1.getNbx() == img2.getNbx()) && (img1.getNby() == img2.getNby())){
        H = 0.0;
        int LIG = img1.getNby();
        int COL = img1.getNbx();
        int** jh;
        jh = joint_histogram(img1,img2);
        for(int i=0; i<256; i++){
            for(int j=0; j<256; j++){
                double pjh = (double) jh[i][j]/(LIG*COL);
                if(pjh != 0.0){
                    H = H + pjh*log(1/pjh);
                }
            }
        }
    }else{
        cout << "Les images n'ont pas la meme taille." << endl;
    }
    return H;
}

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(double A[3][3], double temp[3][3], int p, int q, int n)
{
    int i = 0, j = 0;
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
double determinant(double A[3][3], int n)
{
    double D = 0; // Initialize result
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
    double temp[3][3]; // To store cofactors
    int sign = 1;  // To store sign multiplier
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }
    return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(double A[3][3],double adj[3][3])
{
    // temp is used to store cofactors of A[][]
    int sign = 1;
    double temp[3][3];
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, 3);
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, 2));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(double A[3][3], double inverse[3][3])
{
    // Find determinant of A[][]
    int det = determinant(A, 3);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // Find adjoint
    double adj[3][3];
    adjoint(A, adj);
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            inverse[i][j] = adj[i][j]/double(det);
    return true;
}

// Affine/Rigide
void rotation(Image2D* img, double theta){
    double theta_rad = theta * PI / 180.0;
    double cosT = cos(theta_rad);
    double sinT = sin(theta_rad);
    double A[3][3] = { {cosT, sinT, 0.0},
                    {-sinT, cosT, 0.0},
                    {0.0, 0.0, 1.0}};

    double invA[3][3];
    inverse(A, invA);

    // Point central
    int cx = floor((*img).getNbx() / 2);
    int cy = floor((*img).getNby() / 2);

    // Translation
    int dx = abs(cx - floor(invA[0][0]*cx + invA[0][1]*cy));
    int dy = abs(cy - floor(invA[1][0]*cx + invA[1][1]*cy));


    int** tmp_ptr;
    tmp_ptr = new int* [(*img).getNby()];
    for (int i=0; i<(*img).getNby() ; i++){
        tmp_ptr[i] = new int[(*img).getNbx()];
    }
    int** ptr = (*img).getPtr();
    for (int i=0; i<(*img).getNby(); i++){
        for (int j=0; j<(*img).getNbx(); j++) {
            int posX = floor(invA[0][0]*i + invA[0][1]*j);
            int posY = floor(invA[1][0]*i + invA[1][1]*j);
            if((*img).pixel_is_in_image(posX+dx, posY-dy)){
                tmp_ptr[i][j] = ptr[posX+dx][posY-dy];
            }else{
                tmp_ptr[i][j] = 0;
            }
        }
    }
    (*img).setPtr(tmp_ptr);
    (*img).EnregistrerImage("rotation.bmp");
}

void affine(Image2D* img, double A[3][3]){
    double invA[3][3];
    inverse(A, invA);
    int** tmp_ptr;
    tmp_ptr = new int* [(*img).getNby()];
    for (int i=0; i<(*img).getNby() ; i++){
        tmp_ptr[i] = new int[(*img).getNbx()];
    }
    int** ptr = (*img).getPtr();
    for (int i=0; i<(*img).getNby(); i++){
        for (int j=0; j<(*img).getNbx(); j++) {
            int posX = floor(invA[0][0]*i + invA[1][0]*j + invA[2][0]);
            int posY = floor(invA[0][1]*i + invA[1][1]*j + invA[2][1]);
            if((*img).pixel_is_in_image(posX, posY)){
                tmp_ptr[i][j] = ptr[posX][posY];
            }else{
                tmp_ptr[i][j] = 0;
            }
        }
    }
    (*img).setPtr(tmp_ptr);
}

void identity(Image2D* img){
    double A[3][3] = {{1.0, 0.0, 0.0},
                    {0.0, 1.0, 0.0},
                    {0.0, 0.0, 1.0}};
    affine(img, A);
    (*img).EnregistrerImage("identity.bmp");
}

void scaling(Image2D* img, double cx, double cy){
    double A[3][3] = {{cx, 0.0, 0.0},
                    {0.0, cy, 0.0},
                    {0.0, 0.0, 1.0}};
    affine(img, A);
    (*img).EnregistrerImage("scaling.bmp");
}

void translation(Image2D* img, double tx, double ty){
    double A[3][3] = {{1.0, 0.0, 0.0},
                    {0.0, 1.0, 0.0},
                    {tx, ty, 1.0}};
    affine(img, A);
    (*img).EnregistrerImage("translation.bmp");
}

void shear_vert(Image2D* img, double sv){
    double A[3][3] = {{1.0, 0.0, 0.0},
                    {sv, 1.0, 0.0},
                    {0.0, 0.0, 1.0}};
    affine(img, A);
    (*img).EnregistrerImage("shear_vert.bmp");
}

void shear_horiz(Image2D* img, double sh){
    double A[3][3] = {{1.0, sh, 0.0},
                    {0.0, 1.0, 0.0},
                    {0.0, 0.0, 1.0}};
    affine(img, A);
    (*img).EnregistrerImage("shear_horiz.bmp");
}

double mutual_information(Image2D* img, Image2D* img2){
    int LIG = (*img).getNby();
    int COL = (*img).getNbx();

    int* h1 = (*img).hist();
    double p1[256];
    double H1 = 0.0;

    int* h2 = (*img2).hist();
    double p2[256];
    double H2 = 0.0;

    double H = 0.0;
    int** jh;
    jh = joint_histogram(*img,*img2);
    for(int i=0; i<256; i++){
        for(int j=0; j<256; j++){
            double pjh = (double) jh[i][j]/(LIG*COL);
            if(pjh != 0.0){
                H = H + pjh*log(1/pjh);
            }
        }
    }

    for(int i=0; i<256; i++){
        p1[i] = (h1[i]*1.0) / ((LIG*COL)*1.0);
        p2[i] = (h2[i]*1.0) / ((LIG*COL)*1.0);
    }

    for(int i=0; i<256; i++){
        if(p1[i] != 0.0){
            H1 = H1 + p1[i]*log(1/p1[i]);
        }
        if(p2[i] != 0.0){
            H2 = H2 + p2[i]*log(1/p2[i]);
        }
    }
    double res = (H1 + H2 - H);
    return res;
}

/** Algorithm de recalage de 2 images **/
// Propose par Anh Vu NGUYEN
// Dans cet algorithme:
// Les caracteristiques extraites de l'image: les niveaux de gris, le histogramme, l'entropie
// La mesure de la similarite: l'information mutuelle
// Les etapes de cet algorithme
// 1 - Calculer l'information mutelle entre l'image de reference et elle-meme
// 2 - Calculer l'information mutelle entre l'image tournee et l'image de reference
// 3 - Chercher la degree de l'image tourne par rapport l'image de reference
// 4 - Appliquer la rotation inverse avec la valeur de la degree cherchee
// 5 - Sauvegarder le resultat de la recalage
void recalage(Image2D* img, Image2D* imgref, double pas){
    double deg = 0.0;
    double MI_prev = 0;
    double MI_ref = 0;
    double MI;
    MI_ref = mutual_information(imgref, imgref);
    while(deg>=-360 && deg<=360){
        deg = deg + pas;
        Image2D* imgrot = NULL;
        (*imgrot) = (*img).rotation(deg);
        MI = mutual_information(imgrot, imgref);
        if(abs(MI-MI_ref) < 0.1){
            (*img).EnregistrerImage("recalageResult.bmp");
            break;
        }
        MI_prev = MI;
    }
}

