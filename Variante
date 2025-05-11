void choix_user(char *nomFichier) {
    int choix;
    char nombreTransformer[2];
    char txt[] = ".txt";
    do {
        printf("Choisissez votre piece (1 a 7) : ");
        if (scanf("%d", &choix) != 1) {
            while(getchar() != '\n'); 
            choix = 0; 
        }
    } while (choix < 1 || choix > 7);
    sprintf(nombreTransformer, "%d",choix);
    strcpy(nomFichier, "piece");
    strcat(nomFichier, nombreTransformer);
    strcat(nomFichier, txt);
}
choix_user(nomfi);


void CHOICE_RAND(char *nomFichier,int * derniere_piece,int* avant_derniere){
    int Number_piece;
    char nombreTransformer[2];
    char txt[] = ".txt";
    do {
        Number_piece = rand() % 7 + 1;
    }while(Number_piece == *derniere_piece || Number_piece==*avant_derniere);
    *avant_derniere = *derniere_piece;
    *derniere_piece = Number_piece;
    sprintf(nombreTransformer, "%d", Number_piece);
    strcpy(nomFichier, "piece");
    strcat(nomFichier, nombreTransformer);
    strcat(nomFichier, txt);
}

 int derniere_piece = -1;
int avant_derniere = -1;
CHOICE_RAND(nomfi,&derniere_piece,&avant_derniere);
