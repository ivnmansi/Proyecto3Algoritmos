/**
 * @file generator.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de generacion de datos y archivo csv
 */

#include "generator.h"

static char *teams[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon", "Theta", "Lambda", "Pi", "Tau"};
static int generator_quiet = 0;

static void format_size(size_t size, char *buf, size_t buf_size)
{
	const size_t one_kb = 1024;
	const size_t one_mb = 1024 * 1024;

	if (size >= one_mb) {
		double mb = (double)size / (double)one_mb;
		snprintf(buf, buf_size, "%.2f MB", mb);
	} else if (size >= one_kb) {
		double kb = (double)size / (double)one_kb;
		snprintf(buf, buf_size, "%.2f KB", kb);
	} else {
		snprintf(buf, buf_size, "%lu B", (unsigned long)size);
	}
}

/**
* @brief Funcion para desordenar los jugadores (Fisher-Yates)
* 
* @param players Arreglo de jugadores
* @param n Tamanho del arreglo
*/
static void shuffle_players(Player players[], int n)
{
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		swap_player(&players[i], &players[j]);
	}
}

/**
 * @brief Funcion para invertir el orden de los jugadores
 * 
 * @param players Arreglo de jugadores a invertir
 * @param n Tamanho del arreglo
 */
static void reverse_players(Player players[], int n)
{
	int left = 0;
	int right = n - 1;

	while (left < right) {
		swap_player(&players[left], &players[right]);
		left++;
		right--;
	}
}

/**
 * @brief Genera una letra aleatoria (Minus y mayus).
 * @return char 
 */
static char random_letter()
{
	char c = 'A' + (rand() % 26);

	if (rand() % 2 == 0)
		c = c + 32;

	return c;
}


/**
 * @brief Genera un jugador con campos ID, nombre, equipo, puntaje y cantidad de competencias.
 * 
 * @param id valor unico de identificacion
 * @param player puntero a la estructura Player donde se almacenaran los datos generados
 */
static void generate_player(int id, Player *player) 
{
	int length = MIN_NAME_LENGTH + (rand() % (MAX_NAME_LENGTH - MIN_NAME_LENGTH + 1));

	player->id = id;

	for (int j = 0; j < length; j++) {
		player->name[j] = random_letter();
	}
	player->name[length] = '\0';

	strcpy(player->team, teams[rand() % 9]);
	player->score = (rand() % 100 + 1) / 10.0f;
	player->competitions = rand() % 251;

	// Aqui no hay nada que ver agente...
	player->potatoe = rand() % 2 ? true : false;
	// Usted no vio nada aqui agente...
}

void set_generator_quiet(int quiet)
{
	generator_quiet = quiet ? 1 : 0;
}

/**
 * @brief Funcion general de generacion de csv con datos aleatorios 
 * 
 * @param n cantidad de jugadores a generar
 * 
 * @return int 0 si todo va bien, otro codigo de error en caso de error
 */
int generate_csv(int n, int generationType) 
{
	FILE *csv = fopen("build/db/players.csv", "w");

	if (csv == NULL) {
		print_error(101, "build/db/players.csv", NULL);
		return 101;
	}

	Player *players;

	// Reservamos memoria para los jugadores
	size_t size = n * sizeof(Player);
	char size_string[32];
	format_size(size, size_string, sizeof(size_string));

	if ((players = malloc(n * sizeof(Player))) == NULL) {
		fclose(csv);
		print_error(102, size_string, NULL);
		return 102;
	}
	if (!generator_quiet) {
		printf(BG_GREEN "%s De memoria reservados" RESET"\n", size_string);
	}

	for (int i = 0; i < n; i++) {
		generate_player(i + 1, &players[i]);
	}

	if (generationType == 2) {
		reverse_players(players, n);
	} else if (generationType == 3) {
		shuffle_players(players, n);
	}
	// El best case son los amigos que hicimos en el camino

	// Imprimimos cabecera en el archivo csv
	fprintf(csv, "%d\n", n);
	fprintf(csv, "ID NAME TEAM SCORE COMPETITIONS POTATOE\n");

	// Imprimimos los datos en el archivo csv
	for (int i = 0; i < n; i++) {
		fprintf(csv, "%d %s %s %.1f %d %s\n",
			players[i].id,
			players[i].name,
			players[i].team,
			players[i].score,
			players[i].competitions,
			players[i].potatoe ? "true" : "false"
		);
	}

	if (!generator_quiet) {
		print_player_array_more(players, n);
	}

	free(players);
	fclose(csv);
	if (!generator_quiet) {
		printf("\n" BG_GREEN "Data generated and saved to build/db/players.csv" RESET "\n");
	}

	return 0;
}

/**
 * @brief Funcion para cargar datos de jugadores de un archivo csv
 * 
 * @param file Direccion relativa al archivo csv
 * @param out_n Puntero a la variable que almacenara el numero de jugadores
 * @return Player* Puntero al arreglo de jugadores
 * @important El arreglo debe ser liberado con free()
 */
Player* load_players(char* file, int* out_n)
{
	FILE *csv = fopen(file, "r");
	if (csv == NULL) {
		print_error(101, file, NULL);
		return NULL;
	}

	int n;
	Player* playerArray = NULL;

	// Leer cantidad de jugadores
	if (fscanf(csv, "%d", &n) != 1 || n <= 0) {
		fclose(csv);
		print_error(103, "No se pudo leer la cantidad de jugadores", NULL);
		return NULL;
	}

	// Reservar memoria
	size_t size = (size_t)n * sizeof(Player);
	char size_string[32];
	format_size(size, size_string, sizeof(size_string));

	playerArray = malloc(size);
	if (playerArray == NULL) {
		fclose(csv);
		print_error(102,  size_string, NULL);
		return NULL;
	}
	// Entonces mi punto comercial sonrio y 
	// searching.h

	if (!generator_quiet) {
		printf("%s de memoria reservados\n", size_string);
	}

	// Leer cabecera
	if (fscanf(csv, "%*s %*s %*s %*s %*s %*s") == EOF) {
		free(playerArray);
		fclose(csv);
		print_error(101, file, "No se pudo leer la cabecera");
		return NULL;
	}

	// Leer jugadores
	for (int i = 0; i < n; i++) {
		// Este campo no parece ser muy relevante, no lo tome en cuenta agente.
		char mysteriousStr[8];

		// Leemos los datos de la linea (el ultimo campo lo leemos y guardamos en mysteriousStr)
		int fields = fscanf(csv, "%d %10s %10s %f %d %7s",
			&playerArray[i].id,
			playerArray[i].name,
			playerArray[i].team,
			&playerArray[i].score,
			&playerArray[i].competitions,
			mysteriousStr
		);
	
		if (fields != 6) {
			free(playerArray);
			fclose(csv);
			print_error(101, file, "CSV malformada");
			return NULL;
		}

		// Convertimos la cadena en mysteriousStr a booleano
		playerArray[i].potatoe = (strcmp(mysteriousStr, "true") == 0);
	}

	// Enviamos la cantidad de jugadores si el puntero fue pasado
	if (out_n != NULL) {
		*out_n = n;
	}
	fclose(csv);
	return playerArray;
}

// Se rie en latex: 𝑗𝑎𝑗𝑎𝑗𝑎𝑗𝑎