/**
 * @file generate_exec_times.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones para la ejecucion de pruebas experimentales de algoritmos.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include "generate_exec_times.h"
#include "utilities.h"
#include "team.h"
#include "config.h"

SortAlgorithmFlag current_active_flags = FLAG_ALL_SORTS;
static int experiment_quiet = 0;
static int experiment_show_samples = 1;

void set_active_sort_flags(SortAlgorithmFlag* active_flags, SortAlgorithmFlag selected_flags[]) {
    *active_flags = 0;
    int i = 0;
    while (selected_flags[i] != 0 && i < 16) {
        *active_flags |= selected_flags[i];
        i++;
    }
}

void set_experiment_quiet(int quiet) { experiment_quiet = quiet ? 1 : 0; }
void set_experiment_show_samples(int show_samples) { experiment_show_samples = show_samples ? 1 : 0; }

/* ------------------------------------------------------------------ */
/* Helper: Fisher-Yates shuffle para regenerar el caso promedio       */
/* ------------------------------------------------------------------ */
static void shuffle_players(Player *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Player tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

static double team_total_score(const Team *team)
{
    double total = 0.0;

    for (int i = 0; i < team->num_players; i++) {
        total += team->players[i].score;
    }

    return total;
}

static void copy_prefix(Player *dst, const Player *src, int n)
{
    memcpy(dst, src, (size_t)n * sizeof(Player));
}

/* ------------------------------------------------------------------ */
/* run_experiment: corre los 10 algoritmos sobre un dataset           */
/*                                                                    */
/* Si is_average_case == 1, el dataset se re-mezcla NUM_AVG_RUNS      */
/* veces y se promedia el resultado de cada n. Esto reduce la         */
/* variabilidad del caso promedio.                                    */
/* ------------------------------------------------------------------ */
void run_experiment(const char* target_file, const char* out_filename, int is_average_case)
{
    int n = 0;
    Player* players;
    if ((players = load_players((char*)target_file, &n)) == NULL) {
        return;
    }
    if (!experiment_quiet) {
        printf("Arreglo de jugadores cargado desde %s\n", target_file);
        if (experiment_show_samples) print_player_array(players, n);
    }

    const int outer_runs = is_average_case ? NUM_AVG_RUNS : 1;

    /* Buffers reutilizables */
    Player* buf = malloc(n * sizeof(Player));
    Player* working = malloc(n * sizeof(Player));  /* copia que se re-mezcla en avg */
    if (!buf || !working) {
        print_error(102, "players", NULL);
        free(players); free(buf); free(working);
        return;
    }
    memcpy(working, players, n * sizeof(Player));

    FILE *csv = fopen(out_filename, "w");
    if (csv == NULL) {
        print_error(101, out_filename, NULL);
        free(players); free(buf); free(working);
        return;
    }

    fprintf(csv, "N,Swap Sort,Insertion Sort,Selection Sort,Cocktail Shaker Sort,"
                 "Merge Sort Classic,Merge Sort Opt(16),"
                 "Quick Sort (Last),Quick Sort (First),Quick Sort (Random),Quick Sort (Median)\n");

    if (!experiment_quiet) {
        printf(PURPLE "╔══════════════════════════════════════════════════════╗\n");
    }

    /* Acumuladores por algoritmo (suma sobre outer_runs) */
    for (int s = 0; s < NUM_STEPS; s++) {
        int k = (NUM_STEPS == 1) ? n : 1 + (s * (n - 1)) / (NUM_STEPS - 1);

        double accSwap = 0, accIns = 0, accSel = 0, accCock = 0;
        double accMergeClas = 0, accMerge16 = 0;
        double accQLast = 0, accQFirst = 0, accQRand = 0, accQMed = 0;

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " Procesando n =" WHITE " %8d" PURPLE "                             ║\n", k);
            printf(PURPLE "║" MAGENTA " Paso:" WHITE " %4d/%4d" PURPLE "                                     ║\n", s + 1, NUM_STEPS);
        }

        for (int run = 0; run < outer_runs; run++) {
            if (is_average_case && run > 0) {
                shuffle_players(working, n);
            }

            clock_t start, end;

            #define TIME_BLOCK(flag, fn_call, acc)                                  \
                if (current_active_flags & (flag)) {                                \
                    double t = 0;                                                   \
                    for (int i = 0; i < NUM_TRIALS; i++) {                          \
                        memcpy(buf, working, k * sizeof(Player));                   \
                        start = clock(); fn_call; end = clock();                    \
                        t += (double)(end - start) / CLOCKS_PER_SEC;                \
                    }                                                               \
                    (acc) += t / NUM_TRIALS;                                        \
                }

            TIME_BLOCK(FLAG_SWAP_SORT,      swap_sort(buf, k, compare_id),                  accSwap)
            TIME_BLOCK(FLAG_INSERTION_SORT, insertion_sort(buf, k, compare_id),             accIns)
            TIME_BLOCK(FLAG_SELECTION_SORT, selection_sort(buf, k, compare_id),             accSel)
            TIME_BLOCK(FLAG_COCKTAIL_SORT,  cocktail_shaker_sort(buf, k, compare_id),       accCock)
            TIME_BLOCK(FLAG_MERGE_CLASSIC,  merge_sort_classic(buf, k, compare_id),         accMergeClas)
            TIME_BLOCK(FLAG_MERGE_OPT16,    merge_sort_optimized(buf, k, 16, compare_id),   accMerge16)
            TIME_BLOCK(FLAG_QUICK_LAST,     quick_sort(buf, k, 1, compare_id),              accQLast)
            TIME_BLOCK(FLAG_QUICK_FIRST,    quick_sort(buf, k, 2, compare_id),              accQFirst)
            TIME_BLOCK(FLAG_QUICK_RANDOM,   quick_sort(buf, k, 3, compare_id),              accQRand)
            TIME_BLOCK(FLAG_QUICK_MEDIAN,   quick_sort(buf, k, 4, compare_id),              accQMed)
            #undef TIME_BLOCK
        }

        /* Promediar sobre las outer_runs */
        double tSwap      = accSwap      / outer_runs;
        double tIns       = accIns       / outer_runs;
        double tSel       = accSel       / outer_runs;
        double tCock      = accCock      / outer_runs;
        double tMergeClas = accMergeClas / outer_runs;
        double tMerge16   = accMerge16   / outer_runs;
        double tQLast     = accQLast     / outer_runs;
        double tQFirst    = accQFirst    / outer_runs;
        double tQRand     = accQRand     / outer_runs;
        double tQMed      = accQMed      / outer_runs;

        if (!experiment_quiet) {
            if (current_active_flags & FLAG_SWAP_SORT)      printf(PURPLE "║" LIGHT_BLUE  "\tSwap Sort:             " WHITE " %f" PURPLE "         ║\n", tSwap);
            if (current_active_flags & FLAG_INSERTION_SORT) printf(PURPLE "║" LIGHT_BLUE  "\tInsertion Sort:        " WHITE " %f" PURPLE "         ║\n", tIns);
            if (current_active_flags & FLAG_SELECTION_SORT) printf(PURPLE "║" LIGHT_BLUE  "\tSelection Sort:        " WHITE " %f" PURPLE "         ║\n", tSel);
            if (current_active_flags & FLAG_COCKTAIL_SORT)  printf(PURPLE "║" LIGHT_BLUE  "\tCocktail Shaker Sort:  " WHITE " %f" PURPLE "         ║\n", tCock);
            if (current_active_flags & FLAG_MERGE_CLASSIC)  printf(PURPLE "║" YELLOW     "\tMerge Sort Classic:    " WHITE " %f" PURPLE "         ║\n", tMergeClas);
            if (current_active_flags & FLAG_MERGE_OPT16)    printf(PURPLE "║" YELLOW     "\tMerge Sort Opt(16):    " WHITE " %f" PURPLE "         ║\n", tMerge16);
            if (current_active_flags & FLAG_QUICK_LAST)     printf(PURPLE "║" LIGHT_GREEN "\tQuick Sort (Last):     " WHITE " %f" PURPLE "         ║\n", tQLast);
            if (current_active_flags & FLAG_QUICK_FIRST)    printf(PURPLE "║" LIGHT_GREEN "\tQuick Sort (First):    " WHITE " %f" PURPLE "         ║\n", tQFirst);
            if (current_active_flags & FLAG_QUICK_RANDOM)   printf(PURPLE "║" LIGHT_GREEN "\tQuick Sort (Random):   " WHITE " %f" PURPLE "         ║\n", tQRand);
            if (current_active_flags & FLAG_QUICK_MEDIAN)   printf(PURPLE "║" LIGHT_GREEN "\tQuick Sort (Median):   " WHITE " %f" PURPLE "         ║\n", tQMed);
            printf(PURPLE "╠══════════════════════════════════════════════════════╣\n");
        }

        fprintf(csv, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
                k, tSwap, tIns, tSel, tCock, tMergeClas, tMerge16,
                tQLast, tQFirst, tQRand, tQMed);
    }

    if (!experiment_quiet) {
        printf(PURPLE "║" LIGHT_GREEN "                  CSV Data written                    " PURPLE "║\n");
        printf(PURPLE "╚══════════════════════════════════════════════════════╝\n" RESET);
        printf("\n" BG_GREEN "Data saved in %s" RESET "\n", out_filename);
    }

    fclose(csv);
    free(players);
    free(buf);
    free(working);
}

