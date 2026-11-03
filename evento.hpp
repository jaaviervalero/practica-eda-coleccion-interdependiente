/* 
    Pablo Muruzbal Laborda, 927819 y Javier Valero Fontana 927155
*/

#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>
#include <iostream>

using namespace std;


/* Los valores del TAD evento representan tuplas de la forma (descripción, prioridad),
donde la descripción es una cadena y la prioridad es un número natural.
*/
struct evento; // Forward declaration

/* Dada una cadena descrip y un natural prio,
inicializa el evento e con esos datos.
*/
void crearEvento(const string& descrip, unsigned int prio, evento& e);

/* Dado un evento e, devuelve la cadena correspondiente a la descripción de e.
*/
string descripcion(const evento& e);

/* Dado un evento e y una cadena nueva, devuelve un evento igual a (nueva, P).
*/
void cambiarDescripcion(evento& e, const string& nueva);

/* Dado un evento e, devuelve el natural correspondiente a la prioridad de e.
*/
unsigned int suPrioridad(const evento& e);

/* Dado un evento e y un natural pri, devuelve un evento igual a (D, pri).
*/
void cambiarPrioridad(evento& e, unsigned int pri);


// FIN de la PREDECLARACION DEL TAD evento (fin INTERFAZ)

// DECLARACION DEL TAD evento 

struct evento {
    // Declaracion de amistad para que las funciones externas accedan a los miembros
    friend void crearEvento(const string& descrip, unsigned int prio, evento& e);
    friend string descripcion(const evento& e);
    friend void cambiarDescripcion(evento& e, const string& nueva);
    friend unsigned int suPrioridad(const evento& e);
    friend void cambiarPrioridad(evento& e, unsigned int pri);

private: // declaracion de la representacion interna del tipo
    string descripcion;
    unsigned int prioridad;
};

#endif // EVENTO_HPP