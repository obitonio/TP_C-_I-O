//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Catalogue.h"
#include "TrajetCompose.h"
#include "TrajetSimple.h"
#include "GestFichier.h"

using namespace std;

//--------------------------------------------------------------------------
//fonction main
//   Point d'entrée du programme
//--------------------------------------------------------------------------

int main() {

	Collection maCollection(100);
	GestFichier gestFichier(maCollection);

	maCollection.Ajouter(new TrajetSimple("Lyon", "Paris", MoyenTransport::AUTOCAR));
	maCollection.Ajouter(new TrajetSimple("Lyon", "Strasbourg", MoyenTransport::TRAIN));
	maCollection.Ajouter(new TrajetSimple("Lyon", "Rouen", MoyenTransport::BATEAU));

	TrajetCompose* tc1 = new TrajetCompose(10);
	tc1->Ajouter(new TrajetSimple("Paris", "Rouen", MoyenTransport::BATEAU));
	tc1->Ajouter(new TrajetSimple("Rouen", "Bordeaux", MoyenTransport::AVION));
	tc1->Ajouter(new TrajetSimple("Bordeaux", "Montpellier", MoyenTransport::AUTOCAR));
	maCollection.Ajouter(tc1);

	maCollection.Ajouter(new TrajetSimple("Paris", "Montpellier", MoyenTransport::TRAIN));

	TrajetCompose* tc2 = new TrajetCompose(10);
	tc2->Ajouter(new TrajetSimple("Strasbourg", "Rouen", MoyenTransport::BATEAU));
	tc2->Ajouter(new TrajetSimple("Rouen", "Lyon", MoyenTransport::AVION));
	tc2->Ajouter(new TrajetSimple("Lyon", "Nimes", MoyenTransport::AUTOCAR));
	tc2->Ajouter(new TrajetSimple("Nimes", "Montpellier", MoyenTransport::AUTOCAR));
	maCollection.Ajouter(tc2);


	gestFichier.sauvegarder("test.txt");
	gestFichier.sauvegarder("test2.txt", TypeTrajet::COMPOSE);
	gestFichier.sauvegarder("test3.txt", "Paris", "");
	gestFichier.sauvegarder("test4.txt", 2, 4);

	/*

	Catalogue ctl;
	int choix = 0;
	int nbChoix = 7;
	char choixBuffer[50];


	while (choix != nbChoix)
	{
		choix = 0;
		ctl.ClearScreen();

		cout << "=====================================================================" << endl;
		cout << "------------------------ Catalogue transport ------------------------" << endl;
		cout << "=====================================================================" << endl;
		cout << "\t 1. Ajouter un trajet simple" << endl;
		cout << "\t 2. Ajouter un trajet composé" << endl;
		cout << "\t 3. Chercher un trajet" << endl;
		cout << "\t 4. Afficher le catalogue" << endl;
		cout << "\t 5. Sauvegarder le catalogue" << endl;
		cout << "\t 6. Restaurer le catalogue" << endl;
		cout << "\t 7. Quitter le catalogue" << endl;
		cout << "=====================================================================" << endl;

		while (choix < 1 || choix > nbChoix)
		{
			cout << "Saisir un chiffre : ";
			cin >>choixBuffer;
			choix = int(choixBuffer[0]) % 48;
		}

		switch (choix)
		{
		case 1:
			ctl.Ajouter(1);
			break;
		case 2:
			ctl.Ajouter(2);
			break;
		case 3:
			ctl.Chercher();
			break;
		case 4:
			ctl.Afficher();
			break;
		case 5:
			ctl.ChoisirCritere(1);
			break;
		case 6:
			ctl.ChoisirCritere(2);
			break;
		}
	}

	return 0;
	*/
}
