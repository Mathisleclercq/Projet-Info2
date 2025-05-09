#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#define size 5
#define line 10
#define col 10
typedef struct {
    char nom[50];
    int score;
} Joueur;
void select_piece(char *nomFichier){
    int Number_piece;
    char nombreTransformer[2];
    char txt[] = ".txt";
    Number_piece = rand() %7 + 1;
    sprintf(nombreTransformer, "%d", Number_piece);
    strcpy(nomFichier, "piece");
    strcat(nomFichier, nombreTransformer);
    strcat(nomFichier, txt);
}

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
        
        
        char init_grille(char grille[line][col]){
            for(int i = 0;i<line ;i++){
                for(int j = 0 ;j<col ;j++){
                    grille[i][j]=' ';
                }
            }
            return grille[line][col];
        }
        
        
        
        void display_grille(char grille[line][col]){
            for(int k = 0;k<line ;k++){
                printf(" %d",k);
            }
            printf("\n");
            for(int i = 0;i<line ;i++){
                printf("|");
                for(int j = 0 ;j<col ;j++){
                    if(grille[i][j]=='X'){
                        printf("\033[32m■\033[0m|");
                    }
                    else{
                        printf(" |");
                    }
                }
                printf("\n");
            }
        }
        
        
        
        
        void display_piece(char piece[size][size]){
            for(int i = 0;i<size ;i++){
                for(int j = 0 ;j<size ;j++){
                        printf("%c",piece[i][j]);
                }
                printf("\n");
            }
        }
        
        
        
        
        
        
        
        char rotation_piece(char piece[size][size]){
            char piece_echange[size][size];
            for(int i = 0;i<size ;i++){
                for(int j = 0 ;j<size ;j++){
                    piece_echange[i][j] = piece[j][4-i];
                }
            }
            for(int i = 0;i<size ;i++){
                for(int j = 0 ;j<size ;j++){
                   piece[i][j] = piece_echange[i][j] ;
                }
            }
            return piece[size][size];
        }
        
        
        
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
        
        
        
        
        
        void reduction_Matrice(int* haut,int* bas,int* gauche,int* droite,char piece[size][size]){
            *haut = -1;
            *bas = -1;
            *gauche = -1;
            *droite = -1;
            for(int i =0; i<size; i++){
                for(int j =0; j<size; j++){
                    if(piece[i][j]=='X'){
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
                    if(piece[i][j]=='X'){
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
                        if (piece[i][j] == 'X' && grille[lines][colone] == 'X') {
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
                        printf("game over");
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
        
        int check_full_line(char grille[line][col]){
            int Number_line = 11;
            int Number_croix;
            for(int i = 0;i<line ;i++){
                Number_croix = 0;
                for(int j = 0 ;j<col ;j++){
                    if(grille[i][j]=='X'){
                        Number_croix++;
                    }
                }
                if(Number_croix== 10){
                    Number_line = i;
                }
                
            }
            return Number_line;
        }
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
        void delete_lines(char grille[line][col],int* score){
            int i,j,Number_line;
            int compter = 0;
            while(check_full_line(grille)!= 11){
                Number_line = check_full_line(grille);
                down_line(grille,Number_line);
                compter++;
            }
            *score = *score + 100*compter;
        }
void clear_screen(){
    printf("\033[H\033[J");
}




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
void ajouter_score(Joueur j) {
    FILE *fichier = fopen("highscores.txt", "a+");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier");
        return;
    }
    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    int n;
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
int main() {
    srand(time(NULL));
    int score = 0;
    int defaite = 0;
    char nomfi[20];
    char piece[size][size];
    char JeTourne;
    int haut, bas, gauche, droite;
    int colone_choisie;
    char grille[line][col];
    int verif;
    char nomJoueur[30];
    Joueur J1;
    printf("donner un nom de joueur");
    scanf("%s",&nomJoueur);
    strcpy(J1.nom, nomJoueur);
    init_grille(grille);
    
    while (defaite != 1) {
         int tour_piece = 0;
    
        select_piece(nomfi);
        Matrice_piece(nomfi, piece); 
        clear_screen();
        display_grille(grille);
        display_piece(piece);
        
        while (tour_piece != 1) {
            printf("Appuyer sur d pour tourner la piece, sinon sur s pour continuer : ");
            scanf(" %c", &JeTourne); 
            if (JeTourne == 'd') {
                rotation_piece(piece);
                clear_screen();
                display_grille(grille);
                display_piece(piece);
            } else if (JeTourne == 's') {
                tour_piece = 1;
            }
        }
        reduction_Matrice(&haut, &bas, &gauche, &droite, piece);
        
        do {
            printf("Dans quelle colonne placer la piece ? ");
            verif = scanf("%d", &colone_choisie);
            while (getchar() != '\n'); 
        } while (colone_choisie < 0 || colone_choisie > col - (droite - gauche + 1) || verif != 1);
        
        place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie,&defaite);
        
        clear_screen();
        display_grille(grille);
        delete_lines(grille,&score); 
        clear_screen();
        display_grille(grille);
        }
        J1.score = score;
        ajouter_score(J1);
        display_score();
        return 0;
    }




