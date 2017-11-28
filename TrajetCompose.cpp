//--------------Réalisation de la classe <TrajetCompose> (ficher TrajetCompose.cpp)---------------

using namespace std;
//---------------------------------------------------------------------- Include système
#include <iostream>
//-------------------------------------------------------------------- Include personnel
#include "TrajetCompose.h"

//------------------------------------------------------------------- Méthodes publiques
void TrajetCompose :: Afficher (int n, int nMax)
{
    m_laCollection -> Afficher(true);
}

void TrajetCompose :: Ajouter(Trajet *unTrajet)
{
    m_laCollection -> Ajouter(unTrajet);
    if(m_nbActu == 0)
    {
        m_villeA = unTrajet -> GetVilleA();
    }
    m_villeB = unTrajet -> GetVilleB();
    m_nbActu ++;
}
const char * TrajetCompose :: GetVilleA(void)
{
    return m_villeA;
}
const char * TrajetCompose :: GetVilleB(void)
{
    return m_villeB;
}

//---------------------------------------------------------- Constructeurs - destructeur
TrajetCompose :: TrajetCompose(int nbElements)
                                : m_nbElements (nbElements), m_nbActu (0), m_villeA(0), m_villeB(0)
{
    #if defined (MAP)
        cout << "Appel constructeur [ TrajetCompose ] nbElements = " << nbElements << endl;
    #endif
    m_laCollection = new Collection(m_nbElements);
}
TrajetCompose :: TrajetCompose(Collection * laCollection)
                                : m_laCollection (laCollection), m_nbActu (0), m_nbElements(0)
{
    #if defined (MAP)
        cout << "Appel constructeur [ TrajetCompose ] collection" << endl;
    #endif

    m_nbElements = laCollection->GetLongueur();

    if (m_nbElements > 0)
    {
        m_villeA = laCollection->GetTrajet(0)->GetVilleA();
        m_villeB = laCollection->GetTrajet(m_nbElements -1)->GetVilleB();
    }
}

TrajetCompose :: ~TrajetCompose()
{
  #if defined (MAP)
    cout << "Appel destructeur [ TrajetCompose ]" << endl;
  #endif
  delete m_laCollection;
}
