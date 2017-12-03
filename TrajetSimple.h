//-----------------Interface de la classe <TrajetSimple> (ficher TrajetSimple.h)----------------
#if ! defined (TRAJETSIMPLE_H)
#define TRAJETSIMPLE_H

//---------------------------------------------------------------------------includes---
#include "Trajet.h"
//--------------------------------------------------------------------------Constants---

//-------------------------------------------------------------------------------Enum---

//--------------------------------------------------------------------------------------
//classe TrajetSimple
//    Défini les methodes des objets types TrajetSimple
//--------------------------------------------------------------------------------------
class TrajetSimple : public Trajet
{
  //---------------------------------------------------------------------------public---
  public:
    void Afficher (int n = -1, int nMax = -1);
    //Mode d'emploi :
    //  Afficher les informations d'un objet TrajetSimple
    //	Paramètres : n numéro du trajet à afficher, permet de savoir si c'est l'étape d'un Trajet Composé
    //				 nMax nombre de trajet qui seront affichés si c'est l'étape d'un Trajet Composé
    //Contrat : aucun

    const char * GetVilleA(void);
    //Mode d'emploi :
    //  Retourne la ville de depart du trajet
    //Contrat : aucun

    const char * GetVilleB(void);
    //Mode d'emploi :
    //  Retourne la ville d'arrivee du trajet
    //Contrat : aucun

    const MoyenTransport GetMoyenTransport(void);
    //Mode d'emploi :
    //  Retourne le moyen de transport du trajet simple
    //Contrat : aucun

  //--------------------------------------------------------------------constructeurs---
    TrajetSimple(const char * villeA, const char * villeB, MoyenTransport mt);
    //Mode d'emploi :
    //  Construit un TrajetSimple avec les noms de villes et le moyen de transport
    //Contrat : aucun

  //----------------------------------------------------------------------destructeur---
    virtual ~TrajetSimple();
    //Mode d'emploi :
    //  Detruit l'TrajetSimple existe
    //Contrat : aucun

  //----------------------------------------------------------------------------prive---
  protected:
    char * m_villeA; //ville de départ
    char * m_villeB; //ville d'arrive
    MoyenTransport m_mt; //moyen de transport

};
#endif // TRAJETSIMPLE_H
