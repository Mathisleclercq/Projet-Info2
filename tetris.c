// Librairies pour affichage, fichiers, temps et saisie clavier temporisée
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#include <unistd.h>      // pour select()
#include <sys/select.h>  // pour fd_set et struct timeval


#define size 5
#define line 10
#define col 10



#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif



// Structure pour stocker le nom et le score d'un joueur
typedef struct {
    char nom[50];
    int score;
} Joueur;



// Efface le terminal (Windows ou Linux)
void clear_screen() {
    system(CLEAR_COMMAND);
}


// Génère un nom de fichier pour choisir une pièce aléatoire
void select_piece(char *nomFichier){
    int Number_piece;
    char nombreTransformer[10];
    char txt[] = ".txt";
    Number_piece = rand() % 7 + 1;
    sprintf(nombreTransformer, "%d", Number_piece);
    strcpy(nomFichier, "piece");
    strcat(nomFichier, nombreTransformer);
    strcat(nomFichier, txt);
}



// Remplit la matrice 'piece' avec le contenu d'un fichier
    void Matrice_piece(const char *filename, char piece[size][size]) {
        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
        }
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
        int c = fgetc(fp);
        // Sauter les retours à la ligne si présents
        while (c == '\n' || c == '\r') {
                c = fgetc(fp);
            }
        piece[i][j] = (char)c;
            }
        }
        
        fclose(fp);
        }
        
        


    // Initialise la grille avec des espaces vides
        void init_grille(char grille[line][col]){
            for(int i = 0;i<line ;i++){
                for(int j = 0 ;j<col ;j++){
                    grille[i][j]=' ';
                }
            }
        }
        
        
        


        // Affiche la grille avec des couleurs selon les caractères A-G
        void display_grille(char grille[line][col]) {
            printf("    ");
            for (int j = 0; j < col; j++) {
                printf(" %d  ", j);
            }
            printf("\n");
        
            printf("   ┌");
            for (int j = 0; j < col - 1; j++) {
                printf("───┬");
            }
            printf("───┐\n");
        
            for (int i = 0; i < line; i++) {
                printf("%2d │", i);
                for (int j = 0; j < col; j++) {
                    if (grille[i][j] == 'A' ||grille[i][j] == 'B' ||grille[i][j] == 'C' ||grille[i][j] == 'D' ||grille[i][j] == 'E' ||grille[i][j] == 'F' ||grille[i][j] == 'G'){
                        char c =grille[i][j];
                switch (c) {
                     case 'A': 
                         printf(" \033[31m■\033[0m │"); 
                         break; // Rouge
                     case 'B': 
                         printf(" \033[32m■\033[0m │"); 
                         break; // Vert
                     case 'C': 
                         printf(" \033[34m■\033[0m │"); 
                         break; // Bleu
                     case 'D': 
                         printf(" \033[33m■\033[0m │"); 
                         break; // Jaune
                     case 'E': 
                         printf(" \033[36m■\033[0m │"); 
                         break; // Cyan
                    case 'F': 
                        printf(" \033[35m■\033[0m │"); 
                        break; // Magenta
                     case 'G': 
                         printf(" \033[91m■\033[0m │"); 
                         break; // Rouge clair
                     }
                 }
                    else
                        printf("   │");
                }
                printf("\n");
        
                if (i != line - 1) {
                    printf("   ├");
                    for (int j = 0; j < col - 1; j++) {
                        printf("───┼");
                    }
                    printf("───┤\n");
                }
            }
        
            printf("   └");
            for (int j = 0; j < col - 1; j++) {
                printf("───┴");
            }
            printf("───┘\n");
        }
        
        


        // Affiche une pièce avec ses couleurs
        void display_piece(char piece[size][size]) {
        
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (piece[i][j] != ' '){
                        char c = piece[i][j];
                switch (c) {
                     case 'A': 
                         printf(" \033[31m■\033[0m"); 
                         break; // Rouge
                     case 'B': 
                         printf(" \033[32m■\033[0m"); 
                         break; // Vert
                     case 'C': 
                         printf("\033[34m■\033[0m"); 
                         break; // Bleu
                     case 'D': 
                         printf("\033[33m■\033[0m"); 
                         break; // Jaune
                     case 'E': 
                         printf("\033[36m■\033[0m"); 
                         break; // Cyan
                    case 'F': 
                        printf("\033[35m■\033[0m"); 
                        break; // Magenta
                     case 'G': 
                         printf("\033[91m■\033[0m"); 
                         break; // Rouge clair
                     }
                }
                    else
                        printf(" ");
                }
                printf("\n");
            }
        }
        
        
        
               
        // Fait pivoter une pièce de 90 degrés
        void rotation_piece(char piece[size][size]) {
    char piece_echange[size][size];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            piece_echange[i][j] = piece[size - 1 - j][i];
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            piece[i][j] = piece_echange[i][j];
        }
    }
}
        
        
        

        // Place la pièce dans la grille aux bonnes coordonnées
        void placer_piece(int colone_choisie,int grille_lines,int haut, int bas, int gauche,int droite,char piece[size][size],char grille[line][col]){
            int colone;
            for(int i =haut; i<= bas ;i++){
                colone = colone_choisie;
                for (int j = gauche;j<= droite;j++){
                    if(grille[grille_lines][colone]== ' '){
                        grille[grille_lines][colone] = piece[i][j];
                        }
                    colone++; 
                }
                grille_lines++;
            }
        }
        
        
        
        
        // Réduit la zone utile d'une pièce (haut, bas, gauche, droite)
        void reduction_Matrice(int* haut,int* bas,int* gauche,int* droite,char piece[size][size]){
            *haut = -1;
            *bas = -1;
            *gauche = -1;
            *droite = -1;
            for(int i =0; i<size; i++){
                for(int j =0; j<size; j++){
                    if(piece[i][j]=='A' ||piece[i][j]=='B' ||piece[i][j]=='C' ||piece[i][j]=='D' ||piece[i][j]=='E' ||piece[i][j]=='F' ||piece[i][j]=='G' ){
                        if(*haut== -1){
                            *haut = i;
                        }
                        else{
                            *bas = i;
                        }
                        
                    }
                }
            }
            for(int j =0; j<size; j++){
                for(int i =0; i<size; i++){
                    if(piece[i][j]=='A' ||piece[i][j]=='B' ||piece[i][j]=='C' ||piece[i][j]=='D' ||piece[i][j]=='E' ||piece[i][j]=='F' ||piece[i][j]=='G' ){
                        if(*gauche== -1){
                            *gauche = j;
                        }
                        else{
                            *droite = j;
                        }
                        
                    }
                }
            }
        }
        
               
        
        
        // Teste si la pièce peut être placée, sinon signale la défaite
        void place_OK(char piece[size][size], char grille[line][col], int gauche, int droite, int haut, int bas, int colone_choisie,int* defaite) {
            int grille_lines;
            int ligne_finale = -1;
            int collision;
        
            for (grille_lines = 0; grille_lines <= line - (bas - haut + 1); grille_lines++) {
                int lines = grille_lines;
                collision = 0;
        
                for (int i = haut; i <= bas; i++) {
                    int colone = colone_choisie;
                    for (int j = gauche; j <= droite; j++) {
                        if ((piece[i][j]=='A' ||piece[i][j]=='B' ||piece[i][j]=='C' ||piece[i][j]=='D' ||piece[i][j]=='E' ||piece[i][j]=='F' ||piece[i][j]=='G' ) && (grille[lines][colone] == 'A' ||grille[lines][colone] == 'B' ||grille[lines][colone] == 'C' ||grille[lines][colone] == 'D' ||grille[lines][colone] == 'E' ||grille[lines][colone]== 'F' ||grille[lines][colone] == 'G')) {
                            collision = 1;
                            break;
                        }
                        colone++;
                    }
                    if (collision) break;
                    lines++;
                }
        
                if (collision) {
                    ligne_finale = grille_lines - 1;
                    if(grille_lines== 0){
                        *defaite = 1;
                        return;
                            }
                     else{
                        placer_piece(colone_choisie,ligne_finale, haut,bas,gauche,droite,piece,grille);
                        return;
                        }
                    }
                }
            if (collision == 0) {
                ligne_finale = line - (bas - haut + 1);
            }
        
            placer_piece(colone_choisie, ligne_finale, haut, bas, gauche, droite, piece, grille);
        }
        


        // Retourne l'indice d'une ligne pleine (ou 11 sinon)
        int check_full_line(char grille[line][col]){
            int Number_line = 11;
            int Number_croix;
            for(int i = 0;i<line ;i++){
                Number_croix = 0;
                for(int j = 0 ;j<col ;j++){
                    if(grille[i][j] == 'A' ||grille[i][j] == 'B' ||grille[i][j] == 'C' ||grille[i][j] == 'D' ||grille[i][j] == 'E' ||grille[i][j]== 'F' ||grille[i][j] == 'G'){
                        Number_croix++;
                    }
                }
                if(Number_croix== 10){
                    Number_line = i;
                }
                
            }
            return Number_line;
        }




        // Fait descendre les lignes au-dessus de la ligne supprimée
        void down_line(char grille[line][col],int Number_line){
            int i,j,k;
            for(i = Number_line;i>0;i--){
                for(j=0; j<col ; j++){
                    grille[i][j]=grille[i-1][j];
                }
            }
            for(k=0; k<col; k++ ){
                grille[0][k]=' ';
            }
        }



        // Supprime toutes les lignes pleines et met à jour le score
        void delete_lines(char grille[line][col],int* score,int* ligne_supprimer){
            int Number_line;
            int compter = 0;
            while(check_full_line(grille)!= 11){
                Number_line = check_full_line(grille);
                down_line(grille,Number_line);
                compter++;
            }
            *score = *score + 100*compter;
            *ligne_supprimer = *ligne_supprimer + compter;
        }



    // Affiche les 5 meilleurs scores depuis un fichier
    void display_score() {
        FILE *fichier = fopen("highscores.txt", "r");
        if (fichier == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            exit(1);
        }
        int nb_lignes = 0;
        char c;
        while ((c = fgetc(fichier)) != EOF) {
            if (c == '\n') {
                nb_lignes++;
            }
        }
        rewind(fichier);
        Joueur *joueurs = malloc(nb_lignes * sizeof(Joueur));
        if (joueurs == NULL) {
            printf("Erreur d'allocation mémoire.\n");
            fclose(fichier);
            exit(1);
        }
        int compter = 0;
        while (compter != nb_lignes) {
            fscanf(fichier, "%s %d", joueurs[compter].nom, &joueurs[compter].score);
            compter++;
        }
        fclose(fichier);
        Joueur temp;
        for (int i = 0; i < nb_lignes-1; i++) {
            for (int j = i+1; j<nb_lignes; j++) {
                if(joueurs[i].score <joueurs[j].score){
                temp = joueurs[i];
                joueurs[i] = joueurs[j];
                joueurs[j] = temp;
                }
            }
        }
        printf("Meilleur score\n");
        for (int k = 0; k < nb_lignes && k<5; k++) {
            printf("%s : %d\n", joueurs[k].nom, joueurs[k].score);
        }
        free(joueurs);
    }




    // Ajoute le score actuel au fichier des scores
    void ajouter_score(Joueur j) {
        FILE *fichier = fopen("highscores.txt", "a+");
        if (fichier == NULL) {
            perror("Erreur ouverture fichier");
            return;
        }
        fseek(fichier, 0, SEEK_END);
        long taille = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);
        if (taille == 0) {
            for (int i = 0; i < 5; i++) {
                fprintf(fichier, "%s %d\n", j.nom, j.score);
            }
        } 
        else {
            fprintf(fichier, "%s %d\n", j.nom, j.score);
        }
        fclose(fichier);
    }




    // Attend une entrée clavier pendant X secondes (pour timer)
    int wait_for_input(int seconds) {
        fd_set set;
        struct timeval timeout;

        FD_ZERO(&set);         
        FD_SET(0, &set);       

        timeout.tv_sec = seconds;
        timeout.tv_usec = 0;

        return select(1, &set, NULL, NULL, &timeout);
    }




    // Affiche l'état du jeu avec un nettoyage d'écran
    void afficher_etat(int tour, int score, int lignes_supprimees, char grille[line][col]) {
        clear_screen();  
        printf("--- Tour %d ---\n", tour);
        printf("Score : %d   |   Lignes supprimées : %d\n\n", score, lignes_supprimees);
        display_grille(grille);
    }






