/**
 * @file generator.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funcion y utilidades de generacion
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Quiza sea una referencia a algo de hace !5! anhos atras, 
// Makefile

#include "utilities.h"
#include "errors.h"
#include "player.h"

int generate_csv(int n, int case_type);
void set_generator_quiet(int quiet);
Player* load_players(char* file, int *out_n);

#endif

// 𝑚𝑚𝑚