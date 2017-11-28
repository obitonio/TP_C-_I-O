//---------------Interface de la classe Catalogue (Catalogue.h)---------------
#ifndef CATALOGUE_H
#define CATALOGUE_H
//------------------------------------------------------- Interfaces utilisées
#include "Collection.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
//----------------------------------------------------------------------------
//Rôle de la classe Catalogue
//	défini les methodes concernant de la gestion des trajets
//----------------------------------------------------------------------------
class Catalogue
{
	public:
	//----------------------------------------------------- Méthodes publiques
		void Afficher();
	  	//Mode d'emploi :
	  	//  Affiche tous les Trajets du Catalogue

		void Chercher();
	  	//Mode d'emploi :
	  	//  Recherche simple d'un trajet

		void Ajouter(int type);
		//Mode d'emploi :
		//  Lance le menu d'ajout d'un Trajet
		//  Si type = 1 alors le trajet saisit sera de type TrajetSimple
		//  Si type = 2 alors le trajet saisit sera de type TrajetCompose

		void Attendre();
		//Mode d'emploi :
		//  Attend que l'utilisateur saisise un caractere

		Collection *GetTrajetsCommencePar(const char *ville);
		//Mode d'emploi :
		//  Retourne une Collection de Trajet dont la ville de départ
		//  correspond au parametre ville

		Collection *TrouverVille(Trajet *t, char *ville);
		//Mode d'emploi :
		//  Cette methode recursive retourne une Collection de Trajet qui
		//  atteigne ma ville donnee en parametre.
		//  Retourne 0 si impossible a partir du trajet donne en parametre
	//-------------------------------------------- Constructeurs - destructeur
		Catalogue();
		//Mode d'emploi :
		//  Constructeur de Catalogue

		virtual ~Catalogue();
		//Mode d'emploi :
		//  Destructeur de Catalogue

	protected:
	//---------------------------------------------------- Attributs protégées
		Collection m_lesTrajets;
};
#endif // CATALOGUE_H
