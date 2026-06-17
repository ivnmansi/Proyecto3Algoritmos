/**
 * @file config.h
 * @author Iván Mansilla
 * @brief Definiciones globales del programa
 * 
 */
#ifndef CONFIG_H
#define CONFIG_H

#define CSV_FILE "db/players.csv"
#define CSV_DIR "db/"

#define PLAYERS_SORTED_FILE CSV_DIR "players_sorted.csv"
#define PLAYERS_INVERTED_FILE CSV_DIR "players_inverted.csv"
#define PLAYERS_SHUFFLED_FILE CSV_DIR "players_shuffled.csv"

#define SORT_EXPERIMENT_PREFIX CSV_DIR "sort"
#define THRESHOLD_EXPERIMENT_PREFIX CSV_DIR "threshold"
#define SEARCH_EXPERIMENT_PREFIX CSV_DIR "search"
#define SELECT_EXPERIMENT_PREFIX CSV_DIR "select"
#define TEAM_EXPERIMENT_PREFIX CSV_DIR "team"
#define TEAM_UNCONSTRAINED_EXPERIMENT_PREFIX CSV_DIR "team_unconstrained"

#define COST_MAX 10000

#define TEAM_FIXED_BUDGET 4000
#define TEAM_FIXED_K 100
#define TEAM_FIXED_N 1000

#endif