#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#define RESET     "\x1b[0m"
#define RED       "\x1b[31m"
#define GREEN     "\x1b[32m"
#define YELLOW    "\x1b[33m"

void Clear(){
    printf("\033[H\033[J");
}

struct Weapon{
    char Name[20];
    char Type[20];
    char Description[50];
    int damage;
    int crit_chance;
    int stamina_cost;
    int money_cost;
};

struct Defense{
    char Name[20];
    int damage_reduction;

};

struct Player{
    char name[50];
    int health;
    int stamina;
    int gold;
    struct Weapon Pweapon[6];
    struct Weapon Pdfense[4];
    int times_rested;
};

int MainPmenu(struct Player x[]){
    int option=0;
    printf("Pick an option below \n%-30s%s\n%-30s%s\n", "1. Use Equiped Item", "2. Equip an Item", "3. Rest", "4. Visit Shop");
    scanf("%i", &option);
    getchar();
    return option;
}

void Rest(struct Player *x){
    x->gold += 100 + 50 * (x->times_rested);
    x->stamina = 100;
    printf("You have "YELLOW "RESTED"RESET" and gained %i gold and your stamina is full\nCurrent Gold: %i\n", 100 + 50*(x->times_rested), x->gold);
    getchar();
    x->times_rested++;
}

void Capitalism(struct Player *x, struct Weapon w[]){
    int option=0;
    printf("Welcome to the "YELLOW"SHOP"RESET", this is were you can purchase weapons and defesive items\n" GREEN"It doesn't consume a turn to enter or purchase from the shop\n"RESET);
    printf("\n%-3s%-20s%-10s%-10s%-10s%-20s%s\n","", "Name", "Type", "Damage", "Crit %", "Stamina Cost", "Price");
    for (int i=0; i<16; i++){
        int owened=1;
        for (int n=0;n<6;n++){
            if (strcmp(x->Pweapon[n].Name, w[i].Name)==0){
                owened--;
            }
        }
        if (owened==1){
            printf("%-3i%-20s%-10s%-10i%-10i%-20i%i\n", i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].stamina_cost, w[i].money_cost);
        }
        else{
            printf("%-3i%-20s%-10s%-10i%-10i%-20i%s\n", i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].stamina_cost, "OWNED");
        }
    }
    scanf("%i", &option);
    getchar();
    printf("What would you ")
}


int main(){
    int option = 0;
    // Define all weapons and players
    struct Weapon melee[16] = {
        {"Fists", "Blunt", "Rated E for Everyone!", 5, 5, 1, 0},
        {"Metal Sword", "Sharp", "Can cut bread?(idk)", 15, 6, 5, 0},
        {"KILL ME NOW"},
    };
    struct Defense shield[3] = {
        {},
    };
    struct Defense teleport[2] = {
        {},
    };
    struct Player P[2] = {
        {"Player 1", 100, 100, 500, melee[0], melee[1], 0},
        {"Player 2", 100, 100, 450, melee[0], melee[1], 0},
    };
    while(1){
        Clear();
        option = MainPmenu(P);
        switch (option){
            case 3:
                Rest(&P[0]);
                break;
            case 4:
                Capitalism(&P[0], melee);
                break;
        }
    }

    return 0;
}
