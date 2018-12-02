//
//  rpg.c
//  COE0449-Project-4
//
//  Created by Garrett Hagen on 12/1/18.
//  Copyright © 2018 Garrett Hagen. All rights reserved.
//

//
//  rpg.c
//  COE0449-Project1-RPG
//
//  Created by Garrett Hagen on 9/23/18.
//  Copyright © 2018 Garrett Hagen. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct{
    int diceRolls;
    int diceSize;
    char *name;
}Weapon;

typedef struct{
    int class;
    char *name;
}Armor;

typedef struct{
    char* name;
    int hp;
    int xp;
    int level;
    Weapon weapon;
    Armor armor;
}Player;



void printOptions(int optionType){
    switch(optionType){
        case 0:
            printf("\nList of availible armors:\n");
            printf("0:\tCloth (AC=10)\n");
            printf("1:\tStudded Leather (AC=12)\n");
            printf("2:\tRing Mail (AC=14)\n");
            printf("3:\tChain Mail(AC=16)\n");
            printf("4:\tPlate (AC=18)\n\n");
            break;
        case 1:
            printf("\nList of availible weapons:\n");
            printf("0:\tDagger (damage=1d4)\n");
            printf("1:\tShort Sword Leather (damage=1d6)\n");
            printf("2:\tLong Sword (damage=1d8)\n");
            printf("3:\tGreat Sword (damage=2d6)\n");
            printf("4:\tGreat Axe (damage=1d12)\n\n");
    }
}
void initializePlayer(Player* player,char* playerName,int hp, int level,int armorChoice,int weaponChoice){
    player->name = playerName;
    player->hp = hp;
    player->level = level;
    player->xp = 20 + (level - 1) * 5;
    
    switch (armorChoice){
        case 0:
            player->armor.class = 10;
            player->armor.name = "Cloth";
            break;
        case 1:
            player->armor.class = 12;
            player->armor.name = "Studded Leather";
            break;
        case 2:
            player->armor.class = 14;
            player->armor.name = "Ring Mail";
            break;
        case 3:
            player->armor.class = 16;
            player->armor.name = "Chain Mail";
            break;
        case 4:
            player->armor.class = 18;
            player->armor.name = "Plate";
            break;
        default:
            printf("Invalid choice! Try again.\n");

    }
    switch (weaponChoice){
        case 0:
            player->weapon.diceRolls = 1;
            player->weapon.diceSize = 4;
            player->weapon.name = "Dagger";
            break;
        case 1:
            player->weapon.diceRolls = 1;
            player->weapon.diceSize = 6;
            player->weapon.name = "Short Sword";
            break;
        case 2:
            player->weapon.diceRolls = 1;
            player->weapon.diceSize = 8;
            player->weapon.name = "Long Sword";
            break;
        case 3:
            player->weapon.diceRolls = 2;
            player->weapon.diceSize = 6;
            player->weapon.name = "Great Sword";
            break;
        case 4:
            player->weapon.diceRolls = 1;
            player->weapon.diceSize = 12;
            player->weapon.name = "Great Axe";
            break;
        default:
            printf("Invalid choice! Try again.\n");
      
    }
}
    

