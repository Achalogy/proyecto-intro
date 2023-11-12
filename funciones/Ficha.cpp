#include "Ficha.h"
#include <fstream>
#include <iostream>
#include "Utils.h"

using namespace std;

void alrededorFicha(string vision[], string ficha, t_tablero tablero)
{
  int x = convertirAEntero(ficha[0]) - 1;
  int y = convertirAEntero(ficha[1]) - 1;
  int dFicha = tablero.posiciones[y][x].equipo;

  int nx = x - 1;
  int ny = y;
  while (nx >= 0)
  {
    vision[0] += '0' + tablero.posiciones[ny][nx].equipo;
    nx--;
  }

  nx = x;
  ny = y + (dFicha == 1 ? 1 : -1);

  while (ny >= 0 && ny < 8)
  {
    vision[1] += '0' + tablero.posiciones[ny][nx].equipo;
    ny += (dFicha == 1 ? 1 : -1);
  }

  nx = x + 1;
  ny = y;

  while (nx < 8)
  {
    vision[2] += '0' + tablero.posiciones[ny][nx].equipo;
    nx++;
  }

  if (tablero.posiciones[y][x].esDama)
  {
    nx = x;
    ny = y + (dFicha == 1 ? -1 : 1);

    while (ny >= 0 && ny < 8)
    {
      vision[3] += '0' + tablero.posiciones[ny][nx].equipo;
      ny += (dFicha == 1 ? -1 : 1);
    }
  }
}

void algunaPuedeComer(t_tablero tablero, t_turno *turno, int equipo)
{
  string vision[4];
  string ficha = "";
  turno->cantPuedenComer = 0;

  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      if (tablero.posiciones[y][x].equipo == equipo)
      {
        vision[0] = "";
        vision[1] = "";
        vision[2] = "";
        vision[3] = "";
        ficha = "";
        ficha += convertirAChar(x + 1);
        ficha += (y + 1) + '0';

        alrededorFicha(vision, ficha, tablero);
        if (puedeComer(equipo, vision, tablero.posiciones[y][x].esDama))
        {
          turno->puedenComer[turno->cantPuedenComer][0] = y;
          turno->puedenComer[turno->cantPuedenComer][1] = x;

          turno->cantPuedenComer++;
        }
      }
    }
  }
}

void movimientosDisponibles(string ficha, t_tablero *tablero, t_turno *turno)
{
  turno->come = false;
  int x = convertirAEntero(ficha[0]) - 1;
  int y = convertirAEntero(ficha[1]) - 1;
  int dFicha = tablero->posiciones[y][x].equipo;
  char enemigo = dFicha == 1 ? '2' : '1';
  string vision[4];
  bool flag = false;

  if (dFicha != 0 && dFicha == turno->turno)
  {
    turno->h = 0;
    alrededorFicha(vision, ficha, *tablero);

    if (!puedeComer(dFicha, vision, tablero->posiciones[y][x].esDama))
    {
      if (tablero->posiciones[y][x].esDama)
      {
        for (int a = 0; a < 4; a++)
        {
          flag = false;
          for (int b = 0; (b < vision[a].length() && !flag); b++)
          {
            if (vision[a][b] != '0')
              flag = true;
            else
            {
              switch (a)
              {
              case 0: // izquierda
                turno->avMovs[turno->h][0] = y;
                turno->avMovs[turno->h][1] = x - 1 - b;
                break;
              case 1: // adelante
                turno->avMovs[turno->h][0] = y + (dFicha == 1 ? (1 + b) : (-1 - b));
                turno->avMovs[turno->h][1] = x;
                break;
              case 2: // derecha
                turno->avMovs[turno->h][0] = y;
                turno->avMovs[turno->h][1] = x + 1 + b;
                break;
              case 3: // atrás
                turno->avMovs[turno->h][0] = y + (dFicha == 1 ? (-1 - b) : (1 + b));
                turno->avMovs[turno->h][1] = x;
                break;

              default:
                break;
              }
              turno->h++;
            }
          }
        }
      }
      else
      {
        if (vision[0][0] == '0')
        { // se puede mover a la izquierda
          turno->avMovs[turno->h][0] = y;
          turno->avMovs[turno->h][1] = x - 1;
          turno->h++;
        }
        if (vision[1][0] == '0')
        { // se puede mover en y
          turno->avMovs[turno->h][0] = y + (dFicha == 1 ? 1 : -1);
          turno->avMovs[turno->h][1] = x;
          turno->h++;
        }
        if (vision[2][0] == '0')
        { // se puede mover a la derecha
          turno->avMovs[turno->h][0] = y;
          turno->avMovs[turno->h][1] = x + 1;
          turno->h++;
        }
      }
    }
    else
    {
      if (tablero->posiciones[y][x].esDama)
      {
        for (int a = 0; a < 4; a++)
        {
          for (int b = 0; (b < vision[a].size() - 1) && (vision[a].size() > 0); b++)
          {
            if (vision[a][b] == enemigo && vision[a][b + 1] == '0')
            {
              switch (a)
              {
              case 0: // izquierda
                turno->avMovs[turno->h][0] = y;
                turno->avMovs[turno->h][1] = x - b - 2;
                turno->posCome[turno->h][0] = y;
                turno->posCome[turno->h][1] = x - b - 1;

                break;
              case 1: // adelante
                turno->avMovs[turno->h][0] = y + (dFicha == 1 ? 2 + b : -2 - b);
                turno->avMovs[turno->h][1] = x;
                turno->posCome[turno->h][0] = y + (dFicha == 1 ? 1 + b : -1 - b);
                turno->posCome[turno->h][1] = x;

                break;
              case 2: // derecha
                turno->avMovs[turno->h][0] = y;
                turno->avMovs[turno->h][1] = x + 2 + b;
                turno->posCome[turno->h][0] = y;
                turno->posCome[turno->h][1] = x + 1 + b;

                break;
              case 3: // atrás
                turno->avMovs[turno->h][0] = y + (dFicha == 1 ? -2 - b : 2 + b);
                turno->avMovs[turno->h][1] = x;
                turno->posCome[turno->h][0] = y + (dFicha == 1 ? -1 - b : 1 + b);
                turno->posCome[turno->h][1] = x;

                break;

              default:
                break;
              }
              turno->h++;
            }
          }
        }
      }
      else
      {
        if (vision[0][0] == enemigo && vision[0][1] == '0')
        {
          turno->avMovs[turno->h][0] = y;
          turno->avMovs[turno->h][1] = x - 2;
          turno->posCome[turno->h][0] = y;
          turno->posCome[turno->h][1] = x - 1;

          turno->h++;
        }
        if (vision[1][0] == enemigo && vision[1][1] == '0')
        {
          turno->avMovs[turno->h][0] = y + (dFicha == 1 ? 2 : -2);
          turno->avMovs[turno->h][1] = x;
          turno->posCome[turno->h][0] = y + (dFicha == 1 ? 1 : -1);
          turno->posCome[turno->h][1] = x;

          turno->h++;
        }
        if (vision[2][0] == enemigo && vision[2][1] == '0')
        {
          turno->avMovs[turno->h][0] = y;
          turno->avMovs[turno->h][1] = x + 2;
          turno->posCome[turno->h][0] = y;
          turno->posCome[turno->h][1] = x + 1;

          turno->h++;
        }
      }

      turno->come = true;
    }
  }
}

