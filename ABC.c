#include "ABC.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int indicerand(int courant, int size){
    int k= rand() % size;
    while (k==courant) k=rand() % size;
    return k;
}

Bee * InitOptim(double (*f)(), double minX, double maxX, double minY, double maxY, int size) {
    int i;

    srand(time(NULL));

    Bee * colony=(Bee *)malloc(size*sizeof(Bee));
    if (colony==NULL){
        printf("Erreur init colonie.");
        exit(-1);
    }
    for (i=0;i<size;i++)
    {
        colony[i].x=((double)rand()/RAND_MAX)*(maxX-minX)+minX;
        colony[i].y=((double)rand()/RAND_MAX)*(maxY-minY)+minY;
        colony[i].valeur=f(colony[i].x,colony[i].y);
        if (colony[i].valeur>=0)
            colony[i].fitness=1./(1.+colony[i].valeur);
        else
            colony[i].fitness=1-colony[i].valeur;
        colony[i].essais=0;
    }

    for (i=0;i<size;i++)
    {
        colony[i].proba=colony[i].fitness/sommeFit(colony, size);
    }
    return colony;
}

void affichColony(Bee * colony, int size) {
    int i;

    printf("----x----|----y----|--f(x,y)--|--fitness--|--cycle--|--proba--- \n");
    for (i=0;i<size;i++){
        printf("| %+.4f| %+.4f|  %+.4f |   %+.4f |   %i  |  %+.3f \n", colony[i].x, colony[i].y, colony[i].valeur, colony[i].fitness, colony[i].essais,colony[i].proba);
        printf("|---------|---------|----------|-----------|---------| \n");
    }
}

void affichBest(Bee * bee) {

    printf("----x----|----y----|--f(x,y)--|--fitness--|--cycle--|--proba--- \n");
    printf("| %+.4f| %+.4f|  %+.4f |   %+.4f |   %i  |  %+.3f \n", bee->x, bee->y, bee->valeur, bee->fitness, bee->essais,bee->proba);
    printf("|---------|---------|----------|-----------|---------| \n");
}

double sommeFit(Bee * colony, int size){
    double sum;
    int i;

    sum=0;
    for (i=0;i<size;i++){
        sum=sum+colony[i].fitness;
    }

    return sum;
}

double positionXMAJ(Bee * colony, int ind, int k, double minX, double maxX, int size){
    double r,newx;

    r=((double)rand()/RAND_MAX)*2-1;
    newx=colony[ind].x+r*(colony[ind].x-colony[k].x);
    while (newx<minX || newx>maxX)
    {
        k=indicerand(ind, size);
        r=((double)rand()/RAND_MAX)*2-1;
        newx=colony[ind].x+r*(colony[ind].x-colony[k].x);
    }

    return newx;
}

double positionYMAJ(Bee * colony, int ind, int k, double minY, double maxY, int size){
    double r,newy;

    r=((double)rand()/RAND_MAX)*2-1;
    newy=colony[ind].x+r*(colony[ind].y-colony[k].y);
    while (newy<minY || newy>maxY)
    {
        k=indicerand(ind, size);
        r=((double)rand()/RAND_MAX)*2-1;
        newy=colony[ind].y+r*(colony[ind].y-colony[k].y);
    }

    return newy;
}

double valeurMAJ(double (*f)(), Bee * colony, int ind){
    return f(colony[ind].x,colony[ind].y);
}

double fitnessMAJ(Bee * colony, int ind){
    if (colony[ind].valeur>=0)
        return 1./(1.+colony[ind].valeur);
    else
        return 1-colony[ind].valeur;
}

void EmployedBees(double (*f)(), char opt, double minX, double maxX, double minY, double maxY, Bee * colony, int size){
    int i,k;
    double newx,newy,newval,newfit;

    for (i=0;i<size;i++)
    {
        k=indicerand(i, size);
        newx=positionXMAJ(colony,i,k,minX,maxX,size);
        newy=positionYMAJ(colony,i,k,minY,maxY,size);
        newval=valeurMAJ(f,colony,i);
        newfit=fitnessMAJ(colony,i);
        if (opt=='m')
        {
            if (colony[i].fitness<newfit)
            {
                colony[i].x=newx;
                colony[i].y=newy;
                colony[i].valeur=newval;
                colony[i].fitness=newfit;
                colony[i].essais=0;
            }
            else
                colony[i].essais++;
        }
        else if (opt=='M')
        {
            if (colony[i].fitness>newfit)
            {
                colony[i].x=newx;
                colony[i].y=newy;
                colony[i].valeur=newval;
                colony[i].fitness=newfit;
                colony[i].essais=0;
            }
            else
                colony[i].essais++;
        }

    }
    for (i=0;i<size;i++)
    {
        colony[i].proba=colony[i].fitness/sommeFit(colony, size);
    }

}

