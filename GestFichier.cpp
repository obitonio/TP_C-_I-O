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

		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());

		EcrireMetaDonnees();

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			EcrireTrajet(m_collection.GetTrajet(i), typeTrajet);
		}

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

		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());

		EcrireMetaDonnees();

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			Trajet * trajetCourant = m_collection.GetTrajet(i);

			// Pour ville départ
			if ( !villeDepart.empty() && villeDepart.compare(trajetCourant->GetVilleA()) == 0 )
			{
				if ( !villeArrivee.empty() ) // Vérif si ET ville arrivée
				{
					if ( villeArrivee.compare(trajetCourant->GetVilleB()) == 0 )
						EcrireTrajet(trajetCourant);
				}
				else
				{
					EcrireTrajet(trajetCourant);
				}
			}
			else
			{
				// Pour ville d'arrivée
				if ( !villeArrivee.empty() && villeArrivee.compare(trajetCourant->GetVilleB()) == 0 )
				{
					if ( !villeDepart.empty() ) // Verif di ET ville départ
					{
						if ( villeDepart.compare(trajetCourant->GetVilleA()) == 0 )
							EcrireTrajet(trajetCourant);
					}
					else
					{
						EcrireTrajet(trajetCourant);
					}
				}
			}
		}

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

		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());

		EcrireMetaDonnees();

		for (int i=0; i<m_collection.GetLongueur(); i++)
		{
			if ( (i + 1 ) >= debutIntervalle && (i + 1) <= finIntervalle)
				EcrireTrajet(m_collection.GetTrajet(i));
		}

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

void GestFichier::EcrireTrajetSimple(TrajetSimple *unTrajetSimple)
{
	cout << "VilleDepart: " << unTrajetSimple->GetVilleA() << endl;
	cout << "VilleArrivee: " << unTrajetSimple->GetVilleB() << endl;
	cout << "MoyenTansport: " << lesMoyensTransport[unTrajetSimple->GetMoyenTransport()] << endl;
}

void GestFichier::EcrireTrajet (Trajet *unTrajet, TypeTrajet typeTrajet)
{
	TrajetSimple *trajetSimple = dynamic_cast<TrajetSimple*> (unTrajet);

	if (trajetSimple != nullptr && (typeTrajet == TypeTrajet::SIMPLE || typeTrajet == TypeTrajet::DEUX) )
	{
		cout << "=====" << endl;
		EcrireTrajetSimple(trajetSimple);
		cout << endl;
	}
	else
	{
		TrajetCompose *trajetCompose = dynamic_cast<TrajetCompose*> (unTrajet);
		if (trajetCompose != nullptr && (typeTrajet == TypeTrajet::COMPOSE || typeTrajet == TypeTrajet::DEUX))
		{
			cout << "=====" << endl;
			for (int y=0; y<trajetCompose->GetLesTrajets()->GetLongueur(); y++)
			{
				TrajetSimple *tmp = dynamic_cast<TrajetSimple*> ( trajetCompose->GetLesTrajets()->GetTrajet(y) );
				EcrireTrajetSimple(tmp);
			}
			cout << endl;
		}
	}
}

void GestFichier::EcrireMetaDonnees()
{
	time_t t = time( 0 );

	cout << "Nombre de trajets: " << m_collection.GetLongueur() << endl;
	cout << "Critère de sauvegarde: complète" << endl;
	cout << "Date: " << ctime( &t ) << endl;
}

