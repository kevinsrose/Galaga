#include "mylib.h"
#include "text.h"

#include "logo1.h"
#include "logo1.c"
#include "logo2.h"
#include "logo2.c"
#include "logo3.h"
#include "logo3.c"
#include "logo4.h"
#include "logo4.c"
#include "galaga.h"
#include "galaga.c"
#include "gameover.h"
#include "gameover.c"
#include "pressStart.h"
#include "pressStart.c"
#include "youwin.h"
#include "youwin.c"
#include "minigalaga.c"
#include "minigalaga.h"

//*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*//


// void drawRect(int r, int c, int width,
//	int height, u16 color)


int main()
{
	REG_DISPCNT = MODE3 | BG2_ENABLE;

	while(1)
	{
	//~*~*~*~START SCREEN~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*//
		drawRect(0, 0, 240, 160, BLACK);
		drawImage3(80, 40, PRESSSTART_WIDTH, PRESSSTART_HEIGHT, pressStart);
		//drawString(100, 50, "A B C D", WHITE);
		//drawString(120, 100, "TEXT", MAGENTA);
		// drawChar(0, 0, 56, GREEN);
		//int startGame = 0;
		//int gameisover = 0;
		int winner = 0;
		//drawImage3(10, 10, GALAGA_GUY_WIDTH, GALAGA_GUY_HEIGHT, galaga_guy);
		while(!KEY_DOWN_NOW(BUTTON_START)) // PRESS & HOLD START TO BEGIN GAME
		{
			drawImage3(20, 70, LOGO1_WIDTH, LOGO1_HEIGHT, logo1);
			delay(10);
			drawImage3(20, 70, LOGO2_WIDTH, LOGO2_HEIGHT, logo2);
			delay(10);
			drawImage3(20, 70, LOGO3_WIDTH, LOGO3_HEIGHT, logo3);
			delay(10);
			drawImage3(20, 70, LOGO4_WIDTH, LOGO4_HEIGHT, logo4);
			delay(10);
		}
		//drawString(50, 50, "~*~*~GALAGA~*~*~", WHITE);
		//drawChar(60, 60, 5, GREEN);


	//~*~*~*~VARIABLES~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*//
		
		// Player Spaceship components
		int row = 130;
		int col = 110;
		int size = 20;
		// int height = 20;
		int width = 20;
		u16 color = WHITE;
		int bullet = 0;
		int bullet2 = 0;
		int bulletCD = 0;
		static int bulletRow = 0;
		static int bulletCol = 0;
		static int bulletRow2 = 0;
		static int bulletCol2 = 0;
		

		// Enemy Spaceship components

		int enemyHeight = 15;
		int enemyWidth = 15;
		int enemyRow = 20;
		int moveRight = 1;
		int moveDelay = 0;
		int moveCount = 0;
		// int upDownCount = 0;
		// int moveDown = 1;
		//int lives = 3;

		
		int enemies = 6;
		int enemy1 = 1;
		int enemy2 = 1;
		int enemy3 = 1;
		int enemy4 = 1;
		int enemy5 = 1;
		int enemy6 = 1;

		int enemyCol = 15;
		int enemyCol2 = 55;
		int enemyCol3 = 95;
		int enemyCol4 = 135;
		int enemyCol5 = 175;
		int enemyCol6 = 215;

	//~*~*~*~DRAW GAME SCREEN~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*//
		
		drawRect(0, 0, 240, 160, BLACK);
		for (int i = 0; i < 240; ++i)
		{
			setPixel(150, i, WHITE);
		}
		//drawSpaceship(row, col, size);
		drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);
		drawImage3(151, 1, MINIGALAGA_WIDTH, MINIGALAGA_HEIGHT, minigalaga);
		drawImage3(151, 11, MINIGALAGA_WIDTH, MINIGALAGA_HEIGHT, minigalaga);
		drawImage3(151, 21, MINIGALAGA_WIDTH, MINIGALAGA_HEIGHT, minigalaga);
		drawHollowRect(enemyRow, enemyCol,
			enemyWidth, enemyHeight, RED);
		drawHollowRect(enemyRow, enemyCol + 40,
			enemyWidth, enemyHeight, YELLOW);
		drawHollowRect(enemyRow, enemyCol + 80,
			enemyWidth, enemyHeight, GREEN);
		drawHollowRect(enemyRow, enemyCol + 120,
			enemyWidth, enemyHeight, CYAN);
		drawHollowRect(enemyRow, enemyCol + 160,
			enemyWidth, enemyHeight, BLUE);
		drawHollowRect(enemyRow, enemyCol + 200,
			enemyWidth, enemyHeight, MAGENTA);

	//~*~*~*~GAME LOOP~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*// 
		volatile int gameplay = 1;
		delay(10);
		while(gameplay == 1)
		{

			waitForVblank();

		//PLAYER MOVEMENT//
			if (KEY_DOWN_NOW(BUTTON_UP) && row > 110)
			{

				--row;
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);
				eraseSpaceship(row + 1, col);
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);

				// drawRect(row, col, size, size, color);
				// drawRect(row + 1, col, size, size, BLACK);
				// drawRect(row, col, size, size, color);
			}
			if (KEY_DOWN_NOW(BUTTON_DOWN) && row + size < 150)
			{
				++row;
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);
				eraseSpaceship(row - 1, col);
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);

				// drawRect(row, col, size, size, color);
				// drawRect(row - 1, col, size, size, BLACK);
				// drawRect(row, col, size, size, color);
			}
			if (KEY_DOWN_NOW(BUTTON_RIGHT) && col + size < 240)
			{
				++col;
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);
				eraseSpaceship(row, col - 1);
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);

				// drawRect(row, col, size, size, color);
				// drawRect(row, col - 1, size, size, BLACK);
				// drawRect(row, col, size, size, color);
			}
			if (KEY_DOWN_NOW(BUTTON_LEFT) && col > 0)
			{
				--col;
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);
				eraseSpaceship(row, col + 1);
				drawImage3(row, col, GALAGA_WIDTH, GALAGA_HEIGHT, galaga);

				// drawRect(row, col, 10, 10, color);
				// drawRect(row, col + 1, 10, 10, BLACK);
				// drawRect(row, col, size, size, color);
			}
		//ENEMY MOVEMENT//
			++moveDelay;
			if (moveDelay == 20)
			{
				if (enemy1 == 1)
				{
					drawRect(enemyRow, enemyCol,
					enemyWidth, enemyHeight, BLACK);
				}
				if (enemy2 == 1) {
					drawRect(enemyRow, enemyCol2,
					enemyWidth, enemyHeight, BLACK);
				}
				if (enemy3 == 1) {
					drawRect(enemyRow, enemyCol3,
					enemyWidth, enemyHeight, BLACK);
				}
				if (enemy4 == 1) {
					drawRect(enemyRow, enemyCol4,
					enemyWidth, enemyHeight, BLACK);
				}
				if (enemy5 == 1) {
					drawRect(enemyRow, enemyCol5,
					enemyWidth, enemyHeight, BLACK);
				}
				if (enemy6 == 1) {
					drawRect(enemyRow, enemyCol6,
					enemyWidth, enemyHeight, BLACK);
				}
				++moveCount;
				if (moveRight == 1)
				{
					++enemyCol;
					++enemyCol2;
					++enemyCol3;
					++enemyCol4;
					++enemyCol5;
					++enemyCol6;
					// if (enemyCol6 == 240)
					// {
					// 	enemyCol6 = 0;
					// }
					// if (enemyCol5 == 240)
					// {
					// 	enemyCol5 = 0;
					// }
					// if (enemyCol4 == 240)
					// {
					// 	enemyCol4 = 0;
					// }
					// if (enemyCol3 == 240)
					// {
					// 	enemyCol3 = 0;
					// }
					// if (enemyCol2 == 240)
					// {
					// 	enemyCol2 = 0;
					// }
					// if (enemyCol == 240)
					// {
					// 	enemyCol = 0;
					// }
					if (moveCount >= 10)
					{
						moveRight = 0;
						moveCount = 0;
					}
				} else {
					--enemyCol;
					--enemyCol2;
					--enemyCol3;
					--enemyCol4;
					--enemyCol5;
					--enemyCol6;
					if (moveCount >= 10)
					{
						moveRight = 1;
						moveCount = 0;
					}
				}
				if (enemy1 == 1)
				{
					drawHollowRect(enemyRow, enemyCol,
					enemyWidth, enemyHeight, RED);
				}
				if (enemy2 == 1) {
					drawHollowRect(enemyRow, enemyCol2,
					enemyWidth, enemyHeight, YELLOW);
				}
				if (enemy3 == 1) {
					drawHollowRect(enemyRow, enemyCol3,
					enemyWidth, enemyHeight, GREEN);
				}
				if (enemy4 == 1) {
					drawHollowRect(enemyRow, enemyCol4,
					enemyWidth, enemyHeight, CYAN);
				}
				if (enemy5 == 1) {
					drawHollowRect(enemyRow, enemyCol5,
					enemyWidth, enemyHeight, BLUE);
				}
				if (enemy6 == 1) {
					drawHollowRect(enemyRow, enemyCol6,
					enemyWidth, enemyHeight, MAGENTA);
				}
				moveDelay = 0;

			}

		
		//SHOOT//
			if (KEY_DOWN_NOW(BUTTON_A))
			{
				if (bullet == 0)
				{
					bullet = 1;
					bulletRow = row - 4;
					bulletCol = col + (width/2 - 1);
					bulletCD = 0;
				}
				if (bullet == 1 && bullet2 == 0 && bulletCD > 50)
				{
					bullet2 = 1;
					bulletRow2 = row - 4;
					bulletCol2 = col + width/2 - 1;
					bulletCD = 0;
				}
			}
		//SHOOTING LOGIC//
			if (bullet == 1)
			{
				if (bulletRow + size > 0)
				{
					--bulletRow;
					drawRect(bulletRow, bulletCol, 2, 5, color);
					drawRect(bulletRow + 1, bulletCol, 2, 5, BLACK);
					drawRect(bulletRow, bulletCol, 2, 5, color);
					++bulletCD;
				} else 
				{
					bullet = 0;
				}
			}
			if (bullet2 == 1)
			{
				if (bulletRow2 + size > 0)
				{
					--bulletRow2;
					drawRect(bulletRow2, bulletCol2, 2, 5, color);
					drawRect(bulletRow2 + 1, bulletCol2, 2, 5, BLACK);
					drawRect(bulletRow2, bulletCol2, 2, 5, color);
				} else 
				{
					bullet2 = 0;
				}
			}
		//COLLISION LOGIC//
			if (bulletRow == enemyRow)
			{
				if (bulletCol >= enemyCol && bulletCol <= enemyCol + enemyWidth)
				{
					enemy1 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol >= enemyCol2 && bulletCol <= enemyCol2 + enemyWidth)
				{
					enemy2 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol2,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol >= enemyCol3 && bulletCol <= enemyCol3 + enemyWidth)
				{
					enemy3 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol3,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol >= enemyCol4 && bulletCol <= enemyCol4 + enemyWidth)
				{
					enemy4 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol4,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol >= enemyCol5 && bulletCol <= enemyCol5 + enemyWidth)
				{
					enemy5 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol5,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol >= enemyCol6 && bulletCol <= enemyCol6 + enemyWidth)
				{
					enemy6 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol6,
						enemyWidth, enemyHeight, BLACK);
				}
			} else if (bulletRow2 == enemyRow)
			{
				if (bulletCol2 >= enemyCol && bulletCol2 <= enemyCol + enemyWidth)
				{
					enemy1 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol2 >= enemyCol2 && bulletCol2 <= enemyCol2 + enemyWidth)
				{
					enemy2 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol2,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol2 >= enemyCol3 && bulletCol2 <= enemyCol3 + enemyWidth)
				{
					enemy3 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol3,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol2 >= enemyCol4 && bulletCol2 <= enemyCol4 + enemyWidth)
				{
					enemy4 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol4,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol2 >= enemyCol5 && bulletCol2 <= enemyCol5 + enemyWidth)
				{
					enemy5 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol5,
						enemyWidth, enemyHeight, BLACK);
				} else if (bulletCol2 >= enemyCol6 && bulletCol2 <= enemyCol6 + enemyWidth)
				{
					enemy6 = 0;
					--enemies;
					drawRect(enemyRow, enemyCol6,
						enemyWidth, enemyHeight, BLACK);
				}
			}
			if (KEY_DOWN_NOW(BUTTON_SELECT))
			{
				gameplay = 0;
				//gameisover = 1;
			}
			if (enemies == 0)
			{
				delay(50);
				gameplay = 0;
				winner = 1;
			}
		}

	//~*~*~*~GAME OVER~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*// 	
		// while(winner == 1)
		// {
		// 	drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
		// }

	//~*~*~*~YOU WIN!!~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*// 	
		while (winner == 1)
		{
			drawImage3(0, 0, YOUWIN_WIDTH, YOUWIN_HEIGHT, youwin);
			if (KEY_DOWN_NOW(BUTTON_SELECT))
			{
				enemies = 6;
				winner = 0;
			}
		}

	}	
	return 0;
}