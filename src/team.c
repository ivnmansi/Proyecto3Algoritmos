#include "team.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief 
 * 
 * @return Team 
 */
Team init_team() {
    Team team;
    team.num_players = 0;
    team.players = NULL;
    return team;
}

/**
 * @brief 
 * 
 * @param team 
 */
void free_team(Team* team){
    free(team->players);
    team->players = NULL;
    team->num_players = 0;
}

/**
 * @brief 
 * 
 * @param team 
 * @param player 
 */
void add_player_to_team(Team* team, Player player){
    team->num_players++;
    team->players = realloc(team->players, team->num_players * sizeof(Player));
    team->players[team->num_players - 1] = player;
}

/**
 * @brief 
 * 
 * @param team 
 */
void print_team(const Team* team){
    print_player_array_more(team->players, team->num_players);
}

/** ------ ALGORITMOS ------ */
/**
 * @brief Función auxiliar recursiva para DP Top-Down (presupuesto)
 * 
 * @param i 
 * @param b 
 * @param players 
 * @param n 
 * @param memo 
 * @param decisions 
 * @param dim_b 
 * @return float 
 */
static float dp_topdown_rec_2d(int i, int b, Player *players, int n, float *memo, int *decisions, int dim_b) {
    if (i == n) return 0.0f; 

    long idx = (long)i * dim_b + b;

    if (memo[idx] != -1.0f) return memo[idx];

    // --- TRANSICIONES ---
    float score_skip = dp_topdown_rec_2d(i + 1, b, players, n, memo, decisions, dim_b);

    float score_take = -1.0f;
    if (players[i].costo <= b) {
        score_take = players[i].score + dp_topdown_rec_2d(i + 1, b - players[i].costo, players, n, memo, decisions, dim_b);
    }

    // --- DECISIÓN ---
    if (score_take > score_skip) {
        memo[idx] = score_take;
        decisions[idx] = 1;  
    } else {
        memo[idx] = score_skip;
        decisions[idx] = 0; 
    }

    return memo[idx];
}

/**
 * @brief Crea un equipo utilizando top-down DP con restricción de presupuesto.
 * 
 * @param players 
 * @param n 
 * @param budget 
 * @param team_size r
 * @return Team 
 */
Team create_team_dp_topdown(Player *players, int n, int budget){
    Team team = init_team();
    //Tabla
    int dim_i = n;
    int dim_b = budget + 1; 

    long total_size = (long)dim_i * dim_b;

    // Memoria
    float *memo = (float *)malloc(total_size * sizeof(float));
    int *decisions = (int *)malloc(total_size * sizeof(int));

    if (memo == NULL || decisions == NULL) {
        printf("Error: No hay memoria suficiente para DP.\n");
        if (memo) free(memo);
        if (decisions) free(decisions);
        return team;
    }

    for (long idx = 0; idx < total_size; idx++) {
        memo[idx] = -1.0f;
    }

    // Recursión desde el jugador 0 con el presupuesto total
    dp_topdown_rec_2d(0, budget, players, n, memo, decisions, dim_b);

    // Reconstrucción del equipo seleccionado
    int curr_b = budget;
    for (int i = 0; i < n; i++) {
        long idx = (long)i * dim_b + curr_b;
        if (decisions[idx] == 1) {
            add_player_to_team(&team, players[i]);
            curr_b -= players[i].costo; // Descontamos el presupuesto
        }
    }

    free(memo);
    free(decisions);

    return team;
}

/**
 * @brief Create a team dp bottomup object
 * 
 * @param players 
 * @param n 
 * @param budget 
 * @param team_size 
 * @return Team 
 */
Team create_team_dp_bottomup(Player *players, int n, int budget){
    Team team = init_team();

    //Dimensiones de la tabla 
    int dim_i = n + 1;
    int dim_b = budget + 1; 
    long total_size = (long)dim_i * dim_b;

    //Memoria para la tabla 
    float *dp = (float *)calloc(total_size, sizeof(float));

    if (dp == NULL) {
        printf("Error: No hay memoria suficiente para DP Bottom-Up.\n");
        return team;
    }

    //LLenamos la tabla
    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= budget; b++) {
            
            long curr_idx = (long)i * dim_b + b;
            long prev_idx = (long)(i - 1) * dim_b + b;

            float score_skip = dp[prev_idx];
            float score_take = -1.0f;

            if (players[i - 1].costo <= b) {
                long prev_take_idx = (long)(i - 1) * dim_b + (b - players[i - 1].costo);
                score_take = players[i - 1].score + dp[prev_take_idx];
            }

            // Tomamos la decisión óptima
            if (score_take > score_skip) {
                dp[curr_idx] = score_take;
            } else {
                dp[curr_idx] = score_skip;
            }
        }
    }

    //Reconstrucción del equipo seleccionado
    int curr_b = budget;
    for (int i = n; i > 0; i--) {
        long curr_idx = (long)i * dim_b + curr_b;
        long prev_idx = (long)(i - 1) * dim_b + curr_b;

        if (dp[curr_idx] != dp[prev_idx]) {
            add_player_to_team(&team, players[i - 1]);
            curr_b -= players[i - 1].costo; // Descontamos el presupuesto
        }
    }

    free(dp);

    return team;
}

/* Estrategias voraces (con restricción de presupuesto) */
Team create_team_greedy(Player *players, int n, int budget, GreedyStrategy strategy){
    Team team = init_team();

    // ordenar según estrategia
    switch(strategy){
        case GREEDY_BY_SCORE:
            merge_sort_optimized(players, n, 32, compare_score);
            break;
        case GREEDY_BY_SCORE_COST:
            merge_sort_optimized(players, n, 32, compare_score_cost);
            break;
        case GREEDY_BY_LOWEST_COST:
            merge_sort_optimized(players, n, 32, compare_cost);
            break;
        default:
            printf("Invalid greedy strategy.\n");
            return team;
    }

    for(int i = 0; i < n; i++){
        if (players[i].costo <= budget) {
            add_player_to_team(&team, players[i]);
            budget -= players[i].costo;
        }
    }

    return team;
}

/**
 * @brief Create a team greedy unconstrained object
 * 
 * @param players 
 * @param n 
 * @param team_size 
 * @return Team 
 */
Team create_team_greedy_unconstrained(Player *players, int n, int team_size){
    Team team = init_team();

    // Ordenamos por score
    merge_sort_optimized(players, n, 32, compare_score);

    if (team_size > n) team_size = n;

    for(int i = 0; i < team_size; i++){
        add_player_to_team(&team, players[i]);
    }

    return team;
}

