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

int rb (int min, int max){
  return rand() % (max - min + 1) + min;
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
    float defense_durability;
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
};

int SignsOfLife(struct Player x){
    if (x.health>=0){return 1;}
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
    x->health += 7;
    printf("You have "GREEN "RESTED"RESET" and gained %i gold and 7 health\nCurrent "YELLOW"Gold"RESET": %i\nCurrent "RED"Health"RESET": %g\n", 100 + 50 * (x->times_rested), x->gold, x->health);
    getchar();
    x->times_rested++;
    if (x->times_rested>3){
        x->times_rested=0;
    }
}

int FullInventoryChecker(struct Player x, int type){
    int limit = (type == 4) ? 4 : 6;
    for (int i = 0; i < limit; i++){
        if (type == 4){
            if (x.Pdfense[i].id == 0){
                return i;
            }
        } else {
            if (x.Pweapon[i].id == 0){
                return i;
            }
        }
    }
    return -1;
}

int item_in_inventory(struct Player x, struct Weapon w, int type){
    int limit = (type == 4) ? 4 : 6;
    for (int i = 0; i < limit; i++){
        if (type == 4){
            if (w.id == x.Pdfense[i].id){
                return i;
            }
        } else {
            if (w.id == x.Pweapon[i].id){
                return i;
            }
        }
    }
    return -1;
}

