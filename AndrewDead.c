#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <string.h>
#define RESET     "\x1b[0m"
#define BOLD      "\x1b[1m"
#define RED       "\x1b[31m"
#define GREEN     "\x1b[32m"
#define YELLOW    "\x1b[33m"
#define BLUE      "\x1b[34m"
#define CYAN      "\x1b[36m"
#define ROWS 7
#define COLS 6
const char *letters[26][ROWS] = {
    { // A
        " AAA ",
        "A   A",
        "A   A",
        "AAAAA",
        "A   A",
        "A   A",
        "A   A"
    },
    { // B
        "BBBB ",
        "B   B",
        "BBBB ",
        "B   B",
        "B   B",
        "BBBB ",
        "     "
    },
    { // C
        " CCC ",
        "C   C",
        "C    ",
        "C    ",
        "C    ",
        "C   C",
        " CCC "
    },
    { // D
        "DDDD ",
        "D   D",
        "D   D",
        "D   D",
        "D   D",
        "D   D",
        "DDDD "
    },
    { // E
        "EEEEE",
        "E    ",
        "E    ",
        "EEEE ",
        "E    ",
        "E    ",
        "EEEEE"
    },
    { // F
        "FFFFF",
        "F    ",
        "F    ",
        "FFF  ",
        "F    ",
        "F    ",
        "F    "
    },
    { // G
        " GGG ",
        "G   G",
        "G    ",
        "G GGG",
        "G   G",
        "G   G",
        " GGG "
    },
    { // H
        "H   H",
        "H   H",
        "H   H",
        "HHHHH",
        "H   H",
        "H   H",
        "H   H"
    },
    { // I
        "IIIII",
        "  I  ",
        "  I  ",
        "  I  ",
        "  I  ",
        "  I  ",
        "IIIII"
    },
    { // J
        "JJJJJ",
        "    J",
        "    J",
        "    J",
        "    J",
        "    J",
        "JJJJ "
    },
    { // K
        "K   K",
        "K  K ",
        "K K  ",
        "KK   ",
        "K K  ",
        "K  K ",
        "K   K"
    },
    { // L
        "L    ",
        "L    ",
        "L    ",
        "L    ",
        "L    ",
        "L    ",
        "LLLLL"
    },
    { // M
        "M   M",
        "MM MM",
        "M M M",
        "M   M",
        "M   M",
        "M   M",
        "M   M"
    },
    { // N
        "N   N",
        "NN  N",
        "N N N",
        "N  NN",
        "N   N",
        "N   N",
        "N   N"
    },
    { // O
        " OOO ",
        "O   O",
        "O   O",
        "O   O",
        "O   O",
        "O   O",
        " OOO "
    },
    { // P
        "PPPP ",
        "P   P",
        "P   P",
        "PPPP ",
        "P    ",
        "P    ",
        "P    "
    },
    { // Q
        " QQQ ",
        "Q   Q",
        "Q   Q",
        "Q   Q",
        "Q   Q",
        "Q  Q ",
        " QQ Q"
    },
    { // R
        "RRRR ",
        "R   R",
        "R   R",
        "RRRR ",
        "R R  ",
        "R  R ",
        "R   R"
    },
    { // S
        " SSS ",
        "S   S",
        "S    ",
        " SSS ",
        "    S",
        "S   S",
        " SSS "
    },
    { // T
        "TTTTT",
        "  T  ",
        "  T  ",
        "  T  ",
        "  T  ",
        "  T  ",
        "  T  "
    },
    { // U
        "U   U",
        "U   U",
        "U   U",
        "U   U",
        "U   U",
        "U   U",
        " UUU "
    },
    { // V
        "V   V",
        "V   V",
        "V   V",
        "V   V",
        "V   V",
        " V V ",
        "  V  "
    },
    { // W
        "W   W",
        "W   W",
        "W   W",
        "W W W",
        "W W W",
        "WW WW",
        "W   W"
    },
    { // X
        "X   X",
        "X   X",
        " X X ",
        "  X  ",
        " X X ",
        "X   X",
        "X   X"
    },
    { // Y
        "Y   Y",
        "Y   Y",
        " Y Y ",
        "  Y  ",
        "  Y  ",
        "  Y  ",
        "  Y  "
    },
    { // Z
        "ZZZZZ",
        "   Z ",
        "  Z  ",
        " Z   ",
        "Z    ",
        "     ",
        "ZZZZZ"
    }
};
void print_ascii(const char *text) {
    // Print each char as 7-row ASCII art, row by row; spaces = 6 blanks
    for (int row = 0; row < ROWS; row++) {
        for (int i = 0; text[i]; i++) {
            if (text[i] == ' ') {
                printf("      ");
            } else {
                int idx = text[i] - 'A';
                if (idx >= 0 && idx < 26) {
                    printf("%s ", letters[idx][row]);
                    usleep(5000);
                }
            }
        }
        printf("\n");
    }
}


