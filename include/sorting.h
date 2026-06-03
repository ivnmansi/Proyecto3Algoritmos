/**
 * @file sorting.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de ordenamiento
 */

#ifndef SORTING_H
#define SORTING_H

// Pero no creo que la cajita musical caiga tan bajo como un !GUION BAJO!.
// generate_exec_times.h

#include <stdio.h>
#include <stdlib.h>
#include "player.h"

/**
 * @file sorting.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de ordenamiento
 */
void swap_sort(Player V[], int n, int (*comp_f)(Player *, Player *));
void insertion_sort(Player V[], int n, int (*comp_f)(Player *, Player *));
void selection_sort(Player V[], int n, int (*comp_f)(Player *, Player *));
void cocktail_shaker_sort(Player V[], int n, int (*comp_f)(Player *, Player *));
void merge_sort_classic(Player V[], int n, int (*comp_f)(Player *, Player *));
void merge_sort_optimized(Player V[], int n, int threshold, int (*comp_f)(Player *, Player *));
void quick_sort(Player V[], int n, int pivot_type, int (*comp_f)(Player *, Player *));
Player quick_select(Player V[], int n, int k, int pivot_type, int (*comp_f)(Player *, Player *));

#endif // SORTING_H

//a q kle peptega