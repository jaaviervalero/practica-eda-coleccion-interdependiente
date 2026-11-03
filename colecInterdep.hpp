/*
 * Autores: Pablo Muruzbal Laborda, 927819 y Javier Valero Fontana 927155
 * Fichero: colecInterdep.hpp
 *
 * TAD: colecInterdep (Colección con Interdependencias)
 * Descripción:
 *  - Mantiene una colección de elementos identificados por `ident` y
 *    con un valor asociado `val`.
 *  - Cada elemento puede ser independiente o depender de otro elemento
 *    (su "supervisor"). Los dependientes mantienen un puntero al nodo
 *    supervisor y cada supervisor lleva el conteo de dependientes directos.
 *  - La representación interna es un ABB (árbol binario de búsqueda)
 *    ordenado por el identificador (`id`).
 *
 * Invariante de representación:
 *  - El árbol respeta la propiedad de BST: todos los ids del subárbol
 *    izquierdo son < id y los del derecho son > id.
 *  - `numElementos` refleja el número total de nodos del árbol.
 *  - Para cada nodo, `numDepend` es el número de dependientes directos.
 *  - Si `esDependiente == true` entonces `supervisor` apunta al nodo
 *    supervisor (no debe ser NULL salvo en estados intermedios).
 *
 * Complejidad (en altura h del árbol):
 *  - Búsqueda, inserción y borrado: O(h) en promedio/peor según altura.
 *  - Acceso al iterador y avance en in-orden: O(1) amortizado por paso.
 */

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

#include <iostream>
using namespace std;

template<typename ident, typename val> struct colecInterdep;

// --- Gestión ---
// Operaciones básicas para inicializar la estructura y consultar su tamaño/estado.
template<typename ident, typename val> void crear(colecInterdep<ident, val>& c);
template<typename ident, typename val> unsigned int tamano(const colecInterdep<ident, val>& c);
template<typename ident, typename val> bool esVacia(const colecInterdep<ident, val>& c);

// --- Consultas ---
// Consultas de existencia y estado (dependiente/independiente) de un id.
template<typename ident, typename val> bool existe(const ident& id, const colecInterdep<ident, val>& c);
template<typename ident, typename val> bool existeDependiente(const ident& id, const colecInterdep<ident, val>& c);
template<typename ident, typename val> bool existeIndependiente(const ident& id, const colecInterdep<ident, val>& c);

// --- Modificadores ---
// Inserciones, conversiones entre dependiente/independiente y borrado.
// - `anyadirIndependiente` / `anyadirDependiente` insertan un nuevo nodo.
// - `hacerDependiente` / `hacerIndependiente` cambian el estado de un nodo
//    ya existente sin alterar su posición en el ABB.
// - `borrar` elimina un nodo siempre que no tenga dependientes.
template<typename ident, typename val> 
bool anyadirIndependiente(colecInterdep<ident, val>& c, const ident& id, const val& v);

template<typename ident, typename val> 
bool anyadirDependiente(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super);

template<typename ident, typename val>
int hacerDependiente(colecInterdep<ident, val>& c, const ident& id, const ident& super);

template<typename ident, typename val>
int hacerIndependiente(colecInterdep<ident, val>& c, const ident& id);

template<typename ident, typename val>
bool borrar(colecInterdep<ident, val>& c, const ident& id);

// --- Operaciones Parciales ---
// Operaciones que actúan sobre el valor o devuelven información parcial
// sobre un elemento identificado por `id` (si existe).
template<typename ident, typename val>
bool actualizarVal(colecInterdep<ident, val>& c, const ident& id, const val& nuevo_valor);

template<typename ident, typename val>
bool obtenerVal(const colecInterdep<ident, val>& c, const ident& id, val& valorSalida);

template<typename ident, typename val>
bool obtenerSupervisor(const colecInterdep<ident, val>& c, const ident& id, ident& supervisorSalida);

template<typename ident, typename val>
bool obtenerNumDependientes(const colecInterdep<ident, val>& c, const ident& id, int& numSalida);

