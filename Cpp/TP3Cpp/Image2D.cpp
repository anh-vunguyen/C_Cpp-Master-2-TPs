//
//  Image2D.cpp
//  TP1C++
//
//  Created by Gustavo Guerrero on 15/09/2019.
//  Answered and completed by Anh Vu Nguyen
#include "Image2D.hpp"
#include <bits/stdc++.h> // sort()
#define LONGUEUR_ENTETE 54
#define PI 3.14159265
using namespace std;

// Constructeur par defaut
Image2D::Image2D(){
    nbx = 128;
    nby = 128;
    number_grey_level = 255;
    size = nbx * nby;
    dx = 1;
    dy = 1;
    init(0);
}

// Constructeur avec les arguments
Image2D::Image2D(int nx, int ny, int ngl, double milx, double mily, int p0){
    nbx = nx;
    nby = ny;
    number_grey_level = ngl;
    size = nbx * nby;
    dx = milx;
    dy = mily;
    init(p0);
}

// Ouvrir l'image fournie par le "path" et convertir au niveau gris
Image2D::Image2D(char* path,double milx, double mily){
    FILE* f = fopen(path, "rb");
    //unsigned char en_tete[54];
    fread((*this).en_tete, sizeof(unsigned char), 54, f); // read the 54-byte header
    // extract image height and width from header
    int width = ((unsigned char)((*this).en_tete[21]) << 24 ) | ((unsigned char)((*this).en_tete[20]) << 16) | ((unsigned char)((*this).en_tete[19]) << 8) | ((unsigned char)((*this).en_tete[18]));
    int height = ((unsigned char)((*this).en_tete[25]) << 24) | ((unsigned char)((*this).en_tete[24]) << 16) | ((unsigned char)((*this).en_tete[23]) << 8) | ((unsigned char)((*this).en_tete[22]));
    int size = 3 * width * height;
    (*this).nbx=width;
    (*this).nby=height;
    (*this).size=width*height;
    (*this).dx=milx;
    (*this).dy=mily;
    unsigned char* image = new unsigned char[size]; // allocate 3 bytes per pixel
    unsigned char* imageBLU=new unsigned char[width*height];//definition of the RED
    unsigned char* imageGRE=new unsigned char[width*height];//definition of the GREEN
    unsigned char* imageRED=new unsigned char[width*height];//definition of the BLUE

    fread(image,sizeof(unsigned char),size,f);//We fill the FULL image
    fclose(f);

    for(int id=0;id<(width*height);id++)
    {
        imageBLU[id]=image[3*id];
        imageGRE[id]=image[3*id+1];
        imageRED[id]=image[3*id+2];

    }
    (*this).alloue_partie_dynamique(width,height);
    for (int i=0; i<(*this).nbx; i++) {
        for (int j=0; j<(*this).nby; j++) {
            double mean=0;
            mean=((double)imageRED[i*((*this).nby)+j]+(double)imageBLU[i*((*this).nby)+j]+(double)imageGRE[i*((*this).nby)+j])/3.0;
                (*this).ptr[i][j]=(int)mean;
        }
    }

    delete [] image;
    image=NULL;
    delete [] imageBLU;
    imageBLU=NULL;
    delete [] imageRED;
    imageRED=NULL;
    delete [] imageGRE;
    imageGRE=NULL;

}

