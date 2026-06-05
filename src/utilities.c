#include "utilities.h"

void print_menu(){
    printf(RESET "          ╔═══════════╗\n");
	printf( "          ║ MAIN MENU ║\n");
	printf("╔═════════╩═══════════╩══════════╗\n");
	printf("║ "DARK_YELLOW "1)" YELLOW " Generate new CSV" RESET "            ║\n");
	printf("║ "BROWN "2)" ORANGE " Read actual CSV" RESET "             ║\n");
	printf("║ "DARK_BLUE "3)" LIGHT_BLUE " Sort CSV" RESET "                    ║\n");
	printf("║ "DARK_GREEN "4)" LIGHT_GREEN " Search value in CSV" RESET "         ║\n");
    printf("║ "DARK_CYAN "5)" LIGHT_CYAN " Create team with CSV" RESET "        ║\n");
	printf("║ "PURPLE "6)" MAGENTA " Run experiment" RESET "              ║\n");
	printf("║ "DARK_RED "7)" LIGHT_RED " Exit" RESET "                        ║\n");
	printf("╚════════════════════════════════╝\n");
	printf(DARK_GRAY"Choose an option: " RESET);
}

void print_sort_generate_menu(){
    	printf(BROWN "   ╔════════════════════════╗\n");
		printf(BROWN "   ║" YELLOW "  Choose the case type  " BROWN "║" "\n");
		printf(BROWN "╔══╩════════════════════════╩══╗\n");
		printf(BROWN "║" DARK_YELLOW " 1)" YELLOW " Sorted Array" BROWN "              ║\n");
		printf(BROWN "║" DARK_YELLOW " 2)" YELLOW " Inverse Array" BROWN "             ║\n");
		printf(BROWN "║" DARK_YELLOW " 3)" YELLOW " Shuffled Array" BROWN "            ║\n");
		printf(BROWN"╚══════════════════════════════╝\n");
		printf(DARK_YELLOW"Option: " YELLOW);
}

void print_sort_case_menu(){
        printf(EVEN_DARKER_BLUE"    ╔════════════════════════════╗\n");
        printf(EVEN_DARKER_BLUE"    ║" LIGHT_BLUE " Choose a sorting algorithm " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╔═══╩════════════════════════════╩═══╗\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 1)" LIGHT_BLUE " Swap Sort                       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 2)" LIGHT_BLUE " Insertion Sort                  " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 3)" LIGHT_BLUE " Selection Sort                  " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 4)" LIGHT_BLUE " Cocktail Shaker Sort            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 5)" LIGHT_BLUE " Merge Sort (Classic)            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 6)" LIGHT_BLUE " Merge Sort (Optimized)          " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 7)" LIGHT_BLUE " Quick Sort (Last Pivot)         " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 8)" LIGHT_BLUE " Quick Sort (First Pivot)        " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 9)" LIGHT_BLUE " Quick Sort (Random Pivot)       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 10)" LIGHT_BLUE" Quick Sort (Median of 3)       " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╚════════════════════════════════════╝\n");
        printf(DARK_BLUE "Option: " LIGHT_BLUE);
}

void print_field_to_sort_menu(){
        printf(EVEN_DARKER_BLUE"   ╔══════════════════════╗\n");
        printf(EVEN_DARKER_BLUE"   ║" LIGHT_BLUE " Choose field to sort " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE"   ║" LIGHT_BLUE "    by (Ascending)    " EVEN_DARKER_BLUE "║\n");
        printf(EVEN_DARKER_BLUE "╔══╩══════════════════════╩══╗\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 1)" LIGHT_BLUE " ID                      " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 2)" LIGHT_BLUE " Name                    " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 3)" LIGHT_BLUE " Team                    " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 4)" LIGHT_BLUE " Score                   " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 5)" LIGHT_BLUE " Competitions            " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "║" DARK_BLUE " 6)" LIGHT_BLUE " Cost                    " EVEN_DARKER_BLUE "║" "\n");
        printf(EVEN_DARKER_BLUE "╚════════════════════════════╝\n");

        printf(DARK_BLUE "Option: " LIGHT_BLUE);
}

void print_data_analytics_menu(){
        printf(EVEN_DARKER_GREEN "\n   ╔═══════════════════════════════════════╗\n");
        printf(EVEN_DARKER_GREEN "   ║" LIGHT_GREEN "    Data Analytics & Rankings Menu     " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ╚═══════════════════════════════════════╝\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 1)" LIGHT_GREEN " Generate Top N Ranking (by Score)  " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 2)" LIGHT_GREEN " Find the K-th Best Athlete         " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 3) " LIGHT_GREEN "Search Athletes by Score Range     " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ║" DARK_GREEN " 4) " LIGHT_GREEN "Search Athlete by exact ID         " EVEN_DARKER_GREEN "║\n");
        printf(EVEN_DARKER_GREEN "   ╚═══════════════════════════════════════╝\n");
        
        printf(DARK_GREEN "Selection: " LIGHT_GREEN);
}

void print_goodbye(){
    // 1/2 de probablidad de salir crocodile o aligator
		if (rand() % 2 == 0) {
			printf(DARK_GREEN);
			printf("   _____                                   _                            _     _ _        \n");
			printf("  / ____|                                 (_)                          | |   (_) |       \n");
			printf(" | (___   ___  ___    _   _  ___  _   _    _ _ __      __ _   __      _| |__  _| | ___   \n");
			printf("  \\___ \\ / _ \\/ _ \\  | | | |/ _ \\| | | |  | | '_ \\    / _` |  \\ \\ /\\ / / '_ \\| | |/ _ \\  \n");
			printf("  ____) |  __/  __/  | |_| | (_) | |_| |  | | | | |  | (_| |   \\ V  V /| | | | | |  __/  \n");
			printf(" |_____/ \\___|\\___|   \\__, |\\___/_\\__,_|  |_|_| |_|   \\__,_|    \\_/\\_/ |_| |_|_|_|\\___|  \n");
			printf("                       __/ |  | (_) |    | |                                             \n");
			printf("   ___ _ __ ___   ___ |___/ __| |_| | ___| |                                             \n");
			printf("  / __| '__/ _ \\ / __/ _ \\ / _` | | |/ _ \\ |                                             \n");
			printf(" | (__| | | (_) | (_| (_) | (_| | | |  __/_|                                             \n");
			printf("  \\___|_|  \\___/ \\___\\___/ \\__,_|_|_|\\___(_)                                             \n");
			printf(RESET);
		}
        else {
            printf(DARK_RED);
            printf("   _____                                   _       _                     _ _             _             _ \n");
            printf("  / ____|                                 | |     | |                   | (_)           | |           | |\n");
            printf(" | (___   ___  ___    _   _  ___  _   _   | | __ _| |_ ___ _ __     __ _| |_  __ _  __ _| |_ ___  _ __| |\n");
            printf("  \\___ \\ / _ \\/ _ \\  | | | |/ _ \\| | | |  | |/ _` | __/ _ \\ '__|   / _` | | |/ _` |/ _` | __/ _ \\| '__| |\n");
            printf("  ____) |  __/  __/  | |_| | (_) | |_| |  | | (_| | ||  __/ |     | (_| | | | (_| | (_| | || (_) | |  |_|\n");
            printf(" |_____/ \\___|\\___|   \\__, |\\___/ \\__,_|  |_|\\__,_|\\__\\___|_|      \\__,_|_|_|\\__, |\\__,_|\\__\\___/|_|  (_)\n");
            printf("                       __/ |                                                  __/ |                      \n");
            printf("                      |___/                                                  |___/                       \n");
            printf(RESET);
        }
}