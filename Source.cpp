#include "Objects.h"
#include <iostream>
#include <array>
#include <GL/glut.h> // Include the GLUT header file
//#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions
#include <vector>   // for grid
#include <ctime>
#include <thread>

using namespace std;

#define ESC 27

extern GLUquadricObj* quadratic;

ECE_PacMan Pacman(0, -5, 0);
array<float, 4> redColor{ 1.0, 0.0, 0.0, 1.0 };
array<float, 4> greenColor{ 0.0, 1.0, 0.0, 1.0 };
array<float, 4> orangeColor{ 1.0, 0.55, 0.0, 1.0 };
array<float, 4> pinkColor{ 1.0, 0.753, 0.796, 1.0 };

ECE_Ghosts Ghosts[4]{ {0, 2, 0, redColor}, {0, 1, 0, pinkColor}, {1, 1, 0, orangeColor}, {-1, 1, 0, greenColor} };  // initializing with constructor

// Camera position
float x = 0.0, y = -5.0, z = 1.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move
// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

int sceneRotationAngle = 0;
float dis = 35.0f;
GLfloat light_position1[] = { dis, -dis, dis + 5, 1.0f };    // one light source near the camera or front roght corner of the maze
//GLfloat light_position2[] = { 0, 5, 10, 0.5f };
GLfloat clrWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat clrGray[] = { 0.25f, 0.25f, 0.25f, 1.0f };

float colorDarkBlue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
float colorOffBlue[4] = { 0.0f, 0.0f, 0.6f, 1.0f };
float colorBlue[4] = { 0.289, 0.773, 0.9, 1.0f };
//float colorDarkBlue[4] = { 0.0f, 0.0f, 0.1f, 1.0f };
//float colorOffBlue[4] = { 0.0f, 0.0f, 0.75f, 1.0f };
//float colorBlue[4] = { 0, 0, 0.9, 1.0f };
GLfloat shininessBlue[] = { 5 };

float colorDarkGold[4] = { 1.0f, 0.843f, 0, 1.0f };
float colorOffGold[4] = { 0.855f, 0.65f, 0.126f, 1.0f };
float colorGold[4] = { 1, 0.875f, 0, 1.0f };   //0.9f, 0.72f, 0.0f or 0.94f, 0.902f, 0.549f or 1, 0.843, 0
GLfloat shininessGold[] = { 3 };

float colorDarkGray[4] = { 0.075f, 0.075f, 0.075f, 1.0f };
float colorOffGray[4] = { 0.75f, 0.6f, 0.5f, 1.0f };
float colorGray[4] = { 0.675f, 0.675f, 0.675f, 1.0f };
GLfloat shininessGray[] = { 2 };