// TP3 C++
// Ouvrir l'image fournie par le "path"
Image2D::Image2D(char* path,double milx, double mily, bool rgb){
    if(rgb){
        FILE* f = fopen(path, "rb");
        //unsigned char en_tete[54];
        fread((*this).en_tete, sizeof(unsigned char), 54, f); // read the 54-byte header
        // extract image height and width from header
        int width = ((unsigned char)((*this).en_tete[21]) << 24 ) | ((unsigned char)((*this).en_tete[20]) << 16) | ((unsigned char)((*this).en_tete[19]) << 8) | ((unsigned char)((*this).en_tete[18]));
        int height = ((unsigned char)((*this).en_tete[25]) << 24) | ((unsigned char)((*this).en_tete[24]) << 16) | ((unsigned char)((*this).en_tete[23]) << 8) | ((unsigned char)((*this).en_tete[22]));
        int size = 3 * width * height;
        (*this).nbx=width;
        (*this).nby=height;
        (*this).size=width*height;
        (*this).dx=milx;
        (*this).dy=mily;
        unsigned char* image = new unsigned char[size]; // allocate 3 bytes per pixel
        unsigned char* imageBLU=new unsigned char[width*height];//definition of the RED
        unsigned char* imageGRE=new unsigned char[width*height];//definition of the GREEN
        unsigned char* imageRED=new unsigned char[width*height];//definition of the BLUE

        fread(image,sizeof(unsigned char),size,f);//We fill the FULL image
        fclose(f);
        (*this).alloue_partie_dynamique_R(width,height);
        (*this).alloue_partie_dynamique_G(width,height);
        (*this).alloue_partie_dynamique_B(width,height);
        for (int i=0; i<(*this).nbx; i++) {
            for (int j=0; j<(*this).nby; j++) {
                int id = i*(*this).nbx + j;
                imageBLU[id]=image[3*id];
                (*this).B[i][j] = (int) image[3*id];
                imageGRE[id]=image[3*id+1];
                (*this).G[i][j] = (int) image[3*id+1];
                imageRED[id]=image[3*id+2];
                (*this).R[i][j] = (int) image[3*id+2];
            }
        }
        (*this).alloue_partie_dynamique(width,height);
        for (int i=0; i<(*this).nbx; i++) {
            for (int j=0; j<(*this).nby; j++) {
                double mean=0;
                mean=((double)imageRED[i*((*this).nby)+j]+(double)imageBLU[i*((*this).nby)+j]+(double)imageGRE[i*((*this).nby)+j])/3.0;
                    (*this).ptr[i][j]=(int)mean;
            }
        }

        delete [] image;
        image=NULL;
        delete [] imageBLU;
        imageBLU=NULL;
        delete [] imageRED;
        imageRED=NULL;
        delete [] imageGRE;
        imageGRE=NULL;
    }
}

// Getters et Setters
int Image2D::getNbx(){
    return nbx;
}
void Image2D::setNbx(int a){
    nbx = a;
}
int Image2D::getNby(){
    return nby;
}
void Image2D::setNby(int a){
    nby = a;
}
int Image2D::getNgl(){
    return number_grey_level;
}
void Image2D::setNgl(int a){
    number_grey_level = a;
}
long int Image2D::getSize(){
    return size;
}
double Image2D::getDx(){
    return dx;
}
void Image2D::setDx(double a){
    dx = a;
}
double Image2D::getDy(){
    return dy;
}
void Image2D::setDy(double a){
    dy = a;
}

int Image2D::getPixelValue(int i,int j){
    return ptr[i][j];
}
void Image2D::setPixelValue(int i,int j, int a){
    ptr[i][j] = a;
}

// Allocation dynamique de mémoire via new..
void Image2D::alloue_partie_dynamique(int dimx, int dimy){
    if ( dimx<=0 || dimy<=0 )
    {
        std::cout<<"Dimension de l'allocation anormales...\n";
        std::cout<<"dimx : " << dimx << ", dimy :" << dimy << endl ;
        exit ( 1 );
    }

    ptr = new int* [dimx]; //!< ptr[i] pointe sur la ligne i.
    for (int i=0; i<dimx ; i++){
        ptr[i] = new int[dimy]; //!< ptr[i][j] sur l'element i,j
        if ( ptr==NULL || ptr[i]==NULL )
        {
            std::cout<<"Probleme allocation memoire...exiting\n";
            exit ( 1 );
        }
    }

}

// Liberation de la partie dynamique
void Image2D::libere_partie_dynamique(){
    if ( ptr!=NULL)
    {
        for(int i=0; i< ((*this).nbx) ; i++){
            if ( ptr[i]!=NULL ){
                delete [] ptr[i];
            }
        }
        delete [] ptr;
        ptr=NULL;
    }
}

// TP3 C++
// Allocation dynamique R
void Image2D::alloue_partie_dynamique_R(int dimx, int dimy){
    if ( dimx<=0 || dimy<=0 )
    {
        std::cout<<"Dimension de l'allocation anormales...\n";
        std::cout<<"dimx : " << dimx << ", dimy :" << dimy << endl ;
        exit ( 1 );
    }

    R = new int* [dimx];
    for (int i=0; i<dimx ; i++){
        R[i] = new int[dimy];
        if ( R==NULL || R[i]==NULL )
        {
            std::cout<<"Probleme allocation memoire...exiting\n";
            exit ( 1 );
        }
    }

}

// Liberation de la partie dynamique R
void Image2D::libere_partie_dynamique_R(){
    if ( R!=NULL)
    {
        for(int i=0; i< ((*this).nbx) ; i++){
            if ( R[i]!=NULL ){
                delete [] R[i];
            }
        }
        delete [] R;
        R=NULL;
    }
}

