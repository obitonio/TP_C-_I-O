//-------------Interface de la classe <Trajet> (ficher Trajet.h)--------------
#if ! defined (TRAJET_H)
#define TRAJET_H
//----------------------------------------------------------------------- ENUM
enum MoyenTransport
{
  AUTOCAR, TRAIN, BATEAU, AVION
};
//----------------------------------------------------------------------------
//classe Trajet
//    Définir les methodes des objets types Trajet
//----------------------------------------------------------------------------
class Trajet
{
    //----------------------------------------------------- Méthodes publiques
    public:
        virtual void Afficher (int n = -1, int nMax = -1);
        //Mode d'emploi :
        //  Afficher les informations d'objet type TrajetSimple
        //Paramètres : n numéro du trajet à afficher, permet de savoir si
        //  c'est l'étape d'un Trajet Composé nMax nombre de trajet qui
        //  seront affichés si c'est l'étape d'un Trajet Composé

        virtual const char * GetVilleA(void);
        //Mode d'emploi :
        //  Retourne la ville de départ

        virtual const char * GetVilleB(void);
        //Mode d'emploi :
        //  Retourne la ville d'arrivee

    //-------------------------------------------- Constructeurs - destructeur
        Trajet();
        //Mode d'emploi :
        //  Construit un Trajet

        virtual ~Trajet();
        //Mode d'emploi :
        //  Detruit le Trajet existant
};
#endif // TRAJET_H
