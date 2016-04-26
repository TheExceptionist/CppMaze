// Text-Maze.cpp : Defines the entry point for the console application.
// Add Enemy Attack And Movement 

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

const char HEIGHT = 16;
const char WIDTH = 16;
const char player = 'P';
const char enemy = 'E';
const char chest = 'C';
const char block = '#';
const char goal = '@';
const char space = ' ';

int score = 0;
int chestArr[] = {1, 8};
int goalX = 12;
int goalY = 15;
int enemyX = 12;
int enemyY = 13;
int playerX = 1;
int playerY = 1;

int pHealth = 20, pAttack = 5, pDefense = 5;
int eHealth = 10, eAttack = 10, eDefense = 3;

int currentLevel = 1;

char direction;

bool running = true;
bool gotChest = false;
bool comInfo = false;
bool goalInfo = false;
bool notOpened = true;

unsigned char level_1[HEIGHT][WIDTH] = {
	'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#',
	'#',' ','#',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ','#',
	'#',' ','#',' ',' ','#',' ',' ','#',' ','#','#','#','#',' ','#',
	'#',' ','#',' ',' ','#','#',' ','#',' ',' ',' ',' ',' ',' ','#',
	'#',' ',' ',' ',' ','#',' ',' ','#',' ','#',' ',' ',' ',' ','#',
	'#',' ',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#',
	'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',
	'#','#','#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ','#',
	'#',' ','#',' ',' ',' ',' ','#',' ','#','#','#','#','#','#','#',
	'#',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',
	'#',' ','#',' ','#','#','#','#',' ','#',' ','#',' ','#','#','#',
	'#',' ','#',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',
	'#',' ',' ',' ',' ',' ',' ','#',' ','#','#','#',' ','#','#','#',
	'#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',
	'#',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ','#',
	'#','#','#','#','#','#','#','#','#','#','#','#',' ','#','#','#'
};

unsigned char currentMap[HEIGHT][WIDTH];

void draw()
{
	for(int y = 0; y < WIDTH; y++){
		cout << endl;
		for(int x = 0; x < HEIGHT; x++){
			if(currentLevel == 1){
				currentMap[y][x] = level_1[y][x];
			}else{
				cout << "Score: " << score;
			}

			if(gotChest){
				cout << "You Found Teasure" << endl;
				gotChest = false;
			}

			if(comInfo){
				cout << "The Enemy's Health is Now: " << eHealth << endl;
				cout << "Your Health is Now: " << pHealth << endl;
				comInfo = false;
			}

			if(goalInfo){
				cout << "You Reached Your Goal With a Score Of: " << score << endl;
				goalInfo = false;
			}

			if(x == playerX && y == playerY){
				currentMap[y][x] = player;
			}

			if(x == chestArr[0] && y == chestArr[1] && notOpened){
				currentMap[y][x] = chest;
			}
			
			if(x == enemyX && y == enemyY){
				if(eHealth > 0){
					currentMap[y][x] = enemy;
				}else{
					currentMap[y][x] = space;
				}
			}

			if(x == goalX && y == goalY){
				currentMap[y][x] = goal;
			}

			cout << currentMap[y][x];
		}
	}
}

void chooseEAction(){
		int choice = rand() % 3;

		if(choice == 0){
				if(currentMap[enemyY][enemyX + 1] == chest){
					notOpened = false;
				}else if(currentMap[enemyY][enemyX + 1] == enemy){
					pHealth -= (eAttack - pDefense);
					comInfo = false;
				}else if(currentMap[enemyY][enemyX + 1] != block && currentMap[enemyY][enemyX + 1] != goal){
					enemyX++;
				}
		}else if(choice == 1){
				if(currentMap[enemyY][enemyX - 1] == chest){
					notOpened = false;
				}else if(currentMap[enemyY][enemyX - 1] == enemy){
					pHealth -= (eAttack - pDefense);
					comInfo = true;
				}else if(currentMap[enemyY][enemyX - 1] != block && currentMap[enemyY][enemyX - 1] != goal){
					enemyX--;
				}
		}else if(choice == 2){
				if(currentMap[enemyY + 1][enemyX] == chest){
					notOpened = false;
				}else if(currentMap[enemyY + 1][enemyX] == enemy){
					pHealth -= (eAttack - pDefense);
					comInfo = true;
				}else if(currentMap[enemyY + 1][enemyX] != block && currentMap[enemyY + 1][enemyX] != goal){
					enemyY++;
				}
		}else if(choice == 3){
				if(currentMap[enemyY - 1][enemyX] == chest){
					notOpened = false;
				}else if(currentMap[enemyY - 1][enemyX] == enemy){
					pHealth -= (eAttack - pDefense);
					comInfo = true;
				}else if(currentMap[enemyY - 1][enemyX] != block && currentMap[enemyY - 1][enemyX] != goal){
					enemyY--;
				}
		}
}


int main()
{
	cout << string( 100, '\n' );
	draw();

	while(running){
		cout << "\nMove: ";
		cin >> direction;

		switch(direction){
			case 'd':
				if(currentMap[playerY][playerX + 1] == goal){
					currentLevel++;
					goalInfo = true;
				}else if(currentMap[playerY][playerX + 1] == chest){
					score += 50;
					gotChest = true;
					notOpened = false;
				}else if(currentMap[playerY][playerX + 1] == enemy){
					eHealth -= (pAttack - eDefense);
					comInfo = false;
				}else if(currentMap[playerY][playerX + 1] != block){
					playerX++;
				}
				break;
			case 'a':
				if(currentMap[playerY][playerX - 1] == goal){
					currentLevel++;
					goalInfo = true;
				}else if(currentMap[playerY][playerX - 1] == chest){
					score += 50;
					gotChest = true;
					notOpened = false;
				}else if(currentMap[playerY][playerX - 1] == enemy){
					eHealth -= (pAttack - eDefense);
					comInfo = true;
				}else if(currentMap[playerY][playerX - 1] != block){
					playerX--;
				}
				break;
			case 's':
				if(currentMap[playerY + 1][playerX ] == goal){
					currentLevel++;
					goalInfo = true;
				}else if(currentMap[playerY + 1][playerX] == chest){
					score += 50;
					gotChest = true;
					notOpened = false;
				}else if(currentMap[playerY + 1][playerX] == enemy){
					eHealth -= (pAttack - eDefense);
					comInfo = true;
				}else if(currentMap[playerY + 1][playerX] != block){
					playerY++;
				}
				break;
			case 'w':
				if(currentMap[playerY - 1][playerX] == goal){
					currentLevel++;
					goalInfo = true;
				}else if(currentMap[playerY - 1][playerX] == chest){
					score += 50;
					gotChest = true;
					notOpened = false;
				}else if(currentMap[playerY - 1][playerX] == enemy){
					eHealth -= (pAttack - eDefense);
					comInfo = true;
				}else if(currentMap[playerY - 1][playerX] != block){
					playerY--;
				}
				break;
		}
		
		chooseEAction();

		cout << string( 100, '\n' );
		draw();
	}

	return 0;
}
