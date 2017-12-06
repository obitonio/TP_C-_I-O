#ifndef GESTFICHIER_H_
#define GESTFICHIER_H_

#include <iostream>
#include "Collection.h"
#include "TrajetSimple.h"

using namespace std;

enum TypeTrajet
{
	SIMPLE,
	COMPOSE,
	DEUX
};

enum CritereSauvegarde
{
	COMPLETE,
	TYPE_TRAJETS,
	VILLE,
	INTERVALLE
};

const string lesCriteresSauvegarde[] = {"sans critère de selection", "selon le type des trajets", "selon la ville de départ et / ou d'arrivée", "selon une selection de trajets"};

class GestFichier
{
public:
	bool charger(string url, TypeTrajet typeTrajet = TypeTrajet::DEUX);
	// Mode d'emploi :
	//	Cette méthode permet de charger la collection à partir d'un fichier selon le type de Trajet
	//	(SIMPLE pour les trajets simples, COMPOSE pour les trajets composes, DEUX pour tous les trajets)
	// Parametres:
	// url : nom du fichier de sauvegarde
	// 	typeTrajet : type des trajets à sauvegarder, par défaut les deux

	bool charger(string url, string villeDepart, string villeArrivee);
	// Mode d'emploi :
	//	Cette méthode permet de charger la collection à partir d'un fichier selon le ville de départ et/ou la ville d'arrivée
	// Paramètres :
	//	url : nom du fichier de sauvegarde
	//	villeDepart : ville de départ que les trajets à sauvegarder doivent respecter ou "" pour s'abstenir du paramètre
	//	villeArrivee : ville de d'arrivée que les trajets à sauvegardrr doivent respecter ou "" pour s'abstenir du paramètre

	bool charger(string url, int debutIntervalle, int finIntervalle);
	// Mode d'emploi :	
	//	Cette méthode permet de charger la collection à partir d'un fichier, les trajets qui ont des indices entre l'intervalle donné
	// Paramètres :
	//	url : nom du fichier de sauvegarde
	//	debutIntervalle : début n de l'intervalle
	//	finIntervalle : fin m de l'intervalle

	bool sauvegarder(string url, TypeTrajet typeTrajet = TypeTrajet::DEUX);
	// Mode d'emploi :
	// 	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
	// 	Il est possible de choisir le type des trajets à sauvegarder (par défaut les deux) via le paramètre typeTrajet.
	// 	Si existant le fichier est vidé pour être remplacé par la sauvegarde.
	// Paramètres :
	// 	url : nom du fichier de sauvegarde
	// 	typeTrajet : type des trajets à sauvegarder, par défaut les deux

	bool sauvegarder(string url, string villeDepart, string villeArrivee);
	// Mode d'emploi :
	//	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
	//	Les trajets sauvegardés respecteront la ville de départ et / ou la ville d'arrivée fournit en paramètres.
	// Paramètres :
	//	url : nom du fichier de sauvegarde
	//	villeDepart : ville de départ que les trajets à sauvegarder doivent respecter ou "" pour s'abstenir du paramètre
	//	villeArrivee : ville de d'arrivée que les trajets à sauvegardrr doivent respecter ou "" pour s'abstenir du paramètre

	bool sauvegarder(string url, int debutIntervalle, int finIntervalle);
	// Mode d'emploi :
	//	Cette méthode permet de sauvegarder la collection de trajets (initialisée dans le constructeur) dans le fichier spécifié en paramètre.
	//	La sauvegarde s'effectue en respectant l'intervalle donné, du trajet n au trajet m.
	// Paramètres :
	//	url : nom du fichier de sauvegarde
	//	debutIntervalle : début n de l'intervalle
	//	finIntervalle : fin m de l'intervalle
	
	GestFichier(Collection &collection);
	// Mode d'emploi :
	// 	Constructeur de la classe GestFichier.
	// 	Initialise la collection sur laquelle les fonctions de la classe seront amenées à travailler.
	// Paramètres :
	// 	collection : la collection à sauvegarder pour effectuer les traitements de savegarde / chargement

	virtual ~GestFichier();
	// Mode d'emploi :
	//	Destructeur de la classe

private:
	void EcrireTrajetSimple(TrajetSimple *unTrajetSimple, string &texteAEcrire);
	// Mode d'emploi :
	//	Ecrit la ville de départ et d'arrivé ainsi que le moyen de transport d'un trajet sur la référence donnée en paramètre.
	// Paramètres :
	//	unTrajetSimple : le trajet à écrire
	//	texteAEcrire : le texte sur lequel ajouté le trajet

	bool EcrireTrajet(Trajet *unTrajet, string &texteAEcrire, TypeTrajet typeTrajet = TypeTrajet::DEUX);
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

	void chargerTrajetSimple(ifstream &fic);
	// Mode d'emploi :
	// 	Lecture d'un trajet simple depuis le fichier commandé
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier
	
	void chargerTrajetCompose(ifstream &fic);
	// Mode d'emploi :
	// 	Lecture d'un trajet composé depuis le fichier commandé
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	string getPropriete(ifstream &fic);
	// Mode d'emploi :
	// 	Extrait des données utiles de la ligne actuelle
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	bool isBorne(ifstream &fic);
	// Mode d'emploi :
	// 	Tester si la ligner actuelle contient la marque "=====" qui est un séparateur du trajet
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	bool isFinTrajet(ifstream &fic);
	// Mode d'emploi :
	// 	Tester si la ligner actuelle est la marque de fin du trajet
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	int getNbTrajet(ifstream &fic);
	// Mode d'emploi :
	// 	Doit être appeler au début de la lecture du ficher, renvoyer le numbre total des trajets enregistrés
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	int getType(ifstream &fic);
	// Mode d'emploi :
	// 	Doit être appeler juste après avoir valider isBorne(fic), renvoyer le type du trajet
	//	(1 pour trajet simple, 2 pour trajet composé)
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	string getVille(ifstream &fic);
	// Mode d'emploi :
	// 	Envoyer le nom de la ville
	//	### warning### il faut respecter l'ordre d'appel, ville -> ville -> moyen transport ####
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

	MoyenTransport getMoyenTransport(ifstream &fic);
	// Mode d'emploi :
	// 	Renvoyer le moyen de transport 
	// Paramètre :
	//	fic : flux d'entrée de la lecture du fichier

private:
	Collection &m_collection; // Collection de trajets à partir de laquelle effectuer les sauvegardes / restauration
};

#endif /* GESTFICHIER_H_ */