void printPlayerStats(Player *player){
    printf("\n[%s: hp=%d, armor=%s, weapon=%s]",player->name,player->hp,player->armor.name,player->weapon.name);
}
void doLook(Player enemies[],Player *myPlayer){
    printf("All is peaceful in the land of Mordor.\nSauron and his minions are blissfully going about their business:\n");
    for(int i = 0; i < 10; i++){
        printf("%d: ",i);
        printPlayerStats(&enemies[i]);
    }
    printf("Also at the scene are some adventurers looking for trouble:");
    printf("0: ");
    printPlayerStats(myPlayer);
}
void resolveDeath(Player *attacker,Player *defender){
    //A player has died
    if(attacker->hp > defender->hp){
        char stealWeapon;
        char stealArmor;
        int prevLevel = attacker->level;
        printf("\n\n%s was killed by %s\n\n",defender->name,attacker->name);
        printf("Get %s's %s, exchanging %s's current armor %s (y/n)?",defender->name,defender->armor.name,attacker->name,attacker->armor.name);
        scanf(" %c",&stealArmor);
        printf("Get %s's %s, exchanging %s's current weapon %s (y/n)?",defender->name,defender->weapon.name,attacker->name,attacker->weapon.name);
        scanf(" %c",&stealWeapon);
        if(stealArmor == 'y'){ attacker->armor = defender->armor; }
        if(stealWeapon == 'y'){ attacker->weapon = defender->weapon; }
        attacker->hp = 20;
        attacker->level =
    }
    else if(attacker->hp < defender->hp){
        printf("\n\n%s was killed by %s\n\n",attacker->name,defender->name);
    }
    else{
        printf("\n\n%s and %s have both died.\n\n",attacker->name,defender->name);
    }
   
    
    
}

void doAttack(Player *attacker,Player *defender){
   
    while(attacker->hp > 0 && defender->hp > 0){
        int attackDamage = 0;
        int attackRoll = rand() % (20 - 1 +1)+1;
        
        if (attackRoll >= defender->armor.class){
            //Get the total attack value
            int i;
            for(i=0; i<attacker->weapon.diceRolls; i++){
                attackDamage += rand() % (attacker->weapon.diceSize - 1 + 1)+1;
            }
            defender->hp -= attackDamage;
            printf("\n%s hits %s for %d damage (attack roll %d)",attacker->name,defender->name,attackDamage,attackRoll);
        }
        else{
            printf("\n%s misses %s (attack roll %d)",attacker->name,defender->name,attackRoll);
        }
    }
    
}

int main(int argc, const char * argv[]) {
    Player myPlayer;
    Player enemyPlayers[10];
    srand((unsigned int)time(NULL));
    int i;
    
    
    //Initialize my player
    int armorChoice;
    int weaponChoice;
    char myName[25];
    printf("What is your name?");
    scanf("%s",myName);
    printOptions(0);
    printf("Choose %s's Armor(0~4): ",myName);
    scanf("%d",&armorChoice);
    printOptions(1);
    printf("Choose %s's Weapon(0~4): ",myName);
    scanf("%d",&weaponChoice);
    initializePlayer(&myPlayer,myName,20,1,armorChoice,weaponChoice);
    printf("Player setting complete.\n");
    printPlayerStats(&myPlayer);
   
    //Initialize enemies
    Player sauronPlayer;
    Player gollumPlayer;
    initializePlayer(&sauronPlayer,"Sauron",115,20,4,4);
    initializePlayer(&gollumPlayer,"Gollum",10,1,1,1);
    
    for(i = 0;i < 10;i++){
        Player orcPlayer;
        char orcName[5];
        sprintf(orcName,"Orc %d",i);
        initializePlayer(&orcPlayer,orcName,20,1,(rand() % (4 - 1 +1)+1),(rand() % (4 - 1 +1)+1));
    }
    enemyPlayers[0] = sauronPlayer;
    enemyPlayers[9] = gollumPlayer;
    doLook(enemyPlayers,&myPlayer);

    
    //Begin the game
    int enemyIndex;
    char command[15];
    
    while(1){
        printf("command >> ");
        scanf("%s",command);
        enemyIndex = 3;
        
        if(strcasecmp("look",command)){
            doLook(enemyPlayers,&myPlayer);
        }
        if(strcasecmp("stats",command)){
            printPlayerStats(&myPlayer);
        }
        if(strcasecmp("attack",command)){
            doAttack(&myPlayer,&enemyPlayers[enemyIndex]);
        }
        if(strcasecmp("quit",command)){
            return 0;
            break;
        }
        
    }
    return 0;
}