int rb(int min, int max)
{
   return min + rand() % (max+1 - min);
}

void Clear(){
    printf("\033[H\033[J");
}

struct Weapon{
    char Name[20];
    char Type[20];
    int id;
    int damage;
    int crit_chance;
    int money_cost;
    int damage_reduction;
    int cooldown;
    int coountdown;
    int class_res;
    int last_used;
};

struct Player{
    char name[50];
    float health;
    int gold;
    struct Weapon Pweapon[6];
    struct Weapon Pdfense[4];
    int times_rested;
    struct Weapon equipped_weapon;
    struct Weapon equipped_defense;
    int status_effect;
    int durration;
};

int SignsOfLife(struct Player x){
    if (x.health>0){return 1;}
    else{return 0;}
}

int MainPmenu(struct Player x){
    int option=0;
    printf(BOLD"|=----------------==MAIN-MENU==----------------=|\n\n"RESET);
    printf("It's "CYAN"%s's"RESET" turn\n\n", x.name);
    printf(RED"Health:"RESET" %g    "YELLOW"Gold:"RESET" %i\n\n", x.health, x.gold);
    printf(BOLD"Pick an option below \n%-30s%s\n%-30s%s\n", "1. Use Equiped Item", "2. Equip an Item", "3. Rest", "4. Visit Shop");
    printf("\n|=----------------======-======----------------=|\n"RESET);
    scanf("%i", &option);
    getchar();
    return option;
}

void Rest(struct Player *x){
    Clear();
    x->gold += 100 + 50 * (x->times_rested);
    x->health += 9;
    printf("You have "GREEN "RESTED"RESET" and gained %i gold and 9 health\nCurrent "YELLOW"Gold"RESET": %i\nCurrent "RED"Health"RESET": %g\n", 100 + 50 * (x->times_rested), x->gold, x->health);
    getchar();
    x->times_rested++;
    if (x->times_rested>3){
        x->times_rested=0;
    }
}

int FullInventoryChecker(struct Player x, int type){
    // Returns first empty slot index (weapon: damage<5||>90, defense: id==0), or -1 if full
    for (int i = 0; i < type; i++){
        if (type == 4){
            if (x.Pdfense[i].id == 0){
                return i;
            }
        } else {
            if (x.Pweapon[i].damage<5 ||x.Pweapon[i].damage>90){
                return i;
            }
        }
    }
    return -1;
}

int item_in_inventory(struct Player x, struct Weapon w, int type){
    // Check if item is already owned by name match; returns slot index or -1
    for (int i = 0; i < type; i++){
        if (type == 4){
            if (strcmp(x.Pdfense[i].Name, w.Name)==0){
                return i;
            }
        } else {
            if (strcmp(x.Pweapon[i].Name, w.Name)==0){
                return i;
            }
        }
    }
    return -1;
}

