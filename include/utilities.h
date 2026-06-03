/**
 * @file utilities.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Utilidades micelaneas
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

// Colores para texto
#define CLEAR_SCREEN "\033[H\033[J"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define RESET "\x1b[0m"
#define DARK_GRAY "\x1b[90m"
#define LIGHT_GRAY "\x1b[37m"
#define WHITE "\x1b[97m"
#define YELLOW "\x1b[38;5;229m"
#define DARK_YELLOW "\x1b[38;5;220m"
#define ORANGE "\x1b[38;5;216m"
#define BROWN "\x1b[38;5;172m"
#define DARK_BLUE "\x1b[38;5;75m"
#define LIGHT_BLUE "\x1b[38;5;153m"
#define MAGENTA "\x1b[38;5;183m"
#define PURPLE "\x1b[38;5;92m"
#define LIGHT_RED "\x1b[38;5;210m"
#define DARK_RED "\x1b[38;5;160m"
#define LIGHT_GREEN "\x1b[38;5;157m"
#define DARK_GREEN "\x1b[38;5;2m"

// Colores de cajas (dado que "Even Darker _" resulto comico, asi quedara XD )
#define EVEN_DARKER_GREEN "\x1b[38;5;34m"
// EVEN DARKER ES MUCHO YAPO KJASHDKJHASD COMO VAS A NECESITAR TANTOS VERDES
#define EVEN_DARKER_BLUE "\x1b[38;5;25m"
#define EVEN_DARKER_RED "\x1b[38;5;124m"

// Colores de fondo
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"

// Magenta pallete
#define MAG1 "\x1b[38;5;170m"
#define MAG2 "\x1b[38;5;207m"
#define MAG3 "\x1b[38;5;213m"
#define MAG4 "\x1b[38;5;219m"
#define MAG5 "\x1b[38;5;177m"
#define MAG6 "\x1b[38;5;171m"

// !MIRA! el nivel de !INGLES! que posees,
// searching.c
#endif