#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/logiquetas.h"

#define MAX_ITER 100000

static void seed_rng_once(void){
    static int seeded = 0;
    if(!seeded){
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
}


//initialisation d'un tableau d'entiers de taille n et vide ?
void initialisation(int* tas, int n, int h){
    seed_rng_once();
    for(int i=0; i<n; i++){
        tas[i] = rand()%h;
        
    }
}


//ajout d'un grain à la fois
void ajout(int * tas, int n, int index){
    if(index<n && index>=0) 
        tas[index]+=6;
}



//stabilisation du tas de façon simple à un indice précis
void stabiliser_indice(int * tas, int n, int index){
    seed_rng_once();
    double r;
    if(index==0 && tas[index]-tas[index+1]>2){
        if(tas[index]>0){
            tas[index]--;
            tas[index+1]++;
        }
    }else if(index==n-1 && tas[index]-tas[index-1]>2){
        if(tas[index]>0){
            tas[index]--;
            tas[index-1]++;
        }
    }else {
        if((tas[index]-tas[index-1]>2) || (tas[index]-tas[index+1]>2)){
            if(tas[index+1]==tas[index-1]){
                r = (double)rand()/RAND_MAX;
                if(r>0.5){
                    if(tas[index]>0){
                        tas[index]--;
                        tas[index+1]++;
                    }
                }else{
                    if(tas[index]>0){
                        tas[index]--;
                        tas[index-1]++;
                    }
                }
            }else if(tas[index+1]>tas[index-1]){
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }else{
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }
        }else if((tas[index]-tas[index-1]>2) && (tas[index]-tas[index+1]<=2)){
            if(tas[index]>0){
                tas[index]--;
                tas[index-1]++;
            }
        }else if((tas[index]-tas[index-1]<=2) && (tas[index]-tas[index+1]>2)){
            if(tas[index]>0){
                tas[index]--;
                tas[index+1]++;
            }
        }
    }
}


//comparaison de tas qui retourne -1 si differents en 1 si egaux
int compare_tas(const int* tas, const int* copie, int n){
    for(int i=0; i<n; i++){
        if(tas[i]!=copie[i])    return -1;
    }
    return 1;
}



//stabilisation du tas de façon simple tout le tableau
void stabiliser(int * tas, int n){
    int copie[n];
    int i=0;
    int iter = 0;
    
    do{

        for(i=0; i<n;i++)   copie[i]=tas[i];
        for(i=0; i<n; i++)  stabiliser_indice(tas,n,i);
        iter++;

    }while(compare_tas(tas,copie,n)<0 && iter < MAX_ITER);
}


//effet du vent indice précis
// h_max est il encore nécessaire ?
void effet_vent_indice(int* tas, int n, int index, int sens_vent, double p_speed){
    seed_rng_once();
    double r = (double) rand()/RAND_MAX;
    if(sens_vent<0){
        //vent de la droite vers la gauche (-1)
        if(index==0 && r<0.8-p_speed && tas[index]-tas[index+1]>2){
            //80% de chance de tomber pour indice 0 et vent vers la gauche
            if(tas[index]>0){
                tas[index]--;
                tas[index+1]++;
            }
        }else if(index==n-1){
            if(tas[index]-tas[index-1]>2){
                //100% de chance de tomber pour indice n-1 et vent vers la gauche quand différence > 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }else if(tas[index]-tas[index-1]==2 && r<0.5-p_speed){
                //50% de chance de tomber pour indice n-1 et vent vers la gauche quand différence = 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }else if(tas[index]-tas[index-1]==1 && r<0.15-p_speed){
                //15% de chance de tomber pour indice n-1 et vent vers la gauche quand différence = 1
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }
        }else{
            if((tas[index]-tas[index-1]==1) && (tas[index]-tas[index+1]==1) && r<0.15-p_speed){
                //15% de chance d'aller à gauche si difference a gauche = difference a droite = 1
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }else if((tas[index]-tas[index-1]==2) && (tas[index]-tas[index+1]==2) && r<0.3-p_speed){
                //30% de chance d'aller à gauche si difference a gauche = difference a droite = 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index-1]++;
                }
            }else if((tas[index]-tas[index-1]>2) || (tas[index]-tas[index+1]>2)){
                //les 2 difference > 2
                if(tas[index+1]==tas[index-1]){
                    if(r>0.7-p_speed){
                        //70% de chance d'aller à gauche si gauche = droite
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index-1]++;
                        }
                    }else{
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index+1]++;
                        }
                    }
                }else if(tas[index+1]<tas[index-1]){
                    if(r>0.8-p_speed){
                        //80% de chance d'aller à droite si droite < gauche
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index+1]++;
                        }
                    }else{
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index-1]++;
                        }
                    }
                }else{
                    if(tas[index]>0){
                        tas[index]--;
                        tas[index-1]++;
                    }
                }
            }
        }
    }else{
        //vent de la gauche vers la droite (+1)
        if(index==n-1 && r<0.8-p_speed && tas[index]-tas[index-1]>2){
            //80% de chance de tomber pour indice n-1 et vent vers la droite
            if(tas[index]>0){
                tas[index]--;
                tas[index-1]++;
            }
        }else if(index==0){
            if(tas[index]-tas[index+1]>2){
                //100% de chance de tomber pour indice 0 et vent vers la droite quand différence > 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }else if(tas[index]-tas[index+1]==2 && r<0.5-p_speed){
                //50% de chance de tomber pour indice 0 et vent vers la droite quand différence = 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }else if(tas[index]-tas[index+1]==1 && r<0.15-p_speed){
                //15% de chance de tomber pour indice 0 et vent vers la droite quand différence = 1
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }
        }else{
            if((tas[index]-tas[index-1]==1) && (tas[index]-tas[index+1]==1) && r<0.15-p_speed){
                //15% de chance d'aller à droite si difference a gauche = difference a droite = 1
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }else if((tas[index]-tas[index-1]==2) && (tas[index]-tas[index+1]==2) && r<0.3-p_speed){
                //30% de chance d'aller à droite si difference a gauche = difference a droite = 2
                if(tas[index]>0){
                    tas[index]--;
                    tas[index+1]++;
                }
            }else if((tas[index]-tas[index-1]>2) || (tas[index]-tas[index+1]>2)){
                //les 2 difference > 2
                if(tas[index+1]==tas[index-1]){
                    if(r>0.7-p_speed){
                        //70% de chance d'aller à droite si gauche = droite
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index+1]++;
                        }
                    }else{
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index+1]++;
                        }
                    }
                }else if(tas[index+1]>tas[index-1]){
                    if(r>0.8-p_speed){
                        //80% de chance d'aller à gauche si droite > gauche
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index-1]++;
                        }
                    }else{
                        if(tas[index]>0){
                            tas[index]--;
                            tas[index+1]++;
                        }
                    }
                }else{
                    if(tas[index]>0){
                        tas[index]--;
                        tas[index+1]++;
                    }
                }
            }
        }
    }  
}


//effet du vent sur tout le tas retourne -1 si c'est vers la gauche et 1 dans l'autre cas 
// h_max est il encore nécessaire ?
int effet_vent(int* tas, int n, int speed){
    int copie[n];
    seed_rng_once();
    int sens_vent = (rand()%2 == 0) ? -1 : 1;
    int i=0;
    int iter = 0;
    printf("Sens vent %d",sens_vent);
    double p_speed = (double)speed/500.0;
    do{

        for(i=0; i<n;i++)   copie[i]=tas[i];
        for(i=0; i<n; i++)  effet_vent_indice(tas,n,i,sens_vent,p_speed);
        iter++;

    }while(compare_tas(tas,copie,n)<0 && iter < MAX_ITER);

    return sens_vent;
}
