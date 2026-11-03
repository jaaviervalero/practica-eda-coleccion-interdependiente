/* * Fichero: practica4.cpp (Programa Principal)
 * Autores: Pablo Muruzabal Laborda, 927819 y Javier Valero Fontana, 927155
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "evento.hpp"
#include "colecinterdep.hpp"

using namespace std;

int main() {
    colecInterdep<string, evento> coleccion;
    crear(coleccion); 

    ifstream f_in("entrada.txt");   
    ofstream f_out("salida.txt"); 

    if (!f_in.is_open() || !f_out.is_open()) {
        cerr << "Error abriendo ficheros." << endl;
        return 1;
    }

    string instruccion, salto;

    while (f_in >> instruccion) {
        getline(f_in, salto); 

        if (instruccion == "A") {
            string nombre, desc, prio_str, tipo, supervisor;
            getline(f_in, nombre);     
            getline(f_in, desc);       
            getline(f_in, prio_str);   
            getline(f_in, tipo);       
            getline(f_in, supervisor); 

            unsigned int prioridad;
            stringstream ss(prio_str);
            ss >> prioridad;

            evento nuevoEvento;
            crearEvento(desc, prioridad, nuevoEvento);

            bool introducido = false;
            if (tipo == "INDependiente") { 
                introducido = anyadirIndependiente(coleccion, nombre, nuevoEvento);
            } else if (tipo == "DEPendiente") { 
                if (nombre != supervisor) {
                   introducido = anyadirDependiente(coleccion, nombre, nuevoEvento, supervisor);
                }
            }

            if (introducido) f_out << "INTRODUCIDO: ";
            else f_out << "NO INTRODUCIDO: ";
            
            if (tipo == "INDependiente") {
                 f_out << "[ " << nombre << " ] --- " << desc << " --- ( " << prioridad << " )" << endl;
            } else {
                 // OJO: Espacio antes de -de-> para coincidir con diff '>'
                 f_out << "[ " << nombre << " -de-> " << supervisor << " ] --- " << desc << " --- ( " << prioridad << " )" << endl;
            }
        } 
        else if (instruccion == "C") {
            string nombre, desc, prio_str;
            getline(f_in, nombre);   
            getline(f_in, desc);     
            getline(f_in, prio_str); 
            
            unsigned int prioridad;
            stringstream ss(prio_str);
            ss >> prioridad;

            evento ev;
            crearEvento(desc, prioridad, ev);
            
            if (actualizarVal(coleccion, nombre, ev)) {
                f_out << "CAMBIADO: ";
                int numDep = 0;
                obtenerNumDependientes(coleccion, nombre, numDep);

                if (existeIndependiente(nombre, coleccion)) {
                    // Independientes llevan guiones en SalidaB
                    f_out << "[ " << nombre << " --- " << numDep << " ] --- " << desc << " --- ( " << prioridad << " )" << endl;
                } else {
                    string sup;
                    obtenerSupervisor(coleccion, nombre, sup);
                    // Dependientes llevan ;;; y espacio antes de -de->
                    f_out << "[ " << nombre << " -de-> " << sup << " ;;; " << numDep << " ] --- " << desc << " --- ( " << prioridad << " )" << endl;
                }
            } else {
                f_out << "NO CAMBIADO: " << nombre << endl;
            }
        } 
        else if (instruccion == "O") {
            string nombre;
            getline(f_in, nombre);

            evento ev;
            if (obtenerVal(coleccion, nombre, ev)) { 
                string desc = descripcion(ev);
                int prio = suPrioridad(ev);
                int numDep = 0;
                obtenerNumDependientes(coleccion, nombre, numDep);

                f_out << "LOCALIZADO: ";
                if (existeIndependiente(nombre, coleccion)) {
                    f_out << "[ " << nombre << " --- " << numDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                } else {
                    string sup;
                    obtenerSupervisor(coleccion, nombre, sup);
                    f_out << "[ " << nombre << " -de-> " << sup << " ;;; " << numDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                }
            } else {
                f_out << "NO LOCALIZADO: " << nombre << endl;
            }
        } 
        else if (instruccion == "E") {
            string nombre;
            getline(f_in, nombre);

            if (existeIndependiente(nombre, coleccion)) {
                f_out << "INDEPendiente: " << nombre << endl;
            } else if (existeDependiente(nombre, coleccion)) {
                f_out << "DEPendiente: " << nombre << endl;
            } else {
                f_out << "DESCONOCIDO: " << nombre << endl;
            }
        } 
        else if (instruccion == "I") {
            string nombre;
            getline(f_in, nombre);

            int res = hacerIndependiente(coleccion, nombre);
            
            if (res == 2) f_out << "INDEPENDIZADO: " << nombre << endl;
            else if (res == 1) f_out << "YA ERA INDepend.: " << nombre << endl;
            else f_out << "NO INDEPENDIZADO: " << nombre << endl;
        } 
        else if (instruccion == "D") {
            string nombre, supervisor;
            getline(f_in, nombre);     
            getline(f_in, supervisor); 

            int res = hacerDependiente(coleccion, nombre, supervisor);
            if (res == 1) {
                f_out << "INTENTANDO hacer depend.: ";
            } else {
                f_out << "IMPOSIBLE hacer depend.: ";
            }
            f_out << nombre << " -de-> " << supervisor << endl;
        } 
        else if (instruccion == "B") {
            string nombre;
            getline(f_in, nombre);
            
            if (borrar(coleccion, nombre)) {
                f_out << "BORRADO: " << nombre << endl;
            } else {
                f_out << "NO BORRADO: " << nombre << endl;
            }
        } 
        else if (instruccion == "LD") {
            string nombre;
            getline(f_in, nombre);
            
            f_out << "****DEPENDIENTES: " << nombre << endl; 

            evento ev;
            if (!obtenerVal(coleccion, nombre, ev)) {
                f_out << "****DESCONOCIDO" << endl; 
            } else {
                int numDep = 0;
                obtenerNumDependientes(coleccion, nombre, numDep);
                
                if (existeIndependiente(nombre, coleccion)) {
                    f_out << "[ " << nombre << " --- " << numDep << " ] --- " << descripcion(ev) << " --- ( " << suPrioridad(ev) << " )" << " ****" << endl;
                } else {
                    string sup;
                    obtenerSupervisor(coleccion, nombre, sup);
                    f_out << "[ " << nombre << " -de-> " << sup << " ;;; " << numDep << " ] --- " << descripcion(ev) << " --- ( " << suPrioridad(ev) << " )" << " ****" << endl;
                }
                int puesto = 1;
                iniciarIterador(coleccion);
                while (existeSiguiente(coleccion)) {
                    bool esDep = false;
                    siguienteDependiente(coleccion, esDep);
                    
                    string supActual;
                    if (esDep && siguienteSupervisor(coleccion, supActual) && supActual == nombre) {
                        string depNombre;
                        evento depEv;
                        int depNumDep = 0;
                        
                        siguienteIdent(coleccion, depNombre);
                        siguienteVal(coleccion, depEv);
                        siguienteNumDependientes(coleccion, depNumDep);

                        f_out << "[" << puesto << " -> " << depNombre << " -de-> " << nombre << " ;;; " << depNumDep 
                              << " ] --- " << descripcion(depEv) << " --- ( " << suPrioridad(depEv) << " ) ;;;;" << endl;
                        puesto++;
                    }
                    avanza(coleccion);
                }
                f_out << "****FINAL dependientes -de-> " << nombre << endl;
            }
        } 
        else if (instruccion == "LT") {
            f_out << "-----LISTADO: " << tamano(coleccion) << endl;

            iniciarIterador(coleccion);
            while (existeSiguiente(coleccion)) {
                string nombre;
                evento ev;
                int numDep = 0;
                bool esDep = false;
                
                siguienteIdent(coleccion, nombre);
                siguienteVal(coleccion, ev);
                siguienteNumDependientes(coleccion, numDep);
                siguienteDependiente(coleccion, esDep);
                
                string desc = descripcion(ev);
                int prio = suPrioridad(ev);

                if (esDep) {
                    string sup;
                    siguienteSupervisor(coleccion, sup);
                    f_out << "[ " << nombre << " -de-> " << sup << " ;;; " << numDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                } else {
                    f_out << "[ " << nombre << " --- " << numDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                }
                avanza(coleccion);
            }
            f_out << "-----" << endl;
        }
    } 

    f_in.close();
    f_out.close();
    
    return 0;
}