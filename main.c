
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>  // for strcpy
#define size 5
#define line 10
#define col 10
char Select_Piece(){
    int Number_piece;
    char nomFichier[10] = "piece"
    char nombreTransformer;
    Number_piece = srand() % 7
    nombreTransformer = Number_piece + '0' ;
    strcat(nomFichier,nombreTransformer);
    return nomFichier;
}
Matrice_piece(char fichier[],piece[size][size]){
    a faire
}
char init_grille(char grille[line][col]){
    for(int i = 0;i<line ;i++){
        for(int j = 0 ;j<col ;j++){
            grille[i][j]=" ";
        }
    }
}
char display_grille(char grille[line][col]){
    for(int k = 0;k<line ;k++){
        printf(" %d",k);
    }
    printf("\n")
    for(int i = 0;i<line ;i++){
        printf("|");
        for(int j = 0 ;j<col ;j++){
            printf("%c|"grille[i][j]);
        }
        printf("\n")
    }
}

char display_piece(char piece[size][size]){
    for(int i = 0;i<size ;i++){
        for(int j = 0 ;j<size ;j++){
            printf("%c"piece[i][j]);
        }
        printf("\n")
    }
}
char rotation_piece(char piece[size][size]){
    char piece_echange[size][size]
    for(int i = 0;i<size ;i++){
        for(int j = 0 ;j<size ;j++){
            piece_echange[i][j] = piece[j][4-i];
        }
    }
    return piece_echange;
}
char down_line(char grille[line][col],int Number_line){
    int i,j,k;
    for(i = Number_line;i>0;i--){
        for(j=0; j<col ; j++){
            grille[i][j]=grille[i+1][j];
        }
    }
    for(k=0; k<col; k++ ){
        grille[0][k]=" ";
    }
    return grille;
}
int check_full_line(char grille[line][col]){
    int Number_line = 11;
    int Number_croix
    for(int i = 0;i<size ;i++){
        Number_croix = 0;
        for(int j = 0 ;j<size ;j++){
            if(grille[i][j]=="X"){
                Number_croix++;
            }
        }
        if(Number_croix== 10){
            Number_line = i;
        }
        
    }
    return Number_line
}

char delete_lines(char grille[line][col]){
    int i,j,Number_line;
    while(check_full_line(grille)!= 11){
        Number_line = check_full_line(grille);
        down_line(grille;Number_line)
    }
    return grille;
}

void placer_piece(int colone_choisie,int grille_lines,int haut, int bas, int gauche,int droite,char piece[size][size],char grille[line][col]){
    int colone;
    for(int i =haut; i<= bas ;i++){
        colone = colone_choisie;
        for (int j = gauche;j<= droite;j++){
            grille[grille_lines][colone] = piece[i][j];
            
            colone++; 
        }
        grille_lines++;
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
