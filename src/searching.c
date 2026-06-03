/**
 * @file searching.c
 * @author Andres Barbosa, Milton Hernandez, Ivan Gallardo
 * @brief Funciones de busqueda
 */

#include"searching.h"
#include"player.h"

/**
 * @brief Funcion de busqueda lineal
 * 
 * @param V Arreglo de enteros
 * @param n Tamanho del arreglo
 * @param x Busqueda
 * @param comp_f funcion de comparacion (1 si a < b, -1 si a > b, 0 si a = b)
 * @return int r Indice de la busqueda, retorna n si no se encuentra
 */
int linear_search(Player V[], int n, Player *x, int (*comp_f)(Player *, Player *)) {
	int r = n;
	for (int i = 0; i < n; i++) {
		if (comp_f(&V[i], x) == 0) {
			r = i;
			break;
		}
	}
	return r;
}
// !?!no lo vas a usar? A lo que yo respondi con esta cara !v=!.
// generator.c
/**
 * @brief Funcion de busqueda binaria
 * * @param V Arreglo de jugadores
 * @param beg Indice inicial
 * @param end Indice final
 * @param x Puntero al jugador a buscar (con el criterio clave lleno)
 * @param comp_f Puntero a la función de comparación (ej: compare_id)
 * @return int m Indice de la busqueda, retorna -1 si no se encuentra
 */
int binary_search(Player V[], int beg, int end, Player *x) {
	while (beg <= end) {
		int m = beg + (end - beg) / 2;
		
		// Usamos directamente compare_id por requisito de la profesora
		int res = compare_id(&V[m], x);

		if (res == 0) {
			return m; // Encontrado (IDs iguales)
		} else if (res < 0) {
			beg = m + 1; // El ID de V[m] es menor, buscar en la mitad derecha
		} else {
			end = m - 1; // El ID de V[m] es mayor, buscar en la mitad izquierda
		}
	}
	return -1;
}

// BÚSQUEDA BINARIA RECURSIVA

int binary_search_recursive(Player V[], int beg, int end, Player *x) {
    if (beg > end) {
        return -1; // Caso base: no encontrado
    }
    
    int m = beg + (end - beg) / 2;
    int res = compare_id(&V[m], x);

    if (res == 0) {
        return m; // Encontrado
    } else if (res < 0) {
        // El ID de V[m] es menor, buscar en la mitad derecha
        return binary_search_recursive(V, m + 1, end, x);
    } else {
        // El ID de V[m] es mayor, buscar en la mitad izquierda
        return binary_search_recursive(V, beg, m - 1, x);
    }
}

// BÚSQUEDA BINARIA PARA RANGOS

// Función auxiliar para encontrar la PRIMERA aparición
int binary_search_first(Player V[], int n, Player *x) {
    int beg = 0, end = n - 1;
    int res_idx = -1;
    
    while (beg <= end) {
        int m = beg + (end - beg) / 2;
        int res = compare_id(&V[m], x);
        
        if (res == 0) {
            res_idx = m;
            end = m - 1; // Sigue buscando hacia la izquierda para ver si hay un primer elemento antes
        } else if (res < 0) {
            beg = m + 1;
        } else {
            end = m - 1;
        }
    }
    return res_idx;
}

// Función auxiliar para encontrar la ÚLTIMA aparición
int binary_search_last(Player V[], int n, Player *x) {
    int beg = 0, end = n - 1;
    int res_idx = -1;
    
    while (beg <= end) {
        int m = beg + (end - beg) / 2;
        int res = compare_id(&V[m], x);
        
        if (res == 0) {
            res_idx = m;
            beg = m + 1; // Sigue buscando hacia la derecha para ver si hay un último elemento después
        } else if (res < 0) {
            beg = m + 1;
        } else {
            end = m - 1;
        }
    }
    return res_idx;
}

// Función principal que entrega el rango
void binary_search_range(Player V[], int n, Player *x, int *first, int *last) {
    *first = binary_search_first(V, n, x);
    *last = binary_search_last(V, n, x);
}

// BÚSQUEDA EXPONENCIAL

int exponential_search(Player V[], int n, Player *x) {
    if (n == 0) return -1;
    
    // Validar primera posición directamente
    if (compare_id(&V[0], x) == 0) {
        return 0;
    }

    // Encontrar rango para la búsqueda binaria mediante crecimiento exponencial
    int i = 1;
    while (i < n && compare_id(&V[i], x) < 0) {
        i = i * 2;
    }

    // Llamar a búsqueda binaria en el sub-arreglo encontrado
    int beg = i / 2;
    int end = (i < n - 1) ? i : (n - 1); // Tomar el minimo entre 'i' y 'n-1'
    
    // Reutilizamos tu función iterativa para el rango final
    return binary_search(V, beg, end, x); 
}

// BÚSQUEDA POR INTERPOLACIÓN

int interpolation_search(Player V[], int n, Player *x) {
    int beg = 0, end = n - 1;

    // Asumimos que Player tiene un campo entero 'id'. 
    // La interpolación necesita los valores numéricos para calcular la proporción.
    while (beg <= end && x->id >= V[beg].id && x->id <= V[end].id) {
        
        if (beg == end) {
            if (V[beg].id == x->id) return beg;
            return -1;
        }

        // Fórmula matemática de estimación de la posición
        int pos = beg + (((double)(end - beg) / (V[end].id - V[beg].id)) * (x->id - V[beg].id));

        if (V[pos].id == x->id) {
            return pos;
        }

        // Si el valor estimado es menor que el buscado
        if (V[pos].id < x->id) {
            beg = pos + 1;
        } else {
            // Si es mayor
            end = pos - 1;
        }
    }
    return -1;
}