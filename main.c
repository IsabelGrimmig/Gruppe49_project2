#include <stdio.h>
#include <stdlib.h>

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
struct Pile{
    char *beskrivelse;
    struct Pile* next;
    struct Pile* prev;

    struct Crad* head;
    struct Crad* tail;
};
// Reference til at kunne opsætte et korrekt format af kort spillet
struct KortSpil{
    int antalSuit[4];                   //diamonds = D, Spades = S, Harts = H, Clubs = C
    char SuitNo[4][13];
};

/**Nu vil vi opsætte node opperationer og bevægelige pointer*/


int main() {

};


