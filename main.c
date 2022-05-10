#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**Først vil vi lave/definere strukturen på spillet*/

//Da alle kortene skal være forbundet, bruger vi dobbelt linked list
struct Kort{
    int number;
    int suit;
    char name[3];
    int erSkjult;
    struct Kort* next;
    struct Kort* prev;

};

// Nu laver vi nogen dobbelt linked list Pile, der skal holde styr på hvilket kort der høre til hvilken bunke
struct Bunke{
    char *beskrivelse;
    struct Bunke* next;
    struct Bunke* prev;

    struct Kort* head;
    struct Kort* tail;
};
// Reference til at kunne opsætte et korrekt format af kort spillet
struct KortSpil{
    int antalSuit[4];                   //diamonds = D, Spades = S, Harts = H, Clubs = C
    char SuitNo[4][13];
};

/**Nu vil vi opsætte node opperationer og bevægelige pointer*/

void pushKort(struct Bunke* Location);                                          //Tilføjer kort til Tail af en bunke
void addHeadKort(struct Bunke* Location);                                       //Tilføjer Kort til Head af bunke
void removeKort(struct Bunke* Location, struct Kort* specifikKort);             //fjerner kort fra ukendt lokation
void pushBunke(char *identifier);                                               //Opretter en bunke i slutningen af en liste over bunker
void popBunke(struct Bunke* Location);                                          //Fjerner bunke fra slutningen af en liste over bunker
void swap(struct Bunke* Location, int From, int To);                            //Ombytter lokationer på 2 kort i samme bunke
void duplicateKort(struct Kort* duplicate, struct Bunke* placeWhere);           // dupliker det valgte kort og placere det i slutningen af den angivende bunke
void moveKort(struct Bunke* From, struct Bunke* to);                            //Flyt Kort fra slutningen af bunken til slutningen af en anden bunke
void moveKortR(struct Bunke* From, struct Kort* whichCart, struct Bunke* To);   //Flytter en række af kort fra en bunke til slutningen af en anden bunke

//Logikken til spil stukturen
void opsBunker();                                                               //opsætter alle bunker, som er nødvendig for spillet og de tilhørende navne
void resetKortspil();                                                           //sletter alle bunker og det de indeholder
void ClearBunke();                                                              //sletter alle noder som er tilknyttet til bunken

//indlæsning og tjek om det loaded dæk
int DeckKontrol(struct Bunke* Location);                                        //Kontrollere at deck er et rigtigt deck
void autoDeck();
int LD(char *argument);

//global variabler
struct Bunke* head_p;
struct Bunke* tail_p;


int main() {

};

//De individuelle noder


void pushKort(struct Bunke* Location){
    struct Kort* tempKort = malloc(sizeof(struct Kort));
    if (Location->head == NULL){                                //hvis der ikke er nogen kort i bunken
        tempKort->prev = NULL;
        Location->head = tempKort;
        Location->tail = tempKort;

    } else {                                                    //Hvis der er et eller flere kort i bunken
        Location->tail->next = tempKort;
        tempKort->prev =NULL;
        Location->tail = tempKort;
    }
    tempKort->next = NULL;
}

void addHeadKort(struct Bunke* Location){
    struct Kort* tempKort = malloc(sizeof(struct Kort));
    if (Location->head == NULL){
        tempKort->next = NULL;
        Location->head = tempKort;
        Location->tail =tempKort;
    } else{
        Location->head->prev = tempKort;
        tempKort->next = Location->head;
        Location->head = tempKort;
    }
    tempKort->prev = NULL;
}

void removeKort(struct Bunke* Location, struct Kort* specifikKort){
    if (Location->head == NULL){                            //ingen kort i Bunken
        return;
    } else if (Location->head == Location->tail) {          //kun ét kort i bunken
      Location->head = NULL;
      Location->tail = NULL;
    } else {                                                //Flere kort i bunken
                                                            //Ret pointer til det kort der var located til det tidligere 'specifikKort'
        if (specifikKort->prev != NULL) {                   //Kortet er ikke located til head
            specifikKort->prev->next = specifikKort->next;
        } else {}                                           //else gør ingen ting (kort located til head
                                                            //Ret pointer til det kort der var located til det næste 'specifikKort'
        if (specifikKort->next != NULL){                    //Kort located til tail
            specifikKort->next->prev = specifikKort->prev;
        }else {}                                            //else 'så ændres der ikke noget' kortet er located til tail
    }
    if (specifikKort->name != NULL){
        free(specifikKort->name);
    }
    free(specifikKort);
}

