#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#define size 5
#define line 10
#define col 10
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
    return piece_echange[size][size];
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

void place_OK(char piece[size][size],char grille[line][col],int gauche,int droite,int haut,int bas,int colone_choisie){
    int grille_lines,lines,colone;
    int piece_placer = 0;
    for(grille_lines = 0 ; grille_lines<line-(bas-haut+1);grille_lines++){
        lines = grille_lines;
        colone = colone_choisie;
        int collision = 0;
        for(int i = haut; i<= bas;i++){
            colone = colone_choisie;
            for (int j = gauche;j<= droite;j++){
                if(piece[i][j]=='X' && grille[lines][colone]=='X'){
                     if(grille_lines== 0){
                    printf("game over");
                    }
            else{
                placer_piece(colone_choisie,grille_lines-1, haut,bas,gauche,droite,piece,grille);
                    piece_placer = 1;
                    return;
                    }
                }
                colone++;
            }
            lines++;
        }
    }
    if( piece_placer == 0){
        placer_piece(colone_choisie,line-bas-haut+1, haut,bas,gauche,droite,piece,grille);
    }
}
int main() {
    char piece[size][size]= {{' ',' ',' ',' ',' '},
                                {' ',' ',' ',' ',' '},
                                {'X','X','X','X',' '},
                                {' ',' ',' ','X',' '},
                                {' ',' ',' ',' ',' '}} ;
    int haut ,bas ,gauche,droite;
    
   char grille[line][col];
    init_grille(grille);
    display_grille(grille);
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
    place_OK(piece, grille, gauche, droite, haut, bas, 3);
    
    display_grille(grille);
    return 0;
    
}
