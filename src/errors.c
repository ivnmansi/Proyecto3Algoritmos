/**
 * @file errors.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones para manejo de errores
 */
#include "errors.h"

// que haga !W!iwiwiwi cuando tenga la edad suficiente para 
// install-allegro6.sh

/**
 * @brief Funcion para imprimir un error
 *
 * @param num Codigo de error
 * @param target Algun parametro que puede ser necesario para el error
 * @param obs Algun texto que puede acompannar el error
 */
void print_error(int num, const char *target, const char *obs)
{
	if (num >= 100 && num < 200)
	{
		printf(ANSI_COLOR_RED "Error %d: " ANSI_COLOR_RESET, num);
	}
	else if (num >= 200 && num < 300)
	{
		printf(ANSI_COLOR_RED "Fatal Error %d: " ANSI_COLOR_RESET, num);
	}
	else if (num >= 300 && num < 400)
	{
		printf(ANSI_COLOR_YELLOW "Warning %d: " ANSI_COLOR_RESET, num);
	}
	switch (num)
	{
	// Errores generales
	case 100:
		printf("File %s could not be read\n", target);
		break;
	case 101:
		printf("File %s could not be opened\n", target);
		break;
	case 102:
		printf("It was not possible to allocate memory for %s\n", target);
		break;
	// Errores Fatales
	// Warnings
	case 301:
		printf("The number of players is too high, console will show the first %d players\n", MAX_CONSOLE_READABLE_PLAYERS);
		break;
	//case 302:
	//	printf("Q.E.P.D. mi warning que no duró ni siquiera un commit (creo)\n");
	// Default
	default:
		printf("unknown error %d\n", num);
	}
	if (obs != NULL)
	{
		printf("%s\n", obs);
	}
}