void pushBunke(char *identifier){
    struct Bunke* temp = malloc(sizeof(struct Bunke));
    if (head_p == NULL){                                    //Der er ikke nogen bunker initialiseret
        temp->prev = NULL;
        head_p = temp;
        tail_p =temp;
    } else {                                                //der en eller flere bunker tilstede
        tail_p->next = temp;
        temp->prev = tail_p;
        tail_p = temp;
    }
    temp->next = NULL;
    strcpy(temp->beskrivelse, identifier);
}

void popBunke(struct Bunke* Location){
    if (tail_p == NULL){                                    //der er overhoved ingen bunker(kant tilfælde)
        return;
    }
    struct Bunke *temp = tail_p;
    while (tail_p->head != NULL){
        removeKort(tail_p,tail_p->tail);
    }
    if (head_p != tail_p){                                  //flere Bunker tilbage
       tail_p = tail_p->prev;
       tail_p->next = NULL;
    } else {
        head_p = NULL;
        tail_p =NULL;
    }
    if (temp->beskrivelse !=NULL){
        free(temp->beskrivelse);
    }
    free(temp);
}

void swap(struct Bunke* Location, int From, int To){
    if (Location->head == NULL) {                            //kant tilfælde
        return;
    }
        //vi har valgt at bruge array standarder til at bestemme location, dvs plads 0 er det første kort
    struct Kort *temp = Location->head, *CFrom, *CTo = Location->head;
    int index = 0, max = ((To - From) > 0) ? To : From;
        if ((From - To) == 0){                              //der skal ikke gøres noget
            return;
        }
        //Lokere begge kort
        while (index <= max){
            if (From == index){
                CFrom = temp;
            }
            if (To == index){
                CTo  = temp;
            }
            temp = temp->next;
        }

        //Ombytte kortene, ved at bruge tamp og ændringen af pointer
        //først ændres poninterne til kortet
        temp = malloc(sizeof(struct Kort));
        temp->prev = CFrom->prev;
        temp->next =CFrom->next;
        CFrom->prev = CTo->prev;
        CFrom->next = CTo->next;
        CTo->prev = temp->prev;
        CTo->next = temp->next;

        //Nu ændres pointerne på kortene i bunken for at kunne se de rigtige kort
    if (CTo->prev !=NULL){ CTo->prev->next; }
    if (CTo->next != NULL){ CTo->next->prev; }
    if (CFrom->prev != NULL){ CFrom->prev->next; }
    if (CFrom->next != NULL){ CFrom->next->prev = CFrom;}
    //fjerner the temp node, der blev lavet
        free(temp);
    }


void duplicateKort(struct Kort* duplicate, struct Bunke* placeWhere){
    pushKort(placeWhere);
    placeWhere->tail->number = duplicate->number;
    placeWhere->tail->suit = duplicate->suit;
    placeWhere->tail->erSkjult = duplicate->erSkjult;
    strcpy(placeWhere->tail->name, duplicate->name);
}

void moveKort(struct Bunke* From, struct Bunke* To){
    if(From->head == NULL){                              //kant tilfælde
        return;
    }
    // Frakobling af kortet fra From bunken
    struct Kort *temp = From->tail;
    if(From->tail == From->head){                       // Kun et kort i bunken Form
        From->head = NULL;
        From->tail = NULL;
    } else {                                            // flere kort i bunken
        From->tail = From->tail->prev;
        From->tail->next = NULL;
    }
    // Til slutningen af kortet til To bunken
    if(To->tail == NULL){                               //ingen kort i bunken
        To->head = temp;
        To->tail = temp;
        temp->prev = NULL;

    } else{                                             //En eller flere kort i To bunken
        To->tail->next = temp;
        temp->prev = To->tail;
        To->tail = temp;
    }

}

void moveKortR(struct Bunke* From, struct Kort* whichCard, struct Bunke* To){
    if(From->head == NULL){                             //kant tilfælde
        return;
    }
    if(From->head == whichCard){                        //Flyt hele indholdet af bunken
        From->head = NULL;
        From->tail = NULL;
    } else {                                            // Flyt dele af bunkens indhold
        From->tail = whichCard->prev;
        From->tail->next = NULL;
    }
    //tilføj kortet til en ny bunke
    To->tail->next = whichCard;
    whichCard->prev = To->tail;
    while (whichCard->next != NULL){
        whichCard = whichCard->next;
    }
    To->tail = whichCard;
}


//Logik til spilstrukturen

void opsBunker() {
    if(head_p != NULL){
   //Opsæt af bunker i spillet
    }
    char *bunkeNavn[] = {"Column1", "Column2", "Column3", "Column4", "Column5",
                           "Column6", "Column7", "Foundation1", "Foundation2",
                           "Foundation3", "Foundation4", "sillygoose", NULL};
    for(int i = 0; i < 12; i++){
        opsBunker(bunkeNavn[i]);
    }
}

