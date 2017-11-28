//-------------Réalisation de la classe Catalogue (fichier Catalogue.cpp)---------------
using namespace std;
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <cstdlib>
//-------------------------------------------------------------------- Include personnel
#include "Catalogue.h"
//------------------------------------------------------------------- Méthodes publiques
void Catalogue :: Afficher()
{
	m_lesTrajets.Afficher();

	this->Attendre();
}

void Catalogue :: Chercher()
{
	char villeDepart[50];
	char villeArrive[50];

	cout << endl << "    Ville de départ : ";
	cin >> villeDepart;
	cout << "    Ville d'arrive : ";
	cin >> villeArrive;

	Collection *c = this->GetTrajetsCommencePar(villeDepart);

	for (int i=0; i<c->GetLongueur(); i++)
	{
		Collection *resultat = this->TrouverVille(c->GetTrajet(i), villeArrive);
		if (resultat != 0)
		{
			cout << "Trajet " << i+1 << endl;
			cout << "=====================================================================" << endl;
			for (int j=resultat->GetLongueur()-1; j>=0; j--)
			{
				resultat->GetTrajet(j)->Afficher();
			}
			cout << "=====================================================================" << endl;
		}
	}

	if (c->GetLongueur() == 0)
		cout << "Aucun trajet trouvé." << endl;

	this->Attendre();
}

void Catalogue :: Ajouter(int type)
{
	int continuer = 1;
	int nbNouveauxTrajets = 0;
	char villeDepart[50];
	char villeArrivee[50];
	char mtBuffer[50];
	int mt;
	Collection *c;
	Trajet *nouveauTrajet;

	if (type == 2)
	{
		c = new Collection(100);
	}
	while (continuer)
	{
		mt = 0;
		cout << endl << "    Ville de départ : ";
		if (nbNouveauxTrajets > 0)
		{
			cout << villeDepart << " ('stop' pour finir)" << endl;
		}
		else
		{
			cin >> villeDepart;
		}
		cout << "    Ville d'arrivée : ";
		cin >> villeArrivee;
		if (strcmp(villeArrivee, "stop") == 0)
			break;
		// Saisie moyen de transport
		while (mt < 1 || mt > 4)
		{
			cout << "    Transport disponible :" << endl;
			cout << "      1.AUTOCAR \n      2.TRAIN \n      3.BATEAU  \n      4.AVION" << endl;
			cout << "    Moyen de transport : ";
			cin >> mtBuffer;
			mt = int(mtBuffer[0]) % 48;
			if (mt < 1 || mt > 4)
			{
				cout << "    Entrez ID du moyen de transport :" << endl;
			}
		}
		MoyenTransport mtFinal;
		switch (mt)
		{
		case 1:
			mtFinal = AUTOCAR;
			break;
		case 2:
			mtFinal = TRAIN;
			break;
		case 3:
			mtFinal = BATEAU;
			break;
		case 4:
			mtFinal = AVION;
			break;
		}
		nouveauTrajet = new TrajetSimple(villeDepart, villeArrivee, mtFinal);
		// Pour un trajet Simple
		if (type == 1)
		{
			continuer = 0;
		}
		else if (type == 2) // Pour un trajet composé
		{
			c -> Ajouter(nouveauTrajet);
			nbNouveauxTrajets++;
			strcpy(villeDepart, villeArrivee);
		}
	}
	if (type == 2)
	{
		nouveauTrajet = new TrajetCompose(c);
	}
	m_lesTrajets.Ajouter(nouveauTrajet);
} //----- Fin de Ajouter()

void Catalogue :: Attendre()
{
	char a[50];

	cout << "----------------------------------------------taper pour continuer : " << endl;
	cin >> a;
}

Collection *Catalogue::GetTrajetsCommencePar(const char *ville)
{
	Collection *c = new Collection(10);

	for (int i=0; i<m_lesTrajets.GetLongueur(); i++)
	{
		if (strcmp(m_lesTrajets.GetTrajet(i)->GetVilleA(), ville) == 0)
		{
			c->Ajouter(m_lesTrajets.GetTrajet(i));
		}
	}

	return c;
}//----- Fin de CatalogueGetTrajetsCommencePar

Collection *Catalogue :: TrouverVille(Trajet *t, char *ville)
{
	if (strcmp(t->GetVilleB(), ville) == 0)
	{
		Collection *trajetTotal = new Collection(100);
		trajetTotal->Ajouter(t);
		return trajetTotal;
	}

	Collection *c = GetTrajetsCommencePar(t->GetVilleB());

	if (c->GetLongueur() == 0)
		return 0;
	else
	{
		for (int i=0; i<c->GetLongueur(); i++)
		{
			if ( strcmp(c->GetTrajet(i)->GetVilleB(), ville) == 0)
			{
				Collection *trajetTotal = new Collection(100);
				trajetTotal->Ajouter(c->GetTrajet(i));
				trajetTotal->Ajouter(t);
				return trajetTotal;
			}
			else
			{
				if (TrouverVille(c->GetTrajet(i), ville) == 0)
					return 0;
				else
				{
					Collection *trajetTotal = TrouverVille(c->GetTrajet(i), ville);
					trajetTotal->Ajouter(t);
					return trajetTotal;
				}
			}
		}
	}

	return 0;
}

//---------------------------------------------------------- Constructeurs - destructeur
Catalogue :: Catalogue()
			: m_lesTrajets(100)
{
	#ifndef MAP
		cout << "Appel constructeur [ Catalogue ]" << endl;
	#endif
}

Catalogue :: ~Catalogue()
{
	#ifndef MAP
		cout << "Appel destructeur [ Catalogue ]" << endl;
	#endif
}
