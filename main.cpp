//-----------------------------main (ficher main.cpp)-----------------------------------
using namespace std;
//---------------------------------------------------------------------- Include système
#include <iostream>
#include <cstdlib>
//-------------------------------------------------------------------- Include personnel
#include "Catalogue.h"
//-------------------------------------------------------------------------------- Main
int main()
{
	Catalogue ctl = Catalogue();
	int choix = 0;
	char choixBuffer[50];

	while (choix != 5)
	{
		choix = 0;
		#ifdef WINDOWS
			std::system("cls");
		#else
			std::system ("clear");
		#endif
		cout << "=====================================================================" << endl;
		cout << "------------------------ Catalogue transport ------------------------" << endl;
		cout << "=====================================================================" << endl;
		cout << "\t 1. Ajouter un trajet simple" << endl;
		cout << "\t 2. Ajouter un trajet composé" << endl;
		cout << "\t 3. Chercher un trajet" << endl;
		cout << "\t 4. Afficher le catalogue" << endl;
		cout << "\t 5. Quitter le catalogue" << endl;
		cout << "=====================================================================" << endl;
		while (choix < 1 || choix > 5)
		{
			cout << "Quel service voulez-vous ?\nSaisisez le chiffre correspondant : ";
			cin >>choixBuffer;
			choix = int(choixBuffer[0]) % 48;
		}
		switch (choix)
		{
		case 1:
			cout << " -> Ajouter un trajet simple :";
			ctl.Ajouter(1);
			break;
		case 2:
			cout << " -> Ajouter un trajet composé :";
			ctl.Ajouter(2);
			break;
		case 3:
			cout << " -> Chercher un trajet :";
			ctl.Chercher();
			break;
		case 4:
			cout << " -> Afficher le catalogue : \n";
			ctl.Afficher();
			break;
		}
	}
	return 0;
}
