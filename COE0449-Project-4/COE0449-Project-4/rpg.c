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
#include <signal.h>

/*#define SIGINT 3
#define SIGTERM 15
#define SIGRTMIN

typedef struct{
    int diceRolls;
    int diceSize;
    const char *name;
}Weapon;

typedef struct{
    int class;
    const char *name;
}Armor;*/

typedef struct{
    char playerName[20];
    int hp;
    int xp;
    int level;
    char weaponName[20];
    int weaponDiceRolls;
    int weaponDiceSize;
    char armorName[20];
    int armorClass;
    
}Player;

char *npcNames[10] = {"Sauron","Orc 1","Orc 2","Orc 3","Orc 4","Orc 5","Orc 6","Orc 7","Orc 8","Gollum"};
Player allPlayers[11]; //For earthquake, saving, and looking

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
void initializePlayer(Player* player,int level,int armorChoice,int weaponChoice){
  
    player->hp = 20 + (level - 1) * 5;
    player->level = level;
    player->xp = (int)pow(2,level) * 1000;
    
    switch (armorChoice){
        case 0:
            player->armorClass = 10;
            strcpy(player->armorName,"Cloth");
            break;
        case 1:
            player->armorClass = 12;
            strcpy(player->armorName,"Studded Leather");
            break;
        case 2:
            player->armorClass = 14;
            strcpy(player->armorName,"Ring Mail");
            break;
        case 3:
            player->armorClass = 16;
            strcpy(player->armorName,"Chain Mail");
            break;
        case 4:
            player->armorClass = 18;
            strcpy(player->armorName,"Plate");
            break;
        default:
            printf("Invalid choice! Try again.\n");

    }
    switch (weaponChoice){
        case 0:
            player->weaponDiceRolls = 1;
            player->weaponDiceSize = 4;
            strcpy(player->weaponName,"Dagger");
            break;
        case 1:
            player->weaponDiceRolls = 1;
            player->weaponDiceSize = 6;
            strcpy(player->weaponName,"Short Sword");
            break;
        case 2:
            player->weaponDiceRolls = 1;
            player->weaponDiceSize = 8;
            strcpy(player->weaponName,"Long Sword");
            break;
        case 3:
            player->weaponDiceRolls = 2;
            player->weaponDiceSize = 6;
            strcpy(player->weaponName,"Great Sword");
            break;
        case 4:
            player->weaponDiceRolls = 1;
            player->weaponDiceSize = 12;
            strcpy(player->weaponName,"Great Axe");
            break;
        default:
            printf("Invalid choice! Try again.\n");
      
    }
}
    

void printPlayerStats(Player *player){
    printf("[%s: hp=%d, armor=%s, weapon=%s, level=%d, xp=%d]\n",player->playerName,player->hp,player->armorName,player->weaponName,player->level,player->xp);
}
void doLook(){
    printf("All is peaceful in the land of Mordor.\nSauron and his minions are blissfully going about their business:\n");
    int i;
    for(i = 0; i < 10; i++){
        printf("%d: ",i);
        printPlayerStats(&allPlayers[i]);
    }
    printf("Also at the scene are some adventurers looking for trouble:\n");
    printf("0: ");
    printPlayerStats(&allPlayers[10]);
}
void resolveDeath(Player *attacker,Player *defender){
    int respawnDefender;
    int respawnAttacker;
    
    if(attacker->hp > defender->hp){
        char stealWeapon;
        char stealArmor;
        int prevLevel = attacker->level;
        printf("\n\n%s was killed by %s\n\n",defender->playerName,attacker->playerName);
        printf("Get %s's %s, exchanging %s's current armor %s (y/n)? ",defender->playerName,defender->armorName,attacker->playerName,attacker->armorName);
        scanf(" %c",&stealArmor);
        printf("Get %s's %s, exchanging %s's current weapon %s (y/n)? ",defender->playerName,defender->weaponName,attacker->playerName,attacker->weaponName);
        scanf(" %c",&stealWeapon);
        if(stealArmor == 'y'){
            strcpy(attacker->armorName,defender->armorName);
            attacker->armorClass = defender->armorClass;
        }
        if(stealWeapon == 'y'){
            strcpy(attacker->weaponName,defender->weaponName);
            attacker->weaponDiceRolls = defender->weaponDiceRolls;
            attacker->weaponDiceRolls = defender->weaponDiceRolls;
        }
        
        attacker->xp = attacker->xp + (defender->level * 2000);
        attacker->level = (int)log2(attacker->xp/1000);
        attacker->hp = 20 + (attacker->level - 1) * 5;
        if(attacker->level > prevLevel){ printf("%s levels up to level %d\n",attacker->playerName,attacker->level);}
        printPlayerStats(attacker);
        respawnDefender = 1;
        respawnAttacker = 0;
    }
    else if(attacker->hp < defender->hp){ //We died
        printf("\n\n%s was killed by %s\n\n",attacker->playerName,defender->playerName);
        attacker->hp = 20 + (attacker->level - 1) * 5;
        attacker->xp = (int)pow(2,attacker->level);
        respawnDefender = 0;
        respawnAttacker = 1;
    }
    else{
        printf("\n\n%s and %s have both died.\n\n",attacker->playerName,defender->playerName);
        respawnDefender = 1;
        respawnAttacker = 1;
    }
    
    //Do respawning
    if(respawnAttacker == 1){
        printf("Respawning %s...\n",attacker->playerName);
        
        attacker->hp = 20 + (attacker->level - 1) * 5;
        attacker->xp = (int)pow(2,attacker->level) * 1000;
        printPlayerStats(attacker);
    }
    if(respawnDefender == 1){
        printf("Respawning %s...\n",defender->playerName);
        if(strcmp(defender->playerName,"Sauron") == 0){
            initializePlayer(defender,20,4,4);
        }
        else if(strcmp(defender->playerName,"Gollum") == 0){
            initializePlayer(defender,1,1,1);
            defender->hp = 15;
        }
        else{
            initializePlayer(defender,(rand() % (attacker->level - 1 +1)+1),(rand() % (4 - 1 +1)+1),(rand() % (4 - 1 +1)+1));
        }
        printPlayerStats(defender);
    }
    
    
}

