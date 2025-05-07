#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#define size 5
#define line 10
#define col 10

void select_piece(char *nomFichier){
    int Number_piece;
    char nombreTransformer[2];
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
            printf("Erreur d'ouverture du fichier");
            return;
        }
    
        char texte[100];
        int row = 0;
    
        while (fgets(texte, sizeof(texte), fp) && row < size) {
            for (int coln = 0; coln < size; coln++) {
                piece[row][coln] = (coln < strlen(texte) && texte[coln] != '\n') ? texte[coln] : ' ';
            }
            row++;
        }
    
    
        fclose(fp);
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
            printf("%c|",grille[i][j]);
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







void place_OK(char piece[size][size], char grille[line][col], int gauche, int droite, int haut, int bas, int colone_choisie) {
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
void delete_lines(char grille[line][col]){
    int i,j,Number_line;
    while(check_full_line(grille)!= 11){
        Number_line = check_full_line(grille);
        down_line(grille,Number_line);
    }
}

int main() {
  srand(time(NULL)); 
    char nomfi[20];
    select_piece(nomfi);
    char piece[size][size];
    Matrice_piece(nomfi,piece);
    display_piece(piece);
    char piece[size][size]= {{' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' '},
                                {'X','X','X','X',' '},
                                {' ',' ',' ','X',' '},
                                {' ',' ',' ',' ',' '}} ;
    char piece2[size][size]= {{' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' '},
                                {' ','X','X','X',' '},
                                {' ',' ','X',' ',' '},
                                {' ',' ',' ',' ',' '}} ;
        char piece3[size][size]= {{' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' '},
                                {'X','X','X','X',' '},
                                {' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' '}} ;
    
    int haut ,bas ,gauche,droite;
    
   char grille[line][col];
    init_grille(grille);
   // display_grille(grille);
    display_piece(piece);
    rotation_piece(piece);
    rotation_piece(piece);
    display_piece(piece);
    int colone_choisie = 0;
    reduction_Matrice(&haut,&bas,&gauche,&droite,piece);
    printf("haut %d\n",haut);
    printf("bas %d\n",bas);
    printf("gauche %d\n",gauche);
    printf("droite %d\n",droite);
   // placer_piece(colone_choisie,6,haut, bas,gauche,droite,piece,grille);
    place_OK(piece, grille, gauche, droite, haut, bas, colone_choisie);
   place_OK(piece, grille, gauche, droite, haut, bas, 4);
   place_OK(piece, grille, gauche, droite, haut, bas, 4);
    rotation_piece(piece);
     reduction_Matrice(&haut,&bas,&gauche,&droite,piece);
    printf("haut %d\n",haut);
    printf("bas %d\n",bas);
    printf("gauche %d\n",gauche);
    printf("droite %d\n",droite);
    place_OK(piece, grille, gauche, droite, haut, bas, 1);
    rotation_piece(piece3);
    reduction_Matrice(&haut,&bas,&gauche,&droite,piece3);
    
     place_OK(piece3, grille, gauche, droite, haut, bas, 3);
    place_OK(piece3, grille, gauche, droite, haut, bas, 9);
    place_OK(piece3, grille, gauche, droite, haut, bas, 8);
    // down_line(grille,9);
    display_grille(grille);
   int ligne_sup = check_full_line(grille);
    printf("ligne_sup %d\n",ligne_sup);
    //down_line(grille,9);
    delete_lines(grille);
    display_grille(grille);
    place_OK(piece3, grille, gauche, droite, haut, bas, 0);
    place_OK(piece3, grille, gauche, droite, haut, bas, 1);
    display_grille(grille);
     delete_lines(grille);
    display_grille(grille);
    return 0;


