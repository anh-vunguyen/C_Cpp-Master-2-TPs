//
//  Image2D.cpp
//  TP1C++
//
//  TP Created by Gustavo Guerrero on 15/09/2019.
//  Answered and completed by Anh Vu Nguyen

#include "Image2D.hpp"
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

    for (int i=0; i< (*this).nbx; i++){
        for (int j=0; j < (*this).nby; j++) {
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