/* ------------------------------------------------------------------ */
/* run_threshold_experiment: barre 7 thresholds para Merge Opt        */
/* ------------------------------------------------------------------ */
void run_threshold_experiment(const char* target_file, const char* out_filename, int is_average_case)
{
    int n = 0;
    Player* players;
    if ((players = load_players((char*)target_file, &n)) == NULL) {
        return;
    }
    if (!experiment_quiet) {
        printf("Arreglo de jugadores cargado desde %s\n", target_file);
    }

    const int outer_runs = is_average_case ? NUM_AVG_RUNS : 1;

    const int thresholds[] = {2, 4, 8, 16, 32, 64, 128};
    const int num_thresholds = 7;

    Player* buf = malloc(n * sizeof(Player));
    Player* working = malloc(n * sizeof(Player));
    if (!buf || !working) {
        print_error(102, "players", NULL);
        free(players); free(buf); free(working);
        return;
    }
    memcpy(working, players, n * sizeof(Player));

    FILE *csv = fopen(out_filename, "w");
    if (csv == NULL) {
        print_error(101, out_filename, NULL);
        free(players); free(buf); free(working);
        return;
    }

    fprintf(csv, "N,Merge Sort T(2),Merge Sort T(4),Merge Sort T(8),Merge Sort T(16),"
                 "Merge Sort T(32),Merge Sort T(64),Merge Sort T(128)\n");

    if (!experiment_quiet) {
        printf(PURPLE "╔══════════════════════════════════════════════════════╗\n");
    }

    for (int s = 0; s < NUM_STEPS; s++) {
        int k = (NUM_STEPS == 1) ? n : 1 + (s * (n - 1)) / (NUM_STEPS - 1);

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " Procesando n =" WHITE " %8d" PURPLE "                             ║\n", k);
            printf(PURPLE "║" MAGENTA " Paso:" WHITE " %4d/%4d" PURPLE "                                     ║\n", s + 1, NUM_STEPS);
        }

        double acc[7] = {0};

        for (int run = 0; run < outer_runs; run++) {
            if (is_average_case && run > 0) {
                shuffle_players(working, n);
            }

            for (int t = 0; t < num_thresholds; t++) {
                clock_t start, end;
                double tMerge = 0;
                for (int i = 0; i < NUM_TRIALS; i++) {
                    memcpy(buf, working, k * sizeof(Player));
                    start = clock();
                    merge_sort_optimized(buf, k, thresholds[t], compare_id);
                    end = clock();
                    tMerge += (double)(end - start) / CLOCKS_PER_SEC;
                }
                acc[t] += tMerge / NUM_TRIALS;
            }
        }

        fprintf(csv, "%d", k);
        for (int t = 0; t < num_thresholds; t++) {
            double avg = acc[t] / outer_runs;
            if (!experiment_quiet) {
                printf(PURPLE "║" YELLOW "\tMerge Sort T(%3d):     " WHITE " %f" PURPLE "         ║\n", thresholds[t], avg);
            }
            fprintf(csv, ",%f", avg);
        }
        fprintf(csv, "\n");

        if (!experiment_quiet) {
            printf(PURPLE "╠══════════════════════════════════════════════════════╣\n");
        }
    }

    if (!experiment_quiet) {
        printf(PURPLE "║" LIGHT_GREEN "                  CSV Data written                    " PURPLE "║\n");
        printf(PURPLE "╚══════════════════════════════════════════════════════╝\n" RESET);
        printf("\n" BG_GREEN "Data saved in %s" RESET "\n", out_filename);
    }

    fclose(csv);
    free(players);
    free(buf);
    free(working);
}