// --- Iterador ---
// Recorrido in-orden sobre los nodos usando `iterador`.
// - Llamar `iniciarIterador` para posicionar al primer elemento (mínimo).
// - Usar `existeSiguiente` y las funciones `siguiente*` para leer
//   propiedades del nodo actual. Avanzar con `avanza`.
template<typename ident, typename val> void iniciarIterador(colecInterdep<ident, val>& c);
template<typename ident, typename val> bool existeSiguiente(const colecInterdep<ident, val>& c);
template<typename ident, typename val> bool siguienteIdent(const colecInterdep<ident, val>& c, ident& idSalida);
template<typename ident, typename val> bool siguienteVal(const colecInterdep<ident, val>& c, val& valSalida);
template<typename ident, typename val> bool siguienteDependiente(const colecInterdep<ident, val>& c, bool& esDepSalida);
template<typename ident, typename val> bool siguienteSupervisor(const colecInterdep<ident, val>& c, ident& supSalida);
template<typename ident, typename val> bool siguienteNumDependientes(const colecInterdep<ident, val>& c, int& numSalida);
template<typename ident, typename val> void avanza(colecInterdep<ident, val>& c);


template<typename ident, typename val>
struct colecInterdep {
    friend void crear<ident, val>(colecInterdep<ident, val>& c);
    friend unsigned int tamano<ident, val>(const colecInterdep<ident, val>& c);
    friend bool esVacia<ident, val>(const colecInterdep<ident, val>& c);
    friend bool existe<ident, val>(const ident& id, const colecInterdep<ident, val>& c);
    friend bool existeDependiente<ident, val>(const ident& id, const colecInterdep<ident, val>& c);
    friend bool existeIndependiente<ident, val>(const ident& id, const colecInterdep<ident, val>& c);
    friend bool anyadirIndependiente<ident, val>(colecInterdep<ident, val>& c, const ident& id, const val& v);
    friend bool anyadirDependiente<ident, val>(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super);
    friend int hacerDependiente<ident, val>(colecInterdep<ident, val>& c, const ident& id, const ident& super);
    friend int hacerIndependiente<ident, val>(colecInterdep<ident, val>& c, const ident& id);
    friend bool borrar<ident, val>(colecInterdep<ident, val>& c, const ident& id);
    friend bool actualizarVal<ident, val>(colecInterdep<ident, val>& c, const ident& id, const val& nuevo_valor);
    friend bool obtenerVal<ident, val>(const colecInterdep<ident, val>& c, const ident& id, val& valorSalida);
    friend bool obtenerSupervisor<ident, val>(const colecInterdep<ident, val>& c, const ident& id, ident& supervisorSalida);
    friend bool obtenerNumDependientes<ident, val>(const colecInterdep<ident, val>& c, const ident& id, int& numSalida);
    friend void iniciarIterador<ident, val>(colecInterdep<ident, val>& c);
    friend bool existeSiguiente<ident, val>(const colecInterdep<ident, val>& c);
    friend bool siguienteIdent<ident, val>(const colecInterdep<ident, val>& c, ident& idSalida);
    friend bool siguienteVal<ident, val>(const colecInterdep<ident, val>& c, val& valSalida);
    friend bool siguienteDependiente<ident, val>(const colecInterdep<ident, val>& c, bool& esDepSalida);
    friend bool siguienteSupervisor<ident, val>(const colecInterdep<ident, val>& c, ident& supSalida);
    friend bool siguienteNumDependientes<ident, val>(const colecInterdep<ident, val>& c, int& numSalida);
    friend void avanza<ident, val>(colecInterdep<ident, val>& c);

private:
    struct Nodo {
        ident id;
        val valor;
        Nodo* supervisor;   // Apunta al nodo del que depende
        int numDepend;
        bool esDependiente;
        
        // Estructura del árbol con padre
        Nodo* izq;
        Nodo* der;
        Nodo* padre;
    };

    Nodo* raiz;
    int numElementos;
    Nodo* iterador; // Puntero al nodo actual del recorrido