void doAttack(Player *attacker,Player *defender){
   
    while(attacker->hp > 0 && defender->hp > 0){
        int attackDamage = 0;
        int attackRoll = rand() % (20 - 1 +1)+1;
        
        if (attackRoll >= defender->armorClass){
            //Get the total attack value
            int i;
            for(i=0; i<attacker->weaponDiceRolls; i++){
                attackDamage += rand() % (attacker->weaponDiceSize - 1 + 1)+1;
            }
            defender->hp -= attackDamage;
            printf("\n%s hits %s for %d damage (attack roll %d)",attacker->playerName,defender->playerName,attackDamage,attackRoll);
        }
        else{
            printf("\n%s misses %s (attack roll %d)",attacker->playerName,defender->playerName,attackRoll);
        }
    }
    resolveDeath(attacker,defender);
    
}
void doQuit(){
    FILE *saveFile;
    if((saveFile = fopen("rpg.save","wb")) == NULL){
        printf("There was an error saving the file.\n");
        exit(0);
    }
    //Save players
    int i;
    for(i = 0; i < 11;i++){
        fwrite (&allPlayers[i], sizeof(Player), 1, saveFile);
    }
    printf("File saved successfully!\n");

    fclose(saveFile);
    exit(0);
    
}


int main(int argc, const char * argv[]) {
    FILE *openFile;
  
    Player myPlayer;
    Player enemyPlayers[10];
    srand((unsigned int)time(NULL));
    int i;
    char continueGame = 'n';
    
    if((openFile = fopen("rpg.save","rb")) != NULL){
        printf("Found save file. Continue where you left off (y/n)? :");
        scanf(" %c",&continueGame);
    }
    
    if(continueGame == 'y'){
        for(i = 0; i < 11;i++){
            fread(&allPlayers[i], sizeof(Player), 1, openFile);
            if(i < 10){ enemyPlayers[i] = allPlayers[i]; }
            else{ myPlayer = allPlayers[i]; }
        }
        //fread(&myPlayer, sizeof(Player), 1, openFile);
        
        printf("File loaded successfully!\n");
        fclose(openFile);
    }
    else{
        //Initialize my player
        int armorChoice;
        int weaponChoice;
        char myName[25];
        printf("What is your name? ");
        scanf("%s",myPlayer.playerName);
        printOptions(0);
        printf("Choose %s's Armor(0~4): ",myName);
        scanf("%d",&armorChoice);
        printOptions(1);
        printf("Choose %s's Weapon(0~4): ",myName);
        scanf("%d",&weaponChoice);
        initializePlayer(&myPlayer,1,armorChoice,weaponChoice);
        //strcpy(myPlayer->playerName,,);
        printf("Player setting complete.\n");
        printPlayerStats(&myPlayer);
        allPlayers[10] = myPlayer;
        
        //Initialize enemies
        Player sauronPlayer = {.playerName = "Sauron"};
        Player gollumPlayer = {.playerName = "Gollum"};
        initializePlayer(&sauronPlayer,20,4,4);
        initializePlayer(&gollumPlayer,1,1,1);
        gollumPlayer.hp = 10;
        
        allPlayers[0] = enemyPlayers[0] = sauronPlayer;
        allPlayers[9] = enemyPlayers[9] = gollumPlayer;
        
        for(i = 1;i < 9;i++){
            Player orcPlayer;
            strcpy(orcPlayer.playerName,npcNames[i]);
            initializePlayer(&orcPlayer,1,(rand() % (4 - 1 +1)+1),(rand() % (4 - 1 +1)+1));
            enemyPlayers[i] = orcPlayer;
            allPlayers[i] = orcPlayer;
        }
    }
    
    
    doLook();
    
    //Begin the game
    while(1){
        char input[20];
        char *commands[2];
        
        printf("\ncommand >> ");
        scanf(" %[^\n]s",input);

        commands[0] = strtok(input," ");
        commands[1] = strtok(NULL," ");

        if(strcmp("look",commands[0])==0){
            doLook();
        }
        if(strcmp("stats",commands[0])==0){
            printPlayerStats(&myPlayer);
        }
        if(strcmp("fight",commands[0])==0){
            int enemyIndex = atoi(commands[1]);
            doAttack(&myPlayer,&enemyPlayers[enemyIndex]);
        }
        if(strcmp("quit",commands[0])==0){
            doQuit();
            return 0;
            
        }
        
    }
   
}




