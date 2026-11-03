# TAD colección con interdependencias (C++)

Práctica final de **Estructuras de Datos y Algoritmos** (Ingeniería Informática, Universidad de Zaragoza, curso 2025-26).

`colecInterdep` es un TAD genérico (plantillas de C++) que guarda elementos identificados por una clave. Cada elemento puede ser independiente o depender de otro (su «supervisor»), y cada supervisor lleva la cuenta de sus dependientes directos. Internamente es un **árbol binario de búsqueda** ordenado por la clave, con su invariante de representación documentado en el código.

`practica4.cpp` lo usa para gestionar eventos a partir de un fichero de instrucciones. En `pruebas/` están las entradas y las salidas esperadas.

**Autores:** Javier Valero y Pablo Muruzábal.
