#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include <iostream>
#include "demo_base.h"
#include "lodepng.h"

#define ARRAY_SIZE_X 320
#define ARRAY_SIZE_Y 200

#define GRID_COUNT_X 40
#define GRID_COUNT_Y 25

#define GRID_COUNT_MEDIUM_X 80
#define GRID_COUNT_MEDIUM_Y 50

#define GRID_COUNT_LARGE_X 320
#define GRID_COUNT_LARGE_Y 200

#define FRAMERATE_MIN_DEFAULT 50;
#define FRAMERATE_MIN_MEDIUM 10;
#define FRAMERATE_MIN_LARGE 5;

#define FRAMERATE_MAX_DEFAULT 10;
#define FRAMERATE_MAX_MEDIUM 2;
#define FRAMERATE_MAX_LARGE 1;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define TEXTURE_COUNT 5

class TriangleDemo : public DemoBase
{
private:
	int liveCounter = 0;

	float defaultGridSize = (float)WINDOW_WIDTH / (float)GRID_COUNT_X;
	float mediumGridSize = (float)WINDOW_WIDTH / (float)GRID_COUNT_MEDIUM_X;
	float largeGridSize = (float)WINDOW_WIDTH / (float)GRID_COUNT_LARGE_X;

	float mapSizeDefault = 1;
	float mapSizeMedium = (float)GRID_COUNT_MEDIUM_X / 40;
	float mapSizeLarge = (float)GRID_COUNT_LARGE_X / 40;

	GLuint mTextureID[TEXTURE_COUNT];

	void loadPNG(const char* path, GLuint textureID)
	{
		std::vector<unsigned char> image;
		unsigned width, height;
		unsigned error = lodepng::decode(image, width, height, path);

		if (error != 0)
		{
			std::cout << "png load error: " << error << ": " << lodepng_error_text(error) << std::endl;
			return;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	}

public:

	int gridArray[ARRAY_SIZE_X][ARRAY_SIZE_Y];
	int liveArray[ARRAY_SIZE_X][ARRAY_SIZE_Y];

	int gridCountX = GRID_COUNT_X;
	int gridCountY = GRID_COUNT_Y;

	int feedbackInt = 0;

	float originPointX = 0;
	float originPointY = 0;
	float gridSize = defaultGridSize;
	float tempSize = gridSize;
	
	float currentMapSize = mapSizeDefault;

	float centerX = 0.5 * WINDOW_WIDTH;
	float centerY = 0.5 * WINDOW_HEIGHT;

	float centerWindowX = (0.5 * WINDOW_WIDTH) - 1;
	float centerWindowY = (0.5 * WINDOW_HEIGHT) - 1;

	float duration = 0;
	float frameRateMin = FRAMERATE_MIN_DEFAULT;
	float frameRateMax = FRAMERATE_MAX_DEFAULT;
	float frameRate = frameRateMin;

	float mousePosX = 0;
	float mousePosY = 0;

	bool isPaused = true;
	bool buttonClicked = false;
	bool firstClick = false;

	enum ButtonType
	{
		BTN_PAUSE = 0,
		BTN_CLEAR,
		BTN_FRAMERATE,
		BTN_SIZE,
		BTN_ZOOM,
		BTN_TOTAL
	};

	enum MapSize
	{
		MAP_DEFAULT = 0,
		MAP_MEDIUM,
		MAP_LARGE,
		MAP_TOTAL
	};

	MapSize mapSize = MAP_DEFAULT;

	void init()
	{
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadPNG("../media/PlayPause.png", mTextureID[0]);
		loadPNG("../media/ClearMap.png", mTextureID[1]);
		loadPNG("../media/Framerate.png", mTextureID[2]);
		loadPNG("../media/SizeChange.png", mTextureID[3]);
		loadPNG("../media/Zoom.png", mTextureID[4]);

		for (int i = 0; i < ARRAY_SIZE_X; i++)
		{
			for (int j = 0; j < ARRAY_SIZE_Y; j++)
			{
				gridArray[i][j] = 0;
				liveArray[i][j] = 0;
			}
		}

		//gridArray[39][0] = 1;
		//gridArray[40][0] = 1;
	
	}

	void deinit()
	{
	}

	void drawAxis(const Matrix& viewMatrix)
	{
	// ============draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.3f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.3f, 1.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.3f, 0.3f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		// ============================
	}

	void drawGrid(int gridAmount, float gridSize, const Matrix& viewMatrix)
	{
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		if (!isPaused)
		{
			duration++;

			if (duration > frameRate)
			{
				cellStateCheck();
				duration = 0;
			}
		}

		for (int i = 0; i < gridCountX; i++)
		{
			for (int j = gridCountY-1 ; j >= 0; j--)
			{
				drawCell(viewMatrix, gridSize, originPointX + (i * gridSize), 
					originPointY + (j * gridSize), gridArray[i][j]);
			}
		}

		glBegin(GL_LINES);

		for (int i = 0; i <= gridCountX; i++)
		{
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(originPointX + (i * gridSize), originPointY + gridSize, 0.0f);
			glVertex3f(originPointX + (i * gridSize), originPointY + gridSize + (gridCountY * gridSize), 0.0f);
		}

		for (int i = gridCountY+1; i >= 1; i--)
		{
			glColor3f(0.2f, 0.2f, 0.2f);
			glVertex3f(originPointX, originPointY + (i * gridSize), 0.0f);
			glVertex3f(originPointX + gridCountX * gridSize, originPointY + (i * gridSize), 0.0f);
		}

		glColor3f(1.0f, 0.5f, 0.5f);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
	}

	void drawRectangle(float posX, float posY, float sizeX, float sizeY, int buttonType)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[buttonType]);
		glBegin(GL_TRIANGLES);

