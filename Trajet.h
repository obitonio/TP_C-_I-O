//-----------------Interface de la classe <Trajet> (ficher Trajet.h)----------------
#if ! defined (TRAJET_H)
#define TRAJET_H
//-------------------------------------------------------------------------------Enum---
enum MoyenTransport
{
  AUTOCAR, TRAIN, BATEAU, AVION
};

const static char* const lesMoyensTransport[] = {"AUTOCAR", "TRAIN", "BATEAU", "AVION"};

//--------------------------------------------------------------------------------------
//classe Trajet
//    Défini les methodes des objets types Trajet
//--------------------------------------------------------------------------------------
class Trajet
{
  //---------------------------------------------------------------------------public---
  public:
    virtual void Afficher (int n = -1, int nMax = -1);
    //Mode d'emploi :
    //  Afficher les informations d'objet type TrajetSimple
    //	Paramètres : n numéro du trajet à afficher, permet de savoir si c'est l'étape d'un Trajet Composé
    //				 nMax nombre de trajet qui seront affichés si c'est l'étape d'un Trajet Composé
    //Contrat : aucun

    virtual const char * GetVilleA(void);
    //Mode d'emploi :
    //  Retourne la ville de départ
    //Contrat : aucun

    virtual const char * GetVilleB(void);
    //Mode d'emploi :
    //  Retourne la ville d'arrivee
    //Contrat : aucun

  //--------------------------------------------------------------------constructeurs---
  Trajet();
  //Mode d'emploi :
  //  Construit un Trajet
  //Contrat : aucun

  //----------------------------------------------------------------------destructeur---
  virtual ~Trajet();
  //Mode d'emploi :
  //  Detruit le Trajet existant
  //Contrat : aucun

};
#endif // TRAJET_H
