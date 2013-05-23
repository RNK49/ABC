#ifndef ABC_H_INCLUDED
#define ABC_H_INCLUDED

typedef struct {
    double x;
    double y;
    double valeur;
    double fitness;
    double proba;
    int essais;
}Bee;

int bestPos(Bee * colony, int size, char opt);
void affichBest(Bee * bee);
void affichColony(Bee * colony, int size);
int indicerand(int courant, int size);
Bee * InitOptim(double (*f)(), double minX, double maxX, double minY, double maxY, int size);
double positionXMAJ(Bee * colony, int ind, int k, double minX, double maxX, int size);
double positionYMAJ(Bee * colony, int ind, int k, double minY, double maxY, int size);
double valeurMAJ(double (*f)(), Bee * colony, int ind);
double fitnessMAJ(Bee * colony, int ind);
double sommeFit(Bee * colony, int size);
void EmployedBees(double (*f)(), char opt, double minX, double maxX, double minY, double maxY, Bee * colony, int size);
void OnlookerBees(double (*f)(), char opt, double minX, double maxX, double minY, double maxY, Bee * colony, int size);
void ScoutBees(double (*f)(), char opt, Bee * colony, int size, double minX, double maxX, double minY, double maxY, int *nbcycles, int LimiteEssais, Bee * memoBest);
void AlgoABC(double (*f)(), char opt, Bee * colony, int size, double minX, double maxX, double minY, double maxY, int LimiteEssais, int maxCycle, Bee * memoBest);
#endif // ABC_H_INCLUDED
