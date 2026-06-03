/**
 * @file searching.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de busqueda
 */
#ifndef SEARCHING_H
#define SEARCHING_H

// su boca hizo como una !U!. ?!q!ue habra querido decir con eso?
// generator.h

#include <stdio.h>
#include "player.h"

int linear_search(Player V[], int n, Player *x,int (*comp_f)(Player *, Player *));
int binary_search(Player V[], int beg, int end, Player *x);
int binary_search_recursive(Player V[], int beg, int end, Player *x);
void binary_search_range(Player V[], int n, Player *x, int *first, int *last);
int exponential_search(Player V[], int n, Player *x);
int interpolation_search(Player V[], int n, Player *x);


#endif

// Aqui van unas palabras de Dios:
// ...
// ...
// ...
    // * Nota de autor: Milton dejo el visto y se demoro mas de 5 mins en responder.
    // Por lo que asumiremos que Dios es mudo.