// denne funktion sletter og rydder de tilsluttede kort til den bunke, når der ikke er flere kort afsluttes while løkken
void resetKortspil(){
    while(tail_p != NULL) {
        popBunke(tail_p);
    }
    }
void ClearBunke(struct Bunke* Location){
    while(Location->tail!=NULL){
        removeKort(Location, Location->tail);
    }
}

/** Status for det der bliver returneret
 * hvis det er 0 der returneres, er der ikke nogen kort i bunken
 * hvis 1 returneres, er der noget galt med indholdet af kortene(enten ikke et kort, for mange kort eller for få kort
 * hvis 2, der er ingen problemer
 */

int DeckKontrol(struct Bunke* Location){
    struct KortSpil Status;
    char *content = "A23456789TJQK", suits[] = "DSHC";
    int tempSuit, tempNumber, cardCount = 0;
    if(Location->tail == NULL){
        return 0;                                               // Fejlen
    }
    //Initialiser status strukturen så de alle er 0
    for(int i = 0; i < 4;i++){
        Status.antalSuit[i] = 0;
        for(int j = 0; i < 14;i++){
            Status.SuitNo[i][j] = 0;
        }
    }
    struct Kort *temp = Location->head;
    //Nu finder vi navnet og værdien for hver af dem
    while(temp != NULL){
        tempSuit = -10;
        tempNumber = -10;
        cardCount++;
        if(cardCount== 53){                                     //kant tilfælde, for mange kot i deck
            ClearBunke(Location);
            return 1;
        }
        for(int i = 0; i < 14; i++){
            if(i == 13){                                        //kant tilfælde, kort eksistere ikke, resetter deck og returnere 1
                ClearBunke(Location);
                return 1;
            }
            if(content[i] == temp->name[0]){
                tempNumber = i;
                temp->number = i+1;
                break;
            }
        }
        for(int i = 0; i < 5; i++){
            if(i == 4){                                         //kant tilfælde, kort eksistere ikke og vil returnere 1
                ClearBunke(Location);
                return 1;
            }
            if(suits[i] == temp->name[1]){
                tempSuit = i;
                temp->suit = i+1;
                break;
            }
        }
        // status strukturen
        if(Status.SuitNo[tempSuit][tempNumber] != 0){
            ClearBunke(Location);
            return 1;
        } else{
            Status.SuitNo[tempSuit][tempNumber]++;
            Status.antalSuit[tempSuit]++;
        }
        temp = temp->next;
    }
    for(int i = 0; i<4; i++){
        if(Status.antalSuit[i] != 13){
            ClearBunke(Location);
            return 1;
        }
    }
    return 2;                                                    // deck er verificeret
}
//Auto generering af deck og opsætning af noder.
void autoDeck(){
    int i, j;
    char *content = "A23456789TJQK", suits[] = "DSHC";
    for(i = 0; i< 4;i++){
        for(j = 0; j < 13; j++){
            pushKort(tail_p);
            tail_p->tail->erSkjult = 1;
            tail_p->tail->name[1] = suits[i];
            tail_p->tail->name[0] = content[j];
            tail_p->tail->number = j+1;
            tail_p->tail->suit = i+1;
        }
    }
}
/**retunerings værdier
 * 0 betyder at deck er loaded forkert
 *  1 betyder at der er fejl i deck og at det ikke ser ud til at være sorteret rigtigt
 *  2 betyder at deck er verificeret og indlæst rigtigt
 *  3 betyder indlæsning af et sorteret deck
 */
int LD (char *argument) {
    if (argument == NULL) {
        autoDeck();
        return 3;
    }
    char tempArray[20];
    struct KortSpil status;
    FILE *fp;
    fp = fopen(&argument, "r");                // Åbner filen med 'read' muligheden
    if (fp == NULL) { exit(-1); }
    while (!feof(fp)) {
        fgets(tempArray, 20, fp);
        if (tempArray[strlen(tempArray) - 1] == '\n') {
            tempArray[strlen(tempArray) - 1] = 0;
        }
        if (strlen(tempArray) > 2) {//deck can't possibly be valid
            ClearBunke(tail_p);
            return 1;
        }
        pushKort(tail_p);
        tail_p->tail->erSkjult = 1;
        tail_p->tail->name[0] = tempArray[0];
        tail_p->tail->name[1] = tempArray[1];
    }
    fclose(fp);
    return DeckKontrol(tail_p);
}