/* ------------------------------------------------------------------ */
/* run_search_experiment                                              */
/* ------------------------------------------------------------------ */
void run_search_experiment(const char* target_file, const char* out_filename, int is_worst_case)
{
    int n = 0;
    Player* players;
    if ((players = load_players((char*)target_file, &n)) == NULL) return;
    if (!experiment_quiet) {
        printf("Arreglo de jugadores cargado desde %s para busqueda\n", target_file);
    }

    FILE *csv = fopen(out_filename, "w");
    if (csv == NULL) { free(players); return; }

    fprintf(csv, "N,Binaria Recursiva,Binaria Rango,Exponencial,Interpolacion\n");

    const int reps = 1000;

    for (int s = 0; s < NUM_STEPS; s++) {
        int k = (NUM_STEPS == 1) ? n : 1 + (s * (n - 1)) / (NUM_STEPS - 1);

        double tBinRec = 0, tBinRan = 0, tExp = 0, tInt = 0;

        Player target;
        if (is_worst_case) {
            target = players[0];  // cualquier campo valido
            target.id = __INT_MAX__;       // sentinel garantizado ausente
        }

        struct timespec t0, t1;

        for (int i = 0; i < reps; i++) {
            if (!is_worst_case) target = players[rand() % k];

            int first, last;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            binary_search_recursive(players, 0, k - 1, &target);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            tBinRec += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            binary_search_range(players, k, &target, &first, &last);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            tBinRan += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            exponential_search(players, k, &target);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            tExp += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;

            clock_gettime(CLOCK_MONOTONIC, &t0);
            interpolation_search(players, k, &target);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            tInt += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        }

        tBinRec /= reps; tBinRan /= reps; tExp /= reps; tInt /= reps;
        fprintf(csv, "%d,%.9f,%.9f,%.9f,%.9f\n", k, tBinRec, tBinRan, tExp, tInt);
    }

    fclose(csv);
    free(players);
    if (!experiment_quiet) printf("Search experiment saved in %s\n", out_filename);
}

