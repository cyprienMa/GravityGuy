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

    // ######## PHASE 1 ########//

    //Créaction de la première phase obstacles, les triangles
    //On s'assure que les obstacles ne se superposent pas
    float delta_t_12 = (w + (n_obstacle-1)*300)/vitesse;
    float d_min_12 = (v2-vitesse)*delta_t_12;

    T[0].set(0, w);
    for(int i=1; i<n_obstacle; i++){
        int coef = intRandom(300,600);
        T[i].set(0, T[i-1].center_1(0) + coef);
    }

    //Création de la seconde phase d'obstacles, les losanges
    T[n_obstacle].set(0, T[n_obstacle -1].center_1(0) + d_min_12 + 100);
    for(int i=n_obstacle+1; i<2*n_obstacle; i++){
        int coef = intRandom(300,600);
        T[i].set(0, T[i-1].center_2(0) + coef);
    }

    //Création de la troisième phase d'obstacles, les cercles
    //On s'assure que les obstacles ne se superposent pas
    float delta_t_23 = w/v2 + (n_obstacle-1)*600/v2 + d_min_12/v2 + (n_obstacle-1)*600/v2;
    float d_min_23 = (v3-v2)*delta_t_23;

    T[2*n_obstacle].set(0, T[2*n_obstacle -1].center_2(0) + d_min_23);
    for(int i=2*n_obstacle+1; i<3*n_obstacle; i++){
        int coef = intRandom(300,600);
        T[i].set(0, T[i-1].center_3(0) + coef);
    }

    T[3*n_obstacle].set(0, T[3*n_obstacle -1].center_3(0) + 100);
    // ########  PHASE 2 ######## //
    //Création de la 4eme phase d'obstacles, les triangles du haut
    for(int i=3*n_obstacle+1; i<4*n_obstacle; i++){
       T[i].set(0, 2*w+i*300);
    }
}

