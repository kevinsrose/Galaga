#include "mylib.h"

u16 *videoBuffer = (u16*) 0x6000000;

//*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*//

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;

}

// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width,
	int height, u16 color)
{
	int row = 0;
	while(row < height)
	{
		int col = 0;
		while(col < width)
		{
			setPixel(row + r, col + c, color);
			++col;
		}
		++row;
	}
}

// A function to draw a HOLLOW rectangle starting at (r, c)
void drawHollowRect(int r, int c, int width,
	int height, u16 color)
{
	// TODO
	int row = 0;
	while (row < height)
	{
		int col = 0;
		while(col < width)
		{
			if (row < 1 || row >= height - 1 ||
				col < 1 || col >= width - 1)
			{
				setPixel(row + r, col + c, color);
			}
			++col;
		}
		++row;
	}
}

// A function that will draw an arbitrary sized image
// onto the screen
void drawImage3(int r, int c, int width,
	int height, const u16* image)
{
	int row = 0;
	while (row < height)
	{
		int col = 0;
		while (col < width)
		{
			u16 color = *image;
			setPixel(row + r, col + c, color);
			++image;
			++col;
		}
		++row;
	}

}

void drawSpaceship(int r, int c, int size)
{
	drawRect(r + 17, c, 3, 3, RED); // Left Corner
	drawRect(r + 17, c + 17, 3, 3, RED); // Right corner
	drawRect(r + 13, c + 2, size - 4 , size - 15, WHITE); // Main body
	drawRect(r + 5, c + 4, size - 8, size - 12, WHITE);
	drawRect(r + 4, c + 5, 2, 5, BLACK);
	drawRect(r + 4, c + 13, 2, 5, BLACK);
	drawRect(r + 2, c + 8, 4, 4, WHITE);
	drawRect(r + 6, c + 7, 6, 1, WHITE);
	drawRect(r, c + 9, 2, 2, BLUE);
	drawRect(r + 16, c + 6, 8, 2, BLACK);
	drawHollowRect(r + 10, c + 7, 6, 4, BLACK);	
}

void eraseSpaceship(int r, int c)
{
	drawRect(r + 17, c, 3, 3, BLACK); // Left Corner
	drawRect(r + 17, c + 17, 3, 3, BLACK); // Right corner
	drawRect(r + 13, c + 2, 16 , 5, BLACK); // Main body
	drawRect(r + 5, c + 4, 12, 8, BLACK);
	drawRect(r + 4, c + 5, 10, 1, BLACK);
	drawRect(r + 2, c + 7, 6, 2, BLACK);

	drawRect(r, c + 9, 2, 2, BLACK);
}

// A function to delay the drawing process
void delay(int n)
{
	volatile int jaboo;
	for (int i = 0; i < n*4200; ++i)
	{
		++jaboo;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


// void sendMissile(int r, int c, int width,
// 	int height, u16 color)
// {
// 	delay(4);
// 		--r;
// 		drawRect(r, c, width, height, color);
// 		delay(1);
// 		drawRect(r + 1, c, width, height, BLACK);
// 		drawRect(r, c, width, height, color);
		
// 	}
// }