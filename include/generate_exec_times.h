/**
 * @file generate_exec_times.h
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones para la ejecusion de tests (generate_exec_times.c)
 */
#ifndef EXEC_H
#define EXEC_H
#define NUM_TRIALS 100
#define NUM_STEPS 20
#include <stdio.h>
#include <time.h>

#include "errors.h"
#include "player.h"
#include "sorting.h"
#include "searching.h"
#include "generator.h"

typedef struct ExecResults {
    int n;
    // Tarea 1: Cuadráticos O(n^2)
    double timeSwapSort;
    double timeInsertionSort;
    double timeSelectionSort;
    double timeCocktailSort;
    // Tarea 2: Divide y Vencerás O(n log n)
    double timeMergeClassic;
    double timeMergeOpt10;
    double timeMergeOpt50;
    double timeQuickLast;
    double timeQuickRandom;
    double timeQuickMedian;
} ExecResults;

/**
 * @brief Enum flags para los distintos algoritmos de ordenamiento.
 */
typedef enum {
    FLAG_SWAP_SORT       = 1 << 0,
    FLAG_INSERTION_SORT  = 1 << 1,
    FLAG_SELECTION_SORT  = 1 << 2,
    FLAG_COCKTAIL_SORT   = 1 << 3,
    FLAG_MERGE_CLASSIC   = 1 << 4,
    FLAG_MERGE_OPT16     = 1 << 5,
    FLAG_MERGE_OPT50     = 1 << 6,
    FLAG_QUICK_LAST      = 1 << 7,
    FLAG_QUICK_RANDOM    = 1 << 8,
    FLAG_QUICK_MEDIAN    = 1 << 9,
    FLAG_ALL_SORTS       = 0x3FF
} SortAlgorithmFlag;

void set_active_sort_flags(SortAlgorithmFlag* active_flags, SortAlgorithmFlag selected_flags[]);
void set_experiment_quiet(int quiet);
void set_experiment_show_samples(int show_samples);
void run_threshold_experiment(void);
void run_experiment(const char* target_file, const char* out_filename);
void run_search_experiment(const char* target_file, const char* out_filename, int is_worst_case);
void run_select_experiment(const char* target_file, const char* out_filename, int is_worst_case);
void run_sort_experiments(const char* sorted_file, const char* inverted_file, const char* shuffled_file, const char* out_prefix);
void run_search_experiments(const char* sorted_file, const char* out_prefix);
void run_select_experiments(const char* sorted_file, const char* shuffled_file, const char* out_prefix);

#endif
