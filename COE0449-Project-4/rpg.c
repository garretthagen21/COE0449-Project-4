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

struct Weapon{
    int diceRolls;
    int diceSize;
    char *name;
};

struct Armor{
    int class;
    char *name;
};

struct Player{
    int number;
    int hp;
    struct Weapon weapon;
    struct Armor armor;
};



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
void chooseArmor(struct Player* playerName){
    int armorChoice;
    printf("Choose Player %d Armor(0~4):",playerName->number);
    scanf("%d",&armorChoice);
    
    switch (armorChoice){
        case 0:
            playerName->armor.class = 10;
            playerName->armor.name = "Cloth";
            break;
        case 1:
            playerName->armor.class = 12;
            playerName->armor.name = "Studded Leather";
            break;
        case 2:
            playerName->armor.class = 14;
            playerName->armor.name = "Ring Mail";
            break;
        case 3:
            playerName->armor.class = 16;
            playerName->armor.name = "Chain Mail";
            break;
        case 4:
            playerName->armor.class = 18;
            playerName->armor.name = "Plate";
            break;
        default:
            printf("Invalid choice! Try again.\n");
            chooseArmor(playerName);
    }
    
}

void chooseWeapon(struct Player* playerName){
    int weaponChoice;
    printf("Choose Player %d Weapon(0~4):",playerName->number);
    scanf("%d",&weaponChoice);
    
    switch (weaponChoice){
        case 0:
            playerName->weapon.diceRolls = 1;
            playerName->weapon.diceSize = 4;
            playerName->weapon.name = "Dagger";
            break;
        case 1:
            playerName->weapon.diceRolls = 1;
            playerName->weapon.diceSize = 6;
            playerName->weapon.name = "Short Sword";
            break;
        case 2:
            playerName->weapon.diceRolls = 1;
            playerName->weapon.diceSize = 8;
            playerName->weapon.name = "Long Sword";
            break;
        case 3:
            playerName->weapon.diceRolls = 2;
            playerName->weapon.diceSize = 6;
            playerName->weapon.name = "Great Sword";
            break;
        case 4:
            playerName->weapon.diceRolls = 1;
            playerName->weapon.diceSize = 12;
            playerName->weapon.name = "Great Axe";
            break;
        default:
            printf("Invalid choice! Try again.\n");
            chooseWeapon(playerName);
    }
}
void printPlayerStats(struct Player *playerName){
    printf("\n[Player %d: hp=%d, armor=%s, weapon=%s]",playerName->number,playerName->hp,playerName->armor.name,playerName->weapon.name);
}

void doAttack(struct Player *attacker,struct Player *defender){
    int attackDamage = 0;
    int attackRoll;
    
    attackRoll = rand() % (20 - 1 +1)+1;
    
    if (attackRoll >= defender->armor.class){
        //Get the total attack value
	int i;
        for(i=0; i<attacker->weapon.diceRolls; i++){
            attackDamage += rand() % (attacker->weapon.diceSize - 1 + 1)+1;
        }
        defender->hp -= attackDamage;
        printf("\nPlayer %d hits Player %d for %d damage (attack roll %d)",attacker->number,defender->number,attackDamage,attackRoll);
    }
    else{
         printf("\nPlayer %d misses Player %d (attack roll %d)",attacker->number,defender->number,attackRoll);
    }
   
    
}

int main(int argc, const char * argv[]) {
    struct Player Player1 = {.number = 1,.hp = 20};
    struct Player Player2 = {.number = 2,.hp = 20};
    char doFight;
    srand((unsigned int)time(NULL));
   

    //Choose armor
    printOptions(0);
    chooseArmor(&Player1);
    chooseArmor(&Player2);
    
    //Choose weapons
    printOptions(1);
    chooseWeapon(&Player1);
    chooseWeapon(&Player2);
    
    //Finish set up
    printf("\nPlayer setting complete:");
    printPlayerStats(&Player1);
    printPlayerStats(&Player2);
    
   
     //Begin the game
    while(1){
        int roundNumber = 1;
        Player1.hp = 20;
        Player2.hp = 20;
    
        printf("\n\nFight? (y/n)\n");
        scanf(" %c",&doFight);
        
        if(doFight != 'y'){
            break;
        }
        
       
        
        while(1){
            printf("\n\n----- Round %d ------",roundNumber);
            doAttack(&Player1,&Player2);
            doAttack(&Player2,&Player1);
            printPlayerStats(&Player1);
            printPlayerStats(&Player2);
            
            //A player has died
            if(Player1.hp < 1 || Player2.hp < 1){
                if(Player1.hp > Player2.hp){
                    printf("\n\nPlayer 1 WINS!\n\n");
                }
                else if(Player1.hp < Player2.hp){
                    printf("\n\nPlayer 2 WINS!\n\n");
                }
                else{
                    printf("\n\nPlayer 1 and Player 2 TIE!\n\n");
                }
                break;
            }
            roundNumber++;
        }

        
        
        
    }
    return 0;
}



