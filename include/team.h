#ifndef TEAM_H
#define TEAM_H

#include "player.h"
#include "sorting.h"

typedef struct {
    int num_players;
    Player* players;
} Team;

typedef enum {
    GREEDY_BY_SCORE = 1,
    GREEDY_BY_SCORE_COST = 2,
    GREEDY_BY_LOWEST_COST = 3
} GreedyStrategy;

Team init_team();
void free_team(Team* team);
void add_player_to_team(Team* team, Player player);
void print_team(const Team* team);

/* Algoritmos para conformar equipos */
/* #ANDRES */
Team create_team_dp_topdown(Player *players, int n, int budget, int team_size);
Team create_team_dp_bottomup(Player *players, int n, int budget, int team_size);

/* Estrategias voraces (con restricción de presupuesto) */
/* #IVAN */
Team create_team_greedy(Player *players, int n, int budget, int team_size, GreedyStrategy strategy);

/* Estrategia voraz para escenario sin restricción (selección por score) */
Team create_team_greedy_unconstrained(Player *players, int n, int team_size);
#endif