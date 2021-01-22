#pragma once
using namespace std;
#include <GL/glut.h> // Include the GLUT header file
#include <array>
#include <iostream>
#include <array>
#include <GL/glut.h> // Include the GLUT header file
//#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <vector>   // for grid
#include <ctime>

// Global variables shared with Source file (externs)
GLUquadricObj* quadratic{ nullptr };
vector<vector<int> > grid(19, vector<int>(22, 0));
int movDirn = 0;	// 0-Stop, 1-Top, 2-Down, 3-Right, 4-Left
clock_t timeElapsed = clock();
clock_t vulTime = clock();
vector<vector<int> > gridCoin(19, vector<int>(22, 0));
vector<vector<int> > gridPowerUp(19, vector<int>(22, 0));
int coinPickedUp = 0;
int powerUpsPickedUp = 0;
vector<vector<int>> flatDiscs = { {-8, -5}, {-8, 9}, {8, 9}, {8, -5} }; // (x, y)
// Could have written a loop, but definition is more efficient compared to search functions
vector<vector<int>> coins =
{ {-8,-9}, {-7,-9}, {-6,-9}, {-5,-9}, {-4,-9}, {-3,-9}, {-2,-9}, {-1,-9}, {0,-9}, {1,-9}, {2,-9}, {3,-9}, {4,-9}, {5,-9}, {6,-9}, {7,-9}, {8,-9},
{-8, -8}, {-1, -8}, {1, -8}, {8, -8},
{-8, -7}, {-7, -7}, {-6, -7}, {-5, -7}, {-3, -7}, {-2, -7},{-1, -7}, {1, -7}, {2, -7}, {3, -7}, {5, -7}, {6, -7}, {7, -7}, {8, -7},
{-7, -6}, {-5, -6}, {-3, -6}, {3, -6}, {5, -6}, {7, -6},
{-7, -5}, {-5, -5}, {-4, -5}, {-3, -5}, {-2, -5}, {-1, -5}, {1, -5}, {2, -5}, {3, -5}, {4, -5}, {5, -5}, {7, -5},
{-8, -4}, {-5, -4}, {-1, -4}, {1, -4}, {5, -4}, {8, -4},
{-8, -3}, {-7, -3}, {-6, -3}, {-5, -3}, {-4, -3}, {-3, -3}, {-2, -3}, {-1, -3}, {1, -3}, {2, -3}, {3, -3}, {4, -3}, {5, -3}, {6, -3}, {7, -3}, {8, -3},
{-5, -2}, {5, -2},
{-5, -1}, {5, -1},
{-5, 0}, {5, 0},
{-5, 1}, {5, 1},
{-5, 2}, {5, 2},
{-5, 3}, {5, 3},
{-5, 4}, {5, 4},
{-8, 5}, {-7, 5}, {-6, 5}, {-5, 5}, {-3, 5}, {-2, 5},{-1, 5}, {1, 5}, {2, 5}, {3, 5}, {5, 5}, {6, 5}, {7, 5}, {8, 5},
{-8, 6}, {-5, 6}, {-3, 6}, {3, 6}, {5, 6}, {8, 6},
{-8, 7}, {-7,7}, {-6,7}, {-5,7}, {-4,7}, {-3,7}, {-2,7}, {-1,7}, {0,7}, {1,7}, {2,7}, {3,7}, {4,7}, {5,7}, {6,7}, {7,7}, {8,7},
{-8, 8}, {-5, 8}, {-1, 8}, {1, 8}, {5, 8}, {8, 8},
{-5, 9}, {-1, 9}, {1, 9},{5, 9},
{-8, 10}, {-7,10}, {-6,10}, {-5,10}, {-4,10}, {-3,10}, {-2,10}, {-1,10}, {1,10}, {2,10}, {3,10}, {4,10}, {5,10}, {6,10}, {7,10}, {8,10}
};

float vel = 0;