    // --- Funciones Auxiliares Privadas ---

    // Búsqueda estándar en ABB
    Nodo* buscarNodo(const ident& id_buscado) const {
        Nodo* actual = raiz;
        while (actual != NULL) {
            if (id_buscado == actual->id) return actual;
            else if (id_buscado < actual->id) actual = actual->izq;
            else actual = actual->der;
        }
        return NULL;
    }

    // Auxiliar para encontrar el mínimo de un subárbol
    Nodo* extremoIzquierdo(Nodo* nodo) {
        if (nodo == NULL) return NULL;
        while (nodo->izq != NULL) {
            nodo = nodo->izq;
        }
        return nodo;
    }
};

// --- Implementación ---

template<typename ident, typename val> 
void crear(colecInterdep<ident, val>& c){
    c.raiz = NULL;
    c.numElementos = 0;
    c.iterador = NULL;
}

template<typename ident, typename val> 
unsigned int tamano(const colecInterdep<ident, val>& c){
    return c.numElementos;
}

template<typename ident, typename val> 
bool esVacia(const colecInterdep<ident, val>& c){
    return c.numElementos == 0;
}

template<typename ident, typename val>
bool existe(const ident& id, const colecInterdep<ident, val>& c){
    return c.buscarNodo(id) != NULL;
}

template<typename ident, typename val>
bool existeDependiente(const ident& id, const colecInterdep<ident, val>& c){
    typename colecInterdep<ident, val>::Nodo* n = c.buscarNodo(id);
    return n != NULL && n->esDependiente;
}

template<typename ident, typename val>
bool existeIndependiente(const ident& id, const colecInterdep<ident, val>& c){
    typename colecInterdep<ident, val>::Nodo* n = c.buscarNodo(id);
    return n != NULL && !n->esDependiente;
}


template<typename ident, typename val>
bool anyadirIndependiente(colecInterdep<ident, val>& c, const ident& id, const val& v) {
    typename colecInterdep<ident, val>::Nodo* y = NULL;
    typename colecInterdep<ident, val>::Nodo* x = c.raiz;

    while (x != NULL) {
        y = x;
        if (id == x->id) return false; // Ya existe
        if (id < x->id) x = x->izq;
        else x = x->der;
    }

    typename colecInterdep<ident, val>::Nodo* nuevo = new typename colecInterdep<ident, val>::Nodo;
    nuevo->id = id;
    nuevo->valor = v;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->padre = y; 
    nuevo->numDepend = 0;
    nuevo->esDependiente = false;
    nuevo->supervisor = NULL;

    if (y == NULL) {
        c.raiz = nuevo;
    } else if (id < y->id) {
        y->izq = nuevo;
    } else {
        y->der = nuevo;
    }

    c.numElementos++;
    return true;
}

template<typename ident, typename val>
bool anyadirDependiente(colecInterdep<ident, val>& c, const ident& id, const val& v, const ident& super) {
    if (id == super) return false;

    typename colecInterdep<ident, val>::Nodo* supNode = c.buscarNodo(super);
    if (supNode == NULL) return false;

    typename colecInterdep<ident, val>::Nodo* y = NULL;
    typename colecInterdep<ident, val>::Nodo* x = c.raiz;

    while (x != NULL) {
        y = x;
        if (id == x->id) return false; // Ya existe
        if (id < x->id) x = x->izq;
        else x = x->der;
    }

    typename colecInterdep<ident, val>::Nodo* nuevo = new typename colecInterdep<ident, val>::Nodo;
    nuevo->id = id;
    nuevo->valor = v;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->padre = y;
    nuevo->esDependiente = true;
    nuevo->supervisor = supNode;
    nuevo->numDepend = 0;

    if (y == NULL) {
        c.raiz = nuevo; 
    } else if (id < y->id) {
        y->izq = nuevo;
    } else {
        y->der = nuevo;
    }

    supNode->numDepend++;
    c.numElementos++;
    return true;
}