int Capitalism(struct Player *x, struct Weapon w[]){
    // Shop: lists 17 weapons and 10 defenses with color-coded affordability/ownership
    // Allows buying (if affordable + space) and selling (half price refund)
    // Returns 0 if purchase/sell happened (consumes turn), 1 otherwise
    int option=0;
    printf("Welcome to the "BLUE"SHOP"RESET", this is were you can purchase weapons and defesive items\n" BOLD"It doesn't consume a turn to enter, but it does to purchase/sell from the shop\n"RESET);
    printf("Your current balence is"YELLOW" %i gold"RESET, x->gold);
    printf(CYAN"\nOffensive items"RESET);
    printf(BOLD"\n%-3s%-20s%-10s%-10s%-10s%-10s%s\n"RESET,"", "Name", "Type", "Damage", "Crit %", "Cooldown", "Price");
    for (int i=0; i<17; i++){
        int notowened=1;
        if (item_in_inventory(*x, w[i], 6)>=0){
            notowened--;
        }
        if (notowened==1 && w[i].money_cost<=x->gold){
            printf(GREEN"%-3i"RESET"%-20s%-10s%-10i%-10i%-10i"GREEN"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].cooldown-1, w[i].money_cost);
        }
        else if (notowened==1 && w[i].money_cost>x->gold){
            printf(RED"%-3i"RESET"%-20s%-10s%-10i%-10i%-10i"RED"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].cooldown-1, w[i].money_cost);
        }
        else{
            printf(BLUE"%-3i"RESET"%-20s%-10s%-10i%-10i%-10i%s\n", i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].cooldown-1, BLUE"OWNED"RESET);
        }
    }
    printf(CYAN"\nDefeeisive items"RESET);
    printf(BOLD"\n%-3s%-20s%-20s%-15s%s\n","", "Name", "Class", "Reduction %", "Price"RESET);
    for (int i=17; i<27; i++){
        int notowened=1;
        if (item_in_inventory(*x, w[i], 4)>=0){
            notowened--;
        }
        if (notowened==1 && w[i].money_cost<=x->gold){
            printf(GREEN"%-3i"RESET"%-20s%-20s%-15i"GREEN"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage_reduction, w[i].money_cost);
        }
        else if (notowened==1 && w[i].money_cost>x->gold){
            printf(RED"%-3i"RESET"%-20s%-20s%-15i"RED"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage_reduction, w[i].money_cost);
        }
        else{
            printf(BLUE"%-3i"RESET"%-20s%-20s%-15i%s\n", i+1, w[i].Name, w[i].Type, w[i].damage_reduction, BLUE"OWNED"RESET);
        }
    }
    printf("Enter 0 to leave the shop\n");
    scanf("%i", &option);
    getchar();
    int type=0;
    if (option==0){
        return 1;
    }
    else if (option>=18 && option <=27){
        type = 4;
    }
    else if (option>=1 && option <=17){
        type = 6;
    }
    else{
        printf("WRONG, stupid. I told you to pick an option.");
        getchar();
        return 1;
    }
    printf("What would you like to do with "BLUE"%s?\n"RESET, w[option-1].Name);
    printf("Pick an option below \n%-30s%s\n", "1. Buy", "2. Go back");
    if (item_in_inventory(*x, w[option-1], type)>=0){
        printf("3. Sell\n");
    }
    int doOption=0;
    scanf("%i", &doOption);
    getchar();

    if (doOption == 3 && item_in_inventory(*x, w[option-1], type)>=0){
        int slot = item_in_inventory(*x, w[option-1], type);
        printf("You have sold "BLUE"%s"RESET" and retained half it's value of "YELLOW"%i\n"RESET, w[option-1].Name, w[option-1].money_cost/2);
        printf("You now have "YELLOW"%i"RESET" coins.\n", x->gold + w[option-1].money_cost/2);
        x->gold += w[option-1].money_cost/2;
        if (type==4){
            memset(&x->Pdfense[slot], 0, sizeof(struct Weapon));
        }
        else{
            memset(&x->Pweapon[slot], 0, sizeof(struct Weapon));
        }
        if (x->equipped_defense.id==w[option-1].id){
            printf(BLUE"%s"RESET" has been removed from your inventory", x->equipped_defense.Name);
            memset(&x->equipped_defense, 0, sizeof(struct Weapon));
        }
        if (x->equipped_weapon.id==w[option-1].id){
            printf(BLUE"%s"RESET" has been removed from your inventory", x->equipped_weapon.Name);
            memset(&x->equipped_weapon, 0, sizeof(struct Weapon));
        }
        getchar();
        Clear();
    }
    else if (doOption == 1 && w[option-1].money_cost <= x->gold && FullInventoryChecker(*x, type) != -1 && item_in_inventory(*x, w[option-1], type) == -1){
        int slot = FullInventoryChecker(*x, type);
        printf("You have purchased "BLUE"%s :]\n"RESET, w[option-1].Name);
        printf("You now have "YELLOW"%i"RESET" coins.\n", x->gold - w[option-1].money_cost);
        x->gold -= w[option-1].money_cost;
        if (type==4){
            x->Pdfense[slot]=w[option-1];
        }
        else{
            x->Pweapon[slot]=w[option-1];
        }
        getchar();

    }
    else if (doOption==2) {
        return 1;
    }
    else if (w[option-1].money_cost > x->gold){
        printf("You are too poor to buy this item :(\n");
        getchar();getchar();
        return 1;
    }
    else if (FullInventoryChecker(*x, type)==-1){
        printf("Your inventory is full, sell a weapon if buyng a weapon, or a defence if buying a defence item to clear it up");
        getchar();
        return 1;
    }
    return 0;
}

int EquipItem(struct Player *P, int player_turn){
    // Show weapons; ones on cooldown appear red and are unequippable
    int option=0;
    printf("Which item would you like to equip?\nEnter 0 to go back\n");
    for (int i=0; i<6; i++){
        if (P->Pweapon[i].Name[0] != '\0' && P->Pweapon[i].last_used==0){
            printf(BLUE"%i. %s\n"RESET, i+1, P->Pweapon[i].Name);
        }
        else if (P->Pweapon[i].Name[0] != '\0' && P->Pweapon[i].last_used!=0){
            printf(RED"%i. %s\n"RESET, i+1, P->Pweapon[i].Name);
        }
    }
    scanf("%i", &option);
    getchar();
    if (option<=0){return 2;}
    else if (P->Pweapon[option-1].last_used!=0){printf("\nWeapon is in cooldown, you have "CYAN"%i"RESET" turns left", ((P->Pweapon[option-1].last_used+P->Pweapon[option-1].cooldown)-player_turn)/2);
        getchar();
        return 2;}
    printf("You have eqquped "BOLD"%s"RESET, P->Pweapon[option-1].Name);
    P->equipped_weapon = P->Pweapon[option-1];
    getchar();
    return 1;
}

int Equipdefense(struct Player *P){
    if(FullInventoryChecker(*P, 4)==0){
        printf("You have no defences");
        getchar();
        return 2;
    }
    int option=0;
    printf("Which item would you like to equip?\nEnter 0 to go back\n");
    for (int i=0; i<4; i++){
        if (P->Pdfense[i].Name[0] != '\0'){
            printf(BLUE"%i. %s\n"RESET, i+1, P->Pdfense[i].Name);
        }
    }
    scanf("%i", &option);
    getchar();
    if (option<=0){return 2;}
    printf("You have eqquped "BOLD"%s"RESET, P->Pdfense[option-1].Name);
    P->equipped_defense = P->Pdfense[option-1];
    getchar();
    return 1;
}

int UseWeaponItem(struct Player *P, int player_turn){
    // Attack: apply weapon damage, check crit, apply defense reduction (full if class matches, half otherwise)
    // Then apply cooldown to the weapon slot
    Clear();
    int attacker = player_turn % 2, defender = (player_turn + 1) % 2;
    float total_damage = P[attacker].equipped_weapon.damage;
    if (P[attacker].equipped_weapon.id<=0){
        printf("You have no eqquiped weapon\n");
        getchar();
        return 2;
    }
    if (P[attacker].equipped_weapon.crit_chance > rb(0,100)){
        total_damage *= 1.5;
        printf(CYAN"%s's"RESET" weapon has CRIT and did "BOLD"1.5x"RESET" damage.\n", P[attacker].name);
        if (P[attacker].equipped_weapon.class_res==1){
            printf(CYAN"%s"RESET" adds the "RED"BLEEDING"RESET" effect to %s (-2 hp for the next 2 turns)", P[attacker].name, P[defender].name);
        }
    }
    if (P[defender].equipped_defense.id != 0){
        float reduction;
        if (P[attacker].equipped_weapon.class_res==P[defender].equipped_defense.class_res || P[defender].equipped_defense.class_res==4){
            reduction = P[defender].equipped_defense.damage_reduction / 100.0;
            printf(CYAN"%s's"RESET" defense of a matching class blocked"RED" %g "RESET"out of "RED" %g "RESET"damage\n", P[defender].name, total_damage*reduction, total_damage);
        }
        else{
            reduction = P[defender].equipped_defense.damage_reduction / 200.0;
            printf(CYAN"%s's"RESET" defense of a non-matching class blocked "RED"%g"RESET" out of "RED"%g"RESET" damage\n", P[defender].name, total_damage*reduction, total_damage);
        }
        total_damage -= total_damage * reduction;
        printf(BLUE"\n%s"RESET" did "RED"%g"RESET" damage to "BLUE"%s"RESET".\n\n",
            P[attacker].name, total_damage, P[defender].name);
        printf("Old Health: "RED"%g"RESET"\nNew Health: "RED"%g"RESET, P[defender].health, P[defender].health-total_damage);


        P[defender].health -= total_damage;
        if (P[attacker].equipped_weapon.cooldown!=1){
            printf(CYAN"\n%s"RESET"'s weapon is now on COOLDOWN with "CYAN"%i"RESET" turns left", P[attacker].name, P[attacker].equipped_weapon.cooldown-1);
            getchar();
            P[attacker].equipped_weapon.last_used=player_turn-P[attacker].equipped_weapon.cooldown;
            for (int i=0; i<6; i++){
                if (P[attacker].equipped_weapon.id==P[attacker].Pweapon[i].id){
                    P[attacker].Pweapon[i].id=0;
                    P[attacker].Pweapon[i].last_used=player_turn+P[attacker].Pweapon[i].cooldown;
                }
            }
            P[attacker].equipped_weapon.id=0;}
        else{getchar();}
    }
    else{
        P[defender].health -= total_damage;
        printf(BLUE"%s"RESET" did "RED"%g"RESET" damage to "BLUE"%s"RESET".\n", P[attacker].name, total_damage, P[defender].name);
        printf("Old Health: "RED"%g"RESET"\nNew Health: "RED"%g"RESET, P[defender].health + total_damage, P[defender].health);
        if (P[attacker].equipped_weapon.cooldown!=1){
            printf(CYAN"\n%s"RESET"'s weapon is now on COOLDOWN with "CYAN"%i"RESET" turns left", P[attacker].name, P[attacker].equipped_weapon.cooldown-1);
            getchar();
            P[attacker].equipped_weapon.last_used=player_turn-P[attacker].equipped_weapon.cooldown;
            for (int i=0; i<6; i++){
                if (P[attacker].equipped_weapon.id==P[attacker].Pweapon[i].id){
                    P[attacker].Pweapon[i].id=0;
                    P[attacker].Pweapon[i].last_used=player_turn+P[attacker].Pweapon[i].cooldown;
                }
            }
            P[attacker].equipped_weapon.id=0;}
        else{getchar();}
    }
    return 1;
}

void weapon_checkek(struct Player *x, int player_turn, struct Weapon master[]){
    // Restore weapon IDs when cooldown expires (if last_used + cooldown == player_turn)
    if (x->equipped_weapon.cooldown+x->equipped_weapon.last_used==player_turn){
        x->equipped_weapon.last_used=0;
        for (int j=0; j<17; j++){
            if (strcmp(x->equipped_weapon.Name, master[j].Name)==0){
                x->equipped_weapon.id = master[j].id;
            }
        }
    }
    for (int i=0; i<6; i++){
        if (x->Pweapon[i].cooldown+x->Pweapon[i].last_used==player_turn){
            x->Pweapon[i].last_used=0;
            for (int j=0; j<17; j++){
                if (strcmp(x->Pweapon[i].Name, master[j].Name)==0){
                    x->Pweapon[i].id = master[j].id;
                }
            }
        }
    }
}

int main(){
    int option = 0;
    // Master list: 17 weapons (id 1-17), then 10 defense items (id 18-27)
    struct Weapon melee[27] = {
    //  Name                   Type           ID   Damage    CritChance      Cost    Cooldown           weekness
        {"Fists",              "Blunt",        1,     5,       15,              0,   .cooldown = 1, .class_res = 2},
        {"Rusty Sword",        "Sharp",        2,    10,       18,              0,   .cooldown = 1, .class_res = 1},
        {"Kitchen Knife",      "Sharp",        3,    12,       20,            200,   .cooldown = 2, .class_res = 1},
        {"Stink Bomb",         "Explosive",    4,    25,        1,            680,   .cooldown = 3, .class_res = 3},
        {"Metal Hatchet",      "Sharp",        5,    14,       40,            420,   .cooldown = 2, .class_res = 1},
        {"Baseball Bat",       "Blunt",        6,    15,       25,            400,   .cooldown = 2, .class_res = 2},
        {"Trick Knife",        "Sharp",        7,    17,       42,            551,   .cooldown = 2, .class_res = 1},
        {"Person Beater",      "Blunt",        8,    22,       28,            600,   .cooldown = 2, .class_res = 2},
        {"Murder Of Crowbars", "Blunt",        9,    28,       22,            640,   .cooldown = 2, .class_res = 2},
        {"Pipe Bomb",          "Explosive",   10,    40,        5,            800,   .cooldown = 4, .class_res = 3},
        {"Crossedbow",         "Sharp",       11,    34,       32,           1000,   .cooldown = 2, .class_res = 1},
        {"Leviathan Axe",      "Sharp",       12,    48,       28,           1350,   .cooldown = 3, .class_res = 1},
        {"Rubber Ducky",       "Explosive",   13,    70,        3,           1799,   .cooldown = 7, .class_res = 3},
        {"Katana",             "Sharp",       14,    52,       45,           2200,   .cooldown = 3, .class_res = 1},
        {"Chainsword",         "Sharp",       15,    60,       22,           2500,   .cooldown = 4, .class_res = 1},
        {"Sledgehammer",       "Blunt",       16,    65,       28,           3000,   .cooldown = 4, .class_res = 2},
        {"BoomBoom Gun",       "Explosive",   17,    90,        5,           3500,   .cooldown = 4, .class_res = 3},
    //   Name                 Type                    ID                   Cost                Reduction            class identifier
        {"Knif-vest",         "Light-Chainmail",      18,     .money_cost=   250,   .damage_reduction=18, .class_res = 1},
        {"hurty-vest",        "Light-Kevlar",         19,     .money_cost=   260,   .damage_reduction=18, .class_res = 2},
        {"bombom suit",       "Light-Bombsuit",       20,     .money_cost=   232,   .damage_reduction=22, .class_res = 3},
        {"knif-hat",          "Mid-Chainmail",        21,     .money_cost=   543,   .damage_reduction=32, .class_res = 1},
        {"hurty hat",         "Mid-Kevlar",           22,     .money_cost=   561,   .damage_reduction=30, .class_res = 2},
        {"kablosh hat",       "Mid-Bombsuit",         23,     .money_cost=   539,   .damage_reduction=38, .class_res = 3},
        {"nif armer",         "Strong-Chainmail",     24,     .money_cost=   999,   .damage_reduction=40, .class_res = 1},
        {"owie armor",        "Strong-Kevlar",        25,     .money_cost=  1350,   .damage_reduction=45, .class_res = 2},
        {"boom armoer",       "Strong-Bombgsuit",     26,     .money_cost=  1240,   .damage_reduction=40, .class_res = 3},
        {"everything armor",  "Storng-Special",       27,     .money_cost=  2500,   .damage_reduction=35, .class_res = 4},
    };
    struct Player P[2] = {
        {.name = "Jim Pickens", .health = 100, .gold = 500, .Pweapon = {melee[0], melee[1]}, .times_rested = 0},
        {.name = "TURG",        .health = 100, .gold = 550, .Pweapon = {melee[0], melee[1]}, .times_rested = 0},
    };
    int player_turn=0;

    //Gotta get dat dev logo
    printf("\nPress enter to continue\n"RED BOLD);
    print_ascii("ANDREW HELD HOSTAGE");
    printf(RESET);
    getchar();
    Clear();

    // Overwrite default names with player input
    printf("Player 1, enter your name:\n");
    fgets(P[0].name, sizeof(P[0].name), stdin);
    P[0].name[strcspn(P[0].name, "\n")] = 0;
    printf("\nPlayer 2, enter your name:\n");
    fgets(P[1].name, sizeof(P[0].name), stdin);
    P[1].name[strcspn(P[1].name, "\n")] = 0;
    // */

    // Main game loop: each iteration is one player's turn; alternates via player_turn%2
    while(1){
        Clear();
        weapon_checkek(&P[player_turn%2],player_turn, melee);
        option = MainPmenu(P[player_turn%2]);
        switch (option){
            case 1:
                if (UseWeaponItem(P, player_turn)!=1){player_turn--;}
                break;
            case 2:
                Clear();
                int word = -1;
                while(word<0||word>2){
                    printf("Enter 1 to equip your "RED"weapon"RESET", 2 for your "BLUE"defence"RESET", and 0 to go back\n");
                    scanf("%i", &word);
                    getchar();
                }
                if (word==1){EquipItem(&P[player_turn%2], player_turn);}
                else if(word ==2){Equipdefense(&P[player_turn%2]);}
                player_turn--;
                break;
            case 3:
                Rest(&P[player_turn%2]);
                break;
            case 4:
                Clear();
                if (Capitalism(&P[player_turn%2], melee)==1){player_turn--;}
                break;
            default:
                printf("\nWrong, stupid!\nMake sure you enter AN ACUTAL OPTION, i'm skipping ur turn,\nyou waste of matter.");
                getchar();
                break;
        }
        P[player_turn%2].gold*=1.1;
        player_turn++;
        if(P[player_turn%2].status_effect==1 && P[player_turn%2].durration+2!=player_turn){
            P[player_turn%2].health-=2;
        }
        // Check if the next player to act is dead; if so, print death/winner ASCII and end
        if (SignsOfLife(P[player_turn%2])==0){
            printf(RED"%s is \n\n", P[player_turn%2].name);
            print_ascii("D E A D");
            printf(GREEN"\n%s is the\n\n", P[(player_turn+1)%2].name);
            print_ascii("W I N N E R");
            getchar();
            break;
        }
    }return 0;}///actual is number - 254 for ANDREW HELD HOSTAGE