// Allocation dynamique G
void Image2D::alloue_partie_dynamique_G(int dimx, int dimy){
    if ( dimx<=0 || dimy<=0 )
    {
        std::cout<<"Dimension de l'allocation anormales...\n";
        std::cout<<"dimx : " << dimx << ", dimy :" << dimy << endl ;
        exit ( 1 );
    }

    G = new int* [dimx];
    for (int i=0; i<dimx ; i++){
        G[i] = new int[dimy];
        if ( G==NULL || G[i]==NULL )
        {
            std::cout<<"Probleme allocation memoire...exiting\n";
            exit ( 1 );
        }
    }

}

// Liberation de la partie dynamique G
void Image2D::libere_partie_dynamique_G(){
    if ( G!=NULL)
    {
        for(int i=0; i< ((*this).nbx) ; i++){
            if ( G[i]!=NULL ){
                delete [] G[i];
            }
        }
        delete [] G;
        G=NULL;
    }
}

// Allocation dynamique B
void Image2D::alloue_partie_dynamique_B(int dimx, int dimy){
    if ( dimx<=0 || dimy<=0 )
    {
        std::cout<<"Dimension de l'allocation anormales...\n";
        std::cout<<"dimx : " << dimx << ", dimy :" << dimy << endl ;
        exit ( 1 );
    }

    B = new int* [dimx];
    for (int i=0; i<dimx ; i++){
        B[i] = new int[dimy];
        if ( B==NULL || B[i]==NULL )
        {
            std::cout<<"Probleme allocation memoire...exiting\n";
            exit ( 1 );
        }
    }

}

// Liberation de la partie dynamique B
void Image2D::libere_partie_dynamique_B(){
    if ( B!=NULL)
    {
        for(int i=0; i< ((*this).nbx) ; i++){
            if ( B[i]!=NULL ){
                delete [] B[i];
            }
        }
        delete [] B;
        B=NULL;
    }
}
//////


// Creation un objet Image2D avec la valeur initiale
void Image2D::init(int valeur_init){
    if ((*this).ptr!=NULL)
    {
        for (int i=0; i<(*this).nbx; i++) {
            for (int j=0; j<(*this).nby; j++) {
                (*this).ptr[i][j]=valeur_init;
            }
        }
    }else{
        (*this).alloue_partie_dynamique((*this).nbx,(*this).nby);
        for (int i=0; i<(*this).nbx; i++) {
            for (int j=0; j<(*this).nby; j++) {
                (*this).ptr[i][j]=valeur_init;
            }
        }
    }
}

// Destructeur
Image2D::~Image2D()
{
    (*this).libere_partie_dynamique();
    (*this).libere_partie_dynamique_R();
    (*this).libere_partie_dynamique_G();
    (*this).libere_partie_dynamique_B();
}

// EnregistrerImage
void Image2D::EnregistrerImage(char* path){
    FILE* fp;
    fp = fopen(path, "wb");
    fwrite((*this).en_tete, 1, LONGUEUR_ENTETE, fp);
    for (int i=0; i<(*this).nbx; i++) {
        for (int j=0; j<(*this).nby; j++) {
            unsigned char* colorPixel = (unsigned char*) malloc(3);
            colorPixel[0] = (*this).ptr[i][j];
            colorPixel[1] = (*this).ptr[i][j];
            colorPixel[2] = (*this).ptr[i][j];
            fwrite(colorPixel, 3, 1, fp);
            free(colorPixel);
        }
    }
    fclose(fp);
}

// TP3 C++
// EnregistrerImageRGB
void Image2D::EnregistrerImageRGB(char* path){
    FILE* fp;
    fp = fopen(path, "wb");
    fwrite((*this).en_tete, 1, LONGUEUR_ENTETE, fp);
    for (int i=0; i<(*this).nbx; i++) {
        for (int j=0; j<(*this).nby; j++) {
            unsigned char* colorPixel = (unsigned char*) malloc(3);
            colorPixel[0] = (*this).B[i][j];
            colorPixel[1] = (*this).G[i][j];
            colorPixel[2] = (*this).R[i][j];
            fwrite(colorPixel, 3, 1, fp);
            free(colorPixel);
        }
    }
    fclose(fp);
}

// Seuillage
void Image2D::seuillageImage(int seuil){
    for (int i=0; i< (*this).nbx; i++) {
        for (int j=0; j < (*this).nby; j++) {
            if(ptr[i][j] >= seuil){
                ptr[i][j] = 255;
            }else{
                ptr[i][j] = 0;
            }
        }
    }
}