float boundaries[][7] = { {-9, -10, 90, 0, 1, 0, 18},//   (x, y, angle, (axis), length)
    {-9, -10, -90, 1, 0, 0, 8}, {-9, -2, 90, 0, 1, 0, 3}, {-6, -2, -90, 1, 0, 0, 2},
    {-9, 0, 90, 0, 1, 0, 3}, {-9, 2, 90, 0, 1, 0, 3}, {-6, 2, -90, 1, 0, 0, 2},
    {-9, 4, 90, 0, 1, 0, 3}, {-9, 4, -90, 1, 0, 0, 7}, {-9, 11, 90, 0, 1, 0, 18},
    {-9, -6, 90, 0, 1, 0, 1}, {9, -10, -90, 1, 0, 0, 8}, {9, -6, -90, 0, 1, 0, 1},
    {9, -2, -90, 0, 1, 0, 3}, {6, -2, -90, 1, 0, 0, 2}, {9, 0, -90, 0, 1, 0, 3},
    {9, 2, -90, 0, 1, 0, 3}, {6, 2, -90, 1, 0, 0, 2}, {9, 4, -90, 0, 1, 0, 3},
    {9, 4, -90, 1, 0, 0, 7}, {-7, -8, 90, 0, 1, 0, 5}, {-4, -8, -90, 1, 0, 0, 2},
    {-6, -6, -90, 1, 0, 0, 2}, {-6, -4, -90, 0, 1, 0, 1}, {-4, -4, 90, 0, 1, 0, 2},
    {-4, -2, -90, 1, 0, 0, 2}, {-4, 2, -90, 1, 0, 0, 4}, {-4, 4, 90, 0, 1, 0, 2},
    {-7, 6, 90, 0, 1, 0, 1}, {-7, 8, 90, 0, 1, 0, 1}, {-7, 9, 90, 0, 1, 0, 1},
    {-7, 8, -90, 1, 0, 0, 1}, {-6, 8, -90, 1, 0, 0, 1}, {-4, 8, 90, 0, 1, 0, 2},
    {-4, 9, 90, 0, 1, 0, 2}, {-4, 8, -90, 1, 0, 0, 1}, {-2, 8, -90, 1, 0, 0, 1},
    {7, -8, -90, 0, 1, 0, 5}, {4, -8, -90, 1, 0, 0, 2},{6, -6, -90, 1, 0, 0, 2},
    {6, -4, 90, 0, 1, 0, 1}, {4, -4, -90, 0, 1, 0, 2}, {4, -2, -90, 1, 0, 0, 2},
    {4, 2, -90, 1, 0, 0, 4}, {4, 4, -90, 0, 1, 0, 2}, {7, 6, -90, 0, 1, 0, 1},
    {7, 8, -90, 0, 1, 0, 1}, {7, 9, -90, 0, 1, 0, 1}, {7, 8, -90, 1, 0, 0, 1},
    {6, 8, -90, 1, 0, 0, 1}, {4, 8, -90, 0, 1, 0, 2}, {4, 9, -90, 0, 1, 0, 2},
    {4, 8, -90, 1, 0, 0, 1}, {2, 8, -90, 1, 0, 0, 1}, {0, 8, -90, 1, 0, 0, 3},
    {0, 4, -90, 1, 0, 0, 2}, {-2, 6, 90, 0, 1, 0, 4}, {0, -4, -90, 1, 0, 0, 2},
    {-2, -2, 90, 0, 1, 0, 4}, {0, -8, -90, 1, 0, 0, 2}, {-2, -6, 90, 0, 1, 0, 4},
    {-2, 0, 90, 0, 1, 0, 4}, {-2, 0, -90, 1, 0, 0, 2}, {-2, 2, 90, 0, 1, 0, 1},
    {2, 0, -90, 1, 0, 0, 2}, {2, 2, -90, 0, 1, 0, 1} };


extern vector<vector<int> > grid;
extern vector<vector<int> > gridCoin;
extern vector<vector<int> > gridPowerUp;
extern int coinPickedUp;
extern int powerUpsPickedUp4;
extern vector<vector<int>> flatDiscs;
extern vector<vector<int>> coins;

int deaths = 0;
extern clock_t vulTime;
extern clock_t timeElapsed;
clock_t offsetGhost = clock();
extern int movDirn;
int gameStarted = 0;
int tempDir = 0;
int  ghostMovDirn = 0;
float tempDist = 0;
float shortDist = 1000;
int firstTime = 0;

//thread thread1;
thread thread2;

// Function header: init() to enable depth test and shading
// and setup the grid
void init()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, clrWhite);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, clrGray);
}

bool checkVal(vector<int>& tempCoin)
{
    if (tempCoin[0] == Pacman.getPacManX() && tempCoin[1] == Pacman.getPacManY())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function header: changeSize() to hold the view with the aspect ratio when resizing
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h); // window aspect ratio
    glMatrixMode(GL_PROJECTION); // projection matrix is active
    glLoadIdentity(); // reset the projection
    gluPerspective(20.0, ratio, 0.1, 100000.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW); // return to modelview mode
    glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}


void processNormalKeys(unsigned char key, int xx, int yy)
{
    if (firstTime == 0)
    {
        offsetGhost = clock();
        firstTime = 1;
    }
    if (key == ESC || key == 'q' || key == 'Q')
    {
        cout << "Coins Picked: " << coinPickedUp << endl << "PowerUps Picked: " << powerUpsPickedUp << endl << "Deaths: " << deaths << endl;
        exit(0);
    }
    else if (key == 'r' || key == 'R')
    {
        sceneRotationAngle = (sceneRotationAngle - 5) % 360;
    }
    gameStarted = 1;
}

