//--------------Réalisation de la classe <TrajetSimple> (ficher TrajetSimple.cpp)---------------

using namespace std;
// -----------include systeme---------------
#include <iostream>
// -----------include personnel-------------
#include "Trajet.h"

//------------methodes publiques------------
void Trajet :: Afficher (int n, int nMax)
{
  cout << "Class Trajet : appel methode Afficher (Il me semble une erreur ..)" << endl;
}
const char * Trajet :: GetVilleA(void)
{
  return "Erreur A";
}

const char * Trajet :: GetVilleB(void)
{
  return "Erreur B";
}
//------------constructeurs-----------------
Trajet :: Trajet()
{
  #ifndef MAP
    cout << "Appel constructeur [ Trajet ]" << endl;
  #endif
}
//------------destructeur-----------------
Trajet :: ~Trajet()
{
  #ifndef MAP
    cout << "Appel destructeur [ Trajet ]" << endl;
  #endif
}
