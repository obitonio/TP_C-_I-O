//----------Réalisation de la classe <TrajetSimple> (ficher TrajetSimple.cpp)-----------
using namespace std;
//---------------------------------------------------------------------- Include système
#include <iostream>
//-------------------------------------------------------------------- Include personnel
#include "Trajet.h"
//------------------------------------------------------------------- Méthodes publiques
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
//---------------------------------------------------------- Constructeurs - destructeur
Trajet :: Trajet()
{
  #if defined (MAP)
    cout << "Appel constructeur [ Trajet ]" << endl;
  #endif
}

Trajet :: ~Trajet()
{
  #if defined (MAP)
    cout << "Appel destructeur [ Trajet ]" << endl;
  #endif
}
