#include "team.h"

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

/* DP Top-Down (Memoization) */
Team create_team_dp_topdown(Player *players, int n, int budget) {
    /* TODO: implementar */
    return init_team();
}

/* DP Bottom-Up (Tabulation) */
Team create_team_dp_bottomup(Player *players, int n, int budget) {
    /* TODO: implementar */
    return init_team();
}

/* Greedy: seleccionar por score (con restricción de presupuesto) */
Team create_team_greedy_by_score(Player *players, int n, int budget) {
    /* TODO: implementar */
    return init_team();
}

/* Greedy: seleccionar por relación score/costo (con restricción de presupuesto) */
Team create_team_greedy_by_score_cost(Player *players, int n, int budget) {
    /* TODO: implementar */
    return init_team();
}

/* Greedy: seleccionar por menor costo primero (con restricción de presupuesto) */
Team create_team_greedy_by_lowest_cost(Player *players, int n, int budget) {
    /* TODO: implementar */
    return init_team();
}

/* Greedy para escenario sin restricción: seleccionar mejores por score hasta tamaño */
Team create_team_greedy_unconstrained_by_score(Player *players, int n, int team_size) {
    /* TODO: implementar */
    return init_team();
}