/* ------------------------------------------------------------------ */
/* run_select_experiment                                              */
/* ------------------------------------------------------------------ */
void run_select_experiment(const char* target_file, const char* out_filename, int is_worst_case)
{
    int n = 0;
    Player* players;
    if ((players = load_players((char*)target_file, &n)) == NULL) return;

    FILE *csv = fopen(out_filename, "w");
    if (csv == NULL) { free(players); return; }

    fprintf(csv, "N,Quick Select\n");

    Player* arr = malloc(n * sizeof(Player));
    for (int s = 0; s < NUM_STEPS; s++) {
        int k = (NUM_STEPS == 1) ? n : 1 + (s * (n - 1)) / (NUM_STEPS - 1);
        double tSel = 0;

        int k_target = is_worst_case ? 0 : k / 2;
        int pivot_t  = is_worst_case ? 1 : 3;   /* peor: last, mejor: random */

        for (int i = 0; i < NUM_TRIALS; i++) {
            memcpy(arr, players, k * sizeof(Player));
            clock_t start = clock();
            quick_select(arr, k, k_target, pivot_t, compare_id);
            clock_t end = clock();
            tSel += (double)(end - start) / CLOCKS_PER_SEC;
        }
        tSel /= NUM_TRIALS;
        fprintf(csv, "%d,%f\n", k, tSel);
    }
    fclose(csv);
    free(players);
    free(arr);
    if (!experiment_quiet) printf("Select experiment saved in %s\n", out_filename);
}

/** -----------------------
 *  TEAM EXPERIMENTS
 * ------------------------ 
 */
