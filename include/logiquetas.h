#ifndef LOGIQUETAS_H
#define LOGIQUETAS_H

void initialisation(int *tas, int n, int h);
void ajout(int *tas, int n, int index);
void stabiliser_indice(int *tas, int n, int index);
int compare_tas(const int *tas, const int *copie, int n);
void stabiliser(int *tas, int n);
void effet_vent_indice(int *tas, int n, int index, int sens_vent, double p_speed);
int effet_vent(int *tas, int n, int speed);

#endif // LOGIQUETAS_H