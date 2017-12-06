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

void Catalogue::Afficher()
{
	m_lesTrajets.Afficher();
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

} //----- Fin de Chercher()

void Catalogue::Ajouter(int type)
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
		c = new Collection(100);

	while (continuer)
	{
		if (nbNouveauxTrajets > 0){
			cout << endl;
		}

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

void Catalogue::ChoisirCritere(TypeTraitementFichier typeTraitementFichier)
{
	int choix = 0;
	int nbChoix = 5;
	char choixBuffer[50];
	string nomType = "sauvegarde";
	string villeDepart = "", villeArrivee = "";
	string nomFichier = "save.txt";

	if (typeTraitementFichier == TypeTraitementFichier::RESTAURATION)
		nomType = "restauration";

	while (choix != nbChoix)
	{
		choix = 0;
		cout << endl;
		cout << "======================== " << nomType << " ========================" << endl;
		cout << "\t1. Sans critère de sélection" << endl;
		cout << "\t2. Selon le type des trajets" << endl;
		cout << "\t3. Selon la ville de départ et / ou la ville d'arrivée" << endl;
		cout << "\t4. Selon une séléction de trajets" << endl;
		cout << "\t5. Retour au menu" << endl;
		cout << "===================================================================" << endl;
		while (choix < 1 || choix > nbChoix)
		{
			cout << "Saisir un chiffre : ";
			cin >>choixBuffer;
			choix = int(choixBuffer[0]) % 48;
		}
		if (choix >= 1 && choix < nbChoix){
			cout << "Nom du fichier à traiter : ";
			cin >> nomFichier;
			cout << endl;
		}
		switch (choix)
		{
		case 1: // ===== Sans critère de selection
			if (typeTraitementFichier == TypeTraitementFichier::SAUVEGARDE) // Sauvegarde
			{
				m_GestFichier.sauvegarder(nomFichier);
			}
			else if (typeTraitementFichier == TypeTraitementFichier::RESTAURATION) // Restauration
			{
				m_GestFichier.charger(nomFichier, DEUX);
			}
			break;
		case 2: // ===== Selon le type des trajets
			int typeTrajet;

			cout << "Pour les trajets simple (1) ou composé (2) ? ";
			cin >> typeTrajet;

			if (typeTraitementFichier == TypeTraitementFichier::SAUVEGARDE) // Sauvgarde
			{
				m_GestFichier.sauvegarder(nomFichier, TypeTrajet(typeTrajet - 1)); 
			}
			else if (typeTraitementFichier == TypeTraitementFichier::RESTAURATION) // Restauration
			{
				TypeTrajet tyTrajet = DEUX;
				if(typeTrajet == 1){
					tyTrajet = SIMPLE;
				}else if(typeTrajet == 2){
					tyTrajet = COMPOSE;
				}else{
					cerr << "Saisie unvalide, forcer sur la valeur par défaut (DEUX)" << endl;
				}
				m_GestFichier.charger(nomFichier, tyTrajet);
			}
			break;
		case 3: // ===== Selon la ville de départ et / ou la ville d'arrivée

			cout << "Mettre 0 pour utiliser une seule ville." << endl;
			cout << "Ville de départ : " << endl;
			cin >> villeDepart;
			cout << "Ville d'arrivée : " << endl;
			cin >> villeArrivee;

			if (typeTraitementFichier == TypeTraitementFichier::SAUVEGARDE) // Sauvegarde
			{
					villeDepart = (villeDepart.compare("0") == 0) ? "": villeDepart;
					villeArrivee = (villeArrivee.compare("0") == 0) ? "" : villeArrivee;
					m_GestFichier.sauvegarder(nomFichier, villeDepart, villeArrivee);
			}
			else if (typeTraitementFichier == TypeTraitementFichier::RESTAURATION) {
				villeDepart = (villeDepart.compare("0") == 0) ? "" : villeDepart;
				villeArrivee = (villeArrivee.compare("0") == 0) ? "" : villeArrivee;
				m_GestFichier.charger(nomFichier, villeDepart, villeArrivee);
			}
			break;
		case 4: // ===== Selon une selection de trajet
			int n = 0;
			int m = 0;

			while (m - n < 1)
			{
				cout << "Premier trajet à " << nomType << " : ";
				cin >> n;
				cout << "Dernier trajet à " << nomType << " : ";
				cin >> m;

				if (m - n < 1)
					cout << "Veuillez saisir des bornes correctes." << endl;
			}

			if (typeTraitementFichier == TypeTraitementFichier::SAUVEGARDE) // Sauvegarde
			{
				m_GestFichier.sauvegarder(nomFichier, n, m);
			}
			else if (typeTraitementFichier == TypeTraitementFichier::RESTAURATION) // Restauration
			{
				m_GestFichier.charger(nomFichier, n, m);
			}

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
	#if defined (MAP)
    cout << "Appel constructeur [ Catalogue ]" << endl;
  #endif
} //----- Fin de Catalogue()

Catalogue::~Catalogue()
{
	#if defined (MAP)
    cout << "Appel destructeur [ Catalogue ]" << endl;
  #endif
} //----- Fin de ~Catalogue()