/* ---------------- CONSTRAINED: variar N, budget fijo ---------------- */
static void run_constrained_vary_n(Player *working, Player *buf, int n_players, FILE *csv){

    fprintf(csv,
            "N,Budget,DP_TopDown_s,DP_BottomUp_s,Greedy_Score_s,Greedy_ScoreCost_s,"
            "Greedy_LowestCost_s,DP_TopDown_score,DP_BottomUp_score,"
            "Greedy_Score_score,Greedy_ScoreCost_score,Greedy_LowestCost_score\n");

    int budget = TEAM_FIXED_BUDGET;

    for (int s = 0; s < NUM_STEPS; s++) {
        int n = (NUM_STEPS == 1) ? n_players : 1 + (s * (n_players - 1)) / (NUM_STEPS - 1);

        double t_dp_topdown = 0.0, t_dp_bottomup = 0.0;
        double t_greedy_score = 0.0, t_greedy_score_cost = 0.0, t_greedy_lowest_cost = 0.0;
        double score_dp_topdown = 0.0, score_dp_bottomup = 0.0;
        double score_greedy_score = 0.0, score_greedy_score_cost = 0.0, score_greedy_lowest_cost = 0.0;

        for (int run = 0; run < NUM_AVG_RUNS; run++) {
            if (run > 0) shuffle_players(working, n);

            struct timespec t0, t1;

            copy_prefix(buf, working, n);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            Team team = create_team_dp_topdown(buf, n, budget);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_dp_topdown += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_dp_topdown = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, n);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_dp_bottomup(buf, n, budget);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_dp_bottomup += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_dp_bottomup = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, n);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, n, budget, GREEDY_BY_SCORE);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_score += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_score = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, n);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, n, budget, GREEDY_BY_SCORE_COST);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_score_cost += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_score_cost = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, n);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, n, budget, GREEDY_BY_LOWEST_COST);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_lowest_cost += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_lowest_cost = team_total_score(&team);
            free_team(&team);
        }

        t_dp_topdown /= NUM_AVG_RUNS;
        t_dp_bottomup /= NUM_AVG_RUNS;
        t_greedy_score /= NUM_AVG_RUNS;
        t_greedy_score_cost /= NUM_AVG_RUNS;
        t_greedy_lowest_cost /= NUM_AVG_RUNS;

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " [vs N] N = \t\t" WHITE " %d" PURPLE "\t║\n", n);
            printf(PURPLE "║" LIGHT_BLUE " Budget (fijo) = \t " WHITE " %d" PURPLE "\t║\n", budget);
        }

        fprintf(csv, "%d,%d,%.9f,%.9f,%.9f,%.9f,%.9f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
                n, budget,
                t_dp_topdown, t_dp_bottomup, t_greedy_score, t_greedy_score_cost, t_greedy_lowest_cost,
                score_dp_topdown, score_dp_bottomup, score_greedy_score,
                score_greedy_score_cost, score_greedy_lowest_cost);
    }
}

/* ---------------- CONSTRAINED: variar Budget, N fijo (todo el dataset) ---------------- */
static void run_constrained_vary_budget(Player *working, Player *buf, FILE *csv){

    fprintf(csv,
            "N,Budget,DP_TopDown_s,DP_BottomUp_s,Greedy_Score_s,Greedy_ScoreCost_s,"
            "Greedy_LowestCost_s,DP_TopDown_score,DP_BottomUp_score,"
            "Greedy_Score_score,Greedy_ScoreCost_score,Greedy_LowestCost_score\n");


    for (int s = 0; s < NUM_STEPS; s++) {
        int budget = (COST_MAX / NUM_STEPS) * s + 10;

        double t_dp_topdown = 0.0, t_dp_bottomup = 0.0;
        double t_greedy_score = 0.0, t_greedy_score_cost = 0.0, t_greedy_lowest_cost = 0.0;
        double score_dp_topdown = 0.0, score_dp_bottomup = 0.0;
        double score_greedy_score = 0.0, score_greedy_score_cost = 0.0, score_greedy_lowest_cost = 0.0;

        for (int run = 0; run < NUM_AVG_RUNS; run++) {
            if (run > 0) shuffle_players(working, TEAM_FIXED_N);

            struct timespec t0, t1;

            copy_prefix(buf, working, TEAM_FIXED_K);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            Team team = create_team_dp_topdown(buf, TEAM_FIXED_N, budget);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_dp_topdown += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_dp_topdown = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, TEAM_FIXED_N);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_dp_bottomup(buf, TEAM_FIXED_N, budget);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_dp_bottomup += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_dp_bottomup = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, TEAM_FIXED_K);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, TEAM_FIXED_N, budget, GREEDY_BY_SCORE);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_score += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_score = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, TEAM_FIXED_N);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, TEAM_FIXED_N, budget, GREEDY_BY_SCORE_COST);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_score_cost += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_score_cost = team_total_score(&team);
            free_team(&team);

            copy_prefix(buf, working, TEAM_FIXED_N);
            clock_gettime(CLOCK_MONOTONIC, &t0);
            team = create_team_greedy(buf, TEAM_FIXED_N, budget, GREEDY_BY_LOWEST_COST);
            clock_gettime(CLOCK_MONOTONIC, &t1);
            t_greedy_lowest_cost += (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
            if (run == 0) score_greedy_lowest_cost = team_total_score(&team);
            free_team(&team);
        }

        t_dp_topdown /= NUM_AVG_RUNS;
        t_dp_bottomup /= NUM_AVG_RUNS;
        t_greedy_score /= NUM_AVG_RUNS;
        t_greedy_score_cost /= NUM_AVG_RUNS;
        t_greedy_lowest_cost /= NUM_AVG_RUNS;

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " [vs Budget] Budget =\t" WHITE " %8d" PURPLE "                  ║\n", budget);
            printf(PURPLE "║" LIGHT_BLUE " N (fijo):\t\t" WHITE " %8d" PURPLE "                       ║\n", TEAM_FIXED_N);
        }

        fprintf(csv, "%d,%d,%.9f,%.9f,%.9f,%.9f,%.9f,%.3f,%.3f,%.3f,%.3f,%.3f\n",
                TEAM_FIXED_N, budget,
                t_dp_topdown, t_dp_bottomup, t_greedy_score, t_greedy_score_cost, t_greedy_lowest_cost,
                score_dp_topdown, score_dp_bottomup, score_greedy_score,
                score_greedy_score_cost, score_greedy_lowest_cost);
    }
}


