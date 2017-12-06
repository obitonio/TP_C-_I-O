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
//   Point d'entré du programme
//--------------------------------------------------------------------------

int main() {

	Catalogue ctl;
	int choix = 0;
	int nbChoix = 7;
	char choixBuffer[50];


	while (choix != nbChoix)
	{
		choix = 0;

		cout << endl;
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
		cout << endl;

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
			ctl.ChoisirCritere(TypeTraitementFichier::SAUVEGARDE);
			break;
		case 6:
			ctl.ChoisirCritere(TypeTraitementFichier::RESTAURATION);
			break;
		}
	}

	return 0;
}
