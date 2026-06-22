# Configuración general
set datafile separator ","
set terminal pngcairo size 800,600 enhanced font 'Verdana,10' linewidth 2

# GRÁFICO 1: TIEMPO
set output 'plots/team_time_vs_n.png'
set title "Tiempo de Ejecucion: DP vs Greedy"
set xlabel "Tamano de entrada (N)"
set ylabel "Tiempo (segundos)"
set key outside right top

plot 'db/team_vs_n_experiment.csv' skip 1 using 1:3 with lines title "DP Top-Down", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:4 with lines title "DP Bottom-Up", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:5 with lines title "Greedy (Score)", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:6 with lines title "Greedy (Score/Cost)", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:7 with lines title "Greedy (Lowest Cost)"

# GRÁFICO 2: SCORE
set output 'plots/team_score_vs_n.png'
set title "Calidad de la Solucion: DP vs Greedy"
set xlabel "Tamano de entrada (N)"
set ylabel "Puntaje Total"
set key outside right top

plot 'db/team_vs_n_experiment.csv' skip 1 using 1:8 with lines title "DP Top-Down", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:9 with lines title "DP Bottom-Up", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:10 with lines title "Greedy (Score)", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:11 with lines title "Greedy (Score/Cost)", \
     'db/team_vs_n_experiment.csv' skip 1 using 1:12 with lines title "Greedy (Lowest Cost)"