bool puedeComer(int equipo, string vision[], bool esDama)
{
  bool retorno = false;
  bool damaCome = false;
  char enemigo = equipo == 1 ? '2' : '1';

  if (esDama)
  {
    for (int i = 0; (i < 4) && !retorno; i++)
    {
      damaCome = false;
      for (int a = 0; vision[i].size() > 0 && (a < vision[i].size() - 1) && !retorno && !damaCome; a++)
      {
        retorno = vision[i][a] == enemigo && vision[i][a + 1] == '0';
        if (vision[i][a] == enemigo)
          damaCome = true;
      }
    }
  }
  else
  {
    for (int i = 0; (i < 3) && !retorno; i++)
      retorno = vision[i][0] == enemigo && vision[i][1] == '0';
  }

  return retorno;
}

void mover(string *ficha, int opt, t_tablero *tablero, t_turno *turno)
{
  int x = convertirAEntero((*ficha)[0]) - 1;
  int y = convertirAEntero((*ficha)[1]) - 1;
  int dFicha = tablero->posiciones[y][x].equipo;

  int nx = turno->avMovs[opt][1];
  int ny = turno->avMovs[opt][0];
  string nuevaFicha = "";

  bool pasarTurno = true;

  string vision[4];

  if (opt < turno->h)
  {
    nuevaFicha += convertirAChar(nx + 1);
    nuevaFicha += ('0' + ny + 1);

    tablero->posiciones[ny][nx].equipo = dFicha;
    tablero->posiciones[ny][nx].esDama = tablero->posiciones[y][x].esDama;
    tablero->posiciones[y][x].equipo = 0;
    tablero->posiciones[y][x].esDama = false;

    // revisar si es necesario convertir a dama

    if ((dFicha == 1 && ny == 7) || dFicha == 2 && ny == 0)
      tablero->posiciones[ny][nx].esDama = true;

    if (turno->come)
    {
      cout << turno->posCome[opt][0] << " - " << turno->posCome[opt][1];
      tablero->posiciones[turno->posCome[opt][0]][turno->posCome[opt][1]].equipo = 0;
      tablero->posiciones[turno->posCome[opt][0]][turno->posCome[opt][1]].esDama = false;
      turno->come = false;

      alrededorFicha(vision, nuevaFicha, *tablero);

      if (dFicha == 1)
        tablero->xFuera++;
      else
        tablero->oFuera++;

      if (puedeComer(tablero->posiciones[ny][nx].equipo, vision, tablero->posiciones[ny][nx].esDama))
      {
        pasarTurno = false;
        turno->come = true;
        (*ficha) = nuevaFicha;
      }
    }

    if (pasarTurno)
      turno->turno = turno->turno == 1 ? 2 : 1;

    turno->h = 0;
    turno->cantPuedenComer = 0;
  }
  else
  {
    cout << "Movimiento Ilegal" << endl;
  }
}
