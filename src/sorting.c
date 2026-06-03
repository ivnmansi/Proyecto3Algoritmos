/**
 * @file sorting.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de ordenamiento
 */

#include"sorting.h"
#include"player.h"

/**
 * @brief Funcion interna de intercambio
 * 
 * @param a puntero a elemento a intercambiar por b
 * @param b puntero a elemento a intercambiar por a
 */
static void swap(Player *a, Player *b) {
	Player temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * @brief Ordenamiento por intercambio
 * 
 * @param V arreglo de enteros
 * @param n tamanho del arreglo
 * @param comp_f funcion de comparacion (1 si a < b, -1 si a > b, 0 si a = b)
 */
void swap_sort(Player V[], int n,int(*comp_f)( Player *, Player *)) {
	for (int i = 1; i <= n - 1; i++) {
		int swapped = 0;

		for (int j = 0; j <= n - 1 - i; j++) {
			if (comp_f(&V[j], &V[j + 1]) > 0) {
				swap(&V[j], &V[j + 1]);
				swapped = 1;
			}
		}

		if (swapped == 0) {
			break;
		}
	}
}

/**
 * @brief Ordenamiento por insercion
 * 
 * @param V arreglo de enteros
 * @param n tamanho del arreglo
 * @param comp_f funcion de comparacion (1 si a < b, -1 si a > b, 0 si a = b)
 */
void insertion_sort(Player V[], int n,int(*comp_f)( Player *, Player *)) {
	for (int i = 1; i <= n - 1; i++) {
		Player k = V[i];
		int j = i - 1;

		while ((j >= 0) && (comp_f(&V[j], &k) > 0)) {
			V[j + 1] = V[j];
			j--;
		}

		V[j + 1] = k;
	}
}

/**
 * @brief Ordenamiento por seleccion
 * 
 * @param V arreglo de enteros
 * @param n tamanho del arreglo
 * @param comp_f funcion de comparacion (1 si a < b, -1 si a > b, 0 si a = b)
 */
void selection_sort(Player V[], int n, int (*comp_f)(Player *, Player *)) {
	for (int i = 1; i <= n - 1; i++) {
		int k = i - 1;
		for (int j = i; j <= n - 1; j++) {
			if (comp_f(&V[j], &V[k]) < 0) {
				k = j;
			}
		}
		if (k != i - 1) {
			swap(&V[k], &V[i - 1]);
		}
	}
}

// !PUNTO COMERCIAL!. De vez en cuando, este 
// generate_exec_times.c

/**
 * @brief Ordenamiento por shaker
 * 
 * @param V arreglo de enteros
 * @param n tamanho del arreglo
 * @param comp_f funcion de comparacion (1 si a < b, -1 si a > b, 0 si a = b)
 */
void cocktail_shaker_sort(Player V[], int n, int (*comp_f)(Player *, Player *)) {
	int beg = 0;
	int end = n - 1;
	int swapped;

	while (beg < end) {
		swapped = 0;
		for (int i = beg; i <= end - 1; i++) {
			if (comp_f(&V[i], &V[i + 1]) > 0) {
				swap(&V[i], &V[i + 1]);
				swapped = 1;
			}
		}
		for (int i = end - 1; i >= beg + 1; i--) {
			if (comp_f(&V[i], &V[i - 1]) < 0) {
				swap(&V[i], &V[i - 1]);
				swapped = 1;
			}
		}
		if (swapped == 0) break;
		beg++;
		end--;
	}
}

// ==========================================
// 1. MERGE SORT (Clásico y Optimizado)
// ==========================================

/**
 * @brief Función auxiliar para fusionar dos subarreglos ordenados
 */
static void merge(Player V[], int l, int m, int r, int (*comp_f)(Player *, Player *)) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Player *L = (Player *)malloc(n1 * sizeof(Player));
    Player *R = (Player *)malloc(n2 * sizeof(Player));

    for (int i = 0; i < n1; i++) L[i] = V[l + i];
    for (int j = 0; j < n2; j++) R[j] = V[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comp_f(&L[i], &R[j]) <= 0) { 
            V[k] = L[i];
            i++;
        } else {
            V[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { V[k] = L[i]; i++; k++; }
    while (j < n2) { V[k] = R[j]; j++; k++; }

    free(L);
    free(R);
}

/**
 * @brief Merge Sort Recursivo (Versión Clásica)
 */
void merge_sort_rec(Player V[], int l, int r, int (*comp_f)(Player *, Player *)) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_rec(V, l, m, comp_f);
        merge_sort_rec(V, m + 1, r, comp_f);
        merge(V, l, m, r, comp_f);
    }
}

void merge_sort_classic(Player V[], int n, int (*comp_f)(Player *, Player *)) {
    merge_sort_rec(V, 0, n - 1, comp_f);
}

/**
 * @brief Merge Sort Optimizado (Usa Insertion Sort para subarreglos pequeños)
 * @param threshold Umbral (tamaño del subarreglo) para cambiar a Insertion Sort
 */
