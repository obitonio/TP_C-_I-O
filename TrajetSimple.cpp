//----------Réalisation de la classe <TrajetSimple> (ficher TrajetSimple.cpp)-----------

using namespace std;
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
//-------------------------------------------------------------------- Include personnel
#include "TrajetSimple.h"
//------------------------------------------------------------------- Méthodes publiques
void TrajetSimple :: Afficher (int n, int nMax)
{
	char moyenTransport[50];
	bool estSimple = true;

	if (n !=-1 && nMax !=-1)
		estSimple = false;

	switch (m_mt)
	  {
		case 0:
		  strcpy(moyenTransport, "autocar");
		  break;
		case 1:
		  strcpy(moyenTransport, "train");
		  break;
		case 2:
		  strcpy(moyenTransport, "bateau");
		  break;
		case 3:
		  strcpy(moyenTransport, "avion");
		  break;
		default:
		  cout << "|      Transport : pas de moyen disponible" << endl;
		  break;
	  }

	if (estSimple)
	{
		cout << "----------------------------------------" << endl;
		cout << "|  Trajet Simple :" << endl;
		cout << "|      Depart : " << m_villeA << endl;
		cout << "|      Arrive : " << m_villeB << endl;
	    cout << "|      Transport : <" << moyenTransport << ">"<< endl;
		cout << "----------------------------------------" << endl;

	}
	else
	{
		if (n==0)
		{
			cout << "----------------------------------------" << endl;
			cout << "|  Trajet Compose :" << endl;
			cout << "|      Depart    : " << m_villeA << endl;
		}

	    cout << "|      Transport : <" << moyenTransport << ">" << endl;

		if (n != nMax-1)
		{
		     cout << "|      Etape     : " << m_villeB << endl;
		}
		else
		{

			cout << "|      Arrive    : " << m_villeB << endl;
			cout << "----------------------------------------" << endl;
		}
	}
}

const char * TrajetSimple :: GetVilleA(void)
{
  return m_villeA;
}
const char * TrajetSimple :: GetVilleB(void)
{
  return m_villeB;
}
//---------------------------------------------------------- Constructeurs - destructeur
TrajetSimple :: TrajetSimple(const char * villeA, const char * villeB, MoyenTransport mt)
:m_mt (mt)
{
  #if defined (MAP)
    cout << "Appel constructeur [ TrajetSimple ]" << endl;
  #endif

    m_villeA = new char[strlen(villeA)+1];
    strcpy(m_villeA, villeA);

    m_villeB = new char[strlen(villeB)+1];
    strcpy(m_villeB, villeB);
}

TrajetSimple :: ~TrajetSimple()
{
  #if defined (MAP)
    cout << "Appel destructeur [ TrajetSimple ]" << endl;
  #endif

    delete[] m_villeA;
    delete[] m_villeB;
}
