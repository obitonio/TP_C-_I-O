/*
 * Catalogue.h
 *
 *  Created on: 2 oct. 2017
 *      Author: amathat
 */
//---------- Interface de la classe Catalogue (Catalogue.h) ------
#ifndef CATALOGUE_H_
#define CATALOGUE_H_

//--------------------------------------------------- Interfaces utilisées
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "GestFichier.h"

//------------------------------------------------------------------------
// Rôle de la classe Catalogue
//	Cette classe contient toutes les méthodes et affichage de gestion des
//  Trajets
//------------------------------------------------------------------------


class Catalogue {

	//----------------------------------------------------------------- PUBLIC
	public:

	//----------------------------------------------------- Méthodes publiques

		void Afficher();
	    // Mode d'emploi :
	    // Affiche tous les Trajets du Catalogue

		void Chercher();
	    // Mode d'emploi :
	    // Recherche des combinaisons de Trajet pour partir d'une ville A et arriver à une ville B

		void Ajouter(int type);
	    // Mode d'emploi :
	    // Lance le menu d'ajout d'un Trajet
		// Si type = 1 alors le trajet saisit sera de type TrajetSimple
		// Si type = 2 alors le trajet saisit sera de type TrajetCompose

		void ChoisirCritere(int type);
		//Mode d'emploi :
		//	Demande à l'utilisateur de saisir les paramètres de sauvegarde ou restauration et lance celle-ci
		//  parametre type : 1 pour sauvegarde / 2 pour restauration

		void ClearScreen();
		// Mode d'emploi :
		// Nettoie l'écran

		void Attendre();
		// Mode d'emploi :
		// Attend que l'utilisateur saisise un caractere

		Collection *GetTrajetsCommencePar(const char *ville);
		// Mode d'emploi :
		// Retourne une Collection de Trajet dont la ville de départ correspond au
		// parametre ville

		Collection *TrouverVille(Trajet *t, char *ville);
		// Mode d'emploi :
		// Cette methode recursive retourne une Collection de Trajet qui atteigne
		// ma ville donnee en parametre.
		// Retourne 0 si impossible a partir du trajet donne en parametre

	//-------------------------------------------- Constructeurs - destructeur
		Catalogue();
		// Mode d'emploi :
		// Constructeur de Catalogue

		virtual ~Catalogue();
		// Mode d'emploi :
		// Destructeur de Catalogue

	protected:
	//----------------------------------------------------- Attributs protégées
		Collection m_lesTrajets;
		GestFichier m_GestFichier;



};

#endif /* CATALOGUE_H_ */
