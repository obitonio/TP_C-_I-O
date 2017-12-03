/*
 * Collection.h
 *
 *  Created on: 2 oct. 2017
 *      Author: amathat
 */
//---------- Interface de la classe Collection (fichier Collection.h) ------
#ifndef COLLECTION_H_
#define COLLECTION_H_
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//--------------------------------------------------------------------------
//classe Collection
//   Permet de manipuler une liste de Trajet
//--------------------------------------------------------------------------
class Collection
{
	public:
	//----------------------------------------------------------------- PUBLIC
		void Ajuster(int delta);
		//Mode d'emploi :
		// Augmente la taille de la Collection en fonction du parametre delta
		//Contrat : aucun

		void Ajouter(Trajet *unTrajet);
		//Mode d'emploi :
		// Ajoute un Trajet dans la Collection
		//Contrat : aucun

		void Afficher(bool compose = false);
		//Mode d'emploi :
		//	Affiche tous les elements de la Collection
		//	Paramètre : compose indique si la collection doit être affiché comme un Trajet Composé
		//  Contrat : aucun

		void Chercher(char *villeDepart, char *villeArrive);
		//Mode d'emploi :
		//	Affiche tous les trajets possible avec comme départ le parametre villeDepart
		// 	et comme arrivee villeArrivee
		//	Paramètres : la ville de début et d'arrivee
		//  Contrat : aucun

		int GetLongueur();
		//Mode d'emploi :
		//	Retourne le nombre d'elements de la collection
		//  Contrat : aucun

		Trajet *GetTrajet(int index);
		//Mode d'emploi :
		//	Retourne le Trajet à l'index donné si il existe
		//  Contrat : aucun

	//-------------------------------------------- Constructeurs - destructeur
		Collection(int nbElements);
		//Mode d'emploi :
		// Construit une Collection capable d'accueillir nbElments Trajet
		//Contrat : aucun

		virtual ~Collection();
		//Mode d'emploi :
		// Destructeur de Collection
		//Contrat : aucun

	//-------------------------------------------------------------- PROTECTED
	protected:
		int m_max;
		int m_courant;
		Trajet **m_lesTrajets;
};
#endif /* COLLECTION_H_ */
