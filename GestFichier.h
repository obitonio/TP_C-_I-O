/*
 * GestFichier.h
 *
 *  Created on: 2 déc. 2017
 *      Author: amathat
 */

#ifndef GESTFICHIER_H_
#define GESTFICHIER_H_

#include <iostream>
#include "Collection.h"
#include "TrajetSimple.h"

using namespace std;

enum TypeTrajet
{
	SIMPLE, COMPOSE, DEUX
};

enum CritereSauvegarde
{
	COMPLETE, TYPE_TRAJETS, VILLE, INTERVALLE
};

const string lesCriteresSauvegarde[] = {"sans critère de selection", "selon le type des trajets", "selon la ville de départ et / ou d'arrivée", "selon une selection de trajets"};

class GestFichier
{
	public:
		GestFichier(Collection &collection);
		// Mode d'emploi :
		// 	Constructeur de la classe GestFichier.
		// 	Initialise la collection sur laquelle les fonctions de la classe seront amenées à travailler.
		// Paramètres :
		// 	collection : la collection à sauvegarder pour effectuer les traitements de savegarde / chargement

		bool sauvegarder (string url, TypeTrajet typeTrajet = TypeTrajet::DEUX);
		// Mode d'emploi :
		// 	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
		// 	Il est possible de choisir le type des trajets à sauvegarder (par défaut les deux) via le paramètre typeTrajet.
		// 	Si existant le fichier est vidé pour être remplacé par la sauvegarde.
		// Paramètres :
		// 	url : nom du fichier de sauvegarde
		// 	typeTrajet : type des trajets à sauvegarder, par défaut les deux


		bool sauvegarder (string url, string villeDepart, string villeArrivee);
		// Mode d'emploi :
		//	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
		//	Les trajets sauvegardés respecteront la ville de départ et / ou la ville d'arrivée fournit en paramètres.
		// Paramètres :
		//	url : nom du fichier de sauvegarde
		//	villeDepart : ville de départ que les trajets à sauvegarder doivent respecter ou "" pour s'abstenir du paramètre
		//	villeArrivee : ville de d'arrivée que les trajets à sauvegardrr doivent respecter ou "" pour s'abstenir du paramètre

		bool sauvegarder (string url, int debutIntervalle, int finIntervalle);
		// Mode d'emploi :
		//	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
		//	La sauvegarde s'effectue en respectant l'intervalle donné, du trajet n au trajet m.
		// Paramètres :
		//	url : nom du fichier de sauvegarde
		//	debutIntervalle : début n de l'intervalle
		//	finIntervalle : fin m de l'intervalle

		virtual ~GestFichier();
		// Mode d'emploi :
		//	Destructeur de la classe

	private:
		void EcrireTrajetSimple (TrajetSimple *unTrajetSimple, string &texteAEcrire);
		// Mode d'emploi :
		//	Ecrit la ville de départ et d'arrivé ainsi que le moyen de transport d'un trajet sur la référence donnée en paramètre.
		// Paramètres :
		//	unTrajetSimple : le trajet à écrire
		//	texteAEcrire : le texte sur lequel ajouté le trajet

		bool EcrireTrajet (Trajet *unTrajet, string &texteAEcrire, TypeTrajet typeTrajet = TypeTrajet::DEUX);
		// Mode d'emploi :
		//	Determine si le trajet est simple ou composé puis l'écrit ou non en fonction du type de trajet à écrire
		// Paramètres :
		//	unTrajet : le trajet à traiter
		//	texteAEcrire : le texte sur lequel le trajet sera écrit
		//	typeTrajet : définit le type de trajet autorisé à etre écrit


		void EcrireMetaDonnees(const int nbTrajets, const CritereSauvegarde critereSauvegarde);
		// Mode d'emploi :
		//	Ecrit les métadonnées dans l'entete du fichier de sauvegarde
		// Paramètres :
		//	nbTrajets : le nombre de trajet à indiquer en metadonnées
		//	critereSauvegarde : le critere de sauvegarde à indiquer en metadonnées

	private:
		Collection &m_collection; // Collection de trajets à partir de laquelle effectuer les sauvegardes / restauration
};


#endif /* GESTFICHIER_H_ */
