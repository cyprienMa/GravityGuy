#include "Guy.h"
#include "jeu.h"
#include <Imagine/Graphics.h>
#include <algorithm>
using namespace Imagine;

//On initialise un Guy au sol
Guy::Guy() {
    t = -t_saut;
    ts = -t_gravity;
    state = true;
    previous_state = true;
}

//On actualise la valeur de t quand le Guy saute
void Guy::saut(int t0) {
    t = t0;
}

//On vérifie si le Guy est en train de sauter
bool Guy::check_saut(int t0) const {
    return t<=t0 && t0<=t+t_saut;
}

//Si le guy est sol "state = true". S'il est au plafond "state = false"
void Guy::switch_gravity(int t0) {
    ts = t0;
    previous_state = state;
    state = !state;
}

//On vérifie que le guy n'est pas en train de changer d'état
bool Guy::check_gravity(int t0) const {
    return ts<=t0 && t0<=ts+t_gravity;
}

//Si le Guy est en train de sauter, alors on calcule sa hauteur
float Guy::hauteur_1(int t0) const {
    float H;
    if(check_saut(t0)) {
        if (state){
            float x = 1-2*(t0-t)/(float)t_saut;  //La trajectoire du Guy suit une parabole ce qui nous donne sa hauteur
            H = h - h_saut*(1-x*x) - hGuy - e_b;
        }

        if (!state){
            float x = 1-2*(t0-t)/(float)t_saut;  //La trajectoire du Guy suit une parabole ce qui nous donne sa hauteur
            H = h_saut*(1-x*x) + e_h;
        }
    }
    else{
        if(check_gravity(t0)) {
                    if (previous_state){
                        H = (hGuy-h+e_h+e_b)*t0/(float)t_gravity + e_h - (hGuy-h+e_h+e_b)*(1+ts/(float)t_gravity);
                    }

                    else{
                        H = (h-hGuy-e_h-e_b)*t0/(float)t_gravity - (h-hGuy-e_h-e_b)*(1+ts/(float)t_gravity) + (h-hGuy-e_b);
                    }
                }

        else {
            if (state){
                H = h - hGuy - e_b;
            }

            else{
                H = e_h;
            }
        }
    }
    return H;
}

bool Guy::check_state(int t0) const{
    return state;
}

void obstacle::set(int t, int x) {
    tInit=t;
    xInit=x;
}


//On initialise les paramètres de l'obstacle: t=0 et x=10001
obstacle::obstacle() {
    set(0, 1000);
}

//Renvoie le centre de l'obstacle de la première phase
int obstacle:: center_1(int t) const {
    return xInit-(t-tInit)*vitesse;
}

//Renvoie le centre de l'obstacle de la seconde phase
int obstacle::center_2(int t) const {
    return xInit-(t-tInit)*v2;
}

//Renvoie le centre de l'obstacle de la troisième phase
int obstacle::center_3(int t) const {
    return xInit-(t-tInit)*v3;
}

bool Guy::collision(const obstacle t[n_obstacle*4], int t0) const {
    //Collision avec les triangles et le plafond
    for (int i = 0; i < n_obstacle; i++){
        if ((float(abs(xGuy+wGuy-t[i].center_1(t0))) < 15) and (float(abs(hauteur_1(t0)-h+h_obstacle) < 60))){
            return true;
        }
    }

    //Collision avec les losanges
    for (int i = n_obstacle; i < n_obstacle*2; i++){
        if ((float(abs(xGuy+wGuy-t[i].center_2(t0))) < 15) and (float(abs(hauteur_1(t0)-h+h_obstacle) < 60))){
            return true;
        }
    }

    //Collision avec les cercles
    for (int i = 2*n_obstacle; i < 3*n_obstacle; i++){
        if ((float(abs(xGuy+wGuy-t[i].center_3(t0))) < 15) and (float(abs(hauteur_1(t0)-h+h_obstacle)) < 60)){
            return true;
        }
    }

    //Collision avec les triangles du haut
    for (int i = 3*n_obstacle; i < 4*n_obstacle; i++){
        if ((float(abs(xGuy+wGuy-t[i].center_1(t0))) < 15) and (float(abs(hauteur_1(t0)-h_obstacle) < 25))){
            return true;
        }
    }

    //Collision avec le plafond lors de la phase 1
    if (abs(hauteur_1(t0)-e_h) < 1){
        return true;
    }
    return false;
}
