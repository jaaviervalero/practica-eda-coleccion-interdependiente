/* 
 * Pablo Muruzabal Laborda, 927819 y Javir Valero Fontana 927155
 */

#include "evento.hpp"

// -----------------------------------------------------------------------------
// Implementación de las operaciones del TAD evento
// -----------------------------------------------------------------------------

/* Inicializa el evento e con descrip y prio. (Modifica 'e' por referencia)
*/
void crearEvento(const string& descrip, unsigned int prio, evento& e) {
    e.descripcion = descrip;
    e.prioridad = prio;
}

/* Devuelve la descripción de un evento.
*/
string descripcion(const evento& e) {
    return e.descripcion;
}

/* Cambia la descripción de un evento.
*/
void cambiarDescripcion(evento& e, const string& nueva) {
    e.descripcion = nueva;
}

/* Devuelve la prioridad de un evento.
*/
unsigned int suPrioridad(const evento& e) {
    return e.prioridad;
}

/* Cambia la prioridad de un evento.
*/
void cambiarPrioridad(evento& e, unsigned int pri) {
    e.prioridad = pri;
}