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
 * @brief ARREGLAR FORMATO!!!
 * 
 * @param team 
 */
void print_team(const Team* team){
    for(int i = 0; i < team->num_players; i++){
        printf("Player %d: %s\n", i + 1, team->players[i].name);
    }
}

/** ------ ALGORITMOS ------ */
// Función auxiliar recursiva para DP Top-Down (Opción 1: Solo Presupuesto)
static float dp_topdown_rec_2d(int i, int b, Player *players, int n, 
                               float *memo, int *decisions, int dim_b) {
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
Team create_team_dp_topdown(Player *players, int n, int budget, int team_size){
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

Team create_team_dp_bottomup(Player *players, int n, int budget, int team_size){
    /* TODO: implementar */
    return init_team();
}

/* Estrategias voraces (con restricción de presupuesto) */
/* #IVAN */
Team create_team_greedy(Player *players, int n, int budget, int team_size, GreedyStrategy strategy){
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
        /*
        if(team.num_players >= team_size) break;    sin fijar una cantidad exacta de deportistas
        */
        if (players[i].costo <= budget) {
            add_player_to_team(&team, players[i]);
            budget -= players[i].costo;
        }
    }

    return team;
}

/* Estrategia voraz para escenario sin restricción (selección por score) */
Team create_team_greedy_unconstrained(Player *players, int n, int team_size){
    /* TODO: implementar */
    return init_team();
}

