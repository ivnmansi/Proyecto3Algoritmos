#include <stdio.h>
#include <stdlib.h>
#include "smoke.h"
#include "generate_exec_times.h"
#include "generator.h"

extern SortAlgorithmFlag current_active_flags;

void run_smoke_tests() {
    printf("\n" "\033[0;35m" "=== STARTING SMOKE TESTS ===" "\033[0m" "\n");

    set_generator_quiet(1);
    set_experiment_quiet(0);
    set_experiment_show_samples(0);

    /* Todos los algoritmos activos por defecto, incluyendo los de Tarea 1 */
    current_active_flags = FLAG_ALL_SORTS;
    
    printf("1) Generando conjuntos de datos (Sorted, Inverted, Shuffled 50000 n)...\n");
    generate_csv(50000, 1); rename("build/db/players.csv", "build/db/players_sorted.csv");
    generate_csv(50000, 2); rename("build/db/players.csv", "build/db/players_inverted.csv");
    generate_csv(50000, 3); rename("build/db/players.csv", "build/db/players_shuffled.csv");

    printf("Guardando informacion del equipo...\n");
    system("mkdir -p docs/results");
    system("uname -a > docs/results/system_info.txt");
    system("lscpu >> docs/results/system_info.txt");

    /* ============================================
     * EXPERIMENTO 1: ORDENAMIENTO (los 10 algoritmos)
     * Genera 3 CSVs: sort_best, sort_worst, sort_average
     * ============================================ */
    printf("\n" "\033[44m" "--- Exp 1: Ordenamiento ---" "\033[0m" "\n");
    printf("\n-> Exp 1 (Best/Worst/Average) en progreso...\n");
    run_sort_experiments(
        "build/db/players_sorted.csv",
        "build/db/players_inverted.csv",
        "build/db/players_shuffled.csv",
        "build/db/sort"
    );

    /* ============================================
     * EXPERIMENTO 2: THRESHOLD MERGE SORT
     * Genera 3 CSVs: threshold_best, threshold_worst, threshold_average
     * ============================================ */
    printf("\n" "\033[44m" "--- Exp 2: Threshold de optimizacion ---" "\033[0m" "\n");
    printf("\n-> Exp 2 (Best/Worst/Average) en progreso...\n");
    run_threshold_experiments(
        "build/db/players_sorted.csv",
        "build/db/players_inverted.csv",
        "build/db/players_shuffled.csv",
        "build/db/threshold"
    );

    /* ============================================
     * EXPERIMENTO 3: BUSQUEDAS
     * Genera 2 CSVs: search_average, search_worst
     * ============================================ */
    printf("\n" "\033[44m" "--- Exp 3: Busqueda ---" "\033[0m" "\n");
    printf("\n-> Exp 3 (Average/Worst) en progreso...\n");
    run_search_experiments("build/db/players_sorted.csv", "build/db/search");

    /* ============================================
     * EXPERIMENTO 4: SELECCION QUICK SELECT
     * Genera 2 CSVs: select_best, select_worst
     * ============================================ */
    printf("\n" "\033[44m" "--- Exp 4: Seleccion ---" "\033[0m" "\n");
    printf("\n-> Exp 4 (Best/Worst) en progreso...\n");
    run_select_experiments(
        "build/db/players_sorted.csv",
        "build/db/players_shuffled.csv",
        "build/db/select"
    );

    /* Restaurar estado */
    current_active_flags = FLAG_ALL_SORTS;
    set_generator_quiet(0);
    set_experiment_quiet(0);
    set_experiment_show_samples(1);

    printf("\n" "\033[0;35m" "=== SMOKE TESTS COMPLETED ===" "\033[0m" "\n");
    printf("Recuerda ejecutar 'make plot' para generar los graficos.\n\n");
}
