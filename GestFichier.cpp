#include <fstream>
#include <cstring>
#include "GestFichier.h"
#include "TrajetCompose.h"

bool GestFichier::charger(string url, TypeTrajet typeTrajet){
	Trajet *newTrajet;
	ifstream fic(url);
	if ((fic.rdstate() & ifstream::failbit) != 0)
	{
		cerr << "Erreur d'ouverture de <" << url << ">" << endl;
		return false;
	}
	else
	{
		while (!fic.eof())
		{
			if (isBorne(fic))
			{
				int type = getType(fic);
				if (type == 1)
				{
					if(typeTrajet != COMPOSE){
						chargerTrajetSimple(fic);
					}else{
						while(!isFinTrajet(fic));
					}
				}
				else if (type == 2)
				{
					if(typeTrajet != SIMPLE){
						chargerTrajetCompose(fic);
					}else{
						while (!isFinTrajet(fic));
					}
				}else{
					cerr << "type du trajet non connu" << endl;
				}
			}
		}
		fic.close();
		return true;
	}
}

bool GestFichier::charger(string url, string villeDepart, string villeArrivee){
	Trajet *newTrajet;
	ifstream fic(url);
	if ((fic.rdstate() & ifstream::failbit) != 0)
	{
		cerr << "Erreur d'ouverture de <" << url << ">" << endl;
		return false;
	}
	else
	{
		while (!fic.eof())
		{
			if (isBorne(fic))
			{
				int type = getType(fic);
				if (type == 1)
				{
					char villeA[50];
					char villeB[50];
					strcpy(villeA, getVille(fic).c_str());
					strcpy(villeB, getVille(fic).c_str());
					MoyenTransport mt = getMoyenTransport(fic);
					Trajet *newTrajet = new TrajetSimple(villeA, villeB, mt);
					if (villeDepart.empty()){
						if (strcmp(villeArrivee.c_str(), newTrajet->GetVilleB()) != 0)
						{
							delete newTrajet;
						}else{
							m_collection.Ajouter(newTrajet);
						}
					}else{
						if (strcmp(villeDepart.c_str(), newTrajet->GetVilleA()) != 0)
						{
							delete newTrajet;
						}else{
							if (!villeArrivee.empty()){
								if ((strcmp(villeArrivee.c_str(), newTrajet->GetVilleB()) != 0)){
									delete newTrajet;
								}else{
									m_collection.Ajouter(newTrajet);
								}
							}else{
								m_collection.Ajouter(newTrajet);
							}
						}
					}
				}
				else if (type == 2)
				{
					char villeA[50];
					char villeB[50];
					Collection *tc = new Collection(100);
					strcpy(villeA, getVille(fic).c_str());
					strcpy(villeB, getVille(fic).c_str());
					MoyenTransport mt = getMoyenTransport(fic);
					Trajet *trajet = new TrajetSimple(villeA, villeB, mt);
					tc->Ajouter(trajet);
					while (!isFinTrajet(fic))
					{
						strcpy(villeA, getVille(fic).c_str());
						strcpy(villeB, getVille(fic).c_str());
						MoyenTransport mt = getMoyenTransport(fic);
						Trajet *trajet = new TrajetSimple(villeA, villeB, mt);
						tc->Ajouter(trajet);
					}
					Trajet *newTrajet = new TrajetCompose(tc);
					if (villeDepart.empty())
					{
						if (strcmp(villeArrivee.c_str(), newTrajet->GetVilleB()) != 0)
						{
							delete newTrajet;
						}
						else
						{
							m_collection.Ajouter(newTrajet);
						}
					}
					else
					{
						if (strcmp(villeDepart.c_str(), newTrajet->GetVilleA()) != 0)
						{
							delete newTrajet;
						}
						else
						{
							if (!villeArrivee.empty())
							{
								if ((strcmp(villeArrivee.c_str(), newTrajet->GetVilleB()) != 0))
								{
									delete newTrajet;
								}
								else
								{
									m_collection.Ajouter(newTrajet);
								}
							}
							else
							{
								m_collection.Ajouter(newTrajet);
							}
						}
					}
				}
				else
				{
					cerr << "type du trajet non connu" << endl;
				}
			}
		}
		fic.close();
		return true;
	}
}

