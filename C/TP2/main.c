#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LONGUEUR_ENTETE 54 // la taille de l’entête bmp

// Compléter ici …. functions…
FILE* ouverture_fichier(char* filename){
    FILE* fp;
    fp = fopen(filename, "rb");
    if(!fp){
        printf("ERROR!\n");
        exit(1);
    }
    return fp;
}

void lecture_entete(FILE* fp, char* en_tete){
    fread(en_tete, 1, LONGUEUR_ENTETE, fp);
}

long int analyse_entete(char* en_tete){
    long int width = ((unsigned char)(en_tete[21]) << 24 ) | ((unsigned char)(en_tete[20]) << 16) | ((unsigned char)(en_tete[19]) << 8) | ((unsigned char)(en_tete[18]));
    long int height = ((unsigned char)(en_tete[25]) << 24) | ((unsigned char)(en_tete[24]) << 16) | ((unsigned char)(en_tete[23]) << 8) | ((unsigned char)(en_tete[22]));
    return width * height;
}

void get_width_height(char* en_tete,long int* width,long int* height){
    *width = ((unsigned char)(en_tete[21]) << 24 ) | ((unsigned char)(en_tete[20]) << 16) | ((unsigned char)(en_tete[19]) << 8) | ((unsigned char)(en_tete[18]));
    *height = ((unsigned char)(en_tete[25]) << 24) | ((unsigned char)(en_tete[24]) << 16) | ((unsigned char)(en_tete[23]) << 8) | ((unsigned char)(en_tete[22]));
}

void Lecture_ComposantesRGB(FILE* fp, long int nbre_pixels, unsigned char* R, unsigned char* G, unsigned char* B){
    unsigned char* data = (unsigned char*) malloc(3*nbre_pixels*sizeof(char));
    fread(data, 1, nbre_pixels*3, fp);
    for(int i=0; i<nbre_pixels; i++){
        B[i] = data[3*i];
        G[i] = data[3*i+1];
        R[i] = data[3*i+2];
    }
    free(data);
}

void ecriture_nouveau_fichier(FILE* fp2, char* filename, char* en_tete,long int nbre_pixels,unsigned char* R,unsigned char* G,unsigned char* B){
    fp2 = fopen(filename, "wb");
    fwrite(en_tete, 1, LONGUEUR_ENTETE, fp2);
    for(int i=0; i<nbre_pixels; i++){
        unsigned char* colorPixel = (unsigned char*) malloc(3);
        colorPixel[0] = B[i];
        colorPixel[1] = G[i];
        colorPixel[2] = R[i];
        fwrite(colorPixel, 3, 1, fp2);
        free(colorPixel);
    }
}

void onlyRed(long int nbre_pixels,unsigned char* R,unsigned char* G,unsigned char* B){
    for(int i=0; i<nbre_pixels; i++){
        G[i] = 0x0;
        B[i] = 0x0;
    }
}

void onlyGreen(long int nbre_pixels,unsigned char* R,unsigned char* G,unsigned char* B){
    for(int i=0; i<nbre_pixels; i++){
        R[i] = 0x0;
        B[i] = 0x0;
    }
}

void onlyBlue(long int nbre_pixels,unsigned char* R,unsigned char* G,unsigned char* B){
    for(int i=0; i<nbre_pixels; i++){
        R[i] = 0x0;
        G[i] = 0x0;
    }
}

void invertRGB(long int nbre_pixels,unsigned char* R,unsigned char* G,unsigned char* B){
    for(int i=0; i<nbre_pixels; i++){
        R[i] = 0xFF - R[i];
        G[i] = 0xFF - G[i];
        B[i] = 0xFF - B[i];
    }
}

int main(void)
{
    FILE* fp; // Fichier de lecture
    FILE* fp2 = NULL; // Fichier pour écriture
    char en_tete[LONGUEUR_ENTETE+1];

    //Compléter ici … interface avec l’utilisateur.. etc.
    fp = ouverture_fichier("lena24.bmp"); // utilisez fopen
    lecture_entete(fp, en_tete); // utilisez la fonction fread dedans

    // cette fonction doit retourner la taille de l’image en pixels (hauteur x largeur)
    long int nbre_pixels = analyse_entete(en_tete);
    printf("Nombre de pixels: %ld\n", nbre_pixels);

    // Width & Height
    long int width ;
    long int height ;
    get_width_height(en_tete,&width,&height);
    printf("Width: %ld\n", width);
    printf("Height: %ld\n", height);

    //Compléter ici … allocation memoire.. etc.
    unsigned char* R;
    unsigned char* G;
    unsigned char* B;
    R = (unsigned char*) malloc(nbre_pixels);
    G = (unsigned char*) malloc(nbre_pixels);
    B = (unsigned char*) malloc(nbre_pixels);
    Lecture_ComposantesRGB(fp, nbre_pixels, R, G, B);

    //onlyRed(nbre_pixels, R, G, B);
    //onlyGreen(nbre_pixels, R, G, B);
    //onlyBlue(nbre_pixels, R, G, B);
    invertRGB(nbre_pixels, R, G, B);

    ecriture_nouveau_fichier(fp2, "sortie.bmp", en_tete, nbre_pixels, R, G, B);
    fclose(fp);
    fclose(fp2);
    free(R);
    free(G);
    free(B);
    printf ("\n\nAppuyez sur une touche pour finir!\n\n");
    return 0;
}
