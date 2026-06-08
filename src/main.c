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
#include "config.h"


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

    // Imprime menú
    print_menu();
	
	check =	scanf("%d", &option);
	while (check != 1 || option < 1 || option > 7) {
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

        print_sort_generate_menu();

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
		if ((players = load_players(CSV_FILE, &n)) == NULL) {
			print_error(101, CSV_FILE, NULL);
			return 1;
		}

		printf(ORANGE "\nplayers.csv:\n" RESET);
		print_player_array_more(players, n);
	}

	else if (option == 3) { // Opcion 3: Ordenar arreglo
        // Cargamos el arreglo de jugadores
        if ((players = load_players(CSV_FILE, &n)) == NULL) {
            return 1;
        }

        printf(LIGHT_BLUE "\nOriginal file:\n" RESET);
        print_player_array_more(players, n);

        print_sort_case_menu();
        
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
        
        print_field_to_sort_menu();

        check = scanf("%d", &sortCriteria);
        while (check != 1 || sortCriteria < 1 || sortCriteria > 6) {
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
        else if (sortCriteria == 6) comp_ptr = compare_cost;
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
        
        print_data_analytics_menu();
        scanf("%d", &subOption);

        if ((players = load_players(CSV_FILE, &n)) == NULL) return 1;

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
            Player target = {searchId, "", "", 0.0, 0, 0, false};
            
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

    else if(option == 5){ // Opción 5: Crear equipo con CSV
        int suboption, budget;
        int algorithm_choice;
        // Cargamos el arreglo de jugadores
        if ((players = load_players(CSV_FILE, &n)) == NULL) {
            return 1;
        }
        printf(LIGHT_BLUE "\nOriginal file:\n" RESET);
        print_player_array_more(players, n);

        // seleccionar con o sin restriccion presupuestaria

        print_create_team_budget_menu();
        check = scanf("%d", &suboption);
        while (check != 1 || suboption < 1 || suboption > 2) {
            printf(EVEN_DARKER_BLUE"Invalid option, try again: " DARK_BLUE);
            while (getchar() != '\n');
            check = scanf("%d", &suboption);
        }

        if(suboption == 1){
            printf(DARK_YELLOW "\nEnter team budget ($): " YELLOW);
            check = scanf("%d", &budget);
            while (check != 1 || budget < 0) {
                printf(EVEN_DARKER_BLUE"Invalid budget, try again: " DARK_BLUE);
                while (getchar() != '\n');
                check = scanf("%d", &budget);
            }

            print_create_team_budget_algorithm_menu();
            check = scanf("%d", &algorithm_choice);
            while (check != 1 || algorithm_choice < 1 || algorithm_choice > 5) {
                printf(EVEN_DARKER_BLUE"Invalid option, try again: " DARK_BLUE);
                while (getchar() != '\n');
                check = scanf("%d", &algorithm_choice);
            }

            if (algorithm_choice == 1) {
                printf(LIGHT_BLUE "\nUsing DP Top-Down (Memoization).\n" RESET);
            } else if (algorithm_choice == 2) {
                printf(LIGHT_BLUE "\nUsing DP Bottom-Up (Tabulation).\n" RESET);
            } else if (algorithm_choice == 3) {
                printf(LIGHT_BLUE "\nUsing Greedy (by Score).\n" RESET);
            } else if (algorithm_choice == 4) {
                printf(LIGHT_BLUE "\nUsing Greedy (by Score/Cost).\n" RESET);
            } else {
                printf(LIGHT_BLUE "\nUsing Greedy (by Lowest Cost).\n" RESET);
            }
            printf(BG_RED "Team creation is not implemented yet." RESET "\n");
        }
        // sin restriccion de presupuesto
        else {
            // greedy por score
            
            printf(BG_RED "Team creation is not implemented yet." RESET "\n");
            
        }
        
        free(players);
    }

	else if (option == 6) { // Opcion 6: Ejecutar experimento
        run_smoke_tests();
	}

	else if (option == 7) { // Opcion 7: Salir del programa
        print_goodbye();
	}

	return 0;
}

// MIAU !
                                                                                