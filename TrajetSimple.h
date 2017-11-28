//------Interface de la classe <TrajetSimple> (ficher TrajetSimple.h)---------
#if ! defined (TRAJETSIMPLE_H)
#define TRAJETSIMPLE_H
//------------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//----------------------------------------------------------------------------
//classe TrajetSimple
//    Défini les methodes pour afficher le trajet simple et gerer ce trajet
//----------------------------------------------------------------------------
class TrajetSimple : public Trajet
{
    //----------------------------------------------------- Méthodes publiques
    public:
        void Afficher (int n = -1, int nMax = -1);
        //Mode d'emploi :
        //  Afficher les informations d'un objet TrajetSimple
        //Paramètres : n numéro du trajet à afficher, permet de savoir si
        //  c'est l'étape d'un Trajet Composé nMax nombre de trajet qui
        //  seront affichés si c'est l'étape d'un Trajet Composé

        const char * GetVilleA(void);
        //Mode d'emploi :
        //  Retourne la ville de depart du trajet

        const char * GetVilleB(void);
        //Mode d'emploi :
        //  Retourne la ville d'arrivee du trajet

    //-------------------------------------------- Constructeurs - destructeur
        TrajetSimple(const char * villeA, const char * villeB, MoyenTransport mt);
        //Mode d'emploi :
        //  Construit un TrajetSimple avec les noms de villes et le moyen de
        //  transport

        virtual ~TrajetSimple();
        //Mode d'emploi :
        //  Detruit l'TrajetSimple existe


    protected:
    //---------------------------------------------------- Attributs protégées
        char * m_villeA; //ville de départ
        char * m_villeB; //ville d'arrive
        MoyenTransport m_mt; //moyen de transport

};
#endif // TRAJETSIMPLE_H
