#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M_PI 3.14159265358979323846

double f(double x); // prototype de la fonction f()

// Definition de la founction f
double f(double x){
    // return x*x;
    return x*x - 3*x - 10;
    // return x*x*x - 3*x*x - 3*x - 35;
    // return ((exp(10*x) - 1)/(exp(10*x) + 1)) - 0.5;
    // return cos(x + (3*M_PI/8));
}

// Algorithme de Bissection
void bisection(double a, double b){
    double EPSILON = 0.00001;
    double c = a;
    int nIter = 0;
    if(f(a)*f(b)<0){
        while( (b-a) >= EPSILON){
            c = (a + b)/2;
            if(f(c) == 0){
                break;
            }else if(f(c)*f(a) < 0){
                b = c;
            }else{
                a = c;
            }
            nIter++;
        }
        printf("Le point d'annulation de la fonction f(x): %f\n", c);
        printf("Le nombre d'iterations: %d\n", nIter);
    }else{
        printf("L'interval [a, b] ne sastifait pas l'algorithme\n");
    }
}

// Algorithme de False Position (Regula falsi)
void false_position(double a, double b){
    double MAX_ITER = 1000;
    double c = a;
    double nIter2 = 0;
    if (f(a)* f(b) < 0){
        for(nIter2=0; nIter2 < MAX_ITER; nIter2++){
            c = (a*f(b) - b*f(a))/ (f(b) - f(a));
            if (f(c)==0){
                break;
            }else if(f(c)*f(a) < 0){
                b = c;
            }else{
                a = c;
            }
        }
        printf("Le point d'annulation de la fonction f(x): %f\n", c);
        printf("Le nombre d'iterations: %d\n", nIter2);
    }else{
         printf("L'interval [a, b] ne sastifait pas l'algorithme\n");
    }
}

// Fonction principale
int main()
{
    // Initialisation des variables
    double a,b,pas,x,y;

    // [a, b] et pas
    printf("Tapez [a,b], pas: \n");
    scanf("%lf%lf%lf", &a, &b,&pas);
    printf("Vous avez tape [%f, %f], pas= %f\n",a,b,pas);

    // Pour sauvegarder les valeurs de f
    FILE *fp;
    fp=fopen("function.txt","w");

    // Boucle FOR pour avoir entre x=a et x=b avec un pas
    for(x=a; x<b+pas; x+=pas){
        y = f(x);
        printf("x = %f, y = %f\n", x, y);
        fprintf(fp,"%f,\t %f\n",x,y); // Ecrire x et y dans le fichier txt
    }
    fclose(fp);

    // Le point d'annulation d'une fonction f(x)
    double c, d;
    printf("Tapez [c,d]\n");
    scanf("%lf%lf", &c, &d);
    printf("L'algorithme de bissection\n");
    bisection(c, d);
    printf("L'algorithme de la Fausse Position\n");
    false_position(c, d);
    return 0;
}
