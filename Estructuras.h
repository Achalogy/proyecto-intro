typedef struct s_turno
{
  int avMovs[100][2] = {{0, 0}};
  int h = 0;
  int turno = 1;
  bool come = false;
  int posCome[100][2];

  int puedenComer[100][2];
  int cantPuedenComer = 0;
} t_turno;

typedef struct s_pos
{
  int equipo = 0;
  bool esDama = false;
} t_pos;

typedef struct s_tablero
{
  t_pos posiciones[8][8];
  int xFuera = 0;
  int oFuera = 0;
} t_tablero;
