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

Team create_team_dp_topdown(Player *players, int n, int budget, int team_size){
    /* TODO: implementar */
    return init_team();
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

        if(team.num_players >= team_size) break;

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