void jeu::dessin(int t) const {
    noRefreshBegin();
    clearWindow();
    int image_width_window = 1000;
    int image_height_window = 600;
    byte* rgb;

    loadColorImage(srcPath("ville.jpg"), rgb, image_width_window, image_height_window);
    NativeBitmap my_native_bitmap_ville(image_width_window, image_height_window);
    my_native_bitmap_ville.setColorImage(0,0,rgb,image_width_window, image_height_window);
    putNativeBitmap(0, 0, my_native_bitmap_ville);

    //On dessine l'obstacle_1 (Triangles)
    for(int i=0; i< n_obstacle; i++){
        drawLine(T[i].center_1(t), h-h_obstacle-e_b, T[i].center_1(t)+h_obstacle/sqrt(3), h-e_b, ORANGE, 3);
        drawLine(T[i].center_1(t)+h_obstacle/sqrt(3), h-e_b, T[i].center_1(t)-h_obstacle/sqrt(3), h-e_b, ORANGE, 3);
        drawLine(T[i].center_1(t)-h_obstacle/sqrt(3), h-e_b, T[i].center_1(t), h-h_obstacle-e_b, ORANGE, 3);
    }

    //On dessine les obstacles de la phase 2 (Losanges)
    for(int i=n_obstacle; i< 2*n_obstacle; i++){
        drawLine(T[i].center_2(t), h-h_obstacle-e_b, T[i].center_2(t)+h_obstacle/2, h-h_obstacle/2-e_b, RED, 3);
        drawLine(T[i].center_2(t)+h_obstacle/2, h-h_obstacle/2-e_b, T[i].center_2(t), h-e_b, RED, 3);
        drawLine(T[i].center_2(t), h-e_b, T[i].center_2(t)-h_obstacle/2, h-h_obstacle/2-e_b, RED,3);
        drawLine(T[i].center_2(t)-h_obstacle/2, h-h_obstacle/2-e_b, T[i].center_2(t), h-h_obstacle-e_b, RED, 3);
    }

    //On dessine les obstacles de la phase 3 (Cercles)
    for(int i=2*n_obstacle; i< 3*n_obstacle; i++){
        fillCircle(T[i].center_3(t), h-h_obstacle/2-e_b, h_obstacle/2, BLUE);
    }

    fillRect(T[3*n_obstacle].center_3(t), 400,100, 200,GREEN);

    //On dessine les obstacles de la phase 4 (Triangles du haut)
    for(int i=3*n_obstacle; i< 4*n_obstacle; i++){
        drawLine(T[i].center_1(t), h_obstacle+e_h, T[i].center_1(t)+h_obstacle/sqrt(3), e_h, ORANGE, 3);
        drawLine(T[i].center_1(t)-h_obstacle/sqrt(3), e_h, T[i].center_1(t),h_obstacle+e_h, ORANGE, 3);
        drawLine(T[i].center_1(t)-h_obstacle/sqrt(3), e_h, T[i].center_1(t)+h_obstacle/sqrt(3), e_h, ORANGE, 3);
    }

    //Le rectangle du haut et du bas
    if (T[3*n_obstacle].center_3(t) >= xGuy + wGuy + 20){
        fillRect(0,0,w,e_h,YELLOW); //Plafond dangereux
        fillRect(0,h-e_b,w,e_b, CYAN); //Sol pas dangereux
    }

    if (T[3*n_obstacle].center_3(t) < xGuy + wGuy + 20){
        fillRect(0,0,w,e_h,CYAN); //Plafond pas dangereux
        fillRect(0,h-e_b,w,e_b, YELLOW); //Sol dangereux
    }

    //On dessine le guy
    int image_width = 10;
    int image_height = 10;

    loadColorImage(srcPath("guy_blanc_petit.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap(image_width, image_height);
    my_native_bitmap.setColorImage(0,0,rgb,image_width, image_height);

    loadColorImage(srcPath("guy_blanc_petit_upside.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap_bis(image_width, image_height);
    my_native_bitmap_bis.setColorImage(0,0,rgb,image_width, image_height);

    loadColorImage(srcPath("boom.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap_boom(image_width, image_height);
    my_native_bitmap_boom.setColorImage(0,0,rgb,image_width, image_height);

    delete[] rgb;

    if (guy.check_state(t)){
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap);
    }
    else{
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap_bis);
    }

    if (guy.collision(T,t)){
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap_boom);
    }

    noRefreshEnd();
}



void jeu::dessin2(int t) const {
    noRefreshBegin();
    clearWindow();
    int image_width_window = 1000;
    int image_height_window = 600;
    byte* rgb;

    loadColorImage(srcPath("ville.jpg"), rgb, image_width_window, image_height_window);
    NativeBitmap my_native_bitmap_ville(image_width_window, image_height_window);
    my_native_bitmap_ville.setColorImage(0,0,rgb,image_width_window, image_height_window);
    putNativeBitmap(0, 0, my_native_bitmap_ville);

    //On dessine l'obstacle_1 (Triangles)
    for(int i=0; i< n_obstacle; i++){
        drawLine(T[i].center_1_2(t), h-h_obstacle-e_b, T[i].center_1_2(t)+h_obstacle/sqrt(3), h-e_b, ORANGE, 3);
        drawLine(T[i].center_1_2(t)+h_obstacle/sqrt(3), h-e_b, T[i].center_1_2(t)-h_obstacle/sqrt(3), h-e_b, ORANGE, 3);
        drawLine(T[i].center_1_2(t)-h_obstacle/sqrt(3), h-e_b, T[i].center_1_2(t), h-h_obstacle-e_b, ORANGE, 3);
    }

    //On dessine les obstacles de la phase 2 (Losanges)
    for(int i=n_obstacle; i< 2*n_obstacle; i++){
        drawLine(T[i].center_2_2(t), h-h_obstacle-e_b, T[i].center_2_2(t)+h_obstacle/2, h-h_obstacle/2-e_b, RED, 3);
        drawLine(T[i].center_2_2(t)+h_obstacle/2, h-h_obstacle/2-e_b, T[i].center_2_2(t), h-e_b, RED, 3);
        drawLine(T[i].center_2_2(t), h-e_b, T[i].center_2_2(t)-h_obstacle/2, h-h_obstacle/2-e_b, RED,3);
        drawLine(T[i].center_2_2(t)-h_obstacle/2, h-h_obstacle/2-e_b, T[i].center_2_2(t), h-h_obstacle-e_b, RED, 3);
    }

    //On dessine les obstacles de la phase 3 (Cercles)
    for(int i=2*n_obstacle; i< 3*n_obstacle; i++){
        fillCircle(T[i].center_3_2(t), h-h_obstacle/2-e_b, h_obstacle/2, BLUE);
    }

    fillRect(T[3*n_obstacle].center_3_2(t), 400,100, 200,GREEN);

    //On dessine les obstacles de la phase 4 (Triangles du haut)
    for(int i=3*n_obstacle; i< 4*n_obstacle; i++){
        drawLine(T[i].center_1_2(t), h_obstacle+e_h, T[i].center_1_2(t)+h_obstacle/sqrt(3), e_h, ORANGE, 3);
        drawLine(T[i].center_1_2(t)-h_obstacle/sqrt(3), e_h, T[i].center_1_2(t),h_obstacle+e_h, ORANGE, 3);
        drawLine(T[i].center_1_2(t)-h_obstacle/sqrt(3), e_h, T[i].center_1_2(t)+h_obstacle/sqrt(3), e_h, ORANGE, 3);
    }

    //Le rectangle du haut et du bas
    if (T[3*n_obstacle].center_3_2(t) >= xGuy + wGuy + 20){
        fillRect(0,0,w,e_h,YELLOW); //Plafond dangereux
        fillRect(0,h-e_b,w,e_b, CYAN); //Sol pas dangereux
    }

    if (T[3*n_obstacle].center_3_2(t) < xGuy + wGuy + 20){
        fillRect(0,0,w,e_h,CYAN); //Plafond pas dangereux
        fillRect(0,h-e_b,w,e_b, YELLOW); //Sol dangereux
    }

    //On dessine le guy
    int image_width = 10;
    int image_height = 10;

    loadColorImage(srcPath("guy_blanc_petit.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap(image_width, image_height);
    my_native_bitmap.setColorImage(0,0,rgb,image_width, image_height);

    loadColorImage(srcPath("guy_blanc_petit_upside.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap_bis(image_width, image_height);
    my_native_bitmap_bis.setColorImage(0,0,rgb,image_width, image_height);

    loadColorImage(srcPath("boom.jpg"), rgb, image_width, image_height);
    NativeBitmap my_native_bitmap_boom(image_width, image_height);
    my_native_bitmap_boom.setColorImage(0,0,rgb,image_width, image_height);

    delete[] rgb;

    if (guy.check_state(t)){
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap);
    }
    else{
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap_bis);
    }

    if (guy.collision2(T,t)){
        putNativeBitmap(xGuy, guy.hauteur_1(t), my_native_bitmap_boom);
    }

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

bool jeu::collision(int t) const{
    if (guy.collision(T,t)){
        return true;
    }
    return false;
}

bool jeu::collision2(int t) const{
    if (guy.collision2(T,t)){
        return true;
    }
    return false;
}

int jeu::menu(){
    Window menuWindow = openWindow(w, h, "Menu");
    setBackGround(Color(1,1,0));
    int playButtonX = 300, playButtonY = 200, buttonWidth = 200, buttonHeight = (50);
    int play2ButtonX = 300, play2ButtonY = 300, button2Width = 200, button2Height = (50);
    int quitButtonX = 300, quitButtonY = 400;


    fillRect(playButtonX, playButtonY, buttonWidth, buttonHeight, GREEN);
    drawString(playButtonX + 25, playButtonY + 22, "Level 1", WHITE, 20);

    fillRect(play2ButtonX, play2ButtonY, button2Width, button2Height, BLUE);
    drawString(play2ButtonX + 25, play2ButtonY + 22, "Level 2", WHITE, 20);

    fillRect(quitButtonX, quitButtonY, buttonWidth, buttonHeight, RED);
    drawString(quitButtonX + 25, quitButtonY + 22, "Quit", WHITE, 20);


    while (true) {
        Event e;
        getEvent(0, e);
        if (e.type == EVT_BUT_ON) {
            int x = e.pix[0];
            int y = e.pix[1];

            if (x > playButtonX && x < playButtonX + buttonWidth && y > playButtonY && y < playButtonY + buttonHeight) {
                closeWindow(menuWindow);
                return 1;  // Commence le jeu au niveau 1
            }

            if (x > play2ButtonX && x < play2ButtonX + button2Width && y > play2ButtonY && y < play2ButtonY + button2Height) {
                closeWindow(menuWindow);
                return 2;  // Commence le jeu au niveau 2
            }

            if (x > quitButtonX && x < quitButtonX + buttonWidth && y > quitButtonY && y < quitButtonY + buttonHeight) {
                closeWindow(menuWindow);
                exit(0);  // Quitte le jeu
            }
        }
    }

}






