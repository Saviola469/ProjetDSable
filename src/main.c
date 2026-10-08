#include <stdio.h>
#define N 50
#define H 20
#define Nb_ajout 3
#include "../include/logiquetas.h"
#include "../include/entre_sortie.h"

int main(void){
    
    int tas_init[N];
    //int tas[N];
    int tas_final[N];
    int tas_ajout[N];
    FILE* f = fopen("../datas/data_simple.csv", "a");
    FILE* g = fopen("../datas/data_vent.csv", "a");
    FILE* h = fopen("../datas/data_ajout.csv", "a");
    if(f == NULL || g == NULL || h == NULL){
        perror("fopen");
        if(f != NULL){
            fclose(f);
        }
        if(g != NULL){
            fclose(g);
        }
        if(h != NULL){
            fclose(h);
        }
        return 1;
    }

    //stabilisation simple
    initialisation(tas_init, N, H);
    for(int i=0; i<N; i++){
        tas_final[i] = tas_init[i];
    }
    stabiliser(tas_final, N);
    sauvegarde(tas_init, NULL, tas_final, N, f);
    fclose(f);
    

    //ajout de grains
    for(int i=0; i<N; i++){
        tas_final[i] = tas_init[i];
    }
    stabiliser (tas_final, N);
    for(int i=0; i<Nb_ajout; i++){
        ajout(tas_final, N, N/2);
        for(int i=0; i<N; i++){
            tas_ajout[i] = tas_final[i];
        }  
        stabiliser (tas_final, N);
        sauvegarde(tas_init, tas_ajout, tas_final, N, h);
    }
    
    
    fclose(h);

    //stabilisation avec effet du vent
    
    int speed = 50; //vitesse en km/h
    for(int i=0; i<N; i++){
        tas_final[i] = tas_init[i];
        //tas[i] = tas_init[i];
    }
    //stabiliser (tas, N);
    effet_vent(tas_final, N, speed);
    sauvegarde(tas_init, NULL, tas_final, N, g);
    //sauvegarde(tas_init, tas, tas_final, N, g);

    fclose(g);
    

    return 0;
}