int bestPos(Bee * colony, int size, char opt){
    int i,res;

    res=0;
    for (i=1;i<size;i++)
    {
        if (opt=='m')
        {
            if (colony[i].valeur<colony[res].valeur)
                res=i;
        }
        else if (opt=='M')
        {
            if (colony[i].valeur>colony[res].valeur)
                res=i;
        }
    }

    return res;
}


void OnlookerBees(double (*f)(), char opt, double minX, double maxX, double minY, double maxY, Bee * colony, int size){
    int h,i,j,k;
    double newx, newy, newval, newfit,sum_prob,r;

    for (i=0;i<size;i++)
    {
        r=(double)rand()/RAND_MAX;
        sum_prob=0;
        j=0;
        while (sum_prob<=r)
        {
            sum_prob=sum_prob+colony[i].proba;
            j=j+1;
        }
        k=indicerand(j, size);
        newx=positionXMAJ(colony,j,k,minX,maxX,size);
        newy=positionYMAJ(colony,j,k,minY,maxY,size);
        newval=valeurMAJ(f,colony,j);
        newfit=fitnessMAJ(colony,j);
        if (opt=='m')
        {
            if (colony[j].fitness<newfit)
            {
                colony[j].x=newx;
                colony[j].y=newy;
                colony[j].valeur=newval;
                colony[j].fitness=newfit;
                colony[j].essais=0;
            }
            else
                colony[j].essais++;
        }
        else if (opt=='M')
        {
            if (colony[j].fitness>newfit)
            {
                colony[j].x=newx;
                colony[j].y=newy;
                colony[j].valeur=newval;
                colony[j].fitness=newfit;
                colony[j].essais=0;
            }
            else
                colony[j].essais++;
        }
        for (h=0;h<size;h++)
        {
            colony[h].proba=colony[h].fitness/sommeFit(colony, size);
        }
    }
}

void ScoutBees(double (*f)(),char opt, Bee * colony, int size, double minX, double maxX, double minY, double maxY, int *nbcycles, int LimiteEssais, Bee * memoBest){
    int i,incCycle;

    incCycle=0;

    memoBest=&colony[bestPos(colony,size,opt)];
    for (i=0;i<size;i++)
    {
        if (colony[i].essais>LimiteEssais)
        {
            if (incCycle==0)
                incCycle=1;
            colony[i].x=((double)rand()/RAND_MAX)*(maxX-minX)+minX;
            colony[i].y=((double)rand()/RAND_MAX)*(maxY-minY)+minY;
            colony[i].valeur=f(colony[i].x,colony[i].y);
            if (colony[i].valeur>=0)
                colony[i].fitness=1./(1.+colony[i].valeur);
            else
                colony[i].fitness=1-colony[i].valeur;
            colony[i].essais=0;
        }
    }

    if (incCycle==1)
        (*nbcycles)++;
}

void AlgoABC(double (*f)(), char opt, Bee * colony, int size, double minX, double maxX, double minY, double maxY, int LimiteEssais, int maxCycle, Bee * memoBest){
    int nbcycles;

    memoBest=(Bee *)malloc(sizeof(Bee));
    if (memoBest==NULL)
    {
        printf("Erreur allocation meilleure position.");
        exit(-1);
    }
    colony=InitOptim(f,minX,maxX,minY,maxY,size);
    affichColony(colony,size);
    nbcycles=1;
    while(nbcycles<maxCycle)
    {
        EmployedBees(f,opt,minX,maxX,minY,maxY, colony,size);
        OnlookerBees(f,opt,minX,maxX,minY,maxY,colony,size);
        ScoutBees(f,opt,colony,size,minX,maxX,minY,maxY,&nbcycles,LimiteEssais,memoBest);
        //affichColony(colony,size);
        //printf("Press any key to continue...\n");
        //getchar();
    }
}