// Masque d'une image
// Mettre à 0 les pixels contenus en dehors du masque binaire (ie : les pixels du masque =zero) et de conserver la valeurs des pixel contenus dans le masque binaire
void Image2D::applyBinaryMask(char* path_mask, char* path_result){
    Image2D mask(path_mask,1,1);
    if((mask.getNbx() == (*this).nbx) && (mask.getNby() == (*this).nby)){
        for (int i=0; i< (*this).nbx; i++) {
            for (int j=0; j < (*this).nby; j++) {
                if(mask.ptr[i][j] == 255){
                    ptr[i][j] = 0;
                }
            }
        }
        this->EnregistrerImage(path_result);
    }else{
        cout << "La masque et l'image n'ont pas la meme taille." << endl;
    }
}

// Renvoie vrai si le pixel x, y est dans l’image ou faux sinon.
bool Image2D::pixel_is_in_image(int x, int y){
    if((x>=0 && x<(*this).nbx) && (y>=0 && y<(*this).nbx)){
        return true;
    }else{
        return false;
    }
}

// Renvoie l'indice i du pixel le plus proche
int Image2D::interpolation_nn_x(float x){
    float posX = x / (*this).dx;
    int posX_sup = ceil(posX);
    int posX_inf = floor(posX);
    if((posX_sup-x) <= (x-posX_inf)){
        if(this->pixel_is_in_image(posX_sup, 0)){
            return posX_sup;
        }else if(this->pixel_is_in_image(posX_inf, 0)){
            return posX_inf-1;
        }
    }else{
        if(this->pixel_is_in_image(posX_inf, 0)){
            return posX_inf-1;
        }else if(this->pixel_is_in_image(posX_sup, 0)){
            return posX_sup;
        }
        // Traitement le cas d'erreur
        exit(-1);
    }
}

// Renvoie l'indice j du pixel le plus proche
int Image2D::interpolation_nn_y(float y){
    float posY = y / (*this).dy;
    int posY_sup = ceil(posY);
    int posY_inf = floor(posY);
    if((posY_sup-y) <= (y-posY_inf)){
        if(this->pixel_is_in_image(posY_sup, 0)){
            return posY_sup;
        }else if(this->pixel_is_in_image(posY_inf, 0)){
            return posY_inf-1;
        }
    }else{
        if(this->pixel_is_in_image(posY_inf, 0)){
            return posY_inf-1;
        }else if(this->pixel_is_in_image(posY_sup, 0)){
            return posY_sup;
        }
        // Traitement le cas d'erreur
        exit(-1);
    }
}

// Applique une translation de manière uniforme à tous les pixels de l’image.
// tx est la valeur de la translation en millimètres en x. ty est la valeur de la
// translation en millimètres en y. Cette fonction écrit l’image transformée
// dans un fichier bmp.
void Image2D::translation(float t_x, float t_y, const char* filename){
    int tx = floor(t_x / dx);
    int ty = floor(t_y / dy);
    int** tmp_ptr;
    tmp_ptr = new int* [(*this).nbx];
    for (int i=0; i<(*this).nbx ; i++){
        tmp_ptr[i] = new int[(*this).nby];
    }
    for (int i=0; i< (*this).nbx; i++){
        for (int j=0; j < (*this).nby; j++) {
            if(this->pixel_is_in_image(i+ty, j+tx)){
                tmp_ptr[i][j] = (*this).ptr[i+ty][j+tx];
            }else{
                tmp_ptr[i][j] = 0;
            }
        }
    }
    (*this).ptr = tmp_ptr;
    char * output = const_cast<char*> (filename); // conversion from 'const char*' to 'char*'
    this->EnregistrerImage(output);
}

// Applique une translation de manière uniforme à tous les pixels de l’image.
// tx est la valeur de la translation en millimètres en x. ty est la valeur de la
// translation en millimètres en y. Cette fonction renvoie renvoie l’image transformée
Image2D Image2D::translation(float t_x, float t_y){
    Image2D* res = new Image2D((*this).nbx, (*this).nby, (*this).number_grey_level, (*this).dx, (*this).dy, 0);
    for(int iD=0;iD<54;iD++){
        (*res).en_tete[iD]=(*this).en_tete[iD];
    }
    int tx = floor(t_x / dx);
    int ty = floor(t_y / dy);
    for (int i=0; i< (*this).nbx; i++){
        for (int j=0; j < (*this).nby; j++) {
            if(this->pixel_is_in_image(i+ty, j+tx)){
                (*res).ptr[i][j] = (*this).ptr[i+ty][j+tx];
            }else{
                (*res).ptr[i][j] = 0;
            }
        }
    }
    return (*res);
}

