#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#define size 5
#define line 10
#define col 10
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

void select_piece(char *nomFichier){
    int Number_piece;
    char nombreTransformer[4];
    char txt[] = ".txt";
    Number_piece = rand() % 4 + 1;
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
            if (grille[i][j] == 'X')
                printf(" \033[32m■\033[0m │");
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

void display_piece(char piece[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (piece[i][j] == 'X')
                printf("\033[36m■\033[0m");
            else
                printf(" ");
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

void placer_piece(int colone_choisie, int grille_lines, int haut, int bas, int gauche, int droite, char piece[size][size], char grille[line][col]) {
    int colone;
    for (int i = haut; i <= bas; i++) {
        colone = colone_choisie;
        for (int j = gauche; j <= droite; j++) {
            if (piece[i][j] == 'X') {  // ✅ Ne placer que les blocs actifs
                grille[grille_lines][colone] = 'X';
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

int place_OK(char piece[size][size], char grille[line][col], int gauche, int droite, int haut, int bas, int colone_choisie) {
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
            if (grille_lines == 0) {
                printf("Game Over !\n");
                return 0;
            } else {
                placer_piece(colone_choisie, ligne_finale, haut, bas, gauche, droite, piece, grille);
                return 1;
            }
        }
    }

    if (collision == 0) {
        ligne_finale = line - (bas - haut + 1);
        placer_piece(colone_choisie, ligne_finale, haut, bas, gauche, droite, piece, grille);
        return 1;
    }

    return 1;
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

void down_line(char grille[line][col], int Number_line) {
    for (int i = Number_line; i > 0; i--) {
        for (int j = 0; j < col; j++) {
            grille[i][j] = grille[i - 1][j];  // ✅ ligne du dessus
        }
    }
    for (int j = 0; j < col; j++) {
        grille[0][j] = ' ';  // ligne du haut vidée
    }
}


void delete_lines(char grille[line][col]) {
    int Number_line;
    while ((Number_line = check_full_line(grille)) != 11) {
        down_line(grille, Number_line);
    }
}


int main() {
    srand(time(NULL));
    char grille[line][col];
    init_grille(grille);

    int score = 0;
    int best_score = 0;
    int tour = 1;

    while (1) {
        char piece[size][size];
        char piece1[size][size] = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {'X', 'X', 'X', 'X', ' '},
            {' ', ' ', ' ', 'X', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };
        char piece2[size][size] = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', 'X', 'X', 'X', ' '},
            {' ', ' ', 'X', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };
        char piece3[size][size] = {
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {'X', 'X', 'X', 'X', ' '},
            {' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' '}
        };

        int r = rand() % 3;
        if (r == 0) memcpy(piece, piece1, sizeof(piece1));
        else if (r == 1) memcpy(piece, piece2, sizeof(piece2));
        else memcpy(piece, piece3, sizeof(piece3));

        printf("\n--- Tour %d ---\n", tour);
        display_grille(grille);
        printf("\nPièce :\n");
        display_piece(piece);

        char reponse;
        printf("Rotation (o/n) ? ");
        scanf(" %c", &reponse);
        while (reponse == 'o' || reponse == 'O') {
            rotation_piece(piece);
            display_piece(piece);
            printf("Encore (o/n) ? ");
            scanf(" %c", &reponse);
        }

        int haut, bas, gauche, droite;
        reduction_Matrice(&haut, &bas, &gauche, &droite, piece);

        int colone_choisie;
        printf("Colonne (0 à %d) : ", col - 1);
        scanf("%d", &colone_choisie);

        if (!place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie)) {
            break;
        }

        system(CLEAR);
        tour++;

        int lignes_supprimees = 0;
        while (check_full_line(grille) != 11) {
            lignes_supprimees++;
            int ligne = check_full_line(grille);
            down_line(grille, ligne);
            system(CLEAR);
            printf("--- Tour %d ---\n", tour);
            display_grille(grille);
        }

        score += lignes_supprimees * 100;
        if (score > best_score)
            best_score = score;

        printf("Lignes supprimées : %d   |   Score : %d   |   Meilleur : %d\n", lignes_supprimees, score, best_score);
    }

    printf("\n--- Fin du jeu ---\n");
    printf("Score final     : %d\n", score);
    printf("Meilleur score  : %d\n", best_score);
    return 0;
}