void processSpecialKeys(int key, int xx, int yy)
{
    gameStarted = 1;
    if (firstTime == 0)
    {
        offsetGhost = clock();
        firstTime = 1;
        cout << "firstTime" << endl;
    }
    if (key == GLUT_KEY_UP)
    {
        movDirn = 1;
        timeElapsed = clock();
        if (!grid[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10 + 1])   // if no obstacle is there infront, then move
        {
            Pacman.movePacMan(Pacman.getPacManX(), Pacman.getPacManY() + 1, Pacman.getPacManZ());
            // if coin
            if (gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++coinPickedUp;
                coins.erase(remove_if(coins.begin(), coins.end(), checkVal), coins.end());
                gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
            }
            // else if power-up
            else if (gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++powerUpsPickedUp;
                flatDiscs.erase(remove_if(flatDiscs.begin(), flatDiscs.end(), checkVal), flatDiscs.end());
                gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
                cout << "changing color" << endl;
                vulTime = clock();
            }
        }
    }
    else if (key == GLUT_KEY_DOWN)
    {
        movDirn = 2;
        timeElapsed = clock();
        if (!grid[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10 - 1])   // if no obstacle is there behind, then move
        {
            Pacman.movePacMan(Pacman.getPacManX(), Pacman.getPacManY() - 1, Pacman.getPacManZ());
            // if coin
            if (gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++coinPickedUp;
                coins.erase(remove_if(coins.begin(), coins.end(), checkVal), coins.end());
                gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
            }
            // else if power-up
            else if (gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++powerUpsPickedUp;
                flatDiscs.erase(remove_if(flatDiscs.begin(), flatDiscs.end(), checkVal), flatDiscs.end());
                gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
                cout << "changing color" << endl;
                vulTime = clock();
            }
        }
    }
    else if (key == GLUT_KEY_LEFT)
    {
        movDirn = 4;
        timeElapsed = clock();
        // special case, move to the other side
        if ((Pacman.getPacManX()==-9)&&(Pacman.getPacManY()==1))   // if out of one side
        {
            Pacman.movePacMan(10, 1, Pacman.getPacManZ());   // go to the other side
        }
        // don't move if obstacle is there on left
        if (!grid[Pacman.getPacManX() + 9 - 1][Pacman.getPacManY() + 10])   
        {
            Pacman.movePacMan(Pacman.getPacManX() - 1, Pacman.getPacManY(), Pacman.getPacManZ());
            // if coin
            if (gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++coinPickedUp;
                coins.erase(remove_if(coins.begin(), coins.end(), checkVal), coins.end());
                gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
            }
            // else if power-up
            else if (gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++powerUpsPickedUp;
                flatDiscs.erase(remove_if(flatDiscs.begin(), flatDiscs.end(), checkVal), flatDiscs.end());
                gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
                cout << "changing color" << endl;
                vulTime = clock();
            }
        }
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        movDirn = 3;
        timeElapsed = clock();
        // special case, move to the other side
        if ((Pacman.getPacManX() == 9) && (Pacman.getPacManY() == 1))  // if out of one side
        {
            Pacman.movePacMan(-10, 1, Pacman.getPacManZ());  // go to the other side
        }
        // don't move if obstacle is there on right
        if (!grid[Pacman.getPacManX() + 9 + 1][Pacman.getPacManY() + 10])
        {
            Pacman.movePacMan(Pacman.getPacManX() + 1, Pacman.getPacManY(), Pacman.getPacManZ());
            // if coin
            if (gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++coinPickedUp;
                coins.erase(remove_if(coins.begin(), coins.end(), checkVal), coins.end());
                gridCoin[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
            }
            // else if power-up
            else if (gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10])
            {
                ++powerUpsPickedUp;
                flatDiscs.erase(remove_if(flatDiscs.begin(), flatDiscs.end(), checkVal), flatDiscs.end());
                gridPowerUp[Pacman.getPacManX() + 9][Pacman.getPacManY() + 10] = 0;
                cout << "changing color" << endl;
                vulTime = clock();
            }
        }
    }
}

float calcDist(float x1, float y1, float x2, float y2)
{
    float dx = 0, dy = 0;
    dx = x2 - x1;
    dy = y2 - y1;
    float dist = sqrt(dx * dx + dy * dy);
    return dist;
}

