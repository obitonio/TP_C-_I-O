//--------------Réalisation de la classe Collection (fichier Collection.cpp)---------------

using namespace std;
// -----------include système---------------
#include <iostream>
#include <cstring>

#include "Collection.h"

//------------méthodes publiques------------
void Collection :: Ajuster(int delta)
{
	Trajet **nouveauLesTrajets = 0;
	if (delta > 0)
	{
		nouveauLesTrajets = new Trajet *[m_max+delta];
		for (int i = 0; i < m_max; i ++)
		{
			nouveauLesTrajets[i] = m_lesTrajets[i];
		}
		m_max += delta;
		m_lesTrajets = nouveauLesTrajets;
	}
}

void Collection :: Ajouter(Trajet *unTrajet)
{
	if (m_courant == m_max)
	{
		this -> Ajuster(1);
	}
	m_lesTrajets[m_courant] = unTrajet;
	m_courant ++;
}

void Collection :: Afficher(bool compose)
{
	for(int i = 0; i < m_courant; i ++)
	{
		if (!compose)
			m_lesTrajets[i] -> Afficher();
		else
			m_lesTrajets[i] -> Afficher(i, m_courant);
	}

	if (m_courant == 0)
		cout << "Il n'y a auncun Trajet." << endl;
} //----- Fin de Afficher()

void Collection :: Chercher(char *villeDepart, char *villeArrive)
{
	for (int i=0; i<m_courant; i++)
	{
		if (strcmp(m_lesTrajets[i]->GetVilleA(), villeDepart) == 0
				&& strcmp(m_lesTrajets[i]->GetVilleB(), villeArrive) == 0 )
		{
			m_lesTrajets[i]->Afficher();
		}
	}
} //----- Fin de Chercher()

int Collection::GetLongueur()
{
	return m_courant;
} //----- Fin de GetLongueur()


Trajet *Collection::GetTrajet(int index)
{
	if (index > m_courant)
	{
		return m_lesTrajets[0];
	}

	return m_lesTrajets[index];
} //----- Fin de GetTrajet()

//------------constructeurs-----------------
Collection::Collection(int nbElements)
: m_courant(0), m_max(nbElements)
{
	#ifndef MAP
		cout << "Appel constructeur [ Collection ] nbElements = " << nbElements << endl;
	#endif
	m_lesTrajets = new Trajet *[nbElements];
}

//------------destructeur-------------------
Collection::~Collection()
{
	#ifndef MAP
		cout << "Appel destructeur [ TrajetCompose ]" << endl;
	#endif

	for (int i=0; i<m_courant; i++)
	{
		delete m_lesTrajets[i];
	}
	delete[] m_lesTrajets;
}