static void run_unconstrained_vary_n(Player *working, Player *buf, int n_players, FILE *csv){

    fprintf(csv, "N,K,Greedy_Unconstrained_s,Greedy_Unconstrained_score\n");

    for (int s = 0; s < NUM_STEPS; s++) {
        int n = (NUM_STEPS == 1) ? n_players : 1 + (s * (n_players - 1)) / (NUM_STEPS - 1);

        copy_prefix(buf, working, n);

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        Team team = create_team_greedy_unconstrained(buf, n, TEAM_FIXED_K);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double t_greedy = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        double score_greedy = team_total_score(&team);
        free_team(&team);

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " [vs N] N =\t" WHITE " %8d" PURPLE "                             ║\n", n);
            printf(PURPLE "║" LIGHT_BLUE " K (team size):\t" WHITE " %8d" PURPLE "                       ║\n", TEAM_FIXED_K);
        }

        fprintf(csv, "%d,%d,%.9f,%.3f\n", n, TEAM_FIXED_K, t_greedy, score_greedy);
    }
}

/**
 * @brief SIN BUDGET, N FIJO, K VARIABLE
 */
static void run_unconstrained_vary_k(Player *working, Player *buf, int n, FILE *csv){

    fprintf(csv, "N,K,Greedy_Unconstrained_s,Greedy_Unconstrained_score\n");

    int k_input = n;

    for (int s = 0; s < NUM_STEPS; s++) {
        int team_size = (NUM_STEPS == 1) ? k_input : 1 + (s * (k_input - 1)) / (NUM_STEPS - 1);
        if (team_size > k_input) team_size = k_input;
        if (team_size <= 0) continue;

        copy_prefix(buf, working, k_input);

        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        Team team = create_team_greedy_unconstrained(buf, k_input, team_size);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double t_greedy = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        double score_greedy = team_total_score(&team);
        free_team(&team);

        if (!experiment_quiet) {
            printf(PURPLE "║" MAGENTA " [vs K] K =\t" WHITE " %2d" PURPLE "\t\t║\n", team_size);
            printf(PURPLE "║" LIGHT_BLUE " N (fijo):\t\t" WHITE " %2d" PURPLE "\t\t║\n", k_input);
        }

        fprintf(csv, "%d,%d,%.9f,%.3f\n", k_input, team_size, t_greedy, score_greedy);
    }
}