void identifyPath(ECE_Ghosts gh)
{
    shortDist = 1000;
    float XX = Pacman.getPacManX();
    float YY = Pacman.getPacManY();
    //cout << XX << " " << YY <<endl;
    if (ghostMovDirn!=2 && !(grid[(int)(round(gh.getX()) + 9)][(int)(round(gh.getY()) + 10 + 1)])) // up
    {
        tempDist = calcDist(XX, YY, gh.getX(), gh.getY()+1);
        if (tempDist <= shortDist)
        {
            tempDir = 1;
            shortDist = tempDist;
        }
    }
    if (ghostMovDirn!=1 && !(grid[(int)(round(gh.getX()) + 9)][(int)(round(gh.getY()) + 10 - 1)]))    //down
    {
        tempDist = calcDist(XX, YY, gh.getX(), gh.getY()-1);
        if (tempDist < shortDist)
        {
            tempDir = 2;
            shortDist = tempDist;
        }
    }
    if (ghostMovDirn!=4 && !(grid[(int)(round(gh.getX() + 9 + 1))][(int)(round(gh.getY() + 10))]))    // right
    {
        //cout << "in right";
        tempDist = calcDist(XX, YY, gh.getX()+1, gh.getY());
        if (tempDist < shortDist)
        {
            tempDir = 3;
            shortDist = tempDist;
        }
    }
    if (ghostMovDirn!=3 && !(grid[(int)(round(gh.getX() + 9 - 1))][(int)(round(gh.getY()) + 10)]))    // left
    {
        tempDist = calcDist(XX, YY, gh.getX()-1, gh.getY());
        if (tempDist < shortDist)
        {
            tempDir = 4;
            shortDist = tempDist;
        }
    }
   
    ghostMovDirn = tempDir;

    switch (ghostMovDirn)
    {
    case 1:
        //cout << 9 + round(Ghosts[0].getX()) << " " << 10 + round(Ghosts[0].getY() + 1) << endl;
        if (!grid[9 + round(Ghosts[0].getX())][10 + round(Ghosts[0].getY() + 1)])
        {
            Ghosts[0].moveGhost(Ghosts[0].getX(), Ghosts[0].getY() + 1, Ghosts[0].getZ());
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10] = 0;
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10 + 1] = 1;
        }
        break;
    case 2:
        //cout << 9 + round(Ghosts[0].getX()) << " " << 10 + round(Ghosts[0].getY() - 1) << endl;
        if (!grid[9 + round(Ghosts[0].getX())][10 + round(Ghosts[0].getY() - 1)])
        {
            Ghosts[0].moveGhost(Ghosts[0].getX(), Ghosts[0].getY() - 1, Ghosts[0].getZ());
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10] = 0;
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10 - 1] = 1;
        }
        break;
    case 3:
        //cout << 9 + round(Ghosts[0].getX() + 1) << " " << 10 + round(Ghosts[0].getY()) << endl;
        if (!grid[9 + round(Ghosts[0].getX() + 1)][10 + round(Ghosts[0].getY())])
        {
            Ghosts[0].moveGhost(Ghosts[0].getX() + 1, Ghosts[0].getY(), Ghosts[0].getZ());
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10] = 0;
            //grid[Ghosts[0].getX() + 9 + 1][Ghosts[0].getY() + 10] = 1;
        }
        break;
    case 4:
        //cout << 9 + round(Ghosts[0].getX() - 1) << " " << 10 + round(Ghosts[0].getY()) << endl;
        if (!grid[9 + round(Ghosts[0].getX() - 1)][10 + round(Ghosts[0].getY())])
        {
            Ghosts[0].moveGhost(Ghosts[0].getX() - 1, Ghosts[0].getY(), Ghosts[0].getZ());
            //grid[Ghosts[0].getX() + 9][Ghosts[0].getY() + 10] = 0;
            //grid[Ghosts[0].getX() + 9 - 1][Ghosts[0].getY() + 10] = 1;
        }
        break;
    default:
        break;
    }

    cout << "In identifying path" << tempDir << endl;
}

void update(void)
{
        //cout << coinPickedUp << " " << powerUpsPickedUp << endl;
        if (deltaMove) { // update camera position
            x += deltaMove * lx * 0.1;
            y += deltaMove * ly * 0.1;
        }
        glutPostRedisplay(); // redisplay everything 
}





