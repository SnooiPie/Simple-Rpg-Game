#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Define structures for Player and Enemy
typedef struct {
    char name[50];
    int health;
    int maxHealth;
    int attack;
    int defense;
    int experience;
    int gold;
    int potionCount;
} Player;

typedef struct {
    char name[50];
    int health;
    int attack;
} Enemy;

// Function prototypes
bool battle(Player *player, Enemy *enemy);
void shop(Player *player);
void displayStats(Player *player);
void gameOver(Player *player);
void initializeEnemy(Enemy *enemy, int day);

int main() {
    srand(time(NULL));

    char playerName[50];
    printf("Welcome to the Epic Text RPG Adventure!\n");
    printf("Enter your character's name: ");
    scanf("%s", playerName);

    Player player;
    // Initialize player
    strcpy(player.name, playerName);
    player.health = 100;
    player.maxHealth = 100;
    player.attack = 15;
    player.defense = 8;
    player.experience = 0;
    player.gold = 50;
    player.potionCount = 3;

    printf("\n%s, your adventure begins!\n", player.name);

    int day = 1;
    while (player.health > 0) {
        printf("\n--- Day %d ---\n", day);
        printf("Choose an action:\n");
        printf("1. Explore\n");
        printf("2. Visit Shop\n");
        printf("3. See Stats\n");
        printf("4. Quit\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Enemy enemy;
                initializeEnemy(&enemy, day);

                printf("As you venture into the forest, you encounter a %s!\n", enemy.name);

                if (battle(&player, &enemy)) {
                    printf("You have %d gold and %d experience.\n", player.gold, player.experience);
                } else {
                    gameOver(&player);
                    return 0;
                }

                day++;
                break;
            }

            case 2:
                printf("Welcome to the Shop!\n");
                shop(&player);
                break;
            case 3:
                printf("See Stats\n");
                displayStats(&player);
                break;

            case 4:
                printf("Thanks for playing!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
        
    }

    gameOver(&player);

    return 0;
}

bool battle(Player *player, Enemy *enemy) {
    printf("\n%s's Health: %d | %s's Health: %d\n\n", player->name, player->health, enemy->name, enemy->health);

    while (enemy->health > 0 && player->health > 0) {
        printf("Choose an action:\n");
        printf("1. Attack\n");
        printf("2. Use Potion (%d left)\n", player->potionCount);
        printf("3. Run\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Player attacks
                int playerDamage = player->attack;
                enemy->health -= playerDamage;
                printf("%s attacks %s for %d damage!\n", player->name, enemy->name, playerDamage);

                if (enemy->health <= 0) {
                    printf("%s defeats %s!\n", player->name, enemy->name);
                    player->experience += 30;
                    player->gold += 10;
                    return true;
                }

                // Enemy attacks back
                int enemyDamage = enemy->attack;
                player->health -= enemyDamage;
                printf("%s attacks %s for %d damage!\n", enemy->name, player->name, enemyDamage);
                break;
            }

            case 2:
                if (player->potionCount > 0) {
                    player->health += 20;
                    if (player->health > player->maxHealth) {
                        player->health = player->maxHealth;
                    }
                    player->potionCount--;
                    printf("%s uses a potion and restores 20 health!\n", player->name);
                } else {
                    printf("No potions left!\n");
                }
                break;

            case 3:
                printf("%s tries to run away!\n", player->name);
                if (rand() % 2 == 0) {
                    printf("Escape successful!\n");
                    return true;
                } else {
                    printf("Escape failed! %s attacks!\n", enemy->name);
                }
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return false;
}

void initializeEnemy(Enemy *enemy, int day) {
    if (day == 1) {
        strcpy(enemy->name, "Goblin");
        enemy->health = 40;
        enemy->attack = 10;
    } else if (day == 2) {
        strcpy(enemy->name, "Wolf");
        enemy->health = 50;
        enemy->attack = 12;
    } else {
        strcpy(enemy->name, "Ogre");
        enemy->health = 80;
        enemy->attack = 15;
    }
}

void shop(Player *player) {
    printf("Welcome to the Shop!\n");
    
    while (1) {
        printf("Choose an action:\n");
        printf("1. Buy Potion (10 gold)\n");
        printf("2. Upgrade Attack (20 gold)\n");
        printf("3. Exit Shop\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (player->gold >= 10) {
                    player->gold -= 10;
                    player->potionCount++;
                    printf("%s buys a potion.\n", player->name);
                } else {
                    printf("Not enough gold!\n");
                }
                break;

            case 2:
                if (player->gold >= 20) {
                    player->gold -= 20;
                    player->attack += 5;
                    printf("%s upgrades attack.\n", player->name);
                } else {
                    printf("Not enough gold!\n");
                }
                break;

            case 3:
                printf("Exiting shop.\n");
                return;

            default:
                printf("Invalid choice!\n");
        }
        
        displayStats(player);
    }
}

void displayStats(Player *player) {
    printf("\n--- %s's Stats ---\n", player->name);
    printf("Health: %d/%d\n", player->health, player->maxHealth);
    printf("Attack: %d\n", player->attack);
    printf("Experience: %d\n", player->experience);
    printf("Gold: %d\n", player->gold);
    printf("Potions: %d\n", player->potionCount);
    printf("-------------------\n");
}

void gameOver(Player *player) {
    printf("Game over! %s has been defeated...\n", player->name);
}
