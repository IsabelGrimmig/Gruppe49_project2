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
    tempKort->prev = NULL
}

void removeKort(struct Bunke* Location, struct Kort* specifikKort){
    if (Location->head == Location->tail)

}

void pushBunke(char *identifier){

}

void popBunke(struct Bunke* Location){

}

void swap(struct Bunke* Location, int From, int To){

}

void duplicateKort(struct Kort* duplicate, struct Bunke* placeWhere){

}

void moveKort(struct Bunke* From, struct Bunke* to){

}

void moveKortR(struct Bunke* From, struct Kort* whichCart, struct Bunke* To){

}



