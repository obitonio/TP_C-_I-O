//-----------------Interface de la classe <TrajetCompose> (ficher TrajetCompose.h)----------------
#if ! defined (TRAJETCOMPOSE_H)
#define TRAJETCOMPOSE_H
//---------------------------------------------------------------------------includes---
#include "Collection.h"

//--------------------------------------------------------------------------------------
//classe TrajetCompose
//    Défini les methodes des objets types TrajetCompose
//--------------------------------------------------------------------------------------
class TrajetCompose : public Trajet
{
  //---------------------------------------------------------------------------public---
  public:
    void Afficher (int n = -1, int nMax = -1);
    //Mode d'emploi :
    //  Afficher les informations d'objet type Trajet
    //	Paramètres : n numéro du trajet à afficher, permet de savoir si c'est l'étape d'un Trajet Composé
    //				 nMax nombre de trajet qui seront affichés si c'est l'étape d'un Trajet Composé
    //Contrat : aucun

    void Ajouter(Trajet *unTrajet);
    //Mode d'emploi :
    //  Cette méthode permet d'ajouter un Trajet au TrajetCompose
    //Contrat : aucun

    const char * GetVilleA(void);
    //Mode d'emploi :
    // Retourne la ville de Départ du premier Trajet du TrajetCompose
    //Contrat : aucun

    const char * GetVilleB(void);
    //Mode d'emploi :
    //  Retourne la ville d'arrivee du dernier Trajet du TrajetCompose
    //Contrat : aucun

    Collection* GetLesTrajets();
    //Mode d'emploi :
	// Retourne la collection de Trajets
	//Contrat : aucun

  //--------------------------------------------------------------------constructeurs
    TrajetCompose(int nbElements = 0);
    //Mode d'emploi :
    //  Construit un TrajetCompose avec nombre d'element (de Trajet)
    //Contrat : aucun

    TrajetCompose(Collection * laCollection);
    //Mode d'emploi :
    //  Construit un TrajetCompose à partir d'une Collection
    //Contrat : aucun

  //----------------------------------------------------------------------destructeur---
    virtual ~TrajetCompose();
    //Mode d'emploi :
    //  Destructeur de TrajetCompose
    //Contrat : aucun
  //----------------------------------------------------------------------------prive---
  protected:
    Collection *m_laCollection;//la collection des trajets
    int m_nbElements; //nombre d'elements dans la collection;
    const char *m_villeA;//ville de départ
    const char *m_villeB;//ville destinataire
    int m_nbActu;//nombre d'élement saisi actuellement
};
#endif // TRAJETCOMPOSE_H