int Capitalism(struct Player *x, struct Weapon w[]){
    int option=0;
    printf("Welcome to the "BLUE"SHOP"RESET", this is were you can purchase weapons and defesive items\n" BOLD"It doesn't consume a turn to enter or purchase from the shop\n\n"RESET);
    printf("Your current balence is"YELLOW" %i gold"RESET, x->gold);
    printf(CYAN"\n\nOffensive items"RESET);
    printf(BOLD"\n%-3s%-20s%-10s%-10s%-10s%s\n"RESET,"", "Name", "Type", "Damage", "Crit %", "Price");
    for (int i=0; i<17; i++){
        int notowened=1;
        if (item_in_inventory(*x, w[i], 6)>=0){
            notowened--;
        }
        if (notowened==1 && w[i].money_cost<=x->gold){
            printf("%-3i%-20s%-10s%-10i%-10i"GREEN"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].money_cost);
        }
        else if (notowened==1 && w[i].money_cost>x->gold){
            printf("%-3i%-20s%-10s%-10i%-10i"RED"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, w[i].money_cost);
        }
        else{
            printf("%-3i%-20s%-10s%-10i%-10i%s\n", i+1, w[i].Name, w[i].Type, w[i].damage, w[i].crit_chance, BLUE"OWNED"RESET);
        }
    }
    printf(CYAN"\nDefeeisive items"RESET);
    printf(BOLD"\n%-3s%-20s%-10s%-15s%-15s%s\n","", "Name", "Class", "Reduction %", "Durability", "Price"RESET);
    for (int i=17; i<27; i++){
        int notowened=1;
        if (item_in_inventory(*x, w[i], 4)>=0){
            notowened--;
        }
        if (notowened==1 && w[i].money_cost<=x->gold){
            printf("%-3i%-20s%-10s%-15i%-15f"GREEN"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage_reduction, w[i].defense_durability, w[i].money_cost);
        }
        else if (notowened==1 && w[i].money_cost>x->gold){
            printf("%-3i%-20s%-10s%-15i%-15f"RED"%i\n"RESET, i+1, w[i].Name, w[i].Type, w[i].damage_reduction, w[i].defense_durability, w[i].money_cost);
        }
        else{
            printf("%-3i%-20s%-10s%-15i%-15f%s\n", i+1, w[i].Name, w[i].Type, w[i].damage_reduction, w[i].defense_durability, BLUE"OWNED"RESET);
        }
    }
    printf("Enter 0 to leave the shop\n\n");
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
    printf(RED"\n%i\n"RESET, item_in_inventory(*x, w[option-1], type));
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
            x->Pdfense[slot].id=0;
        }
        else{
            x->Pweapon[slot].id=0;
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
    }
    else if (doOption == 1 && w[option-1].money_cost <= x->gold && FullInventoryChecker(*x, type) != -1 && item_in_inventory(*x, w[option-1], type) == -1){
        int slot = FullInventoryChecker(*x, type);
        printf("You have purchased "BLUE"%s\n"RESET, w[option-1].Name);
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
        printf("You do not have enough gold to buy this item.\n");
        getchar();
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
    else if (P->Pweapon[option-1].last_used!=0){printf("\nWeapon is in cooldown, you have "CYAN"%i"RESET" turns left");
        getchar();
        return 2;}
    printf("You have eqquped "BOLD"%s"RESET, P->Pweapon[option-1].Name);
    P->equipped_weapon = P->Pweapon[option-1];
    getchar();
    return 1;
}

int Equipdefense(struct Player *P){
    int option=0;
    printf("Which item would you like to equip?\nEnter 0 to go back\n");
    for (int i=0; i<4; i++){
        if (P->Pdfense[i].Name[0] != '\0'){
            printf("%i. %s\n", i+1, P->Pdfense[i].Name);
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
    Clear();
    int attacker = player_turn % 2, defender = (player_turn + 1) % 2;
    float total_damage = P[attacker].equipped_weapon.damage;
    if (P[attacker].equipped_weapon.id<=0){
        printf("You have no eqquiped weapon\n");
        getchar();
        return 2;
    }
    if (P[attacker].equipped_weapon.crit_chance > rb(1,100)){
        total_damage *= 2;
        printf(CYAN"%s's"RESET" weapon has CRIT and did double damage.\n", P[attacker].name);
    }
    if (P[defender].equipped_defense.id != 0){
        float reduction = P[defender].equipped_defense.damage_reduction / 100.0;
        total_damage -= total_damage * reduction;
        P[defender].health -= total_damage;
        printf(BLUE"%s"RESET" did "RED"%g"RESET" damage to "BLUE"%s"RESET".\n"BLUE"%s"RESET" blocked "BLUE"%i percent"RESET"\n",
            P[attacker].name, total_damage, P[defender].name,
            P[defender].name, P[defender].equipped_defense.damage_reduction);
        printf("Old Health: "RED"%g"RESET"\nNew Health: "RED"%g"RESET, P[defender].health + total_damage, P[defender].health);
        printf(CYAN"\n%s"RESET"'s weapon is now on COOLDOWN with "CYAN"%i"RESET" turns left", P[attacker].name, P[attacker].equipped_weapon.cooldown);
        getchar();
        P[attacker].equipped_weapon.last_used=player_turn;
        P[attacker].equipped_weapon.id=0;
    }
    else{
        P[defender].health -= total_damage;
        printf(BLUE"%s"RESET" did "RED"%g"RESET" damage to "BLUE"%s"RESET".\n", P[attacker].name, total_damage, P[defender].name);
        printf("Old Health: "RED"%g"RESET"\nNew Health: "RED"%g"RESET, P[defender].health + total_damage, P[defender].health);
        printf(CYAN"\n%s"RESET"'s weapon is now on COOLDOWN with "CYAN"%i"RESET" turns left", P[attacker].name, P[attacker].equipped_weapon.cooldown);
        getchar();
        P[attacker].equipped_weapon.last_used=player_turn;
        P[attacker].equipped_weapon.id=0;
    }
    return 1;
}

void weapon_checkek(struct Player *x, int player_turn){
    if (x->equipped_weapon.cooldown+x->equipped_weapon.last_used==player_turn){
        x->equipped_weapon.last_used=0;
    }
    for (int i=0; i<6; i++){
        if (x->Pweapon[i].cooldown+x->Pweapon[i].last_used==player_turn){
            x->Pweapon[i].last_used=0;
        }
    }
}

int main(){
    int option = 0;
    // Define all weapons and players
    struct Weapon melee[27] = {
    //   Name                  Type            ID    Damage    CritChance      Cost
        {"Fists",              "Blunt",        1,    5,        5,              0,      .cooldown = 0},
        {"Rusty Sword",        "Sharp",        2,    12,       8,              0,      .cooldown = 0},
        {"Kitchen Knife",      "Sharp",        3,    14,      22,            200,      .cooldown = 5},
        {"Wooden Club",        "Blunt",        4,    16,      15,            280,      .cooldown = 5},
        {"Metal Hatchet",      "Sharp",        5,    18,      12,            320,},
        {"Baseball Bat",       "Blunt",        6,    20,      18,            400,},
        {"Trick Knife",        "Sharp",        7,    15,      28,            480,      .cooldown = 8},
        {"Person Beater",      "Blunt",        8,    22,      20,            520,},
        {"Murder Of Crowbars", "Blunt",        9,    24,      15,            580,},
        {"Pipe Bomb",          "Explosive",   10,    35,       5,            750,},
        {"Crossedbow",         "Ranged",      11,    28,      22,            950,},
        {"Leviathan Axe",      "Sharp",       12,    32,      18,           1250,},
        {"Rubber Ducky",       "Blunt",       13,    50,      25,           1500,},
        {"Katana",             "Sharp",       14,    36,      35,           1800,},
        {"Chainsword",         "Sharp",       15,    45,      12,           2400,},
        {"Sledgehammer",       "Blunt",       16,    42,      18,           2800,},
        {"BoomBoom Gun",       "Explosive",   17,    60,       5,           3500,},
    //   Name                  Type           ID       Cost                  Reduction              Durability
        {"Cardboard Shield",   "Light",       18,     .money_cost=   250,   .damage_reduction=10, .defense_durability = 50},
        {"Wooden Shield",      "Medium",      19,     .money_cost=   500,   .damage_reduction=20, .defense_durability = 60},
        {"Metal Shield",       "Heavy",       20,     .money_cost=   950,   .damage_reduction=30, .defense_durability = 100},
        {"Kevlar Vest",        "Special",     21,     .money_cost=  1700,   .damage_reduction=45, .defense_durability = 200},
        {"Cardboard Shield",   "Light",       22,     .money_cost=   250,   .damage_reduction=10, .defense_durability = 50},
        {"Wooden Shield",      "Medium",      23,     .money_cost=   500,   .damage_reduction=20, .defense_durability = 60},
        {"Metal Shield",       "Heavy",       24,     .money_cost=   950,   .damage_reduction=30, .defense_durability = 100},
        {"Kevlar Vest",        "Special",     25,     .money_cost=  1700,   .damage_reduction=45, .defense_durability = 200},
        {"Cardboard Shield",   "Light",       26,     .money_cost=   250,   .damage_reduction=10, .defense_durability = 50},
        {"Wooden Shield",      "Medium",      27,     .money_cost=   500,   .damage_reduction=20, .defense_durability = 60},
    };

    struct Player P[2] = {
        {.name = "Jim Pickens", .health = 100, .gold = 500, .Pweapon = {melee[0], melee[1]}, .times_rested = 0},
        {.name = "TURG", .health = 100, .gold = 550, .Pweapon = {melee[0], melee[1]}, .times_rested = 0},
    };
    int player_turn=0;

    //Gotta get dat dev logo
    //printf("\nPress enter to continue\n"RED BOLD);
    //print_ascii("ANDREW HELD HOSTAGE");
    //printf(RESET);
    //getchar();
    //Clear();

    //printf("Player 1, enter your name:\n");
    //scanf("%s", P[0].name);
    //printf("\nPlayer 2, enter your name:\n");
    //scanf("%s", P[1].name);

    while(1){
        Clear();
        option = MainPmenu(P[player_turn%2]);
        switch (option){
            case 1:
                if (UseWeaponItem(P, player_turn)!=1){player_turn--;}
                break;
            case 2:
                Clear();
                int word = 0;
                while(word<1||word>2){
                    printf("Enter 1 to equip your weapon and 2 for your defence\n");
                    scanf("%i", &word);
                }
                if (word==1){EquipItem(&P[player_turn%2], player_turn);}
                else{Equipdefense(&P[player_turn%2]);}
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
        if (P[player_turn%2].gold*0.05>=100){P[player_turn%2].gold*=1.05;}
        player_turn++;
        if (SignsOfLife(P[player_turn%2])==0){
            printf(RED"%s is \n\n", P[player_turn%2].name);
            print_ascii("D E A D");
            printf(GREEN"\n%s is the\n\n", P[(player_turn+1)%2].name);
            print_ascii("W I N N E R");
            getchar();
            break;
        }
    }

    return 0;
}