// Applique une rotation uniforme tous les pixels de l’image. theta est la valeur de l’angle de rotation en degrés.
// Cette fonction écrit l’image transformée dans un fichier bmp.
void Image2D::rotation(float theta, const char* filename){
    float theta_rad = -theta * PI / 180.0;

    // La matrice de rotation
    double a, b, c, d;
    a = cos(theta_rad);
    b = -sin(theta_rad);
    c = sin(theta_rad);
    d = cos(theta_rad);

    // La matrice inverse de rotation
    double ia, ib, ic, id;
    ia = d / (a*d-b*c);
    ib = -b / (a*d-b*c);
    ic = -c / (a*d-b*c);
    id = a / (a*d-b*c);

    // Point central
    int cx = floor((*this).nbx / 2);
    int cy = floor((*this).nby / 2);

    // Translation
    int dx = abs(cx - floor(ia*cx + ib*cy));
    int dy = abs(cy - floor(ic*cx + id*cy));


    int** tmp_ptr;
    tmp_ptr = new int* [(*this).nbx];
    for (int i=0; i<(*this).nbx ; i++){
        tmp_ptr[i] = new int[(*this).nby];
    }
    for (int i=0; i< (*this).nbx; i++){
        for (int j=0; j < (*this).nby; j++) {
            int posX = floor(ia*i + ib*j);
            int posY = floor(ic*i + id*j);
            if(this->pixel_is_in_image(posX+dx, posY-dy)){
                tmp_ptr[i][j] = (*this).ptr[posX+dx][posY-dy];
            }else{
                tmp_ptr[i][j] = 0;
            }
        }
    }
    (*this).ptr = tmp_ptr;
    char * output = const_cast<char*> (filename); // conversion from 'const char*' to 'char*'
    this->EnregistrerImage(output);
}

// Applique une rotation uniforme tous les pixels de l’image. theta est la valeur de l’angle de rotation en degrés.
// Cette fonction renvoie l’image transformée.
Image2D Image2D::rotation(float theta){
    float theta_rad = -theta * PI / 180.0;

    // La matrice de rotation
    double a, b, c, d;
    a = cos(theta_rad);
    b = -sin(theta_rad);
    c = sin(theta_rad);
    d = cos(theta_rad);

    // La matrice inverse de rotation
    double ia, ib, ic, id;
    ia = d / (a*d-b*c);
    ib = -b / (a*d-b*c);
    ic = -c / (a*d-b*c);
    id = a / (a*d-b*c);;

    // Point central
    int cx = floor((*this).nbx / 2);
    int cy = floor((*this).nby / 2);

    // Translation
    int dx = abs(cx - floor(ia*cx + ib*cy));
    int dy = abs(cy - floor(ic*cx + id*cy));


    Image2D* res = new Image2D((*this).nbx, (*this).nby, (*this).number_grey_level, (*this).dx, (*this).dy, 0);
    for(int iD=0;iD<54;iD++){
        (*res).en_tete[iD]=(*this).en_tete[iD];
    }

    for (int i=0; i< (*this).nby; i++){
        for (int j=0; j < (*this).nbx; j++) {
            int posX = floor(ia*i + ib*j);
            int posY = floor(ic*i + id*j);
            if(this->pixel_is_in_image(posX+dx, posY-dy)){
                (*res).ptr[i][j] = (*this).ptr[posX+dx][posY-dy];
            }else{
                (*res).ptr[i][j] = 0;
            }
        }
    }
    return (*res);
}

// TP3 C++
// Operateur + (addition)
Image2D Image2D::operator+(const Image2D &B){
    if(((*this).nbx == B.nbx) && ((*this).nby == B.nby)){
        Image2D* res = new Image2D(*this); // Deepcopy
        bool isRGB =  (res->B != NULL);
        for (int i=0; i< (*this).nby; i++){
            for (int j=0; j < (*this).nbx; j++) {
                res->ptr[i][j] = min((*this).ptr[i][j] + B.ptr[i][j], 255);
                if(isRGB){
                    res->B[i][j] = min((*this).B[i][j] + B.B[i][j], 255);
                    res->G[i][j] = min((*this).G[i][j] + B.G[i][j], 255);
                    res->R[i][j] = min((*this).R[i][j] + B.R[i][j], 255);
                }
            }
        }
        return (*res);
    }else{
        cout << "Erreur des tailles de deux image." << endl;
        Image2D* res = nullptr;
        return (*res);
    }
}

