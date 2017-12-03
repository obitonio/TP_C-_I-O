/*
 * Catalogue.cpp
 *
 *  Created on: 2 oct. 2017
 *      Author: amathat
 */

//---------- Réalisation de la classe Catalogue (fichier Catalogue.cpp) --

//---------------------------------------------------------------- INCLUDE
#include "Catalogue.h"
#include "GestFichier.h"

//-------------------------------------------------------- Include syst�me

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Catalogue::Afficher()
{
	m_lesTrajets.Afficher();

	this->Attendre();
} //----- Fin de Afficher()

void Catalogue::Chercher()
{
	char villeDepart[50];
	char villeArrivee[50];

	cout << "Ville de départ : ";
	cin >> villeDepart;
	cout << "Ville d'arrive : ";
	cin >> villeArrivee;
	cout << endl;

	Collection *c = this->GetTrajetsCommencePar(villeDepart);

	for (int i=0; i<c->GetLongueur(); i++)
	{
		Collection *resultat = this->TrouverVille(c->GetTrajet(i), villeArrivee);
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
} //----- Fin de Chercher()

void Catalogue::Ajouter(int type)
{
	cout << "================================" << endl;
	cout << "\tAjouter un trajet" << endl;
	cout << "================================" << endl;

	int continuer = 1;
	int nbNouveauxTrajets = 0;
	char villeDepart[50];
	char villeArrivee[50];
	char mtBuffer[50];
	int mt;
	Collection *c;
	Trajet *nouveauTrajet;

	if (type == 2)
		c = new Collection(100);

	while (continuer)
	{

		this->ClearScreen();
		cout << "========================  Ajouter un trajet  ========================" << endl;
		mt = 0;
		cout << endl << "Ville de départ : ";
		if (nbNouveauxTrajets > 0)
		{
			cout << villeDepart << " ('stop' pour finir)" << endl;
		}
		else
			cin >> villeDepart;

		//villeArrivee = new char[50];
		cout << "Ville d'arrivée : ";
		cin >> villeArrivee;

		if (strcmp(villeArrivee, "stop") == 0)
			break;

		// Saisie moyen de transport
		cout << "1.AUTOCAR 2.TRAIN 3.BATEAU 4.AVION" << endl;
		while (mt < 1 || mt > 4)
		{
			cout << "Moyen de transport : ";
			cin >> mtBuffer;

			mt = int(mtBuffer[0]) % 48;

			if (mt < 1 || mt > 4)
				cout << "Entrez l'id du moyen de transport." << endl;
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
			c->Ajouter(nouveauTrajet);
			nbNouveauxTrajets++;
			strcpy(villeDepart, villeArrivee);
		}
	}

	if (type == 2)
		nouveauTrajet = new TrajetCompose(c);


	m_lesTrajets.Ajouter(nouveauTrajet);

} //----- Fin de Ajouter()

void Catalogue::ChoisirCritere(int type)
{
	int choix = 0;
	int nbChoix = 5;
	char choixBuffer[50];
	string nomType = "sauvegarde";
	string ville;

	if (type == 2)
		nomType = "restauration";

	while (choix != nbChoix)
	{
		choix = 0;

		cout << "=====================================================================" << endl;
		cout << "Types de " << nomType << ": " << endl;
		cout << "1. Sans critère de sélection" << endl;
		cout << "2. Selon le type des trajets" << endl;
		cout << "3. Selon la ville de départ et / ou la ville d'arrivée" << endl;
		cout << "4. Selon une séléction de trajets" << endl;
		cout << "5. Retour au menu" << endl;
		while (choix < 1 || choix > nbChoix)
		{
			cout << "Saisir un chiffre : ";
			cin >>choixBuffer;
			choix = int(choixBuffer[0]) % 48;
		}

		switch (choix)
		{
		case 1: // ===== Sans critère de selection
			if (type == 1) // Sauvegarde
			{
				//m_GestFichier.sauvegarder("test.txt");
			}
			else if (type == 2) // Restauration
			{}
			break;
		case 2: // ===== Selon le type des trajets
			int typeTrajet;

			cout << "Pour les trajets simple (1) ou composé (2) ? ";
			cin >> typeTrajet;

			if (type == 1) // Sauvegarde
			{}
			else if (type == 2) // Restauration
			{}
			break;
		case 3: // ===== Selon la ville de départ et / ou la ville d'arrivée
			int typeVille;

			cout << "Pour une ville de départ (1) ou une ville d'arrivée (2) ? ";
			cin >> typeVille;
			cout << "Saisir la ville : ";
			cin >> ville;

			if (type == 1) // Sauvegarde
			{}
			else if (type == 2) // Restauration
			{}
			break;
		case 4: // ===== Selon une selection de trajet
			int n = 0;
			int m = 0;

			while (m - n < 1)
			{
				cout << "Premier trajet à sauver : ";
				cin >> n;
				cout << "Dernier trajet à sauver : ";
				cin >> m;

				if (m - n < 1)
					cout << "Veuillez saisir des bornes correctes." << endl;
			}

			if (type == 1) // Sauvegarde
			{}
			else if (type == 2) // Restauration
			{}
			break;
		}
	}
} //----- Fin de ChoisirCritere()

void Catalogue::ClearScreen()
{
	#ifdef WINDOWS
		std::system("cls");
	#else
		// Assume POSIX
		std::system ("clear");
	#endif
} //----- Fin de ClearScreen()

void Catalogue::Attendre()
{
	char a[50];

	cout << "Continuer (oui) : ";
	cin >> a;
} //----- Fin de Attendre()

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
} //----- Fin de CatalogueGetTrajetsCommencePar

Collection *Catalogue::TrouverVille(Trajet *t, char *ville)
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


//-------------------------------------------- Constructeurs - destructeur

Catalogue::Catalogue()
: m_lesTrajets(100), m_GestFichier(m_lesTrajets)
{
#ifndef MAP
	cout << "Début constructeur de Catalogue...";
#endif

	//m_lesTrajets = new Collection(100);
} //----- Fin de Catalogue()

Catalogue::~Catalogue()
{
	//delete m_lesTrajets;
} //----- Fin de ~Catalogue()
