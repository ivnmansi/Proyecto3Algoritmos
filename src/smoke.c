#include <stdio.h>
#include <stdlib.h>
#include "smoke.h"
#include "generate_exec_times.h"
#include "generator.h"
#include "config.h"

extern SortAlgorithmFlag current_active_flags;

static int generate_case_csv(int generation_type, const char* destination_file)
{
    if (generate_csv(10000, generation_type) == 0) {
        if (rename(CSV_FILE, destination_file) == 0) return 0;
        return -2; /* rename failed */
    }
    return -1; /* generation failed */
}

void run_smoke_tests(int selection) {
    printf("\n" "\033[0;35m" "=== STARTING SMOKE TESTS ===" "\033[0m" "\n");

    set_generator_quiet(1);
    set_experiment_quiet(0);
    set_experiment_show_samples(0);

    /* Todos los algoritmos activos por defecto, incluyendo los de Tarea 1 */
    current_active_flags = FLAG_ALL_SORTS;
    
    printf("Guardando informacion del equipo...\n");
    system("mkdir -p docs/results");
    system("uname -a > docs/results/system_info.txt");
    system("lscpu >> docs/results/system_info.txt");

    /* Decide qué experimento(s) ejecutar según selection
     * 1 = all, 2 = sort, 3 = threshold, 4 = search, 5 = select,
     * 6 = team (budget), 7 = team (no-budget)
     */
    if (selection == 1 || selection == 2) {
        printf("\n" "\033[44m" "--- Exp: Ordenamiento ---" "\033[0m" "\n");
        if (generate_case_csv(1, PLAYERS_SORTED_FILE) == 0 && generate_case_csv(2, PLAYERS_INVERTED_FILE) == 0 && generate_case_csv(3, PLAYERS_SHUFFLED_FILE) == 0) {
            run_sort_experiments(PLAYERS_SORTED_FILE, PLAYERS_INVERTED_FILE, PLAYERS_SHUFFLED_FILE, SORT_EXPERIMENT_PREFIX);
        }
    }

    if (selection == 1 || selection == 3) {
        printf("\n" "\033[44m" "--- Exp: Threshold Merge ---" "\033[0m" "\n");
        if (generate_case_csv(1, PLAYERS_SORTED_FILE) == 0 && generate_case_csv(2, PLAYERS_INVERTED_FILE) == 0 && generate_case_csv(3, PLAYERS_SHUFFLED_FILE) == 0) {
            run_threshold_experiments(PLAYERS_SORTED_FILE, PLAYERS_INVERTED_FILE, PLAYERS_SHUFFLED_FILE, THRESHOLD_EXPERIMENT_PREFIX);
        }
    }

    if (selection == 1 || selection == 4) {
        printf("\n" "\033[44m" "--- Exp: Busqueda ---" "\033[0m" "\n");
        if (generate_case_csv(1, PLAYERS_SORTED_FILE) == 0) {
            run_search_experiments(PLAYERS_SORTED_FILE, SEARCH_EXPERIMENT_PREFIX);
        }
    }

    if (selection == 1 || selection == 5) {
        printf("\n" "\033[44m" "--- Exp: Select ---" "\033[0m" "\n");
        if (generate_case_csv(1, PLAYERS_SORTED_FILE) == 0 && generate_case_csv(3, PLAYERS_SHUFFLED_FILE) == 0) {
            run_select_experiments(PLAYERS_SORTED_FILE, PLAYERS_SHUFFLED_FILE, SELECT_EXPERIMENT_PREFIX);
        }
    }

    if (selection == 1 || selection == 6) {
        printf("\n" "\033[44m" "--- Exp: Team (budget) ---" "\033[0m" "\n");
        if (generate_case_csv(3, PLAYERS_SHUFFLED_FILE) == 0) {
            run_team_experiment(PLAYERS_SHUFFLED_FILE, TEAM_EXPERIMENT_PREFIX, 1);
        }
    }

    if (selection == 1 || selection == 7) {
        printf("\n" "\033[44m" "--- Exp: Team (no-budget) ---" "\033[0m" "\n");
        if (generate_case_csv(3, PLAYERS_SHUFFLED_FILE) == 0) {
            run_team_experiment(PLAYERS_SHUFFLED_FILE, TEAM_UNCONSTRAINED_EXPERIMENT_PREFIX, 0);
        }
    }

    /* Restaurar estado */
    current_active_flags = FLAG_ALL_SORTS;
    set_generator_quiet(0);
    set_experiment_quiet(0);
    set_experiment_show_samples(1);

    printf("\n" "\033[0;35m" "=== SMOKE TESTS COMPLETED ===" "\033[0m" "\n");
    printf("Recuerda ejecutar 'make plot' para generar los graficos.\n\n");
}