void merge_sort_opt_rec(Player V[], int l, int r, int threshold, int (*comp_f)(Player *, Player *)) {
    if (r - l + 1 <= threshold) {
        // Reutilizamos tu insertion_sort enviando desde la dirección del subarreglo
        insertion_sort(&V[l], r - l + 1, comp_f);
        return;
    }
    
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_opt_rec(V, l, m, threshold, comp_f);
        merge_sort_opt_rec(V, m + 1, r, threshold, comp_f);
        merge(V, l, m, r, comp_f);
    }
}

void merge_sort_optimized(Player V[], int n, int threshold, int (*comp_f)(Player *, Player *)) {
    merge_sort_opt_rec(V, 0, n - 1, threshold, comp_f);
}

// ==========================================
// 2. QUICK SORT (Lomuto y Variantes de Pivote)
// ==========================================

/**
 * @brief Función auxiliar para seleccionar el índice del pivote según la variante
 * pivot_type: 1 (Último), 2 (Primero), 3 (Aleatorio), 4 (Mediana de tres)
 */
static int select_pivot_index(Player V[], int low, int high, int pivot_type, int (*comp_f)(Player *, Player *)) {
    if (pivot_type == 1) return high;
    if (pivot_type == 2) return low;
    if (pivot_type == 3) return low + rand() % (high - low + 1);
    if (pivot_type == 4) {
        int mid = low + (high - low) / 2;
        int a_gt_b = comp_f(&V[low], &V[mid]) > 0;
        int b_gt_c = comp_f(&V[mid], &V[high]) > 0;
        int a_gt_c = comp_f(&V[low], &V[high]) > 0;

        // Lógica para encontrar la mediana
        if (a_gt_b) {
            if (b_gt_c) return mid; 
            else if (a_gt_c) return high; 
            else return low; 
        } else {
            if (!b_gt_c) return mid; 
            else if (a_gt_c) return low; 
            else return high; 
        }
    }
    return high; // Por defecto retorna el último
}

/**
 * @brief Esquema de partición de Lomuto
 */
static int lomuto_partition(Player V[], int low, int high, int pivot_type, int (*comp_f)(Player *, Player *)) {
    // Obtenemos el pivote y lo movemos al final (comportamiento estándar de Lomuto)
    int p_idx = select_pivot_index(V, low, high, pivot_type, comp_f);
    swap(&V[p_idx], &V[high]); 

    Player pivot = V[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (comp_f(&V[j], &pivot) <= 0) {
            i++;
            swap(&V[i], &V[j]);
        }
    }
    swap(&V[i + 1], &V[high]);
    return i + 1;
}

/**
 * @brief Quick Sort Recursivo
 */
void quick_sort_rec(Player V[], int low, int high, int pivot_type, int (*comp_f)(Player *, Player *)) {
    if (low < high) {
        int pi = lomuto_partition(V, low, high, pivot_type, comp_f);
        quick_sort_rec(V, low, pi - 1, pivot_type, comp_f);
        quick_sort_rec(V, pi + 1, high, pivot_type, comp_f);
    }
}
/**
 * @brief Función principal de Quick Sort
 * @param pivot_type 1: Último, 2: Primero, 3: Aleatorio, 4: Mediana de tres
 */
void quick_sort(Player V[], int n, int pivot_type, int (*comp_f)(Player *, Player *)) {
    quick_sort_rec(V, 0, n - 1, pivot_type, comp_f);
}

/**
 * @brief Función recursiva interna para Quick Select
 * Utiliza la partición de Lomuto ya implementada para Quick Sort.
 */
static Player quick_select_rec(Player V[], int low, int high, int k, int pivot_type, int (*comp_f)(Player *, Player *)) {
    // Si el arreglo tiene un solo elemento, devolvemos ese
    if (low == high) {
        return V[low];
    }

    // Reutilizamos lomuto_partition de tu Quick Sort
    int pi = lomuto_partition(V, low, high, pivot_type, comp_f);

    // Si el pivote quedó exactamente en la posición k, lo encontramos
    if (pi == k) {
        return V[pi];
    } else if (k < pi) {
        // Si k es menor, buscamos solo en la mitad izquierda
        return quick_select_rec(V, low, pi - 1, k, pivot_type, comp_f);
    } else {
        // Si k es mayor, buscamos solo en la mitad derecha
        return quick_select_rec(V, pi + 1, high, k, pivot_type, comp_f);
    }
}

/**
 * @brief Retorna el k-ésimo elemento del arreglo (0-indexado) basado en un criterio
 * @param k El índice del elemento a buscar (ej. k=0 es el menor absoluto).
 * @return Retorna un jugador vacío/inválido en caso de error
 */
Player quick_select(Player V[], int n, int k, int pivot_type, int (*comp_f)(Player *, Player *)) {
    if (k < 0 || k >= n) {
        Player empty = {-1, "", "", 0.0, 0, false};
        return empty;
    }
    return quick_select_rec(V, 0, n - 1, k, pivot_type, comp_f);
}