// Operateur -
Image2D Image2D::operator-(const Image2D &B){
    if(((*this).nbx == B.nbx) && ((*this).nby == B.nby)){
        Image2D* res = new Image2D(*this); // Deepcopy
        bool isRGB =  (res->B != NULL);
        for (int i=0; i< (*this).nby; i++){
            for (int j=0; j < (*this).nbx; j++) {
                res->ptr[i][j] = max((*this).ptr[i][j] - B.ptr[i][j], 0);
                if(isRGB){
                    res->B[i][j] = max((*this).B[i][j] - B.B[i][j], 0);
                    res->G[i][j] = max((*this).G[i][j] - B.G[i][j], 0);
                    res->R[i][j] = max((*this).R[i][j] - B.R[i][j], 0);
                }
            }
        }
        return (*res);
    }else{
        cout << "Erreur des tailles de deux image." << endl;
        Image2D* res = nullptr;
        return (*res);
    }
}

// Operateur ==
bool Image2D::operator==(const Image2D &B){
    bool res = false;
    if(((*this).nbx == B.nbx) && ((*this).nby == B.nby)){
        for (int i=0; i< (*this).nby; i++){
            for (int j=0; j < (*this).nbx; j++){
                if((*this).ptr[i][j] ==  B.ptr[i][j]){
                    res = true;
                }else{
                    res = false;
                    return res;
                }
            }
        }
    }
    return res;
}

// histogramme en niveau de gris
int* Image2D::hist(){
    // In C++, an empty initialization list will also initialize every element to 0
    static int h[256];
    for (int i=0; i< (*this).nby; i++){
        for (int j=0; j < (*this).nbx; j++){
            h[(*this).ptr[i][j]] += 1;
        }
    }
    return h;
}

// histogramme RGB
int** Image2D::histRGB(){
    int** h = 0;
    h = new int*[3];
    h[0] = new int[256]; // R
    h[1] = new int[256]; // G
    h[2] = new int[256]; // B
    for (int i=0; i<256; i++){
        h[0][i] = 0;
        h[1][i] = 0;
        h[2][i] = 0;
    }
    for (int i=0; i< (*this).nby; i++){
        for (int j=0; j < (*this).nbx; j++){
            h[0][(*this).R[i][j]] += 1;
            h[1][(*this).G[i][j]] += 1;
            h[2][(*this).B[i][j]] += 1;
        }
    }
    return h;
}

// ajoute du bruit "sel et poivre"
void Image2D::saltAndPepper(int nbNoise, int sizeNoise){
    int x, y;
    int pbNoise;
    while(nbNoise){
        x = rand() % ((*this).nbx - sizeNoise + 1);
        y = rand() % ((*this).nby - sizeNoise + 1);
        pbNoise = rand() % 2;
        if(pbNoise){
            for(int i=0; i<sizeNoise; i++){
                for(int j=0; j<sizeNoise; j++){
                    (*this).ptr[y + i][x + j] = 255;
                }
            }
        }else{
            for(int i=0; i<sizeNoise; i++){
                for(int j=0; j<sizeNoise; j++){
                    (*this).ptr[y + i][x + j] = 0;
                }
            }
        }
        nbNoise--;
    }
}

// ajoute du bruit "sel et poivre"
void Image2D::saltAndPepperRGB(int nbNoise, int sizeNoise){
    int x, y;
    int pbNoise;
    while(nbNoise){
        x = rand() % ((*this).nbx - sizeNoise + 1);
        y = rand() % ((*this).nby - sizeNoise + 1);
        pbNoise = rand() % 2;
        if(pbNoise){
            for(int i=0; i<sizeNoise; i++){
                for(int j=0; j<sizeNoise; j++){
                    (*this).ptr[y + i][x + j] = 255;
                    (*this).R[y + i][x + j] = 255;
                    (*this).G[y + i][x + j] = 255;
                    (*this).B[y + i][x + j] = 255;
                }
            }
        }else{
            for(int i=0; i<sizeNoise; i++){
                for(int j=0; j<sizeNoise; j++){
                    (*this).ptr[y + i][x + j] = 0;
                    (*this).R[y + i][x + j] = 0;
                    (*this).G[y + i][x + j] = 0;
                    (*this).B[y + i][x + j] = 0;
                }
            }
        }
        nbNoise--;
    }
}

