#include "Tablero.h"
#include <fstream>
#include <iostream>
#include "Utils.h"

using namespace std;

// 00 00 00 00 00 00 00 00
// 10 10 10 10 10 10 10 10
// 10 10 10 10 10 10 10 10
// 00 00 00 00 00 00 00 00
// 00 00 00 00 00 00 00 00
// 20 20 20 20 20 20 20 20
// 20 20 20 20 20 20 20 20
// 00 00 00 00 00 00 00 00
// 0
// 0
// 1

void saveGame(t_tablero tablero, t_turno turno)
{
  ofstream fout;
  string linea;
  fout.open("game_data/save.dat");
  if (fout.is_open())
  {
    for (int y = 0; y < 8; y++)
    {
      for (int x = 0; x < 8; x++)
      {
        linea += ('0' + tablero.posiciones[y][x].equipo);
        linea += ('0' + tablero.posiciones[y][x].esDama);
        linea += ' ';
      }
      fout << linea << endl;
      linea = "";
    }
    fout << tablero.oFuera << endl;
    fout << tablero.xFuera << endl;
    fout << turno.turno << endl;
  }
  fout.close();
}

void loadGame(t_tablero *tablero, t_turno *turno)
{
  ifstream fin;
  string linea;
  fin.open("game_data/save.dat");

  for (int y = 0; y < 8; y++)
  {
    getline(fin, linea);
    for (int x = 0; x < 8; x++)
    {
      tablero->posiciones[y][x].equipo = convertirAEntero(linea[x * 3]);
      tablero->posiciones[y][x].esDama = linea[(x * 3) + 1] == '1';
    }
  }

  getline(fin, linea);
  tablero->oFuera = convertirAEntero(linea[0]);
  getline(fin, linea);
  tablero->xFuera = convertirAEntero(linea[0]);
  getline(fin, linea);
  turno->turno = convertirAEntero(linea[0]);

  fin.close();
}

void generarTablero(t_tablero *T)
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      T->posiciones[y][x].equipo = ((y == 1) || (y == 2) ? 1 : (y == 5) || (y == 6) ? 2
                                                                                    : 0);
    }
  }
}

void imprimirTablero(t_tablero T, t_turno turno)
{
  int ficha = 0;
  bool esDama = false;
  bool flag = false;

  cout << endl;
  cout << "    A B C D E F G H " << endl;
  cout << "  ╔═════════════════╗" << endl;
  for (int y = 0; y < 8; y++)
  {
    cout << y + 1 << " ║ ";
    for (int x = 0; x < 8; x++)
    {
      flag = false;
      for (int i = 0; i < turno.h; i++)
        if (turno.avMovs[i][0] == y && turno.avMovs[i][1] == x)
          flag = true;

      ficha = T.posiciones[y][x].equipo;
      esDama = T.posiciones[y][x].esDama;
      cout
          << (flag ? "- " : (ficha == 1 ? (esDama ? "ø " : "o ") : ficha == 2 ? (esDama ? "% " : "x ")
                                                                              : ". "));
    }
    cout << "║" << endl;
  }
  cout << "  ╚═════════════════╝" << endl;
}
