function pause() {
  read -s -n 1 -p "Press any key to continue . . ."
  echo ""
}

g++ -O -Ifunciones main.cpp funciones/*.cpp
./a.out
