#include"jeu.h"
#include"Guy.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

//Fonction keyboard
int keyboard() {
    Event e;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON)
            return e.key;
    } while(e.type!=EVT_NONE);
    return 0;
}

//Initialisation du jeu
jeu::jeu(){
    //On initialise la liste des premiers obstacles, les triangles (ils sont en dehors de la fenêtre)
    for(int i=0; i<n_obstacle; i++)
        T[i].set(0,w+2*i*t_saut*vitesse);
}
void jeu::dessin(int t) const {
    noRefreshBegin();
    clearWindow();

    //On dessine l'obstacle_1 (Triangles)
    for(int i=0; i< n_obstacle; i++){
        drawLine(T[i].center(t), h-h_obstacle, T[i].center(t)+h_obstacle/sqrt(3), h, ORANGE, 3);
        drawLine(T[i].center(t)+h_obstacle/sqrt(3), h, T[i].center(t)-h_obstacle/sqrt(3), h, ORANGE, 3);
        drawLine(T[i].center(t)-h_obstacle/sqrt(3), h, T[i].center(t), h-h_obstacle, ORANGE, 3);
    }

    //On dessine le guy
    fillRect(xGuy, h-hGuy-guy.hauteur(t), wGuy, hGuy, PURPLE);
    noRefreshEnd();
}

//Si le Guy n'est pas en train de sauter, et si l'utilisateur appuie sur espace, faire sauter le Guy
void jeu::action(int t) {
    if(! guy.check_saut(t)) {
        int key = keyboard();
        if(key == ' ') {
            guy.saut(t);
        }
    }
}