int main() {


    srand(time(NULL));
    int tour = 1;
    int score = 0;
    int ligne_supprimer = 0;
    int defaite = 0;
    char nomfi[20];
    char piece[size][size];
    int haut, bas, gauche, droite;
    int colone_choisie;
    char grille[line][col];
    int verif;
    char nomJoueur[30];
    Joueur J1;



    // Demande le nom du joueur et initialise la grille
    printf("Donner un nom de joueur : ");
    scanf("%s", nomJoueur);
    strcpy(J1.nom, nomJoueur);
    init_grille(grille);



    // Boucle principale du jeu
    while (defaite != 1) {
        select_piece(nomfi);
        Matrice_piece(nomfi, piece);


        // Affichage du jeu
        clear_screen();
        printf("               --- Tour %d ---               \n\n", tour);
        printf("    Score : %d   |   Lignes supprimées : %d  \n\n", score, ligne_supprimer);
        display_grille(grille);
        printf("\nPièce actuelle :\n");
        display_piece(piece);



        // Gestion de la rotation de la pièce
        char reponse;
        do {
            printf("Rotation (o/n) ? ");
            scanf(" %c", &reponse);
            while (getchar() != '\n');
        } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');

        while (reponse == 'o' || reponse == 'O') {
            rotation_piece(piece);
            clear_screen();
            printf("               --- Tour %d ---               \n\n", tour);
            printf("    Score : %d   |   Lignes supprimées : %d  \n\n", score, ligne_supprimer);
            display_grille(grille);
            printf("\nPièce après rotation :\n");
            display_piece(piece);

            do {
                printf("Encore (o/n) ? ");
                scanf(" %c", &reponse);
                while (getchar() != '\n');
            } while (reponse != 'o' && reponse != 'O' && reponse != 'n' && reponse != 'N');
        }


        // Calcul des dimensions utiles de la pièce
        reduction_Matrice(&haut, &bas, &gauche, &droite, piece);


        // Placement avec limite de temps
        printf("Tu as 4 secondes pour choisir la colonne : ");
        fflush(stdout);
        if (wait_for_input(4) == 1) {
            verif = scanf("%d", &colone_choisie);
            while (getchar() != '\n');

            if (verif != 1 || colone_choisie < 0 || colone_choisie > col - (droite - gauche + 1)) {
                printf("❌ Colonne invalide. Pièce placée aléatoirement\n");
                sleep(2);
                colone_choisie = rand() % (col - (droite - gauche + 1));
                place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie, &defaite);
                tour++;
                continue;
            }
        }
        else {
            printf("\n⏱ Temps écoulé ! Pièce placée aléatoirement.\n");
            sleep(2);
            colone_choisie = rand() % (col - (droite - gauche + 1));
            place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie, &defaite);
            tour++;
            continue;
        }


        // Placement final et mise à jour de la grille
        place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie, &defaite);
        delete_lines(grille, &score, &ligne_supprimer);


        // Affichage pour le prochain tour
        tour++;
        clear_screen();
        printf("               --- Tour %d ---               \n\n", tour);
        printf("    Score : %d   |   Lignes supprimées : %d  \n\n", score, ligne_supprimer);
        display_grille(grille);
    }



    // Fin du jeu : sauvegarde et affichage des meilleurs scores
    printf("\n💀 Partie terminée. Merci d’avoir joué, %s !\n", J1.nom);
    J1.score = score;
    ajouter_score(J1);
    display_score();
    return 0;
}
