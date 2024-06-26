#include"jeu.h"
#include"Guy.h"
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>

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

int jeu::init() {
    byte* rgb;
    int image_width_window = 1000;
    int image_height_window = 600;

    int image_width_rect = 100;
    int image_height_rect = 200;

    int image_width_guy = 60;
    int image_height_guy = 60;

    int image_width_boom = 60;
    int image_height_boom = 60;
    int e_h = 20;

    // On charge l'image de la ville
    if (!(loadColorImage(srcPath("ville_strip.png"), rgb, image_width_window, image_height_window))){
        std::cout << "Erreur : Impossible de charger l'image ville_strip.png" << std::endl;
        return 0;
    }
    my_native_bitmap_ville = NativeBitmap(image_width_window, image_height_window);
    my_native_bitmap_ville.setColorImage(0, 0, rgb, image_width_window, image_height_window);
    delete[] rgb;

    // On charge l'image du triangle
    if (!(loadColorImage(srcPath("triangle_strip.png"), rgb, image_width_window, image_height_window))){
        std::cout << "Erreur : Impossible de charger l'image triangle_strip.png" << std::endl;
        return 0;
    }
    my_native_bitmap_triangle = NativeBitmap(image_width_window, image_height_window);
    my_native_bitmap_triangle.setColorImage(0, 0, rgb, image_width_window, image_height_window);
    delete[] rgb;

    // On charge l'image du losange
    if ((!loadColorImage(srcPath("losange_strip.png"), rgb, image_width_window, image_height_window))){
        std::cout << "Erreur : Impossible de charger l'image losange_strip.png" << std::endl;
        return 0;
    }
    my_native_bitmap_losange = NativeBitmap(image_width_window, image_height_window);
    my_native_bitmap_losange.setColorImage(0, 0, rgb, image_width_window, image_height_window);
    delete[] rgb;

    // On charge l'image du rond
    if (!(loadColorImage(srcPath("rond.jpg"), rgb, image_width_window, image_height_window))){
        std::cout << "Erreur : Impossible de charger l'image rond.jpg" << std::endl;
        return 0;
    }
    my_native_bitmap_rond = NativeBitmap(image_width_window, image_height_window);
    my_native_bitmap_rond.setColorImage(0, 0, rgb, image_width_window, image_height_window);
    delete[] rgb;

    // On charge l'image du rectangle qui mène au switch
   if (!(loadColorImage(srcPath("rect_strip.png"), rgb, image_width_rect, image_height_rect))){
       std::cout << "Erreur : Impossible de charger l'image rect_strip.png" << std::endl;
       return 0;
    }
    my_native_bitmap_rect = NativeBitmap(image_width_rect, image_height_rect);
    my_native_bitmap_rect.setColorImage(0, 0, rgb, image_width_rect, image_height_rect);
    delete[] rgb;

    // On charge l'image du sol et du plafond
    if (!(loadColorImage(srcPath("sol_rouge_strip.png"), rgb, image_width_window, e_h))){
        std::cout << "Erreur : Impossible de charger l'image sol_rouge_strip.png" << std::endl;
        return 0;
    }
    my_native_bitmap_lava = NativeBitmap(image_width_window, e_h);
    my_native_bitmap_lava.setColorImage(0, 0, rgb, image_width_window, e_h);
    delete[] rgb;

    if (!(loadColorImage(srcPath("sol_bleu_strip.png"), rgb, image_width_window, e_h))){
        std::cout << "Erreur : Impossible de charger l'image sol_bleu_strip.png" << std::endl;
        return 0;
    }
    my_native_bitmap_sol = NativeBitmap(image_width_window, e_h);
    my_native_bitmap_sol.setColorImage(0, 0, rgb, image_width_window, e_h);
    delete[] rgb;

    // On charge l'image du guy et du boom
    if (!load(Img_guy, srcPath("guy_strip.png"))) {
        cout << "Failed to load image guy!" << endl;
        return 0;
    }
    AlphaColor backgroundColorGuy = Img_guy(0, 0);
    makeBackgroundTransparent(Img_guy, backgroundColorGuy);

    if (!load(Img_guy_upside, srcPath("guy_upside_strip.png"))) {
        cout << "Failed to load image guy upside!" << endl;
        return 0;
    }
    AlphaColor backgroundColorGuyUpside = Img_guy_upside(0, 0);
    makeBackgroundTransparent(Img_guy_upside, backgroundColorGuyUpside);

    if (!load(Img_boom, srcPath("boom_strip.png"))) {
        cout << "Failed to load image boom!" << endl;
        return 0;
    }
    AlphaColor backgroundColorBoom = Img_boom(0, 0);
    makeBackgroundTransparent(Img_boom, backgroundColorBoom);

    return 1;
}

