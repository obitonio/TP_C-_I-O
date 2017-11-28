//-----Interface de la classe <TrajetCompose> (ficher TrajetCompose.h)--------
#if ! defined (TRAJETCOMPOSE_H)
#define TRAJETCOMPOSE_H
//------------------------------------------------------- Interfaces utilisées
#include "Collection.h"
//----------------------------------------------------------------------------
//classe TrajetCompose
//  Défini les methodes concernant l'affichage d'un trajet composé et la
//  gestion du trajet
//----------------------------------------------------------------------------
class TrajetCompose : public Trajet
{
    public:
    //----------------------------------------------------- Méthodes publiques
        void Afficher (int n = -1, int nMax = -1);
        //Mode d'emploi :
        //  Afficher les informations d'objet type Trajet
        //Paramètres : n numéro du trajet à afficher, permet de savoir si
        //  c'est l'étape d'un Trajet Composé nMax nombre de trajet qui
        //  seront affichés si c'est l'étape d'un Trajet Composé

        void Ajouter(Trajet *unTrajet);
        //Mode d'emploi :
        //  Cette méthode permet d'ajouter un Trajet au TrajetCompose

        const char * GetVilleA(void);
        //Mode d'emploi :
        // Retourne la ville de Départ du premier Trajet du TrajetCompose

        const char * GetVilleB(void);
        //Mode d'emploi :
        //  Retourne la ville d'arrivee du dernier Trajet du TrajetCompose

    //-------------------------------------------- Constructeurs - destructeur
        TrajetCompose(int nbElements = 0);
        //Mode d'emploi :
        //  Construit un TrajetCompose avec nombre d'element (de Trajet)

        TrajetCompose(Collection * laCollection);
        //Mode d'emploi :
        //  Construit un TrajetCompose à partir d'une Collection

        virtual ~TrajetCompose();
        //Mode d'emploi :
        //  Destructeur de TrajetCompose

    protected:
    //---------------------------------------------------- Attributs protégées
        Collection *m_laCollection;//la collection des trajets
        int m_nbElements; //nombre d'elements dans la collection;
        const char *m_villeA;//ville de départ
        const char *m_villeB;//ville destinataire
        int m_nbActu;//nombre d'élement saisi actuellement
};
#endif // TRAJETCOMPOSE_H
