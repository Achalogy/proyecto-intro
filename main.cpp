#include <iostream>
#include "funciones/Utils.h"
#include "funciones/Tablero.h"
#include "funciones/Ficha.h"

using namespace std;

void imprimirMovimientos(t_turno turno);
void menuPrincipal(t_tablero *tablero, t_turno *turno);
bool fichasBloqueadas(t_tablero tablero, t_turno turno);

int main(void)
{
  string ficha = "";
  int opt;
  t_tablero tablero;
  t_turno turno;
  bool bloq = false;

  int ganador = 0;

  menuPrincipal(&tablero, &turno);
  imprimirTablero(tablero, turno);

  while (
      (tablero.xFuera != 15 || tablero.oFuera != 15) // empate
      && tablero.xFuera != 16 && !bloq && tablero.oFuera != 16)
  {
    bloq = fichasBloqueadas(tablero, turno);

    if (!bloq)
    {
      system("clear");
      imprimirTablero(tablero, turno);
      cout << "Turno de las fichas: " << (turno.turno == 1 ? "o" : "x") << endl;

      algunaPuedeComer(tablero, &turno, turno.turno);

      if (turno.cantPuedenComer > 0)
      {
        turno.come = true;

        if (turno.cantPuedenComer > 1)
        {
          do
          {
            cout << "Una de tus fichas pueden comer, elige una: " << endl;
            for (int i = 0; i < turno.cantPuedenComer; i++)
            {
              cout << i + 1 << ") " << convertirAChar(turno.puedenComer[i][1] + 1) << turno.puedenComer[i][0] << endl;
            }
            cin >> opt;
          } while (opt > turno.cantPuedenComer || opt < 1);

          ficha = "";
          ficha += convertirAChar(turno.puedenComer[opt - 1][1] + 1);
          ficha += ('0' + turno.puedenComer[opt - 1][0] + 1);
        }
        else
        {
          ficha = "";
          ficha += convertirAChar(turno.puedenComer[0][1] + 1);
          ficha += ('0' + turno.puedenComer[0][0] + 1);
        }
      }

      if (!turno.come)
      {
        cout << "¿Que ficha quieres mover? > ";
        cin >> ficha;
      }

      movimientosDisponibles(ficha, &tablero, &turno);

      system("clear");
      imprimirTablero(tablero, turno);

      if (turno.h > 0)
      {
        cout << "Turno de las fichas: " << (turno.turno == 1 ? "o" : "×") << endl;
        cout << "Moviendo la ficha " << ficha << " la puedes mover a: ";
        imprimirMovimientos(turno);
        cout << "0) No mover" << endl;
        cin >> opt;
        if (opt > 0)
          mover(&ficha, opt - 1, &tablero, &turno);
        imprimirTablero(tablero, turno);
      }
    }

    saveGame(tablero, turno);
  }

  // Definir ganador

  if ((tablero.xFuera == 15 && tablero.oFuera == 15))
  {
    ganador = 0;
  }
  else
  {
    if (bloq)
    {
      ganador = turno.turno == 1 ? 2 : 1;
    }
    else if (tablero.xFuera == 16)
      ganador = 1;
    else
      ganador = 2;
  }

  // Mostrar ganador

  system("clear");
  turno.h = 0;

  imprimirTablero(tablero, turno);

  cout << endl;
  if (ganador == 0)
  {
    cout << "El juego a terminado en un empate";
  }
  else
  {
    cout << "El ganador es el jugador de las fichas " << (ganador == 1 ? "o" : "x");
  }

  cout << endl;

  return 0;
}

void menuPrincipal(t_tablero *tablero, t_turno *turno)
{
  int opt;

  system("clear");

  cout << "========= Damas Turcas =========" << endl;
  cout << "Creado por: Miguel " << endl;
  cout << "            Juliana" << endl;
  cout << "            Karime " << endl;
  cout << "================================" << endl
       << endl;

  cout << " 1) Nueva Partida" << endl;
  cout << " 2) Cargar Partida Guardada" << endl
       << endl;
  cout << "> ";
  cin >> opt;

  switch (opt)
  {
  case 1:
    generarTablero(tablero);
    break;

  case 2:
    loadGame(tablero, turno);
    cout << endl;
    break;

  default:
    break;

    system("clear");
  }
}

void imprimirMovimientos(t_turno turno)
{
  cout << endl;
  for (int i = 0; i < turno.h; i++)
  {
    cout << (i + 1) << ") " << convertirAChar(turno.avMovs[i][1] + 1) << turno.avMovs[i][0] + 1 << endl;
  }
}

bool fichasBloqueadas(t_tablero tablero, t_turno turno)
{
  string vision[4];
  string nuevaFicha = "";
  bool bloqueado = true;

  for (int y = 0; (y < 8) && bloqueado; y++)
    for (int x = 0; (x < 8) && bloqueado; x++)
    {
      if (tablero.posiciones[y][x].equipo == turno.turno)
      {
        vision[0] = "";
        vision[1] = "";
        vision[2] = "";
        vision[3] = "";
        nuevaFicha = "";

        nuevaFicha += convertirAChar(x + 1);
        nuevaFicha += '0' + (y + 1);

        alrededorFicha(vision, nuevaFicha, tablero);

        if (tablero.posiciones[y][x].esDama)
        {
          bloqueado = !(vision[0][0] == '0' ||
                        vision[1][0] == '0' ||
                        vision[2][0] == '0' ||
                        vision[3][0] == '0');
        }
        else
        {
          bloqueado = !(vision[0][0] == '0' ||
                        vision[1][0] == '0' ||
                        vision[2][0] == '0');
        }
      }
    }
  return bloqueado;
}