		glTexCoord2f(-1, 0); glVertex3d(posX, posY, 0);
		glTexCoord2f(0, -1); glVertex3d(posX + sizeX, posY + sizeY, 0);
		glTexCoord2f(-1, -1); glVertex3d(posX, posY + sizeY, 0);

		glTexCoord2f(1, 0); glVertex3d(posX + sizeX , posY + sizeY, 0);
		glTexCoord2f(1, 1); glVertex3d(posX + sizeX, posY, 0);
		glTexCoord2f(0, 1); glVertex3d(posX, posY, 0); 
	
		glEnd(); 
	}

	void drawButton(const Matrix& viewMatrix, float sizeX, float sizeY, 
		float posX, float posY, int buttonType)
	{
		glColor3f(1.0, 1.0, 1.0);

		drawRectangle(posX, posY, sizeX, sizeY, buttonType);

		if (buttonClicked)
		{
			buttonClickCheck(posX, posY, sizeX, sizeY, buttonType);
		}
	}

	void scaleControl(float defaultSize)
	{
		if (gridSize > defaultSize || gridSize < defaultSize)
		{
			originPointX = centerX - (0.5 * gridSize * gridCountX);
			originPointY = centerY - (0.5 * gridSize * gridCountY);
		}
		else
		{
			originPointX = 0;
			originPointY = 0;
		}
		
		std::cout << originPointX << std::endl << std::endl;
		std::cout << originPointY << std::endl << std::endl;
	}

	void buttonClickCheck(float posX, float posY, float sizeX, float sizeY, int buttonType)
	{
		sizeX *= 0.9;
		posX *= 0.9;

		sizeY *= 0.9;
		posY /= -8;
		posY = 459 + posY;

		if (mousePosX > 43 + posX && mousePosX < 43 + posX + sizeX)
		{
			if (mousePosY > posY && mousePosY < posY + sizeY)
			{
				std::cout << "Clicked" << std::endl << std::endl;
				buttonFunction(buttonType);
				mousePosX = 0;
			}
		}
	}

	void mousePositionDetector(float posX, float posY)
	{
		mousePosX = posX;
		mousePosY = posY;
	}

	void buttonFunction(int buttonType)
	{
		switch (buttonType)
		{
			case BTN_PAUSE:
				pauseFunction();
				break;

			case BTN_CLEAR:
				clearMap();
				break;

			case BTN_FRAMERATE:
				frameRateControl();
				break;
			
			case BTN_SIZE:
				mapSizeChange();
				break;
			
			case BTN_ZOOM:
				zoomFunction();
				break;
		}
	}

	void drawCell(const Matrix& viewMatrix, float gridSize, float x, float y, int state)
	{
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_TRIANGLES);

		if (state == 0)
		{
			glColor3f(0.0, 0.0, 0.0);
		}
		else
		{
			glColor3f(1.0, 1.0, 1.0);
		}

		glVertex3f(x, y + gridSize, 0);
		glVertex3f(x + gridSize, y + gridSize, 0);
		glVertex3f(x, y + gridSize + gridSize, 0);

		glVertex3f(x + gridSize, y + gridSize, 0);
		glVertex3f(x + gridSize, y + gridSize + gridSize, 0);
		glVertex3f(x, y + gridSize + gridSize, 0);

		glEnd();
	}

	void cellStateCheck()
	{
		for (int i = 0; i < gridCountX; i++)
		{
			for (int j = gridCountY-1; j >= 0; j--)
			{
				
				if (i == 0)
				{
					liveCounter -= gridArray[i - 1][j] +
						gridArray[i - 1][j + 1] +
						gridArray[i - 1][j - 1];
				}

				if (j == 0)
				{
					liveCounter -= gridArray[i][j - 1] +
						gridArray[i + 1][j - 1] +
						gridArray[i - 1][j - 1];
				}

				if (i == gridCountX - 1)
				{
					liveCounter -= gridArray[gridCountX][j] +
						gridArray[gridCountX][j + 1] +
						gridArray[gridCountX][j - 1];
				}

				if (j == gridCountY - 1)
				{
					liveCounter -= gridArray[i][gridCountY] +
						gridArray[i + 1][gridCountY] +
						gridArray[i - 1][gridCountY];
				}
				
				
				liveCounter += gridArray[i - 1][j - 1] + gridArray[i - 1][j] + gridArray[i - 1][j + 1] +
					gridArray[i][j - 1] + gridArray[i][j + 1] + gridArray[i + 1][j - 1] + gridArray[i + 1][j] +
					gridArray[i + 1][j + 1];
				

				liveArray[i][j] = liveCounter;

				liveCounter = 0;
			}
		}


		for (int i = 0; i < gridCountX; i++)
		{
			for (int j = gridCountY-1; j >= 0; j--)
			{	
				if (gridArray[i][j] == 0)
				{
					if (liveArray[i][j] == 3)
					{
						gridArray[i][j] = 1;
					}
					else if (liveArray[i][j] != 3)
					{
						gridArray[i][j] = 0;
					}
				}

				if (gridArray[i][j] == 1)
				{
					if (liveArray[i][j] < 2)
					{
						gridArray[i][j] = 0;
					}
					else if (liveArray[i][j] > 1 && liveArray[i][j] < 4)
					{
						gridArray[i][j] = 1;
					}
					else
					{
						gridArray[i][j] = 0;
					}
				}
				
				liveArray[i][j] = 0;
			}
		}
	}

	void buttonClick()
	{
		buttonClicked = true;
	}

	void mouseClick()
	{
		firstClick = true;
	}

	void mouseRelease()
	{
		feedbackInt = 0;
		firstClick = false;
	}

	void mapSizeChange()
	{
		if (mapSize == MAP_DEFAULT)
		{
			mapSize = MAP_MEDIUM;
			currentMapSize = mapSizeMedium;
			gridSize = mediumGridSize;

			gridCountX = GRID_COUNT_MEDIUM_X;
			gridCountY = GRID_COUNT_MEDIUM_Y;

			frameRateMin = FRAMERATE_MIN_MEDIUM;
			frameRateMax = FRAMERATE_MAX_MEDIUM;
			
		}
		else if (mapSize == MAP_MEDIUM)
		{
			mapSize = MAP_LARGE;
			currentMapSize = mapSizeLarge;
			gridSize = largeGridSize;

			gridCountX = GRID_COUNT_LARGE_X;
			gridCountY = GRID_COUNT_LARGE_Y;

			frameRateMin = FRAMERATE_MIN_LARGE;
			frameRateMax = FRAMERATE_MAX_LARGE;
			
		}
		else if (mapSize == MAP_LARGE)
		{
			mapSize = MAP_DEFAULT;
			currentMapSize = mapSizeDefault;
			gridSize = defaultGridSize;
		
			gridCountX = GRID_COUNT_X;
			gridCountY = GRID_COUNT_Y;

			frameRateMin = FRAMERATE_MIN_DEFAULT;
			frameRateMax = FRAMERATE_MAX_DEFAULT;
			
		}

		tempSize = gridSize;
		frameRate = frameRateMin;
		scaleControl(tempSize);
	}

	void zoomFunction()
	{
		switch (mapSize)
		{
			case MAP_DEFAULT:
				zoomControl(tempSize, 10, 30);
				break;
			
			case MAP_MEDIUM:
				zoomControl(tempSize, 10, 40);
				break;
			
			case MAP_LARGE:
				zoomControl(tempSize, 40, 80);
				break;
		}
	}

	void zoomControl(float defaultSize, float sizeOne, float sizeTwo)
	{
		if (gridSize == defaultSize)
		{
			gridSize = 500 / sizeOne;
		}
		else if (gridSize == 500 / sizeOne)
		{
			gridSize = 500 / sizeTwo;
		}
		else
		{
			gridSize = defaultSize;
		}
		scaleControl(defaultSize);
	}


	void frameRateControl()
	{
		if (frameRate > frameRateMax) frameRate -= frameRateMax;
		if (frameRate <= frameRateMax) frameRate = frameRateMin;

		std::cout << frameRate << std::endl;
	}

	void pauseFunction()
	{
		if (!isPaused) isPaused = true;
		else if (isPaused) isPaused = false;
	}



	void stateSwitch(double x, double y)
	{
		float tempOriginX = centerWindowX - (0.5 * gridSize * gridCountX * 0.89);
		float tempOriginY = centerWindowY - (0.5 * gridSize * gridCountY * 0.834);
		
		std::cout<<"Size: "<<gridSize<<" Count: "<<gridCountX << std::endl << std::endl;
		std::cout << "Actual Size: " << 0.5 * gridSize * gridCountX * 0.89 << std::endl << std::endl;
		std::cout << "Actual Origin Y: " << originPointY << std::endl;
		std::cout << "Mouse Origin Y: " << tempOriginY << std::endl;
		std::cout << "Actual Origin X: " << originPointX << std::endl;
		std::cout << "Mouse Origin X: " << tempOriginX << std::endl << std::endl;

		float ratioX = ((gridSize * gridCountX * 0.89)) / gridCountX;
		float ratioY = ((gridSize * gridCountY * 0.834) - 1) / gridCountY;

		x -= tempOriginX;
		x /= ratioX;

		y -= tempOriginY;
		y /= -ratioY;
		y--;
		y += (25 * currentMapSize);
	

		std::cout << "X: " << (int)x << std::endl;
		std::cout << "Y: " << (int)y << std::endl;
		std::cout << "Grid Test: " << gridArray[0][0] << std::endl;
		std::cout << "Grid Before: " << gridArray[(int)x][(int)y] << std::endl << std::endl;

		if (firstClick)
		{
			if (x >= 0 && x < gridCountX && y >= 0 && y < gridCountY)
			{
				if (gridArray[(int)x][(int)y] == 0)
				{
					feedbackInt = 1;
					gridArray[(int)x][(int)y] = 1;
				}
				else
				{
					feedbackInt = 2;
					gridArray[(int)x][(int)y] = 0;
				}
			}
			
			firstClick = false;
		}
		

		if (feedbackInt == 1)
		{
			gridArray[(int)x][(int)y] = 1;
		}
		else if(feedbackInt == 2)
		{
			gridArray[(int)x][(int)y] = 0;
		}

		/*std::cout << "Grid Test: " << gridArray[0][0] << std::endl;
		std::cout << "Grid After: " << gridArray[(int)x][(int)y] << std::endl << std::endl;*/
	}

	void clearMap()
	{
		std::cout << "clear map" << std::endl;

		for (int i = 0; i < ARRAY_SIZE_X; i++)
		{
			for (int j = 0 ; j < ARRAY_SIZE_Y; j++)
			{
				gridArray[i][j] = 0;
			}
		}
	}

	void draw(const Matrix& viewMatrix)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		
		drawGrid(30, gridSize, viewMatrix);
		drawButton(viewMatrix, 100, 30, 0, -40, BTN_FRAMERATE);
		drawButton(viewMatrix, 100, 30, 110, -40, BTN_CLEAR);
		drawButton(viewMatrix, 100, 30, 350, -40, BTN_PAUSE);
		drawButton(viewMatrix, 100, 30, 600, -40, BTN_SIZE);
		drawButton(viewMatrix, 100, 30, 710, -40, BTN_ZOOM);
		
	}
};

#endif

//! Here are the pre-assigned array for the cells. If you need it, can assigned them to the init function.
//Blinker
/*gridArray[2][1] = 1;
  gridArray[2][3] = 1;
  gridArray[2][2] = 1;*/

//Toad
/*gridArray[4][5] = 1;
gridArray[5][5] = 1;
gridArray[6][5] = 1;
gridArray[3][4] = 1;
gridArray[4][4] = 1;
gridArray[5][4] = 1;*/

//Glider
/*gridArray[3][15] = 1;
gridArray[4][14] = 1;
gridArray[2][13] = 1;
gridArray[3][13] = 1;
gridArray[4][13] = 1;*/

