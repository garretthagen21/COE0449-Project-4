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
#include <math.h>


typedef struct{
    int diceRolls;
    int diceSize;
    const char *name;
}Weapon;

typedef struct{
    int class;
    const char *name;
}Armor;

typedef struct{
    const char* name;
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
void initializePlayer(Player* player,const char *playerName,int level,int armorChoice,int weaponChoice){
    player->name = playerName;
    player->hp = 20 + (level - 1) * 5;
    player->level = level;
    player->xp = (int)pow(2,level) * 1000;
    
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
    printf("[%s: hp=%d, armor=%s, weapon=%s, level=%d, xp=%d]\n",player->name,player->hp,player->armor.name,player->weapon.name,player->level,player->xp);
}
void doLook(Player *enemies,Player *myPlayer){
    printf("All is peaceful in the land of Mordor.\nSauron and his minions are blissfully going about their business:\n");
    int i;
    for(i = 0; i < 10; i++){
        printf("%d: ",i);
        printPlayerStats(&enemies[i]);
    }
    printf("Also at the scene are some adventurers looking for trouble:\n");
    printf("0: ");
    printPlayerStats(myPlayer);
}
void resolveDeath(Player *attacker,Player *defender){
    int respawnDefender;
    int respawnAttacker;
    
    if(attacker->hp > defender->hp){
        char stealWeapon;
        char stealArmor;
        int prevLevel = attacker->level;
        printf("\n\n%s was killed by %s\n\n",defender->name,attacker->name);
        printf("Get %s's %s, exchanging %s's current armor %s (y/n)? ",defender->name,defender->armor.name,attacker->name,attacker->armor.name);
        scanf(" %c",&stealArmor);
        printf("Get %s's %s, exchanging %s's current weapon %s (y/n)? ",defender->name,defender->weapon.name,attacker->name,attacker->weapon.name);
        scanf(" %c",&stealWeapon);
        if(stealArmor == 'y'){ attacker->armor = defender->armor; }
        if(stealWeapon == 'y'){ attacker->weapon = defender->weapon; }
        attacker->xp = attacker->xp + (defender->level * 2000);
        attacker->level = (int)log2(attacker->xp/1000);
        attacker->hp = 20 + (attacker->level - 1) * 5;
        if(attacker->level > prevLevel){ printf("%s levels up to level %d\n",attacker->name,attacker->level);}
        printPlayerStats(attacker);
        respawnDefender = 1;
        respawnAttacker = 0;
    }
    else if(attacker->hp < defender->hp){ //We died
        printf("\n\n%s was killed by %s\n\n",attacker->name,defender->name);
        attacker->hp = 20 + (attacker->level - 1) * 5;
        attacker->xp = (int)pow(2,attacker->level);
        respawnDefender = 0;
        respawnAttacker = 1;
    }
    else{
        printf("\n\n%s and %s have both died.\n\n",attacker->name,defender->name);
        respawnDefender = 1;
        respawnAttacker = 1;
    }
    
    //Do respawning
    if(respawnAttacker == 1){
        printf("Respawning %s...\n",attacker->name);
        
        attacker->hp = 20 + (attacker->level - 1) * 5;
        attacker->xp = (int)pow(2,attacker->level);
        printPlayerStats(attacker);
    }
    if(respawnDefender == 1){
        printf("Respawning %s...\n",defender->name);
        if(strcmp(defender->name,"Sauron") == 0){
            initializePlayer(defender,"Sauron",20,4,4);
        }
        else if(strcmp(defender->name,"Gollum") == 0){
            initializePlayer(defender,"Gollum",1,1,1);
        }
        else{
           initializePlayer(defender,defender->name,(rand() % (attacker->level - 1 +1)+1),(rand() % (4 - 1 +1)+1),(rand() % (4 - 1 +1)+1));
        }
        printPlayerStats(defender);
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
    resolveDeath(attacker,defender);
    
}

char *npcNames[10] = {"Sauron","Orc 1","Orc 2","Orc 3","Orc 4","Orc 5","Orc 6","Orc 7","Orc 8","Gollum"};

int main(int argc, const char * argv[]) {
    Player myPlayer;
    Player enemyPlayers[10];
    srand((unsigned int)time(NULL));
    int i;
    
    
    //Initialize my player
    int armorChoice;
    int weaponChoice;
    char myName[25];
    printf("What is your name? ");
    scanf("%s",myName);
    printOptions(0);
    printf("Choose %s's Armor(0~4): ",myName);
    scanf("%d",&armorChoice);
    printOptions(1);
    printf("Choose %s's Weapon(0~4): ",myName);
    scanf("%d",&weaponChoice);
    initializePlayer(&myPlayer,myName,1,armorChoice,weaponChoice);
    printf("Player setting complete.\n");
    printPlayerStats(&myPlayer);
   
    //Initialize enemies
   
    Player sauronPlayer;
    Player gollumPlayer;
    initializePlayer(&sauronPlayer,npcNames[0],20,4,4);
    initializePlayer(&gollumPlayer,npcNames[9],1,1,1);
    gollumPlayer.hp = 10;
    
    enemyPlayers[0] = sauronPlayer;
    enemyPlayers[9] = gollumPlayer;

    for(i = 1;i < 9;i++){
        Player orcPlayer;
        initializePlayer(&orcPlayer,npcNames[i],1,(rand() % (4 - 1 +1)+1),(rand() % (4 - 1 +1)+1));
        enemyPlayers[i] = orcPlayer;
        
    }
    
    doLook(enemyPlayers,&myPlayer);

    
    //Begin the game
    int enemyIndex;
    char command[15];
    
    while(1){
        printf("\ncommand >> ");
        scanf(" %s",command);
        enemyIndex = 9;
        
        if(strcmp("look",command)==0){
            doLook(enemyPlayers,&myPlayer);
        }
        if(strcmp("stats",command)==0){
            printPlayerStats(&myPlayer);
        }
        if(strcmp("attack",command)==0){
            doAttack(&myPlayer,&enemyPlayers[enemyIndex]);
        }
        if(strcmp("quit",command)==0){
            return 0;
            break;
        }
        
    }
    return 0;
}




