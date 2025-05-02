#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy

#define size 5
#define line 10
#define col 10

// **MODIF** : Changement du type de retour en void
void init_grille(char grille[line][col]){
    for(int i = 0; i < line; i++){
        for(int j = 0; j < col; j++){
            grille[i][j] = ' ';  // **MODIF** : Utilisation de ' ' au lieu de " "
        }
    }
}

void display_grille(char grille[line][col]){
    for(int k = 0; k < line; k++){
        printf(" %d", k);
    }
    printf("\n");
    for(int i = 0; i < line; i++){
        printf("|");
        for(int j = 0; j < col; j++){
            printf("%c|", grille[i][j]);
        }
        printf("\n");
    }
}

void display_piece(char piece[size][size]){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%c", piece[i][j]);
        }
        printf("\n");
    }
}

// **MODIF** : Type void et pas de return
void rotation_piece(char piece[size][size]){
    char piece_echange[size][size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            piece_echange[i][j] = piece[j][size - 1 - i];  // **MODIF** : 4-i devient size-1-i
        }
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            piece[i][j] = piece_echange[i][j];
        }
    }
}

// **MODIF** : Type void, et correction de ' ' et indices
void down_line(char grille[line][col], int Number_line){
    for(int i = Number_line; i > 0; i--){
        for(int j = 0; j < col; j++){
            grille[i][j] = grille[i - 1][j];  // **MODIF** : i+1 -> i-1 pour décaler vers le bas
        }
    }
    for(int k = 0; k < col; k++){
        grille[0][k] = ' ';  // **MODIF**
    }
}

// **MODIF** : Point-virgule manquant et mauvaise comparaison de caractères
int check_full_line(char grille[line][col]){
    int Number_line = 11;
    int Number_croix;  // **MODIF**
    for(int i = 0; i < line; i++){  // **MODIF** : loop sur line, pas size
        Number_croix = 0;
        for(int j = 0; j < col; j++){  // **MODIF**
            if(grille[i][j] == 'X'){  // **MODIF**
                Number_croix++;
            }
        }
        if(Number_croix == col){
            return i;
        }
    }
    return Number_line;
}

// **MODIF** : Type void et appel corrigé
void delete_lines(char grille[line][col]){
    int Number_line;
    while((Number_line = check_full_line(grille)) != 11){
        down_line(grille, Number_line);  // **MODIF**
    }
}

void placer_piece(int colone_choisie, int grille_lines, int haut, int bas, int gauche, int droite, char piece[size][size], char grille[line][col]){
    int colone;
    for(int i = haut; i <= bas; i++){
        colone = colone_choisie;
        for(int j = gauche; j <= droite; j++){
            if(grille[grille_lines][colone] == ' '){
                grille[grille_lines][colone] = piece[i][j];
            }
            colone++; 
        }
        grille_lines++;
    }
}

void reduction_Matrice(int* haut, int* bas, int* gauche, int* droite, char piece[size][size]){
    *haut = -1;
    *bas = -1;
    *gauche = -1;
    *droite = -1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(piece[i][j] == 'X'){
                if(*haut == -1){
                    *haut = i;
                }
                *bas = i;  // **MODIF** : toujours mettre à jour bas
            }
        }
    }
    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            if(piece[i][j] == 'X'){
                if(*gauche == -1){
                    *gauche = j;
                }
                *droite = j;  // **MODIF** : toujours mettre à jour droite
            }
        }
    }
}

// **MODIF** : Simplification + gestion correcte du placement
void place_OK(char piece[size][size], char grille[line][col], int gauche, int droite, int haut, int bas, int colone_choisie){
    int grille_lines;
    int piece_placer = 0;

    for(grille_lines = 0; grille_lines <= line - (bas - haut + 1); grille_lines++){
        int lines = grille_lines;
        int colone;
        int collision = 0;
        for(int i = haut; i <= bas; i++){
            colone = colone_choisie;
            for(int j = gauche; j <= droite; j++){
                if(piece[i][j] == 'X' && grille[lines][colone] == 'X'){
                    collision = 1;
                }
                colone++;
            }
            lines++;
        }

        if(collision){
            if(grille_lines == 0){
                printf("Game Over\n");
                exit(0);  // **MODIF** : termine le programme
            } else {
                placer_piece(colone_choisie, grille_lines - 1, haut, bas, gauche, droite, piece, grille);
                piece_placer = 1;
                break;
            }
        }
    }

    if(piece_placer == 0){
        placer_piece(colone_choisie, grille_lines - 1, haut, bas, gauche, droite, piece, grille);  // **MODIF**
    }
}





int main() {
    char grille[line][col];

    // Initialisation de la grille
    init_grille(grille);

    // Définir une pièce (bloc carré "O")
    char piece[size][size] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', 'X', 'X', ' ', ' '},
        {' ', 'X', 'X', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };

    // Afficher la grille vide
    printf("Grille initiale :\n");
    display_grille(grille);

    // Afficher la pièce
    printf("\nPiece à placer :\n");
    display_piece(piece);

    // Réduire la matrice pour identifier les bords utiles
    int haut, bas, gauche, droite;
    reduction_Matrice(&haut, &bas, &gauche, &droite, piece);

    // Choisir une colonne (ex : colonne 3)
    int colonne_choisie = 3;

    // Placer la pièce sur la grille
    place_OK(piece, grille, gauche, droite, haut, bas, colonne_choisie);

    // Afficher la grille après placement
    printf("\nGrille après placement :\n");
    display_grille(grille);

    return 0;
}
