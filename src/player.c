/**
 * @file player.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Implementacion de las funciones de comparacion para la estructura Player.
 */

#include "player.h"
#include "utilities.h"

/**
 * @brief Intercambia dos jugadores
 * @param p1 puntero a jugador 1
 * @param p2 puntero a jugador 2
 */
void swap_player(Player *p1, Player *p2) {
	Player temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}


// y c!u!ando la intente construir se rompa al ya haber transcurrido un laaargo tiempo tras eso... 
// sorting.h



/**
 * @brief Compara si dos jugadores son exactamente iguales en todos sus campos.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return true Si todos los campos son equivalentes.
 * @return false Si al menos un campo es distinto.
 */
bool are_players_equal(Player *p1, Player *p2) {
	// Validar que los punteros no sean nulos
	if (p1 == NULL || p2 == NULL) return false;

	// Comparar campos numericos y booleanos
	if (p1->id != p2->id) return false;
	if (p1->score != p2->score) return false;
	if (p1->competitions != p2->competitions) return false;
	if (p1->potatoe != p2->potatoe) return false;

	// Comparar arreglos de caracteres estaticos (name y team)
	if (strcasecmp(p1->name, p2->name) != 0) return false;
	if (strcasecmp(p1->team, p2->team) != 0) return false;

	return true;
}

/**
 * @brief Compara dos jugadores basandose en su ID.
 * * Realiza una comparacion numerica directa del campo `id`.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return -1 si el ID de p1 es menor, 1 si es mayor, 0 si son iguales.
 */
int compare_id(Player *p1, Player *p2) {
	return p1->id - p2->id;
}

/**
 * @brief Compara dos jugadores alfabeticamente por su nombre.
 * * Utiliza la funcion estandar strcmp para determinar el orden lexicografico.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return -1 si el nombre de p1 va antes, 1 si va despues, 0 si son iguales.
 */
int compare_name(Player *p1, Player *p2) {
	return strcasecmp(p1->name, p2->name);
}

/**
 * @brief Compara dos jugadores alfabeticamente por el nombre de su equipo.
 * * Utiliza la funcion estandar strcmp para evaluar la cadena de caracteres del equipo.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return -1 si el equipo de p1 va antes, 1 si va despues, 0 si son iguales.
 */
int compare_team(Player *p1, Player *p2) {
	return strcasecmp(p1->team, p2->team);
}

/**
 * @brief Compara dos jugadores basandose en su puntuacion.
 * * Evalua los valores de punto flotante (double) del campo `score`.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return Desempate por ID.
 */
int compare_score(Player *p1, Player *p2) {
	if (p1->score > p2->score) return 1;
	if (p1->score < p2->score) return -1;
	return p1->id - p2->id;
}
/**
 * @brief Compara dos jugadores basandose en la cantidad de competiciones.
 * * Compara los valores enteros del campo `competitions` jugadas por cada uno.
 * * @param p1 Puntero al primer jugador.
 * @param p2 Puntero al segundo jugador.
 * @return Desempate por ID.
 */
int compare_competitions(Player *p1, Player *p2) {
    if (p1->competitions > p2->competitions) return 1;
    if (p1->competitions < p2->competitions) return -1;
	return p1->id - p2->id;
}


/**
 * @brief Imprime un jugador por consola.
 * 
 * @param player Puntero al jugador a imprimir.
 */
void print_player(Player *player) {
	printf(EVEN_DARKER_GREEN "╔════════════════════╗\n");
	printf(EVEN_DARKER_GREEN "║ " LIGHT_GRAY"ID: "DARK_GRAY"%4d" EVEN_DARKER_GREEN "           ║\n", player->id);
	printf(EVEN_DARKER_GREEN "║ " DARK_YELLOW"Name: "YELLOW"%10s" EVEN_DARKER_GREEN "   ║\n", player->name);
	printf(EVEN_DARKER_GREEN "║ " DARK_BLUE"Team: "LIGHT_BLUE"%7s" EVEN_DARKER_GREEN "      ║\n", player->team);
	printf(EVEN_DARKER_GREEN "║ " DARK_GREEN"Score: "LIGHT_GREEN"%.1f" EVEN_DARKER_GREEN "         ║\n", player->score);
	printf(EVEN_DARKER_GREEN "║ " PURPLE"Competitions: "MAGENTA"%4d" EVEN_DARKER_GREEN " ║\n", player->competitions);
	printf(EVEN_DARKER_GREEN "╚════════════════════╝\n");
	printf(RESET"\n");
}

/**
 * @brief Imprime el arreglo de jugadores en formato de tabla
 * * @param players Arreglo de jugadores
 * @param n Tamanho del arreglo
 */