bool GestFichier::charger(string url, int debutIntervalle, int finIntervalle){
	int nbTrajet = 0;
	Trajet *newTrajet;
	ifstream fic(url);
	if ((fic.rdstate() & ifstream::failbit) != 0)
	{
		cerr << "Erreur d'ouverture de <" << url << ">" << endl;
		return false;
	}
	else
	{
		if(finIntervalle <= getNbTrajet(fic)){
			while (!fic.eof())
			{
				if (isBorne(fic))
				{
					int type = getType(fic);
					nbTrajet++;
					if ((nbTrajet >= debutIntervalle) && (nbTrajet <= finIntervalle))
					{
						if (type == 1)
						{
							chargerTrajetSimple(fic);
						}
						else if (type == 2)
						{
							chargerTrajetCompose(fic);
						}
						else
						{
							cerr << "type du trajet non connu" << endl;
						}
					}else{
						while(!isFinTrajet(fic));
					}
				}
			}
			fic.close();
			return true;
		}else{
			fic.close();
			cerr << "index overflow" << endl;
			return false;
		}
	}
}

bool GestFichier::sauvegarder(string url, TypeTrajet typeTrajet)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();
		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i = 0; i < m_collection.GetLongueur(); i++)
		{
			if (EcrireTrajet(m_collection.GetTrajet(i), texteAEcrire, typeTrajet))
				nbTrajets++;
		}

		CritereSauvegarde critereSauvegarde = (typeTrajet == TypeTrajet::DEUX) ? CritereSauvegarde::COMPLETE : CritereSauvegarde::TYPE_TRAJETS;

		EcrireMetaDonnees(nbTrajets, critereSauvegarde);
		cout << texteAEcrire;

		cout.rdbuf(oldCoutBuffer);
		fic.close();
	}
	else
		return false;

	return true;
}

