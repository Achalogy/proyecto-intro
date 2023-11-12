#include "Tablero.h"
#include <iostream>
#include "Utils.h"

using namespace std;

void alrededorFicha(string vision[], string ficha, t_tablero tablero);
bool puedeComer(int equipo, string vision[], bool esDama);
void algunaPuedeComer(t_tablero tablero, t_turno *turno, int equipo);
void movimientosDisponibles(string ficha, t_tablero *tablero, t_turno *turno);
void mover(string *ficha, int opt, t_tablero *tablero, t_turno *turno);