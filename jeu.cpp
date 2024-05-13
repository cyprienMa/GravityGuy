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
    initRandom();

    // ######## NIVEAU 1 ########//

    //Créaction de la première phase obstacles, les triangles
    //On s'assure que les obstacles ne se superposent pas
    float delta_t_12 = (w + (n_obstacle-1)*300)/vitesse;
    float d_min_12 = (v2-vitesse)*delta_t_12;

    T[0].set(0, w);
    for(int i=1; i<n_obstacle; i++){
        int coef = intRandom(150,300);
        T[i].set(0, T[i-1].center_1(0) + coef);
    }

    //Création de la seconde phase d'obstacles, les losanges
    T[n_obstacle].set(0, T[n_obstacle -1].center_1(0) + d_min_12);
    for(int i=n_obstacle+1; i<2*n_obstacle; i++){
        int coef = intRandom(150,300);
        T[i].set(0, T[i-1].center_2(0) + coef);
    }

    //Création de la troisième phase d'obstacles, les cercles
    //On s'assure que les obstacles ne se superposent pas
    float delta_t_23 = w/v2 + (n_obstacle-1)*300/v2 + d_min_12/v2 + (n_obstacle-1)*300/v2;
    float d_min_23 = (v3-v2)*delta_t_23;

    T[2*n_obstacle].set(0, T[2*n_obstacle -1].center_2(0) + d_min_23);
    for(int i=2*n_obstacle+1; i<3*n_obstacle; i++){
        int coef = intRandom(150,300);
        T[i].set(0, T[i-1].center_3(0) + coef);
    }
}
void jeu::dessin(int t) const {
    noRefreshBegin();
    clearWindow();

    //On dessine l'obstacle_1 (Triangles)
    for(int i=0; i< n_obstacle; i++){
        drawLine(T[i].center_1(t), h-h_obstacle, T[i].center_1(t)+h_obstacle/sqrt(3), h, ORANGE, 3);
        drawLine(T[i].center_1(t)+h_obstacle/sqrt(3), h, T[i].center_1(t)-h_obstacle/sqrt(3), h, ORANGE, 3);
        drawLine(T[i].center_1(t)-h_obstacle/sqrt(3), h, T[i].center_1(t), h-h_obstacle, ORANGE, 3);
    }

    //On dessine les obstacles de la phase 2 (Losanges)
    for(int i=n_obstacle; i< 2*n_obstacle; i++){
        drawLine(T[i].center_2(t), h-h_obstacle, T[i].center_2(t)+h_obstacle/2, h-h_obstacle/2, RED, 3);
        drawLine(T[i].center_2(t)+h_obstacle/2, h-h_obstacle/2, T[i].center_2(t), h, RED, 3);
        drawLine(T[i].center_2(t), h, T[i].center_2(t)-h_obstacle/2, h-h_obstacle/2, RED,3);
        drawLine(T[i].center_2(t)-h_obstacle/2, h-h_obstacle/2, T[i].center_2(t), h-h_obstacle, RED, 3);
    }

    //On dessine les obstacles de la phase 3 (Cercles)
        for(int i=2*n_obstacle; i< 3*n_obstacle; i++){
            fillCircle(T[i].center_3(t), h-h_obstacle/2, h_obstacle/2, BLUE);
        }

    //On dessine le guy
    fillRect(xGuy, guy.hauteur(t), wGuy, hGuy, PURPLE);
    noRefreshEnd();
}

//Si le Guy n'est pas en train de sauter, et si l'utilisateur appuie sur espace, faire sauter le Guy
void jeu::action(int t) {
    if(! guy.check_saut(t)) {
        int key = keyboard();
        if(key == ' ') {
            guy.saut(t);
        }

        if(key == 'g'){
            guy.switch_gravity(t);
        }
    }
}