bool GestFichier::sauvegarder(string url, string villeDepart, string villeArrivee)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();

		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i = 0; i < m_collection.GetLongueur(); i++)
		{
			Trajet *trajetCourant = m_collection.GetTrajet(i);

			// Pour ville départ
			if (!villeDepart.empty() && villeDepart.compare(trajetCourant->GetVilleA()) == 0)
			{
				if (!villeArrivee.empty()) // Vérif si ET ville arrivée
				{
					if (villeArrivee.compare(trajetCourant->GetVilleB()) == 0)
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
				if (!villeArrivee.empty() && villeArrivee.compare(trajetCourant->GetVilleB()) == 0)
				{
					if (!villeDepart.empty()) // Verif di ET ville départ
					{
						if (villeDepart.compare(trajetCourant->GetVilleA()) == 0)
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

bool GestFichier::sauvegarder(string url, int debutIntervalle, int finIntervalle)
{
	ofstream fic(url);

	if (fic)
	{
		fic.clear();

		string texteAEcrire = "";
		streambuf *oldCoutBuffer = cout.rdbuf(fic.rdbuf());
		int nbTrajets = 0;

		for (int i = 0; i < m_collection.GetLongueur(); i++)
		{
			if ((i + 1) >= debutIntervalle && (i + 1) <= finIntervalle)
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

GestFichier::GestFichier(Collection &collection)
		: m_collection(collection)
{
	#if defined (MAP)
		cout << "Appel constructeur [ GestFichier ]" << endl;
	#endif
}

GestFichier::~GestFichier()
{
	#if defined (MAP)
	cout << "Appel destructeur [ GestFichier ]" << endl;
	#endif
}

void GestFichier::EcrireTrajetSimple(TrajetSimple *unTrajetSimple, string &texteAEcrire)
{
	texteAEcrire += "VilleDepart: " + string(unTrajetSimple->GetVilleA()) + "\n";
	texteAEcrire += "VilleArrivee: " + string(unTrajetSimple->GetVilleB()) + "\n";
	texteAEcrire += "MoyenTansport: " + string(lesMoyensTransport[unTrajetSimple->GetMoyenTransport()]) + "\n";
}

bool GestFichier::EcrireTrajet(Trajet *unTrajet, string &texteAEcrire, TypeTrajet typeTrajet)
{
	bool resultat = false;
	TrajetSimple *trajetSimple = dynamic_cast<TrajetSimple *>(unTrajet);

	if (trajetSimple != nullptr && (typeTrajet == TypeTrajet::SIMPLE || typeTrajet == TypeTrajet::DEUX))
	{
		texteAEcrire += "=====\n";
		texteAEcrire += "Type: TS\n";
		EcrireTrajetSimple(trajetSimple, texteAEcrire);
		texteAEcrire += "\n";

		resultat = true;
	}
	else
	{
		TrajetCompose *trajetCompose = dynamic_cast<TrajetCompose *>(unTrajet);
		if (trajetCompose != nullptr && (typeTrajet == TypeTrajet::COMPOSE || typeTrajet == TypeTrajet::DEUX))
		{
			texteAEcrire += "=====\n";
			texteAEcrire += "Type: TC\n";
			for (int y = 0; y < trajetCompose->GetLesTrajets()->GetLongueur(); y++)
			{
				TrajetSimple *tmp = dynamic_cast<TrajetSimple *>(trajetCompose->GetLesTrajets()->GetTrajet(y));
				EcrireTrajetSimple(tmp, texteAEcrire);
				if (y < trajetCompose->GetLesTrajets()->GetLongueur() - 1)
					texteAEcrire += "-----\n";
			}
			texteAEcrire += "\n";

			resultat = true;
		}
	}

	return resultat;
}

void GestFichier::EcrireMetaDonnees(const int nbTrajets, const CritereSauvegarde critereSauvegarde)
{
	time_t t = time(0);

	cout << "Nombre de trajets: " << nbTrajets << "\n";
	cout << "Critère de sauvegarde: " << lesCriteresSauvegarde[critereSauvegarde] << "\n";
	cout << "Date: " << ctime(&t) << "\n";
}

void GestFichier::chargerTrajetSimple(ifstream &fic){
	char villeA[50];
	char villeB[50];
	strcpy(villeA, getVille(fic).c_str());
	strcpy(villeB, getVille(fic).c_str());
	MoyenTransport mt = getMoyenTransport(fic);
	Trajet *newTrajet = new TrajetSimple(villeA, villeB, mt);
	m_collection.Ajouter(newTrajet);
}

void GestFichier::chargerTrajetCompose(ifstream &fic){
	char villeA[50];
	char villeB[50];
	Collection *tc = new Collection(100);
	strcpy(villeA, getVille(fic).c_str());
	strcpy(villeB, getVille(fic).c_str());
	MoyenTransport mt = getMoyenTransport(fic);
	Trajet *trajet = new TrajetSimple(villeA, villeB, mt);
	tc->Ajouter(trajet);
	while (!isFinTrajet(fic))
	{
		strcpy(villeA, getVille(fic).c_str());
		strcpy(villeB, getVille(fic).c_str());
		MoyenTransport mt = getMoyenTransport(fic);
		Trajet *trajet = new TrajetSimple(villeA, villeB, mt);
		tc->Ajouter(trajet);
	}
	Trajet *newTrajet = new TrajetCompose(tc);
	m_collection.Ajouter(newTrajet);
}

string GestFichier::getPropriete(ifstream &fic)
{
	string text;
	getline(fic, text);
	string subText = text.substr(text.find(":") + 2, text.find("\n") - 1);
	return subText;
}

bool GestFichier::isBorne(ifstream &fic)
{
	string text;
	getline(fic, text);
	//cout << "isBorne : " << text << endl;
	if (text.compare("=====") != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GestFichier::isFinTrajet(ifstream &fic)
{
	string text;
	getline(fic, text);
	//cout << "isFinTrajet : " << text << endl;
	if (text.compare("-----") == 0)
	{
		return false;
	}
	else if (text.compare("") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int GestFichier::getNbTrajet(ifstream & fic)
{
	string nbTrajet = getPropriete(fic);
	//cout << "getNbTrajet : " << nbTrajet << endl;
	return stoi(nbTrajet.c_str());
}

int GestFichier::getType(ifstream &fic)
{
	string type = getPropriete(fic);
	//cout << "getType : " << type << endl;
	if (type.compare("TS") == 0)
	{
		return 1;
	}
	else if (type.compare("TC") == 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

string GestFichier::getVille(ifstream &fic)
{
	string ville = getPropriete(fic);
	//cout << "getVille : " << ville << endl;
	return ville;
}

MoyenTransport GestFichier::getMoyenTransport(ifstream &fic)
{
	MoyenTransport mt = AUTOCAR;
	string transport = getPropriete(fic);
	//cout << "getMoyenTransport : " << transport << endl;
	if (transport.compare("AUTOCAR") == 0)
	{
		mt = AUTOCAR;
	}
	else if (transport.compare("TRAIN") == 0)
	{
		mt = TRAIN;
	}
	else if (transport.compare("BATEAU") == 0)
	{
		mt = BATEAU;
	}
	else if (transport.compare("AVION") == 0)
	{
		mt = AVION;
	}
	else
	{
		cerr << "Moyen de transport inconnu (forcer sur la valeur par défaut AUTOCAR)" << endl;
	}
	return mt;
}