template<typename ident, typename val>
int hacerDependiente(colecInterdep<ident, val>& c, const ident& id, const ident& super) {
    if (id == super) return 1;

    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    typename colecInterdep<ident, val>::Nodo* supNode = c.buscarNodo(super);

    if (nodo == NULL || supNode == NULL) return 0;

    if (nodo->esDependiente && nodo->supervisor != NULL) {
        nodo->supervisor->numDepend--;
    }
    
    nodo->esDependiente = true;
    nodo->supervisor = supNode;
    supNode->numDepend++;
    return 1;
}

template<typename ident, typename val>
int hacerIndependiente(colecInterdep<ident, val>& c, const ident& id) {
    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    if (nodo == NULL) return 0;
    if (!nodo->esDependiente) return 1;

    if (nodo->supervisor != NULL) {
        nodo->supervisor->numDepend--;
    }
    nodo->esDependiente = false;
    nodo->supervisor = NULL;
    return 2;
}

template<typename ident, typename val>
bool borrar(colecInterdep<ident, val>& c, const ident& id) {
    // 1. Buscar el nodo 'z' a borrar
    typename colecInterdep<ident, val>::Nodo* z = c.buscarNodo(id);
    if (z == NULL) return false;

    // No se puede borrar si tiene dependientes (numDepend > 0)
    if (z->numDepend > 0) return false;

    // Si es dependiente, actualizamos el contador de su supervisor
    if (z->esDependiente && z->supervisor != NULL) {
        z->supervisor->numDepend--;
    }

    // 3. Algoritmo de borrado físico en ABB con Puntero al Padre

    // CASO A: 'z' no tiene hijo izquierdo (cubre hoja y solo hijo derecho)
    // Queremos reemplazar el subárbol 'z' por el subárbol 'z->der'
    if (z->izq == NULL) {
        typename colecInterdep<ident, val>::Nodo* v = z->der;
        
        // Enlazar el padre de z con v
        if (z->padre == NULL) {
            c.raiz = v;
        } else if (z == z->padre->izq) {
            z->padre->izq = v;
        } else {
            z->padre->der = v;
        }
        // Enlazar v con el padre de z (si v existe)
        if (v != NULL) {
            v->padre = z->padre;
        }
    }
    // CASO B: 'z' solo tiene hijo izquierdo
    // Queremos reemplazar el subárbol 'z' por el subárbol 'z->izq'
    else if (z->der == NULL) {
        typename colecInterdep<ident, val>::Nodo* v = z->izq;
        
        // Enlazar el padre de z con v
        if (z->padre == NULL) {
            c.raiz = v;
        } else if (z == z->padre->izq) {
            z->padre->izq = v;
        } else {
            z->padre->der = v;
        }
        // Enlazar v con el padre de z
        if (v != NULL) {
            v->padre = z->padre;
        }
    }
    // CASO C: 'z' tiene dos hijos
    else {
        // 1. Buscar el sucesor 'y' (mínimo del subárbol derecho)
        typename colecInterdep<ident, val>::Nodo* y = c.extremoIzquierdo(z->der);

        // 2. Si el sucesor 'y' no es hijo directo de 'z', lo preparamos para subir
        if (y->padre != z) {
            // Reemplazamos 'y' por su propio hijo derecho (y->der) en su posición original
            typename colecInterdep<ident, val>::Nodo* r = y->der;
            
            
            if (y->padre == NULL) c.raiz = r; // Caso improbable pues y no es raiz
            else if (y == y->padre->izq) y->padre->izq = r;
            else y->padre->der = r;
            
            if (r != NULL) {
                r->padre = y->padre;
            }

            // 'y' adopta el hijo derecho de 'z'
            y->der = z->der;
            y->der->padre = y;
        }

        // 3. Reemplazamos 'z' por el sucesor 'y'
        if (z->padre == NULL) {
            c.raiz = y;
        } else if (z == z->padre->izq) {
            z->padre->izq = y;
        } else {
            z->padre->der = y;
        }
        y->padre = z->padre;

        // 4. 'y' adopta el hijo izquierdo de 'z'
        y->izq = z->izq;
        y->izq->padre = y;
    }

    // 4. Limpieza final
    // Si el iterador estaba justo en el nodo borrado, lo invalidamos
    if (c.iterador == z) c.iterador = NULL;
    
    delete z;
    c.numElementos--;
    return true;
}

