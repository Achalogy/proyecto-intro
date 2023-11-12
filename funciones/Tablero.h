#include "../Estructuras.h"
#pragma once

void saveGame(t_tablero tablero, t_turno turno);
void loadGame(t_tablero *tablero, t_turno *turno);
void generarTablero(t_tablero *T);
void imprimirTablero(t_tablero T, t_turno turno);