void renderScene(void)
{   
    if (!(coinPickedUp == 152 && powerUpsPickedUp == 4) && deaths < 3)
    {
        //cout << coinPickedUp << " " << powerUpsPickedUp << endl;
        int i, j;

        // Clear color and depth buffers
        glClearColor(0.0, 0.0, 0.0, 1.0); // black background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();

        // Set the camera centered at (x,y,1) and looking along directional
        // vector (lx, ly, 0), with the z-axis pointing up
        gluLookAt(
            dis, -dis, dis, // camera location
            0.0, 0.0, 0.0,    // where camera is pointed
            0.0, 0.0, 1.0);      // landscape or portrait

        // Rotate the wholescene by an angle around the z-axis
        glRotatef(sceneRotationAngle, 0.0f, 0.0f, 1.0f);

        // Move the light with the scene
        glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
        //glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

        //cylinders here
        glColor3f(0.0f, 0.0f, 1.0f);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininessBlue);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffBlue);
        glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkBlue);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorBlue);
        for (int iter = 0; iter < 66; ++iter)
        {
            glPushMatrix();
            glTranslatef(boundaries[iter][0], boundaries[iter][1], 0.0);
            glRotatef(boundaries[iter][2], boundaries[iter][3], boundaries[iter][4], boundaries[iter][5]);
            gluCylinder(quadratic, 0.15f, 0.15f, boundaries[iter][6], 50, 50);
            glPopMatrix();
        }
        // powerups here
        glColor3f(1.0f, 0.875f, 0.0f);  // for golden color, from https://qph.fs.quoracdn.net/main-qimg-95026696e2212bf4bfd1fe615e059bae
        glMaterialfv(GL_FRONT, GL_SHININESS, shininessGold);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffGold);
        glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkGold);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorGold);
        for (int iter = 0; iter < flatDiscs.size(); ++iter)
        {
            glPushMatrix();
            glTranslatef(flatDiscs[iter][0], flatDiscs[iter][1], 0.0);
            gluCylinder(quadratic, 0.3f, 0.3f, 0.15, 256, 256);   // disc of radius 0.3 and width 0.15 units respectively
            glPopMatrix();
            glPushMatrix();
            glTranslatef(flatDiscs[iter][0], flatDiscs[iter][1], 0.15);
            gluDisk(quadratic, 0.0f, 0.3f, 256, 256);
            glPopMatrix();
        }
        //coins here
        glColor3f(0.75f, 0.75f, 0.75f);  // for gray color
        glMaterialfv(GL_FRONT, GL_SHININESS, shininessGray);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorOffGray);
        glMaterialfv(GL_FRONT, GL_AMBIENT, colorDarkGray);
        glMaterialfv(GL_FRONT, GL_SPECULAR, colorGray);
        for (int iter = 0; iter < coins.size(); ++iter)
        {
            glPushMatrix();
            glTranslatef(coins[iter][0], coins[iter][1], 0.0);
            glutSolidSphere(0.15f, 64, 64);
            glPopMatrix();
        }
        
        // draw pacman and ghosts
        Pacman.renderPacMan();
        if (((((float)(clock() - vulTime)) / CLOCKS_PER_SEC) < 5) && powerUpsPickedUp > 0)
        {
            //cout << "vulnerable" << endl;
            Ghosts[0].changeColor(4);
            Ghosts[1].changeColor(4);
            Ghosts[2].changeColor(4);
            Ghosts[3].changeColor(4);
            // write escape code
        }
        else if (gameStarted)
        {
            //thread thread1(identifyPath, ref(Ghosts[0]));
            //thread thread1(identifyPath, ref(Ghosts[0]));
            Ghosts[0].changeColor(0);
            Ghosts[1].changeColor(1);
            Ghosts[2].changeColor(2);
            Ghosts[3].changeColor(3);            
            if (firstTime == 1)
            {
                
                if (((((float)(clock() - offsetGhost)) / CLOCKS_PER_SEC) < 2))
                {
                    cout << "Spawning first ghost";
                    thread(identifyPath, Ghosts[0]).detach();
                }
            }
            //Ghosts[0].moveGhost();
            //write attack code
            
            if ((Ghosts[0].getX() == Pacman.getPacManX()) && (Ghosts[0].getY() == Pacman.getPacManY())) //death
            {
                gameStarted = 0;
                ++deaths;
                firstTime = 0;
                ghostMovDirn = 0;
            }
        }
        if (!gameStarted)
        {
            Pacman.movePacMan(0, -5, 0);
            Ghosts[0].moveGhost(0, 2, 0);
        }
        for (int iter = 0; iter < 4; ++iter)
        {          
            Ghosts[iter].renderGhost();
        }

        glutSwapBuffers(); // Make it all visible
    }
    else
    {
        cout << "Coins Picked: " << coinPickedUp << endl << "PowerUps Picked: " << powerUpsPickedUp << endl << "Deaths: " << deaths << endl;
        exit(0);
    }
}