// En niveau de gris ===============================
// Applique un noyau 3x3 a l'image en niveau de gris
void Image2D::appliqueFiltre(float** kernel){
    int** tmp_ptr;
    tmp_ptr = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
    }
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            float tmp = 0.0f;
            for (int k = 0; k<3; k++){
                for (int l = 0; l<3; l++){
                    int posx = j - 1 + l;
                    int posy = i - 1 + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        tmp += (*this).ptr[posy][posx] * kernel[k][l];
                    }
                }
            tmp_ptr[i][j] = floor(tmp);
            }
        }
    }
    (*this).ptr = tmp_ptr;
}

// Applique le filtre moyenne 3x3 a l'image en niveau de gris
void Image2D::filtreMoyenne(){
    float** kernel;
    kernel = new float*[3];
    for(int i = 0; i <3; i++)
        kernel[i] = new float[3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            kernel[i][j] = 1.0/9.0;
        }
    }
    (*this).appliqueFiltre(kernel);
}

// Applique le filtre median 3x3 a l'image en niveau de gris
void Image2D::filtreMedian(){
    int** tmp_ptr;
    tmp_ptr = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
    }
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            int arr[9];
            for (int k = 0; k<3; k++){
                for (int l = 0; l<3; l++){
                    int posx = j - 1 + l;
                    int posy = i - 1 + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        arr[k*3+l] = (*this).ptr[posy][posx];
                    }
                }
            }
            sort(arr, arr+9);
            tmp_ptr[i][j] = arr[4];
        }
    }
    (*this).ptr = tmp_ptr;
}

// Filtre passe haut en utilisant un filtre lineaire
// Filtre gaussien passe haut
void Image2D::filtrePasseHaut(){
    float** kernel;
    kernel = new float*[3];
    kernel[0] = {new float[3]{-1.0/9.0, -1.0/9.0, -1.0/9.0}};
    kernel[1] = {new float[3]{-1.0/9.0, 8.0/9.0, -1.0/9.0}};
    kernel[2] = {new float[3]{-1.0/9.0, -1.0/9.0, -1.0/9.0}};
    (*this).appliqueFiltre(kernel);
}

// Applique un noyau size*size l'image en niveau de gris
void Image2D::appliqueFiltre(float** kernel, int size){
    int** tmp_ptr;
    tmp_ptr = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
    }
    int dx = size / 2;
    int dy = size / 2;
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            float tmp = 0.0f;
            for (int k = 0; k<size; k++){
                for (int l = 0; l<size; l++){
                    int posx = j - dx + l;
                    int posy = i - dy + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        tmp += (*this).ptr[posy][posx] * kernel[k][l];
                    }
                }
            tmp_ptr[i][j] = floor(tmp);
            }
        }
    }
    (*this).ptr = tmp_ptr;
}
// =================================================
// En RGB ==========================================
// Applique un noyau 3x3 a l'image en RGB
void Image2D::appliqueFiltreRGB(float** kernel){
    int** tmp_ptr;
    int** tmp_ptrR;
    int** tmp_ptrG;
    int** tmp_ptrB;
    tmp_ptr = new int* [(*this).nbx];
    tmp_ptrR = new int* [(*this).nby];
    tmp_ptrG = new int* [(*this).nby];
    tmp_ptrB = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
        tmp_ptrR[i] = new int[(*this).nbx];
        tmp_ptrG[i] = new int[(*this).nbx];
        tmp_ptrB[i] = new int[(*this).nbx];
    }
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            float tmp = 0.0f;
            float tmpR = 0.0f;
            float tmpG = 0.0f;
            float tmpB = 0.0f;
            for (int k = 0; k<3; k++){
                for (int l = 0; l<3; l++){
                    int posx = j - 1 + l;
                    int posy = i - 1 + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        tmp += (*this).ptr[posy][posx] * kernel[k][l];
                        tmpR += (*this).R[posy][posx] * kernel[k][l];
                        tmpG += (*this).G[posy][posx] * kernel[k][l];
                        tmpB += (*this).B[posy][posx] * kernel[k][l];
                    }
                }
            tmp_ptr[i][j] = floor(tmp);
            tmp_ptrR[i][j] = floor(tmpR);
            tmp_ptrG[i][j] = floor(tmpG);
            tmp_ptrB[i][j] = floor(tmpB);
            }
        }
    }
    (*this).ptr = tmp_ptr;
    (*this).R = tmp_ptrR;
    (*this).G = tmp_ptrG;
    (*this).B = tmp_ptrB;
}

// Applique le filtre moyenne 3x3 a l'image en RGB
void Image2D::filtreMoyenneRGB(){
    float** kernel;
    kernel = new float*[3];
    for(int i = 0; i <3; i++)
        kernel[i] = new float[3];
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            kernel[i][j] = 1.0/9.0;
        }
    }
    (*this).appliqueFiltreRGB(kernel);
}