//Initialisation du jeu
jeu::jeu(){
    init();
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
    T[n_obstacle].set(0, T[n_obstacle -1].center_1(0) + d_min_12 + 200);
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


    //Création d'un gros rectangle qui mène au switch 1
    T[3*n_obstacle].set(0, T[3*n_obstacle -1].center_3(0) + 100);

    // ########  PHASE 2 ######## //
    //Création de la 4eme phase d'obstacles, les triangles du haut
    for(int i=3*n_obstacle+1; i<5*n_obstacle; i++){
       T[i].set(0, 2*w+i*300);
    }

    // ####### PHASE 3 ####### //
    //Création d'un gros rectangle qui mène au switch 2
    T[5*n_obstacle].set(0, T[5*n_obstacle-1].center_3(0) + 500);
}

void jeu::dessin(int t) const {
    noRefreshBegin();
    clearWindow();
    int image_width_window = 1000;
    int image_height_window = 600;

    // Dessin de la ville
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

    if (guy.check_state(t)){
        display(Img_guy,xGuy, guy.hauteur_1(t));
    }
    else{
        display(Img_guy_upside,xGuy, guy.hauteur_1(t));;
    }

    if (guy.collision(T,t)){
        display(Img_boom,xGuy, guy.hauteur_1(t));;
    }

    // Les messages de la demo
    // Instruction pour le saut
    if (T[0].center_1(t) > 200) {
        fillRect(350, 230, 290, 50, YELLOW);
        drawString(355, 260, "Pour sauter, appuyez sur espace", BLACK, 20);
    }

    // Message d'annonce du switch
    if (T[3 * n_obstacle].center_3(t) < 800 && T[3 * n_obstacle].center_3(t) > 200) {
        fillRect(350, 230, 340, 50, YELLOW);
        drawString(355, 260, "Pour changer la gravité, appuyez sur G", BLACK, 20);
    }

    //Instruction pour le saut au plafond
    if (T[3*n_obstacle].center_3(t) < xGuy + wGuy){
        fillRect(320, 230, 400, 50, YELLOW);
        drawString(325, 260, "Pour décoller du plafond, appuyez sur espace", BLACK, 20);
    }


    noRefreshEnd();
}

