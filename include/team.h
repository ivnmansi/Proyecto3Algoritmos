#ifndef TEAM_H
#define TEAM_H

#include "player.h"

typedef struct {
    int num_players;
    Player* players;
} Team;

Team init_team();
void free_team(Team* team);
void add_player_to_team(Team* team, Player player);
void print_team(const Team* team);

/* Algoritmos para conformar equipos */
Team create_team_dp_topdown(Player *players, int n, int budget);
Team create_team_dp_bottomup(Player *players, int n, int budget);

/* Estrategias voraces (con restricción de presupuesto) */
Team create_team_greedy_by_score(Player *players, int n, int budget);
Team create_team_greedy_by_score_cost(Player *players, int n, int budget);
Team create_team_greedy_by_lowest_cost(Player *players, int n, int budget);

/* Estrategia voraz para escenario sin restricción (selección por score) */
Team create_team_greedy_unconstrained_by_score(Player *players, int n, int team_size);
#endif