#ifndef ENTRE_SORTIE_H
#define ENTRE_SORTIE_H

#include <stdio.h>

void sauvegarde(const int *tas_init,
                const int *tas_ajout,
                const int *tas_final,
                int n,
                FILE *f);

#endif // ENTRE_SORTIE_H