void jeu::dessin2(int t) const {
    noRefreshBegin();
    clearWindow();

    // Dessin de la ville
    putNativeBitmap(0, 0, my_native_bitmap_ville);

    // Dessin des obstacles (triangle)
    for (int i = 0; i < n_obstacle; i++) {
        putNativeBitmap(T[i].center_1_2(t) - h_obstacle / 2., h - e_b - h_obstacle, my_native_bitmap_triangle);
    }

    // Dessin des losanges
    for (int i = n_obstacle; i < 2 * n_obstacle; i++) {
        putNativeBitmap(T[i].center_2_2(t) - h_obstacle / 2., h - e_b - h_obstacle, my_native_bitmap_losange);
    }

    // Dessin des ronds
    for (int i = 2 * n_obstacle; i < 3 * n_obstacle; i++) {
        putNativeBitmap(T[i].center_3_2(t) - h_obstacle / 2., h - e_b - h_obstacle, my_native_bitmap_rond);
    }

    // Dessin du rectangle qui mène au switch
    putNativeBitmap(T[3 * n_obstacle].center_3_2(t), 400, my_native_bitmap_rect);

    // Dessin du rectangle qui mène au switch 2
    putNativeBitmap(T[5 * n_obstacle].center_1_2(t), e_h, my_native_bitmap_rect);

    // Dessin des triangles du haut
    for (int i = 3 * n_obstacle; i < 5 * n_obstacle; i++) {
        putNativeBitmap(T[i].center_1_2(t) - h_obstacle / 2., e_b , my_native_bitmap_triangle);
    }

    // Dessin du sol et du plafond
    if (T[3 * n_obstacle].center_3_2(t) >= xGuy + wGuy + 20) {
        putNativeBitmap(0, 0, my_native_bitmap_lava);
        putNativeBitmap(0, h - e_h, my_native_bitmap_sol);
    }
    if (T[3 * n_obstacle].center_3_2(t) < xGuy + wGuy + 20) {
        putNativeBitmap(0, h - e_h, my_native_bitmap_lava);
        putNativeBitmap(0, 0, my_native_bitmap_sol);
    }

    // Si le premier gros rectangle est passé et que le second est proche, le plafond redevient de la lave
    if ((T[5*n_obstacle].center_1_2(t) < xGuy + wGuy + 20) and (T[3*n_obstacle].center_3_2(t) < xGuy + wGuy + 20)){
        putNativeBitmap(0, 0, my_native_bitmap_lava);
        putNativeBitmap(0, h - e_h, my_native_bitmap_sol);
    }


    // Messages d'annonce du switch
    if (T[3 * n_obstacle].center_3_2(t) < 800 && T[3 * n_obstacle].center_3_2(t) > 200) {
        fillRect(300, 300, 280, 50, WHITE);
        drawString(400, 260, "Get ready to SWITCH", BLACK, 20);
    }

    if (T[5 * n_obstacle].center_1_2(t) < 800 && T[5 * n_obstacle].center_1_2(t) > 200){
        fillRect(300, 300, 280, 50, WHITE);
        drawString(400, 260, "Get ready to SWITCH", BLACK, 20);
    }


    // Dessin du guy
    if (guy.check_state(t)) {
        display(Img_guy,xGuy, guy.hauteur_2(t));
    } else {
        display(Img_guy_upside,xGuy, guy.hauteur_2(t));;
    }

    // Dessin de l'explosion au moment de la collision
    if (guy.collision2(T, t)) {
        display(Img_boom,xGuy, guy.hauteur_2(t));;
    }

    //Message de fin du niveau
    if((T[5 * n_obstacle].center_1_2(t) < 0)){
        fillRect(350, 250, 280, 50, CYAN);
        drawString(350+55, 280+5, "Level 1 completed", BLACK, 20);
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
    int playButtonX = 300, playButtonY = 50, buttonWidth = 200, buttonHeight = (50);
    int play2ButtonX = 300, play2ButtonY = 150, button2Width = 200, button2Height = (50);
    int play3ButtonX = 300, play3ButtonY = 250, button3Width = 200, button3Height = (50);
    int play4ButtonX = 300, play4ButtonY = 350, button4Width = 200, button4Height = (50);
    int quitButtonX = 300, quitButtonY = 450;


    fillRect(playButtonX, playButtonY, buttonWidth, buttonHeight, WHITE);
    drawString(playButtonX + 25, playButtonY + 22, "Demo", BLACK, 20);

    fillRect(play2ButtonX, play2ButtonY, button2Width, button2Height, GREEN);
    drawString(play2ButtonX + 25, play2ButtonY + 22, "Level 1", BLACK, 20);

    fillRect(play3ButtonX, play3ButtonY, button3Width, button3Height, ORANGE);
    drawString(play3ButtonX + 25, play3ButtonY + 22, "Level 2", BLACK, 20);

    fillRect(play4ButtonX, play4ButtonY, button4Width, button4Height, RED);
    drawString(play4ButtonX + 25, play4ButtonY + 22, "Level 3", BLACK, 20);

    fillRect(quitButtonX, quitButtonY, buttonWidth, buttonHeight, BLUE);
    drawString(quitButtonX + 25, quitButtonY + 22, "Quit", WHITE, 20);


    while (true) {
        Event e;
        getEvent(0, e);
        if (e.type == EVT_BUT_ON) {
            int x = e.pix[0];
            int y = e.pix[1];

            if (x > playButtonX && x < playButtonX + buttonWidth && y > playButtonY && y < playButtonY + buttonHeight) {
                closeWindow(menuWindow);
                return 1;  // Commence la demo
            }

            if (x > play2ButtonX && x < play2ButtonX + button2Width && y > play2ButtonY && y < play2ButtonY + button2Height) {
                closeWindow(menuWindow);
                return 2;  // Commence le jeu au niveau 1
            }

            if (x > play3ButtonX && x < play3ButtonX + button3Width && y > play3ButtonY && y < play3ButtonY + button3Height) {
                closeWindow(menuWindow);
                return 3;  // Commence le jeu au niveau 2
            }

            if (x > play4ButtonX && x < play4ButtonX + button4Width && y > play4ButtonY && y < play4ButtonY + button4Height) {
                closeWindow(menuWindow);
                return 4;  // Commence le jeu au niveau 3
            }

            if (x > quitButtonX && x < quitButtonX + buttonWidth && y > quitButtonY && y < quitButtonY + buttonHeight) {
                closeWindow(menuWindow);
                exit(0);  // Quitte le jeu
            }
        }
    }

}



void makeBackgroundTransparent(Image<AlphaColor>& img, AlphaColor backgroundColor){
    int width = img.width();
    int height = img.height();

    for(int y=0; y<height; y++){
        for(int x=0; x< width; x++){
            AlphaColor& pixel = img(x, y);
            if (pixel.r() == backgroundColor.r()&& pixel.g()==backgroundColor.g()&& pixel.b()==backgroundColor.b()&& pixel.a() ==backgroundColor.a()){
                pixel.a() = 0;
            }

        }
    }
}


