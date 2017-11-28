//-----------Interface de la classe Collection (fichier Collection.h)---------
#ifndef COLLECTION_H
#define COLLECTION_H
//--------------------------------------------------------Interfaces utilisées
#include "Trajet.h"
//----------------------------------------------------------------------------
//classe TrajetCompose
//    Défini les methodes pour gérer des differents trajets
//----------------------------------------------------------------------------
class Collection
{
	public:
	//----------------------------------------------------------------- PUBLIC
		void Ajuster(int delta);
		//Mode d'emploi :
		//	Augmente la taille de la Collection en fonction du paramètre delta

		void Ajouter(Trajet *unTrajet);
		//Mode d'emploi :
		//	Ajoute un Trajet dans la Collection

		void Afficher(bool compose = false);
		//Mode d'emploi :
		//	Affiche tous les elements de la Collection
		//	Paramètre : compose indique si la collection doit être affichée
		//  comme un Trajet Composé

		void Chercher(char *villeDepart, char *villeArrive);
		//Mode d'emploi :
		//	Affiche tous les trajets possible avec comme départ le parametre
		// 	villeDepart et comme arrivee villeArrivee
		//	Paramètres : la ville de début et d'arrivee

		void ChercherAvancee(char *villeDepart, char *villeArrive);
		//Mode d'emploi :
		//	Cette recherche avancee cumule les Trajet (simple et composee) pour
		//	trouver un itineraire en fonction des parametres

		int GetLongueur();
		//Mode d'emploi :
		//	Retourne le nombre d'elements de la collection

		Trajet *GetTrajet(int index);
		//Mode d'emploi :
		//	Retourne le Trajet à l'index donné si il existe

		//-------------------------------------------- Constructeurs - destructeur
		Collection(int nbElements);
		//Mode d'emploi :
		//	Construit une Collection capable d'accueillir nbElments Trajet

		virtual ~Collection();
		//Mode d'emploi :
		//	Destructeur de Collection

	//-------------------------------------------------------------- PROTECTED
	protected:
		int m_max;
		int m_courant;
		Trajet **m_lesTrajets;
};
#endif /* COLLECTION_H */