void run_team_experiment(const char* target_file, const char* out_filename, int is_constrained)
{
    int n = 0;
    Player *players;
    if ((players = load_players((char*)target_file, &n)) == NULL) {
        return;
    }

    Player *buf = malloc((size_t)n * sizeof(Player));
    Player *working = malloc((size_t)n * sizeof(Player));
    if (buf == NULL || working == NULL) {
        print_error(102, "players", NULL);
        free(players);
        free(buf);
        free(working);
        return;
    }
    memcpy(working, players, (size_t)n * sizeof(Player));

    char out_file_a[256];
    char out_file_b[256];

    if (is_constrained) {
        snprintf(out_file_a, sizeof(out_file_a), "%s_vs_n_experiment.csv", out_filename);
        snprintf(out_file_b, sizeof(out_file_b), "%s_vs_budget_experiment.csv", out_filename);
    }
    else {
        snprintf(out_file_a, sizeof(out_file_a), "%s_vs_n_experiment.csv", out_filename);
        snprintf(out_file_b, sizeof(out_file_b), "%s_vs_k_experiment.csv", out_filename);
    }

    FILE *csv_a = fopen(out_file_a, "w");
    if (csv_a == NULL) {
        print_error(101, out_file_a, NULL);
        free(players); free(buf); free(working);
        return;
    }

    FILE *csv_b = fopen(out_file_b, "w");
    if (csv_b == NULL) {
        print_error(101, out_file_b, NULL);
        fclose(csv_a);
        free(players); free(buf); free(working);
        return;
    }

    switch (is_constrained) {
        case 1:
            run_constrained_vary_n(working, buf, n, csv_a);
            memcpy(working, players, (size_t)n * sizeof(Player));
            run_constrained_vary_budget(working, buf, csv_b);
            break;
        case 0:
            run_unconstrained_vary_n(working, buf, n, csv_a);
            memcpy(working, players, (size_t)n * sizeof(Player));
            run_unconstrained_vary_k(working, buf, n, csv_b);
            break;
        default:
            break;
    }

    if (!experiment_quiet) {
        printf("Team experiment saved in %s and %s\n", out_file_a, out_file_b);
    }

    fclose(csv_a);
    fclose(csv_b);
    free(players);
    free(buf);
    free(working);
}

/* ------------------------------------------------------------------ */
/* Orquestadores                                                      */
/* ------------------------------------------------------------------ */
void run_sort_experiments(const char* sorted_file, const char* inverted_file, const char* shuffled_file, const char* out_prefix)
{
    char out_file[256];

    // Best case: sorted input — exclude Last/First pivots (sorted is their worst case)
    SortAlgorithmFlag saved = current_active_flags;
    current_active_flags &= ~(FLAG_QUICK_LAST | FLAG_QUICK_FIRST);

    snprintf(out_file, sizeof(out_file), "%s_best_experiment.csv", out_prefix);
    run_experiment(sorted_file, out_file, 0);

    current_active_flags = saved;  // restore before worst and average

    snprintf(out_file, sizeof(out_file), "%s_worst_experiment.csv", out_prefix);
    run_experiment(inverted_file, out_file, 0);

    snprintf(out_file, sizeof(out_file), "%s_average_experiment.csv", out_prefix);
    run_experiment(shuffled_file, out_file, 1);
}

void run_threshold_experiments(const char* sorted_file, const char* inverted_file, const char* shuffled_file, const char* out_prefix)
{
    char out_file[256];

    snprintf(out_file, sizeof(out_file), "%s_best_experiment.csv", out_prefix);
    run_threshold_experiment(sorted_file, out_file, 0);

    snprintf(out_file, sizeof(out_file), "%s_worst_experiment.csv", out_prefix);
    run_threshold_experiment(inverted_file, out_file, 0);

    snprintf(out_file, sizeof(out_file), "%s_average_experiment.csv", out_prefix);
    run_threshold_experiment(shuffled_file, out_file, 1);
}

void run_search_experiments(const char* sorted_file, const char* out_prefix)
{
    char out_file[256];

    snprintf(out_file, sizeof(out_file), "%s_average_experiment.csv", out_prefix);
    run_search_experiment(sorted_file, out_file, 0);

    snprintf(out_file, sizeof(out_file), "%s_worst_experiment.csv", out_prefix);
    run_search_experiment(sorted_file, out_file, 1);
}

void run_select_experiments(const char* sorted_file, const char* shuffled_file, const char* out_prefix)
{
    char out_file[256];

    snprintf(out_file, sizeof(out_file), "%s_best_experiment.csv", out_prefix);
    run_select_experiment(shuffled_file, out_file, 0);

    snprintf(out_file, sizeof(out_file), "%s_worst_experiment.csv", out_prefix);
    run_select_experiment(sorted_file, out_file, 1);
}