void print_player_array(Player *players, int n)
{
	if (n > MAX_CONSOLE_READABLE_PLAYERS) {
		n = MAX_CONSOLE_READABLE_PLAYERS;
		print_error(301, NULL, NULL);
	}
	// Imprimimos cabecera
	printf(
		DARK_GRAY "|" RESET " "
		LIGHT_GRAY "%4s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_YELLOW "%10s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_BLUE "%7s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_GREEN "%4s" RESET " "
		DARK_GRAY "|" RESET " "
		PURPLE "%3s" RESET " "
		DARK_GRAY "|" RESET "\n",
		"ID", "NAME", "TEAM", "SCORE", "COMPS"
	);

	// Imprimimos los datos
	for (int i = 0; i < n; i++) {
		printf(
			DARK_GRAY "|" RESET " "
			WHITE "%4d" RESET " "
			DARK_GRAY "|" RESET " "
			YELLOW "%10s" RESET " "
			DARK_GRAY "|" RESET " "
			LIGHT_BLUE "%7s" RESET " "
			DARK_GRAY "|" RESET " "
			LIGHT_GREEN "%5.1f" RESET " "
			DARK_GRAY "|" RESET " "
			MAGENTA "%5d" RESET " "
			DARK_GRAY "|" RESET "\n",
			players[i].id,
			players[i].name,
			players[i].team,
			players[i].score,
			players[i].competitions
		);
	}
	printf(RESET"\n");
}

/**
 * @brief Funcion para imprimir un arreglo de jugadores en formato de pagina, se usara junto a print_player_array_more
 * 
 * @param players Jugadores a imprimir
 * @param start indice inicial de la pagina a mostrar (inclusivo)
 * @param end indice final de la pagina a mostrar (exclusivo)
 */
static void print_player_array_page(Player *players, int start, int end)
{
	printf(
		DARK_GRAY "|" RESET " "
		LIGHT_GRAY "%4s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_YELLOW "%10s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_BLUE "%7s" RESET " "
		DARK_GRAY "|" RESET " "
		DARK_GREEN "%4s" RESET " "
		DARK_GRAY "|" RESET " "
		PURPLE "%3s" RESET " "
		DARK_GRAY "|" RESET "\n",
		"ID", "NAME", "TEAM", "SCORE", "COMPS"
	);

	for (int i = start; i < end; i++) {
		printf(
			DARK_GRAY "|" RESET " "
			WHITE "%4d" RESET " "
			DARK_GRAY "|" RESET " "
			YELLOW "%10s" RESET " "
			DARK_GRAY "|" RESET " "
			LIGHT_BLUE "%7s" RESET " "
			DARK_GRAY "|" RESET " "
			LIGHT_GREEN "%5.1f" RESET " "
			DARK_GRAY "|" RESET " "
			MAGENTA "%5d" RESET " "
			DARK_GRAY "|" RESET "\n",
			players[i].id,
			players[i].name,
			players[i].team,
			players[i].score,
			players[i].competitions
		);
	}
}

/**
 * @brief Funcion para limpiar la pagina actual de print_player_array_page()
 * 
 */
static void clear_player_page()
{
	for (int i = 0; i < PAGE_LINES; i++) {
		printf("\r\033[2K"); // Mueve el cursor al inicio de la linea y limpia la linea
		if (i < PAGE_LINES - 1) {
			printf("\033[1A"); // Mueve el cursor hacia arriba una linea
		}
	}
	printf("\r"); // Mueve el cursor al inicio de la linea
	fflush(stdout);
	printf(RESET);
}

/**
 * @brief Funcion para ver a los jugadores al estilo 'more' de UNIX
 * 
 * @param players Jugadores a imprimir
 * @param n cantidad de jugadores
 */
void print_player_array_more(Player *players, int n)
{
	int start = 0;

	getchar(); // Parche para que el paginador print_player_array_more() funcione como corresponde
	while (start < n) {
		int end = start + PAGE_SIZE;
		if (end > n) {
			end = n;
		}

		print_player_array_page(players, start, end);

		if (end == n) {
			printf(RESET "\n");
			return;
		}

		printf("\n" DARK_GRAY "--More--       |" LIGHT_GRAY " Enter: next " DARK_GRAY "|" LIGHT_GRAY " q: quit " DARK_GRAY "| ["LIGHT_GRAY"%d"DARK_GRAY"-"LIGHT_GRAY"%d" DARK_GRAY" of " LIGHT_GRAY "%d" DARK_GRAY "] Action:  " LIGHT_GRAY, start + 1, end, n);
		fflush(stdout);

		int c = getchar();

// Nota de jays: los \n son mis peores enemigos.
		
		if (c == 'q' || c == 'Q') {
			while (c != '\n' && c != EOF) {
				c = getchar();
			}
			printf("\n");
			return;
		}

		while (c != '\n' && c != EOF) {
			c = getchar();
		}

		printf("\033[1A"); // Mueve el cursor hacia arriba una linea
		clear_player_page();

		start = end;
	}
}