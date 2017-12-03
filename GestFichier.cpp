/*
 * GestFichier.cpp
 *
 *  Created on: 2 déc. 2017
 *      Author: amathat
 */

#include "GestFichier.h"
#include "TrajetCompose.h"
#include <fstream>

GestFichier::GestFichier(Collection &collection)
:m_collection(collection)
{
}

bool GestFichier::sauvegarder (string url, TypeTrajet typeTrajet)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();
		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			if (EcrireTrajet(m_collection.GetTrajet(i), texteAEcrire, typeTrajet))
				nbTrajets++;
		}

		CritereSauvegarde critereSauvegarde = (typeTrajet == TypeTrajet::DEUX)? CritereSauvegarde::COMPLETE : CritereSauvegarde::TYPE_TRAJETS;

		EcrireMetaDonnees(nbTrajets, critereSauvegarde);
		cout << texteAEcrire;

		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	else
		return false;

	return true;
}

bool GestFichier::sauvegarder (string url, string villeDepart, string villeArrivee)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();

		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			Trajet * trajetCourant = m_collection.GetTrajet(i);

			// Pour ville départ
			if ( !villeDepart.empty() && villeDepart.compare(trajetCourant->GetVilleA()) == 0 )
			{
				if ( !villeArrivee.empty() ) // Vérif si ET ville arrivée
				{
					if ( villeArrivee.compare(trajetCourant->GetVilleB()) == 0 )
						EcrireTrajet(trajetCourant, texteAEcrire);
				}
				else
				{
					EcrireTrajet(trajetCourant, texteAEcrire);
				}

				nbTrajets++;
			}
			else
			{
				// Pour ville d'arrivée
				if ( !villeArrivee.empty() && villeArrivee.compare(trajetCourant->GetVilleB()) == 0 )
				{
					if ( !villeDepart.empty() ) // Verif di ET ville départ
					{
						if ( villeDepart.compare(trajetCourant->GetVilleA()) == 0 )
							EcrireTrajet(trajetCourant, texteAEcrire);
					}
					else
					{
						EcrireTrajet(trajetCourant, texteAEcrire);
					}

					nbTrajets++;
				}
			}
		}

		EcrireMetaDonnees(nbTrajets, CritereSauvegarde::VILLE);
		cout << texteAEcrire;

		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	else
		return false;

	return true;
}

bool GestFichier::sauvegarder (string url, int debutIntervalle, int finIntervalle)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();

		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			if ( (i + 1 ) >= debutIntervalle && (i + 1) <= finIntervalle)
			{
				EcrireTrajet(m_collection.GetTrajet(i), texteAEcrire);
				nbTrajets++;
			}
		}

		EcrireMetaDonnees(nbTrajets, CritereSauvegarde::INTERVALLE);
		cout << texteAEcrire;

		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	else
		return false;

	return true;
}

GestFichier::~GestFichier()
{
}

void GestFichier::EcrireTrajetSimple(TrajetSimple *unTrajetSimple, string &texteAEcrire)
{
	texteAEcrire += "VilleDepart: " + string( unTrajetSimple->GetVilleA() ) + "\n";
	texteAEcrire += "VilleArrivee: " + string( unTrajetSimple->GetVilleB() ) + "\n";
	texteAEcrire += "MoyenTansport: " + string( lesMoyensTransport[unTrajetSimple->GetMoyenTransport()] ) + "\n";
}

bool GestFichier::EcrireTrajet (Trajet *unTrajet, string &texteAEcrire, TypeTrajet typeTrajet)
{
	bool resultat = false;
	TrajetSimple *trajetSimple = dynamic_cast<TrajetSimple*> (unTrajet);

	if (trajetSimple != nullptr && (typeTrajet == TypeTrajet::SIMPLE || typeTrajet == TypeTrajet::DEUX) )
	{
		texteAEcrire += "=====\n";
		EcrireTrajetSimple(trajetSimple, texteAEcrire);
		texteAEcrire += "\n";

		resultat = true;
	}
	else
	{
		TrajetCompose *trajetCompose = dynamic_cast<TrajetCompose*> (unTrajet);
		if (trajetCompose != nullptr && (typeTrajet == TypeTrajet::COMPOSE || typeTrajet == TypeTrajet::DEUX))
		{
			texteAEcrire += "=====\n";
			for (int y=0; y<trajetCompose->GetLesTrajets()->GetLongueur(); y++)
			{
				TrajetSimple *tmp = dynamic_cast<TrajetSimple*> ( trajetCompose->GetLesTrajets()->GetTrajet(y) );
				EcrireTrajetSimple(tmp, texteAEcrire);
			}
			texteAEcrire += "\n";

			resultat = true;
		}
	}

	return resultat;
}

void GestFichier::EcrireMetaDonnees(const int nbTrajets, const CritereSauvegarde critereSauvegarde)
{
	time_t t = time( 0 );

	cout << "Nombre de trajets: " << nbTrajets << "\n";
	cout << "Critère de sauvegarde: " << lesCriteresSauvegarde[critereSauvegarde] << "\n";
	cout << "Date: " << ctime( &t ) << "\n";
}

