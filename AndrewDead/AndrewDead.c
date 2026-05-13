#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#define BOLD      "\x1b[1m"
#define RESET     "\x1b[0m"
#define RED       "\x1b[31m"
#define GREEN     "\x1b[32m"
#define YELLOW    "\x1b[33m"
#define BLUE      "\x1b[34m"

void Clear(){
    printf("\033[H\033[J");
}

struct Weapon{
    char Name[20];
    char Type[20];
    int id;
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
    struct Weapon equipped_weapon;
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

int FullInventoryChecker(struct Player x, int type){
    int items=0;
    for (int i=0;i<6;i++){
        switch (type) {
            case 1:
                if (x.Pweapon[i].id==0){
                    items++;
                }
                break;
            case 2:
                if (x.Pdfense->id!=0){
                    items++;
                }
                break;
        }
    }
    return items-2;
}

int Capitalism(struct Player *x, struct Weapon w[]){
    int option=0;
    printf("Welcome to the "BLUE"SHOP"RESET", this is were you can purchase weapons and defesive items\n" BOLD"It doesn't consume a turn to enter or purchase from the shop\n\n"RESET);
    printf("Your current balence is"YELLOW" %i gold"RESET, x->gold);
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
    printf("Enter 0 to leave the shop\n\n");
    scanf("%i", &option);
    getchar();
    if (option==0){
        return 0;
    }
    printf("What would you like to do with "BLUE"%s?\n"RESET, w[option-1].Name);
    printf("Pick an option below \n%-30s%s\n", "1. Buy", "2. Go back");
    int in_inventory=0;
    for(int i=0; i<6; i++){
        if (w[option-1].id==x->Pweapon[i].id){
            in_inventory++;
            printf("3. Sell\n");
        }
    }
    int doOption=0;
    scanf("%i", &doOption);
    getchar();
    if (doOption == 2){
        return 1;
    }
    else if (doOption == 1  && w[option-1].money_cost <= x->gold && FullInventoryChecker(*x, 1)<6){
        printf("You have purchased "BLUE"%s\n"RESET, w[option-1].Name);
        printf("You now have "YELLOW"%i"RESET" coins.\n", x->gold - w[option-1].money_cost);
        x->gold -= w[option-1].money_cost;
        x->Pweapon[FullInventoryChecker(*x, 1)]=w[option-1];
        getchar();
    }
    else if (w[option-1].money_cost > x->gold){
        printf("You do not have enough gold to buy this item.\n");
        getchar();
        sleep(5);
        return 1;
    }
    return 0;
}

void EquipItem(struct Player *P){
    int option=0;
    printf("Which item would you like to equip?\n");
    for (int i=0; i<6; i++){
        if (P->Pweapon[i].Name[0] != '\0'){
            printf("%i. %s\n", i+1, P->Pweapon[i].Name);
        }
    }
    scanf("%i", &option);
    getchar();
    printf("You have eqquped "BOLD"%s"RESET, P->Pweapon[option-1].Name);
    P->equipped_weapon = P->Pweapon[option-1];
    getchar();
}

void UseItem(struct Player *P, struct Weapon *w[]){
    if (P->equipped_weapon.Name[0] == '\0'){
        printf("You have no equipped item.\n");
    }

}

int main(){
    int option = 0;
    // Define all weapons and players
    struct Weapon melee[17] = {
        {"Fists", "Blunt", 1, 5, 5, 1, 0}, {"Rusty Sword", "Sharp", 2, 15, 6, 5, 0},
        {"Metal Hatchet", "Sharp", 3, 20, 6, 10, 180}, {},
        {},{},
        {},{},
        {},{},
        {},{},
        {},{},
        {},{},
    };
    struct Defense shield[3] = {
        {},
    };
    struct Defense teleport[2] = {
        {},
    };
    struct Player P[2] = {
        {"Player1", 100, 100, 500, melee[0],melee[1], 0},
        {"Player2", 100, 100, 550, melee[0],melee[1], 0},
    };
    int player_turn=0;

    //printf("Player 1, enter your name:\n");
    //scanf("%s", P[0].name);
    //printf("\nPlayer 2, enter your name:\n");
    //scanf("%s", P[1].name);

    while(1){
        Clear();
        printf("It's "BLUE"%s's"RESET" turn\n", P[player_turn%2].name);
        option = MainPmenu(P);
        switch (option){
            case 2:
                Clear();
                EquipItem(&P[player_turn%2]);
                continue;
            case 3:
                Rest(&P[player_turn%2]);
                break;
            case 4:
                Clear();
                while (Capitalism(&P[player_turn%2], melee) == 1){
                    Clear();
                    Capitalism(&P[player_turn%2], melee);
                }
                continue;
        }
        if (P[player_turn%2].times_rested<2){
            P[player_turn%2].times_rested=0;
        }
        player_turn++;
    }

    return 0;
}