float colorDarkYellow[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
float colorOffYellow[4] = { 0.7f, 0.7f, 0.0f, 1.0f };
float colorYellow[4] = { 0.9, 0.9, 0, 1.0f };
GLfloat shininessYellow[] = { 4 };

float colorDarkRed[4] = { 0.4f, 0.0f, 0.0f, 1.0f };
float colorOffRed[4] = { 0.7f, 0.0f, 0.0f, 1.0f };
float colorRed[4] = { 0.9f, 0.0f, 0.0f, 1.0f };
GLfloat shininessRed[] = { 3 };

float colorDarkGreen[4] = { 0.0f, 0.4f, 0.0f, 1.0f };
float colorOffGreen[4] = { 0.0f, 0.7f, 0.0f, 1.0f };
float colorGreen[4] = { 0.0, 0.9, 0, 1.0f };
GLfloat shininessGreen[] = { 3 };

float colorDarkPink[4] = { 0.4f, 0.301f, 0.318f, 1.0f };
float colorOffPink[4] = { 0.7f, 0.527f, 0.558f, 1.0f };
float colorPink[4] = { 0.9, 0.677, 0.716, 1.0f };
GLfloat shininessPink[] = { 3 };

float colorDarkOrange[4] = { 0.4f, 0.216f, 0.0f, 1.0f };
float colorOffOrange[4] = { 0.7f, 0.385f, 0.0f, 1.0f };
float colorOrange[4] = { 0.9, 0.495, 0, 1.0f };
GLfloat shininessOrange[] = { 3 };

float colorDarkWhite[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
float colorOffWhite[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
float colorWhite[4] = { 0.9, 0.9, 0.9, 1.0f };
GLfloat shininessWhite[] = { 3 };


class ECE_PacMan
{
private:
	float x{ 0 }, y{ 0 }, z{ 0 };
	const float color[4] = { 1.0, 1.0, 0.0, 1.0f };	//maybe remove const
public:
	ECE_PacMan(float xx, float yy, float zz)
	{
		this->x = xx;
		this->y = yy;
		this->z = zz;
	}
	float getPacManX()
	{
		return this->x;
	}
	float getPacManY()
	{
		return this->y;
	}
	float getPacManZ()
	{
		return this->z;
	}
	bool checkVal(vector<int>& tempCoin)
	{
		if (tempCoin[0] == this->getPacManX() && tempCoin[1] == this->getPacManY())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void movePacMan(float xx, float yy, float zz)
	{
		this->x = xx;
		this->y = yy;
		this->z = zz;
	}
	
	void movePM()
	{
		if (movDirn == 0)
		{
			vel = 0;
		}
		else
		{
			vel = 0.1;
		}
		// move pc
		if (movDirn == 1)
		{
			if (!grid[this->getPacManX() + 9][this->getPacManY() + 10 + 1])   // if no obstacle is there infront, then move
			{
				this->movePacMan(this->getPacManX(), this->getPacManY() + 1, this->getPacManZ());
			}
		}

		/*
		// if coin
		if (gridCoin[this->getPacManX() + 9][this->getPacManY() + 10])
		{
			++coinPickedUp;
			coins.erase(remove_if(coins.begin(), coins.end(), checkVal), coins.end());
			gridCoin[this->getPacManX() + 9][this->getPacManY() + 10] = 0;
		}
		// else if power-up
		else if (gridPowerUp[this->getPacManX() + 9][this->getPacManY() + 10])
		{
			++powerUpsPickedUp;
			flatDiscs.erase(remove_if(flatDiscs.begin(), flatDiscs.end(), checkVal), flatDiscs.end());
			gridPowerUp[this->getPacManX() + 9][this->getPacManY() + 10] = 0;
			cout << "changing color" << endl;
			vulTime = clock();
		}
		*/
	}
	
	void renderPacMan()
	{
		glColor3f(1.0f, 1.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininessYellow);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffYellow);
		glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkYellow);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colorYellow);
		glPushMatrix();
		glTranslatef(this->x, this->y, 0.0);
		glutSolidSphere(0.55f, 64, 64);	// 0.55, a constant radius for Pacman sphere
		glPopMatrix();
	}
};

class ECE_Ghosts
{
private:
	float x{ 0 }, y{ 0 }, z{ 0 };
	array <float, 4> color{ 1.0, 0, 0, 1.0 };	// default to red
	array <float, 4> red{ 1.0, 0, 0, 1.0 };	// redColor
	array <float, 4> green{ 0.0, 1.0, 0, 1.0 };	// greenColor
	array <float, 4> pink{ 1.0, 0.753, 0.796, 1.0 };	// pinkColor
	array <float, 4> orange{ 1.0, 0.55, 0.0, 1.0 };	// orangeColor
	array <float, 4> white{ 1.0, 1.0, 1.0, 1.0 }; // white
public:
	ECE_Ghosts(float xx, float yy, float zz, array<float, 4> arr)
	{
		this->x = xx;
		this->y = yy;
		this->z = zz;
		this->color = arr;
	}
	float getX()
	{
		return this->x;
	}
	float getY()
	{
		return this->y;
	}
	float getZ()
	{
		return this->z;
	}
	void moveGhost(float xx, float yy, float zz)
	{
		this->x = xx;
		this->y = yy;
		this->z == zz;
	}
	void changeColor(int vul)
	{
		if (vul == 4)
		{
			this->color = white;
		}
		else if (vul == 0)
		{
			this->color = red;
		}
		else if (vul == 1)
		{
			this->color = pink;
		}
		else if (vul == 2)
		{
			this->color = orange;
		}
		else if (vul == 3)
		{
			this->color = green;
		}
	}

	

	void renderGhost()
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(this->color[0], this->color[1], this->color[2]);
		if (this->color == red)
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessRed);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffRed);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkRed);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorRed);
		}
		else if (this->color == green)
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessGreen);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffGreen);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkGreen);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorGreen);
		}
		else if (this->color == pink)
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessPink);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffPink);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkPink);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorPink);
		}
		else if (this->color == orange)
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessOrange);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffOrange);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkOrange);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorOrange);
		}
		else if (this->color == white)
		{
			glMaterialfv(GL_FRONT, GL_SHININESS, shininessWhite);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffWhite);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkWhite);
			glMaterialfv(GL_FRONT, GL_SPECULAR, colorWhite);
		}

		glPushMatrix();
		glTranslatef(this->x, this->y, 0.0);
		gluCylinder(quadratic, 0.4f, 0.4f, 0.4, 50, 50);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(this->x, this->y, 0.4);
		glutSolidSphere(0.4f, 64, 64);	// 0.55, a constant radius for Pacman sphere
		glPopMatrix();
	}
};
