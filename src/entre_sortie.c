#include <stdio.h>
#include "../include/entre_sortie.h"

//sauvegarder dans le fichier f les valeurs du tas et les indices
void sauvegarde(const int *tas_init, const int *tas_ajout, const int *tas_final, int n, FILE *f){
    if(tas_ajout == NULL)
        for(int i=0; i<n; i++){
            fprintf(f, "%d\t%d\t%d\n", i, tas_init[i], tas_final[i]);
        }
    else
        for(int i=0; i<n; i++){
        fprintf(f, "%d\t%d\t%d\t%d\n", i, tas_init[i], tas_ajout[i], tas_final[i]);
    }
}


/*
void sauvegarde_v2(const int *tas_init, const int *tas_ajout, const int *tas_final, int n, FILE *f){
    for(int i=0; i<n; i++){
        fprintf(f, "%d\t%d\t%d\t%d\n", i, tas_init[i], tas_ajout[i], tas_final[i]);
    }
}*/