template<typename ident, typename val>
bool actualizarVal(colecInterdep<ident, val>& c, const ident& id, const val& nuevo_valor) {
    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    if (nodo == NULL) return false;
    nodo->valor = nuevo_valor;
    return true;
}

template<typename ident, typename val>
bool obtenerVal(const colecInterdep<ident, val>& c, const ident& id, val& valorSalida) {
    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    if (nodo == NULL) return false;
    valorSalida = nodo->valor;
    return true;
}

template<typename ident, typename val>
bool obtenerSupervisor(const colecInterdep<ident, val>& c, const ident& id, ident& supervisorSalida) {
    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    if (nodo == NULL || !nodo->esDependiente || nodo->supervisor == NULL) return false;
    supervisorSalida = nodo->supervisor->id;
    return true;
}

template<typename ident, typename val>
bool obtenerNumDependientes(const colecInterdep<ident, val>& c, const ident& id, int& numSalida) {
    typename colecInterdep<ident, val>::Nodo* nodo = c.buscarNodo(id);
    if (nodo == NULL) return false;
    numSalida = nodo->numDepend;
    return true;
}

// --- Iterador (Usando puntero padre para recorrer in-orden) ---

template<typename ident, typename val>
void iniciarIterador(colecInterdep<ident, val>& c) {
    // El primero en in-orden es el nodo más a la izquierda
    c.iterador = c.extremoIzquierdo(c.raiz);
}

template<typename ident, typename val>
bool existeSiguiente(const colecInterdep<ident, val>& c) {
    return c.iterador != NULL;
}

template<typename ident, typename val>
bool siguienteIdent(const colecInterdep<ident, val>& c, ident& idSalida) {
    if (c.iterador == NULL) return false;
    idSalida = c.iterador->id;
    return true;
}

template<typename ident, typename val>
bool siguienteVal(const colecInterdep<ident, val>& c, val& valSalida) {
    if (c.iterador == NULL) return false;
    valSalida = c.iterador->valor;
    return true;
}

template<typename ident, typename val>
bool siguienteDependiente(const colecInterdep<ident, val>& c, bool& esDepSalida) {
    if (c.iterador == NULL) return false;
    esDepSalida = c.iterador->esDependiente;
    return true;
}

template<typename ident, typename val>
bool siguienteSupervisor(const colecInterdep<ident, val>& c, ident& supSalida) {
    if (c.iterador == NULL || !c.iterador->esDependiente || c.iterador->supervisor == NULL) return false;
    supSalida = c.iterador->supervisor->id;
    return true;
}

template<typename ident, typename val>
bool siguienteNumDependientes(const colecInterdep<ident, val>& c, int& numSalida) {
    if (c.iterador == NULL) return false;
    numSalida = c.iterador->numDepend;
    return true;
}

template<typename ident, typename val>
void avanza(colecInterdep<ident, val>& c) {
    if (c.iterador == NULL) return;

    // Algoritmo del sucesor en un BST con punteros al padre
    if (c.iterador->der != NULL) {
        // Si tiene hijo derecho, el sucesor es el mínimo del subárbol derecho
        c.iterador = c.extremoIzquierdo(c.iterador->der);
    } else {
        // Si no tiene hijo derecho, subir hasta encontrar el primer ancestro
        // del cual el nodo actual es parte del subárbol izquierdo
        typename colecInterdep<ident, val>::Nodo* padre = c.iterador->padre;
        typename colecInterdep<ident, val>::Nodo* actual = c.iterador;
        
        while (padre != NULL && actual == padre->der) {
            actual = padre;
            padre = padre->padre;
        }
        c.iterador = padre;
    }
}

#endif