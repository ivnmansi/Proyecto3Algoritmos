/**
 * @file main.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones principales del programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generator.h"
#include "sorting.h"
#include "searching.h"
#include "utilities.h"
#include "player.h" 
#include "generate_exec_times.h"
#include "smoke.h"


int main() {
	// Variables de control
	int option = 0;
	int generationType = 0;
	int check = 1;

	Player* players = NULL;
	int n; // Numero de jugadores

	// Variables para ordenamiento (Opcion 2)
	int sortOption;
	int sortCriteria;

	// Variables para busqueda (Opcion 3)
	int searchId;
	int result;

	srand(time(0));

	printf(RESET "          ╔═══════════╗\n");
	printf( "          ║ MAIN MENU ║\n");
	printf("╔═════════╩═══════════╩══════════╗\n");
	printf("║ "DARK_YELLOW "1)" YELLOW " Generate new CSV" RESET "            ║\n");
	printf("║ "BROWN "2)" ORANGE " Read actual CSV" RESET "             ║\n");
	printf("║ "DARK_BLUE "3)" LIGHT_BLUE " Sort CSV" RESET "                    ║\n");
	printf("║ "DARK_GREEN "4)" LIGHT_GREEN " Search value in CSV" RESET "         ║\n");
	printf("║ "PURPLE "5)" MAGENTA " Run experiment" RESET "              ║\n");
	printf("║ "DARK_RED "6)" LIGHT_RED " Exit" RESET "                        ║\n");
	printf("╚════════════════════════════════╝\n");
	printf(DARK_GRAY"Choose an option: " RESET);
	
	check =	scanf("%d", &option);
	while (check != 1 || option < 1 || option > 6) {
		printf(DARK_GRAY"Invalid option, try again: " RESET);
		while (getchar() != '\n');
		check = scanf("%d", &option);
	}

	//getchar(); // Parche de paginador

	if (option == 1) { // Opcion 1: Generar CSV
		printf(DARK_YELLOW "\nType the number of players to generate: " YELLOW);
		check = scanf("%d", &n);
		while (check != 1 || n < 0) {
			printf(BROWN "Invalid number, try again: " DARK_YELLOW);
			while (getchar() != '\n');
			check = scanf("%d", &n);
		}

		printf(BROWN "   ╔════════════════════════╗\n");
		printf(BROWN "   ║" YELLOW "  Choose the case type  " BROWN "║" "\n");
		printf(BROWN "╔══╩════════════════════════╩══╗\n");
		printf(BROWN "║" DARK_YELLOW " 1)" YELLOW " Sorted Array" BROWN "              ║\n");
		printf(BROWN "║" DARK_YELLOW " 2)" YELLOW " Inverse Array" BROWN "             ║\n");
		printf(BROWN "║" DARK_YELLOW " 3)" YELLOW " Shuffled Array" BROWN "            ║\n");
		printf(BROWN"╚══════════════════════════════╝\n");

		printf(DARK_YELLOW"Option: " YELLOW);
		check = scanf("%d", &generationType);
		while (check != 1 || n < 0) {
			printf(BROWN "Invalid option, try again: " DARK_YELLOW);
			while (getchar() != '\n');
			check = scanf("%d", &generationType);
		}

		if (generationType == 1) {
			printf(YELLOW "\nGenerating SORTED array...\n");
		} else if (generationType == 2) {
			printf(YELLOW "\nGenerating INVERSE array...\n");
		} else {
			printf(YELLOW "\nGenerating SHUFFLED array...\n");
		}

		generate_csv(n, generationType);
	}

	else if (option == 2) { // Opcion 2: Leer CSV
		// Cargamos el arreglo de jugadores
		if ((players = load_players("build/db/players.csv", &n)) == NULL) {
			print_error(101, "build/db/players.csv", NULL);
			return 1;
		}

		printf(ORANGE "\nplayers.csv:\n" RESET);
		print_player_array_more(players, n);
	}

	else if (option == 3) { // Opcion 3: Ordenar arreglo
        // Cargamos el arreglo de jugadores
        if ((players = load_players("build/db/players.csv", &n)) == NULL) {
            return 1;
        }

        printf(LIGHT_BLUE "\nOriginal file:\n" RESET);
        print_player_array_more(players, n);

        
        printf(EVEN_DARKER_BLUE"    ╔════════════════════════════╗\n");
        printf(EVEN_DARKER_BLUE"    ║" LIGHT_BLUE " Choose a sorting algorithm " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╔═══╩════════════════════════════╩═══╗\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 1)" LIGHT_BLUE " Swap Sort                       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 2)" LIGHT_BLUE " Insertion Sort                  " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 3)" LIGHT_BLUE " Selection Sort                  " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 4)" LIGHT_BLUE " Cocktail Shaker Sort            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 5)" LIGHT_BLUE " Merge Sort (Classic)            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 6)" LIGHT_BLUE " Merge Sort (Optimized)          " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 7)" LIGHT_BLUE " Quick Sort (Last Pivot)         " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 8)" LIGHT_BLUE " Quick Sort (First Pivot)        " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 9)" LIGHT_BLUE " Quick Sort (Random Pivot)       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 10)" LIGHT_BLUE" Quick Sort (Median of 3)       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╚════════════════════════════════════╝\n");
        printf(DARK_BLUE "Option: " LIGHT_BLUE);
        
        check = scanf("%d", &sortOption);
        while (check != 1 || sortOption < 1 || sortOption > 10) {
            printf(EVEN_DARKER_BLUE"Invalid option, try again: " DARK_BLUE);
            while (getchar() != '\n');
            check = scanf("%d", &sortOption);
        }

        // Si elige Merge Sort Optimizado, le pedimos el umbral para el Insertion Sort
        int threshold = 10; // Valor por defecto
        if (sortOption == 6) {
            printf(DARK_BLUE "\nType the threshold for Insertion Sort (e.g. 10): " LIGHT_BLUE);
            check = scanf("%d", &threshold);
            while (check != 1 || threshold < 1) {
                printf(EVEN_DARKER_BLUE"Invalid threshold, try again: " DARK_BLUE);
                while (getchar() != '\n');
                check = scanf("%d", &threshold);
            }
        }

        // Elegir el campo a ordenar
        
        printf(EVEN_DARKER_BLUE"   ╔══════════════════════╗\n");
        printf(EVEN_DARKER_BLUE"   ║" LIGHT_BLUE " Choose field to sort " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE"   ║" LIGHT_BLUE "    by (Ascending)    " EVEN_DARKER_BLUE "║\n");
        printf(EVEN_DARKER_BLUE "╔══╩══════════════════════╩══╗\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 1)" LIGHT_BLUE " ID                      " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 2)" LIGHT_BLUE " Name                    " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 3)" LIGHT_BLUE " Team                    " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 4)" LIGHT_BLUE " Score                   " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 5)" LIGHT_BLUE " Competitions            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╚════════════════════════════╝\n");

        printf(DARK_BLUE "Option: " LIGHT_BLUE);

        check = scanf("%d", &sortCriteria);
        while (check != 1 || sortCriteria < 1 || sortCriteria > 5) {
            printf(EVEN_DARKER_BLUE"Invalid option, try again: " DARK_BLUE);
            while (getchar() != '\n');
            check = scanf("%d", &sortCriteria);
        }

        // Asignar el comparador segun la eleccion del usuario
        int (*comp_ptr)(Player*, Player*) = NULL;
        if (sortCriteria == 1) comp_ptr = compare_id;
        else if (sortCriteria == 2) comp_ptr = compare_name;
        else if (sortCriteria == 3) comp_ptr = compare_team;
        else if (sortCriteria == 4) comp_ptr = compare_score;
        else if (sortCriteria == 5) comp_ptr = compare_competitions;
        else {
            printf(RESET BG_RED "Invalid criteria option.\n" RESET);
        }

        // Ejecutar el ordenamiento
        if (sortOption == 1) {
            swap_sort(players, n, comp_ptr);
        } else if (sortOption == 2) {
            insertion_sort(players, n, comp_ptr);
        } else if (sortOption == 3) {
            selection_sort(players, n, comp_ptr);
        } else if (sortOption == 4) {
            cocktail_shaker_sort(players, n, comp_ptr);
        } else if (sortOption == 5) {
            merge_sort_classic(players, n, comp_ptr);
        } else if (sortOption == 6) {
            merge_sort_optimized(players, n, threshold, comp_ptr);
        } else if (sortOption >= 7 && sortOption <= 10) {
            // Transformamos la opcion del menu (7-10) al tipo de pivote (1-4)
            int pivot_type = sortOption - 6; 
            quick_sort(players, n, pivot_type, comp_ptr);
        } else {
            printf(RESET BG_RED "Invalid sorting option.\n" RESET);
        }

        printf(LIGHT_BLUE "\nSorted file (Ascending):\n" RESET);
        print_player_array_more(players, n);
        free(players);
    }

	else if (option == 4) { // Opcion 4: Data Analytics & Rankings
        int subOption = 0, searchAlgo = 0, sortAlgo = 0;
        int topN, k_rank;
        float minScore, maxScore;
        
        printf(EVEN_DARKER_GREEN "\n   ╔═══════════════════════════════════════╗\n");
        printf(EVEN_DARKER_GREEN "   ║" LIGHT_GREEN "    Data Analytics & Rankings Menu     " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ╚═══════════════════════════════════════╝\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 1)" LIGHT_GREEN " Generate Top N Ranking (by Score)  " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 2)" LIGHT_GREEN " Find the K-th Best Athlete         " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 3) " LIGHT_GREEN "Search Athletes by Score Range     " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 4) " LIGHT_GREEN "Search Athlete by exact ID         " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ╚═══════════════════════════════════════╝\n");
        
        printf(DARK_GREEN "Selection: " LIGHT_GREEN);
        scanf("%d", &subOption);

        if ((players = load_players("build/db/players.csv", &n)) == NULL) return 1;

        if (subOption == 1) { // TOP N RANKING
            printf(DARK_GREEN "\nHow many top athletes? " LIGHT_GREEN);
            scanf("%d", &topN);
            
            // SUBMENU DE ORDENAMIENTO
            printf("\nChoose Sorting Algorithm:\n1) Quick Sort (Median of 3)\n2) Merge Sort (Optimized)\nSelection: ");
            scanf("%d", &sortAlgo);

            if (sortAlgo == 1) quick_sort(players, n, 4, compare_score);
            else merge_sort_optimized(players, n, 10, compare_score);
            
            printf(BG_GREEN "\n--- TOP %d RANKING ---" RESET "\n\n", topN);
            for (int i = 0; i < topN && i < n; i++) print_player(&players[n - 1 - i]);
        }
        else if (subOption == 2) { // K-TH BEST
            printf(DARK_GREEN "\nEnter rank (K): " LIGHT_GREEN);
            scanf("%d", &k_rank);
            
            printf("\nChoose Selection Algorithm:\n1) Quick Select (O(n))\n2) Full Sort + Index (O(n log n))\nSelection: ");
            scanf("%d", &sortAlgo);

            Player result_p;
            if (sortAlgo == 1) {
                result_p = quick_select(players, n, n - k_rank, 3, compare_score);
            } else {
                quick_sort(players, n, 3, compare_score);
                result_p = players[n - k_rank];
            }
            print_player(&result_p);
        }
		else if (subOption == 3) { // SEARCH BY SCORE RANGE
            printf(DARK_GREEN "\nMin Score: " LIGHT_GREEN);
            check = scanf("%f", &minScore);
            printf(DARK_GREEN "Max Score: " LIGHT_GREEN);
            check = scanf("%f", &maxScore);

            /* JUSTIFICACIÓN: Para buscar un rango de manera eficiente, primero ordenamos el 
               arreglo por Score. Quick Sort (O(n log n)) es ideal para preparar los datos. */
            quick_sort(players, n, 3, compare_score);
            
            printf(BG_GREEN "\nAthletes with scores between %.1f and %.1f:" RESET "\n\n", minScore, maxScore);
            int count = 0;
            // Al estar ordenado, podemos mostrar todos los que caigan en el rango
            for(int i = 0; i < n; i++) {
                if (players[i].score >= minScore && players[i].score <= maxScore) {
                    print_player(&players[i]);
                    count++;
				if (count >= 10) {
                    printf(DARK_GRAY "\n... Limit of 10 reached.\n" RESET);
                    break; 
                    }
                }
                // Como está ordenado ascendentemente, si nos pasamos del máximo, podemos detener el ciclo para ahorrar tiempo
                if (players[i].score > maxScore) break; 
            }
            if (count == 0) printf(BG_RED "No athletes found in this range." RESET "\n");
        }
        else if (subOption == 4) { // EXACT ID SEARCH
            printf("\nChoose Searching Algorithm:\n1) Linear\n2) Binary (Iterative)\n3) Binary (Recursive)\n4) Exponential\n5) Interpolation\nSelection: ");
            scanf("%d", &searchAlgo);

            printf(DARK_GREEN "\nEnter exact ID: " LIGHT_GREEN);
            scanf("%d", &searchId);
            Player target = {searchId, "", "", 0.0, 0, false};
            
            // Si el algoritmo requiere orden previo (Binarias, Exponencial, Interpolación)
            if (searchAlgo >= 2) {
                quick_sort(players, n, 3, compare_id);
            }

            // Ejecutamos el algoritmo seleccionado
            if (searchAlgo == 1) result = linear_search(players, n, &target, compare_id);
            else if (searchAlgo == 2) result = binary_search(players, 0, n-1, &target);
            else if (searchAlgo == 3) result = binary_search_recursive(players, 0, n-1, &target);
            else if (searchAlgo == 4) result = exponential_search(players, n, &target);
            else if (searchAlgo == 5) result = interpolation_search(players, n, &target);
            else {
                printf(BG_RED "Invalid search algorithm." RESET "\n");
                result = -1;
            }
            
            if (result != -1 && result != n) {
                printf(BG_GREEN "\nAthlete found:" RESET "\n\n");
                print_player(&players[result]);
            } else {
                printf(BG_RED "\nAthlete with ID %d not found." RESET "\n", searchId);
            }
        }
        free(players);
    }

	else if (option == 5) { // Opcion 5: Ejecutar experimento
        run_smoke_tests();
	}

	else if (option == 6) { // Opcion 6: Salir del programa

		// 1/2 de probablidad de salir crocodile o aligator
		if (rand() % 2 == 0) {
			printf(DARK_GREEN);
			printf("   _____                                   _                            _     _ _        \n");
			printf("  / ____|                                 (_)                          | |   (_) |       \n");
			printf(" | (___   ___  ___    _   _  ___  _   _    _ _ __      __ _   __      _| |__  _| | ___   \n");
			printf("  \\___ \\ / _ \\/ _ \\  | | | |/ _ \\| | | |  | | '_ \\    / _` |  \\ \\ /\\ / / '_ \\| | |/ _ \\  \n");
			printf("  ____) |  __/  __/  | |_| | (_) | |_| |  | | | | |  | (_| |   \\ V  V /| | | | | |  __/  \n");
			printf(" |_____/ \\___|\\___|   \\__, |\\___/_\\__,_|  |_|_| |_|   \\__,_|    \\_/\\_/ |_| |_|_|_|\\___|  \n");
			printf("                       __/ |  | (_) |    | |                                             \n");
			printf("   ___ _ __ ___   ___ |___/ __| |_| | ___| |                                             \n");
			printf("  / __| '__/ _ \\ / __/ _ \\ / _` | | |/ _ \\ |                                             \n");
			printf(" | (__| | | (_) | (_| (_) | (_| | | |  __/_|                                             \n");
			printf("  \\___|_|  \\___/ \\___\\___/ \\__,_|_|_|\\___(_)                                             \n");
			printf(RESET);
			return 0;
		}

		printf(DARK_RED);
		printf("   _____                                   _       _                     _ _             _             _ \n");
		printf("  / ____|                                 | |     | |                   | (_)           | |           | |\n");
		printf(" | (___   ___  ___    _   _  ___  _   _   | | __ _| |_ ___ _ __     __ _| |_  __ _  __ _| |_ ___  _ __| |\n");
		printf("  \\___ \\ / _ \\/ _ \\  | | | |/ _ \\| | | |  | |/ _` | __/ _ \\ '__|   / _` | | |/ _` |/ _` | __/ _ \\| '__| |\n");
		printf("  ____) |  __/  __/  | |_| | (_) | |_| |  | | (_| | ||  __/ |     | (_| | | | (_| | (_| | || (_) | |  |_|\n");
		printf(" |_____/ \\___|\\___|   \\__, |\\___/ \\__,_|  |_|\\__,_|\\__\\___|_|      \\__,_|_|_|\\__, |\\__,_|\\__\\___/|_|  (_)\n");
		printf("                       __/ |                                                  __/ |                      \n");
		printf("                      |___/                                                  |___/                       \n");
		printf(RESET);
	}

	return 0;
}

// MIAU !
                                                                                