void setupGrids()
{
    // Obstacle grid update
    grid[8][11] = 1;   //positions of ghosts is an obstacle : (x+9, y+10) for grid adjustment
    grid[9][11] = 1;   //positions of ghosts is an obstacle : (x+9, y+10) for grid adjustment
    grid[10][11] = 1;   //positions of ghosts is an obstacle : (x+9, y+10) for grid adjustment
    //grid[9][12] = 1;   //positions of ghosts is an obstacle : (x+9, y+10) for grid adjustment
    for (int gridCount = 0; gridCount < 66; ++gridCount)    // 66 boundaries
    {
        if (boundaries[gridCount][3] == 1)  // change y coordinate
        {
            if (boundaries[gridCount][2] == 90) // decrease y-coordinate
            {
                for (int obsNum = 0; obsNum <= boundaries[gridCount][6]; ++obsNum)
                {
                    grid[boundaries[gridCount][0] + 9][boundaries[gridCount][1] + 10 - obsNum] = 1;
                }
            }
            else if (boundaries[gridCount][2] == -90)   // increase y-coordinate
            {
                for (int obsNum = 0; obsNum <= boundaries[gridCount][6]; ++obsNum)
                {
                    grid[boundaries[gridCount][0] + 9][boundaries[gridCount][1] + 10 + obsNum] = 1;
                }
            }
        }
        else if (boundaries[gridCount][4] == 1) // change x coordinate
        {
            if (boundaries[gridCount][2] == 90) // increase x-coordinate
            {
                for (int obsNum = 0; obsNum <= boundaries[gridCount][6]; ++obsNum)
                {
                    grid[boundaries[gridCount][0] + 9 + obsNum][boundaries[gridCount][1] + 10] = 1;
                }
            }
            else if (boundaries[gridCount][2] == -90) // decrease x-coordinate
            {
                for (int obsNum = 0; obsNum <= boundaries[gridCount][6]; ++obsNum)
                {
                    grid[boundaries[gridCount][0] + 9 - obsNum][boundaries[gridCount][1] + 10] = 1;
                }
            }
        }
    }
    // print obstacle grid
    /*
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    */

    // update coin grid
    for (int gridCount = 0; gridCount < 152; ++gridCount)  // 152 coins in the grid
    {
        gridCoin[coins[gridCount][0] + 9][coins[gridCount][1] + 10] = 1;
    }

    // update power-up grid
    for (int gridCount = 0; gridCount < 4; ++gridCount)  // 4 power-ups in the grid
    {
        gridPowerUp[flatDiscs[gridCount][0] + 9][flatDiscs[gridCount][1] + 10] = 1;
    }
}

int main(int argc, char** argv)
{
    printf("\n\
-----------------------------------------------------------------------\n\
Welcome to Pac Man\n\
Press \'r\' or \'R\' to change rotate the maze/ change the view\n\
Press \'q\' or \'Q\' to quit \n\
Press up or down or left or right arrow keys to move your character\n\
-----------------------------------------------------------------------\n");


    // general initializations
    setupGrids();
    /*for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }*/
    //thread thread1(identifyPath, ref(Ghosts[0]));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 400);
    glutCreateWindow("PacMan");
    init();
    // register callbacks
    glutReshapeFunc(changeSize); // window reshape callback
    glutDisplayFunc(renderScene); // (re)display callback
    glutIdleFunc(update); // incremental update
    glutKeyboardFunc(processNormalKeys); // process standard key clicks
    glutSpecialFunc(processSpecialKeys);

    if (!quadratic)
        quadratic = gluNewQuadric();

    // enter GLUT event processing cycle
    glutMainLoop();

    return 0; // this is just to keep the compiler happy
}
