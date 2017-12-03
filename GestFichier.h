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

class GestFichier
{
	public:
		GestFichier(Collection &collection);

		bool sauvegarder (string url, TypeTrajet typeTrajet = TypeTrajet::DEUX);

		bool sauvegarder (string url, string villeDepart, string villeArrivee);
		// Spécifier une ville de départ et / ou d'arrivée, pour un ou mettre la ville non desirée en null

		bool sauvegarder (string url, int debutIntervalle, int finIntervalle);

		virtual ~GestFichier();

	private:
		void EcrireTrajetSimple (TrajetSimple *unTrajetSimple);

		void EcrireTrajet (Trajet *unTrajet, TypeTrajet typeTrajet = TypeTrajet::DEUX);

		void EcrireMetaDonnees();

	private:
		Collection &m_collection;
};


#endif /* GESTFICHIER_H_ */
