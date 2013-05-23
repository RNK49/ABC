#include <stdio.h>
#include <stdlib.h>
#include "ABC.c"

int main(void)
{
    double minX,maxX,minY,maxY;
    int taille, nbessais,nbcycles;
    Bee * colonie,* meilleur;

    double rayon(double x,double y){
        return x*x+y*y;
    }
    printf("Entrez un nombre d'ouvrieres : ");
    scanf("%i",&taille);
    printf("Entrez le seuil minimal de X : ");
    scanf("%lf",&minX);
    printf("Entrez le seuil maximal de X : ");
    scanf("%lf",&maxX);
    printf("Entrez le seuil minimal de Y : ");
    scanf("%lf",&minY);
    printf("Entrez le seuil maximal de Y : ");
    scanf("%lf",&maxY);
    printf("Entrez le nombre d'essais maximum : ");
    scanf("%i",&nbessais);
    printf("Entrez le nombre de cycles maximum : ");
    scanf("%i",&nbcycles);
    AlgoABC(rayon,'m',colonie,taille,minX,maxX,minY,maxY,nbessais,nbcycles,meilleur);
    affichBest(meilleur);
    return 0;
}