// Applique le filtre median 3x3 a l'image en niveau de gris
void Image2D::filtreMedianRGB(){
    int** tmp_ptr;
    int** tmp_ptrR;
    int** tmp_ptrG;
    int** tmp_ptrB;
    tmp_ptr = new int* [(*this).nbx];
    tmp_ptrR = new int* [(*this).nby];
    tmp_ptrG = new int* [(*this).nby];
    tmp_ptrB = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
        tmp_ptrR[i] = new int[(*this).nbx];
        tmp_ptrG[i] = new int[(*this).nbx];
        tmp_ptrB[i] = new int[(*this).nbx];
    }
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            int arr[9];
            int arrR[9];
            int arrG[9];
            int arrB[9];
            for (int k = 0; k<3; k++){
                for (int l = 0; l<3; l++){
                    int posx = j - 1 + l;
                    int posy = i - 1 + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        arr[k*3+l] = (*this).ptr[posy][posx];
                        arrR[k*3+l] = (*this).R[posy][posx];
                        arrG[k*3+l] = (*this).G[posy][posx];
                        arrB[k*3+l] = (*this).B[posy][posx];
                    }
                }
            }
            sort(arr, arr+9);
            sort(arrR, arrR+9);
            sort(arrG, arrG+9);
            sort(arrB, arrB+9);
            tmp_ptr[i][j] = arr[4];
            tmp_ptrR[i][j] = arrR[4];
            tmp_ptrG[i][j] = arrG[4];
            tmp_ptrB[i][j] = arrB[4];
        }
    }
    (*this).ptr = tmp_ptr;
    (*this).R = tmp_ptrR;
    (*this).G = tmp_ptrG;
    (*this).B = tmp_ptrB;
}


// Filtre passe haut en utilisant un filtre lineaire
void Image2D::filtrePasseHautRGB(){
    float** kernel;
    kernel = new float*[3];
    kernel[0] = {new float[3]{-1.0/9.0, -1.0/9.0, -1.0/9.0}};
    kernel[1] = {new float[3]{-1.0/9.0, 8.0/9.0, -1.0/9.0}};
    kernel[2] = {new float[3]{-1.0/9.0, -1.0/9.0, -1.0/9.0}};
    (*this).appliqueFiltreRGB(kernel);
}

// Applique un noyau size*size l'image en RGB
void Image2D::appliqueFiltreRGB(float** kernel, int size){
    int** tmp_ptr;
    int** tmp_ptrR;
    int** tmp_ptrG;
    int** tmp_ptrB;
    tmp_ptr = new int* [(*this).nbx];
    tmp_ptrR = new int* [(*this).nby];
    tmp_ptrG = new int* [(*this).nby];
    tmp_ptrB = new int* [(*this).nby];
    for (int i=0; i<(*this).nby ; i++){
        tmp_ptr[i] = new int[(*this).nbx];
        tmp_ptrR[i] = new int[(*this).nbx];
        tmp_ptrG[i] = new int[(*this).nbx];
        tmp_ptrB[i] = new int[(*this).nbx];
    }
    int dx = size / 2;
    int dy = size / 2;
    for (int i = 0; i<(*this).nbx; i++){
        for (int j = 0; j<(*this).nby; j++){
            float tmp = 0.0f;
            float tmpR = 0.0f;
            float tmpG = 0.0f;
            float tmpB = 0.0f;
            for (int k = 0; k<size; k++){
                for (int l = 0; l<size; l++){
                    int posx = j - dx + l;
                    int posy = i - dy + k;
                    if (posx >= 0 && posx < (*this).nbx && posy >= 0 && posy < (*this).nby){
                        tmp += (*this).ptr[posy][posx] * kernel[k][l];
                        tmpR += (*this).R[posy][posx] * kernel[k][l];
                        tmpG += (*this).G[posy][posx] * kernel[k][l];
                        tmpB += (*this).B[posy][posx] * kernel[k][l];
                    }
                }
            tmp_ptr[i][j] = floor(tmp);
            tmp_ptrR[i][j] = floor(tmpR);
            tmp_ptrG[i][j] = floor(tmpG);
            tmp_ptrB[i][j] = floor(tmpB);
            }
        }
    }
    (*this).ptr = tmp_ptr;
    (*this).R = tmp_ptrR;
    (*this).G = tmp_ptrG;
    (*this).B = tmp_ptrB;
}
