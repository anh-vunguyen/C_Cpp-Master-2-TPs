//
//  main.cpp
//  TP1C++
//
//  TP Created by Gustavo Guerrero on 15/09/2019.
//  Answered and completed by Anh Vu Nguyen

#include <iostream>
#include "point2D.h"
#include "point3D.h"
#include "Image2D.hpp"

using namespace std;

int main()
{
/** Exercise 1 Objet point2D **/
/*
    cout << "Objet point2D" << endl;
    point2D A(1,1);
    point2D B;
    cout << "A : " << endl;
    A.print();
    cout << "B : " << endl;
    B.print();
    cout << "Norme de A : " << endl;
    cout<<A.CalculeNorme()<<endl;

    cout<<"B=A  : "<<endl;
    B=A;
    B.print();

    cout<<"C=B  : "<<endl;
    point2D C=B;

    cout<<"C : "<<endl;
    C.print();
    C.set_x(4);
    cout<<"C x =4: "<<endl;
    C.print();

    cout<<"B : "<<endl;
    B.print();

    cout << "Operateur surcharge" << endl;
    point2D D;
    D = B + C;
    cout<<"D  = B + C : "<<endl;
    D.print();
    cout << "B != B ? : " << endl;
    bool res = (B != B);
    cout << res << endl;

    cout <<"A+=B  : "<<endl;
    A+=B;
    A.print();

    cout << "A=B? :" << endl;
    if (A==B)
        cout<<">> A=B"<<endl;
    else cout<<">> A!=B"<<endl;
    B.set_x(4);
    cout << "C=B? :" << endl;
    if (C==B)
        cout<<">> C=B"<<endl;
    else cout<<">> C!=B"<<endl;
*/
/** Points 3D **/
//    cout << "----- Test points 3D -----" << endl;
//    point3D C;
//    point3D D(1,1,2);
//    cout << "C: " << endl;
//    C.print();
//    cout << "D: " << endl;
//    D.print();
//
//    /** test surcharge opérateur += **/
//    cout << "test operateur += :" << endl;
//    D+=D;
//    D.print();
//
//    /** test opérateur << **/
//    cout << "test operateur << :" << endl;
//    cout <<"Point D: "<<D <<endl;
//
//    /** test opérateur == **/
//    cout << "test operateur == : D==D?" << endl;
//    bool res = (D==D);
//    cout << "Operateur == :" << res <<endl;
//
//    /** test création objets dynamique */
//    cout << "test creation objets dynamique" << endl;
//    point3D *pE=new point3D(0,1,2);
//    pE->print();
//    cout << *pE << endl;

    //-----PROJET-----
    cout<<"PROJET"<<endl;
    Image2D A;
    Image2D X(800, 600, 255, 1, 1, 12);
    char* f="mola.bmp";
    Image2D B(f,1,1);
    char* f2="lena24.bmp";
    Image2D C(f2,1,1);

    FILE *fp;
    FILE *fp2;
    fp=fopen("lena24.bmp","rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, fp); // read the 54-byte header
    fclose(fp);
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int size = 3 * width * height;
    unsigned char* image_and_en_tete_to_save = new unsigned char[size];
    for(int iD=0;iD<54;iD++)//the first 54 bytes
    {
        image_and_en_tete_to_save[iD]=info[iD];
        //printf("%d %x\n",i,image_and_en_tete_to_save[i]);
    }
    for (int i=0; i<C.getNbx(); i++) {
        for (int j=0; j<C.getNby(); j++) {
            image_and_en_tete_to_save[54+(i*(C.getNby())+j)*3]=(unsigned char)C.getPixelValue(i,j);
            image_and_en_tete_to_save[54+1+(i*(C.getNby())+j)*3]=(unsigned char)C.getPixelValue(i,j);
            image_and_en_tete_to_save[54+2+(i*(C.getNby())+j)*3]=(unsigned char)C.getPixelValue(i,j);
        }
    }
    fp2=fopen("lena24_gray2.bmp","wb");
    fwrite(image_and_en_tete_to_save,sizeof(char),(54+C.getSize()*3),fp2);// fonction to read binary
    ///Closure
    fclose(fp2);
s
    return 0;
}
