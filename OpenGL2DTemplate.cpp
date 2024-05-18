/*------------------------------------------------------------------------------------------------------------------
	Ali Mohamed Wafa 202100302
	Zenith: A Cosmic Odyssey

	Controls:
			- A and D keys for moving left and right respectively.
			- 'W' key for jumping.

	Testing Controls:
			- 'H' key: Toggles HitBox visibility.
			- 'G' key: Toggles MoonLight visibility.
			- 'R' key: Increases Health.
			- 'F' key: Toggles Ground Gaps Filling.

			- 'P' key: Switches to the Start Scene.
			- '[' key: Switches to the Game Scene.
			- ']' key: Switches to the Game Over Scene.
*/



#include <stdlib.h>
#include <glut.h>
#include <ctime>

int randomValue(int start, int end) {
	int value = rand() % (end - start + 1) + start;

	return value;
}

struct Coordinate
{
	// Point (x, y) is the lower left point of the HitBox of the Object
	int x;
	int y;
};

struct hitBox
{
	Coordinate coordinate;
	int width;
	int height;

	// Point (newX, newY) is the upper right point of the HitBox of the Object
	int newX;
	int newY;
};

// Window settings
int windowHeight = 400;
int windowWidth = 700;

//debugging
bool showHitbox = false;
bool fillGaps = true;
bool light = true;

// Character settings
float characterSpeed = 7;
float characterMoveY = 0;

bool move_right = false;
bool move_left = false;

bool jump = false;
float gravity = -0.7;
float defaultJumpForce = 18;
float jumpForce = defaultJumpForce;

int characterX = 290;
int characterY = 70;
int characterWidth = 55;
int characterHeight = 100;

Coordinate characterLocation;
hitBox characterHitBox;


// Ground settings
float moveGround[3] = { 0, 0, 0 };
bool groundCollision = false;


// Health bar settings
float health = 1.0;
float damageTaken = 1.0 / 8;
float increaseHealth = 1.0 / 8;
bool damage = false;
int hit = 0;

// Score bar settings
float score = 0.0;
float scoreIncrease = 1.0 / 8;
bool coinCollected = false;

// Coin settings
int coinWidth = 20;
float moveCoin[3][2] = { {0, 0},
						 {0, 0},
						 {0, 0} };

bool coinAvailable[3][2] = { {true, true},
							{true, true},
							{true, true} };

Coordinate coinCoordinate[3][2];
hitBox coinHitBox[3][2];


// Obstacle settings
int obstacleWidth = 100;
int obstacleHeight = 100;

bool repelLeft = false;
bool repelRight = false;
bool repelUp = false;
float repelAcceleration = -1;
float defaultRepelForce = 18;
float repelForce = defaultRepelForce;

Coordinate obstacleCoordinate[3][1];
hitBox obstacleHitBox[3][1];

//Scenes
/*
	0-> Start Menu
	1-> Game
	2-> Game over
*/
int Scene = 0;

Coordinate ButtonCoordinate;
hitBox ButtonHitBox;

//Button
bool ChangeButtonColor = false;


void drawString(float x, float y, char* string, void* font) {
	glRasterPos2f(x, y);
	for (char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);  // Updates the position
	}
}

void drawObstacle(int x) {
	//37,25,78
	glPushMatrix();
	glTranslated(x, 70, 0);
	glScaled(obstacleWidth, obstacleHeight, 1);

	//HitBox
	if (showHitbox) {
		glBegin(GL_QUADS);
		glColor3f(50.0f / 255.0f, 25.0f / 255.0f, 78.0f / 255.0f);
		glVertex2f(0, 0);//W1
		glVertex2f(1, 0);//Z1
		glVertex2f(1, 1);//A1
		glVertex2f(0, 1);//B1
		glEnd();
	}

	//Crystals

	//Crystal 1
	glBegin(GL_POLYGON);
	glColor3f(37.0f / 255.0f, 25.0f / 255.0f, 78.0f / 255.0f);
	glVertex2f(.615, .4643);//Q
	glVertex2f(0.8, .6);//R
	glVertex2f(0.8045, .4257);//S

	//22, 1, 36
	glColor3f(22.0f / 255.0f, 1.0f / 255.0f, 36.0f / 255.0f);
	glVertex2f(.610, 0.1418);//T
	glVertex2f(.5938, 0.2534);//P
	glEnd();

	//t1
	glBegin(GL_TRIANGLES);
	glColor3f(131 / 255.0f, 80.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(0.8, .6);//R

	//107, 53, 140
	glColor3f(107 / 255.0f, 53 / 255.0f, 140.0f / 255.0f);
	glVertex2f(.615, .4643);//Q
	glVertex2f(.73589, .42977);//L1
	glEnd();

	//t2
	glBegin(GL_TRIANGLES);
	glColor3f(131 / 255.0f, 80.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(0.8, .6);//R

	//58, 12, 87
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(0.8045, .4257);//S
	glVertex2f(.73589, .42977);//L1
	glEnd();

	//t3
	glBegin(GL_TRIANGLES);
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(.615, .4643);//Q
	glVertex2f(.73589, .42977);//L1
	glVertex2f(.61635, .2932);//M1
	glEnd();




	//Crystal 2
	glBegin(GL_POLYGON);
	glColor3f(37.0f / 255.0f, 25.0f / 255.0f, 78.0f / 255.0f);
	glVertex2f(.3574, 0);//O
	glVertex2f(.33, .4315);//K
	glVertex2f(.0774, .6135);//L
	glVertex2f(.06519, .39269);//M
	glVertex2f(.1, .3);//N
	glVertex2f(.24287, 0);//B2
	glEnd();

	//t1
	glBegin(GL_TRIANGLES);
	//44, 6, 69
	glColor3f(44 / 255.0f, 6 / 255.0f, 69.0f / 255.0f);
	glVertex2f(.06519, .39269);//M
	glVertex2f(.1, .3);//N
	glVertex2f(.15306, .3060);//H1
	glEnd();

	//t2
	glBegin(GL_TRIANGLES);
	//81, 25, 117
	glColor3f(81 / 255.0f, 25 / 255.0f, 117 / 255.0f);
	glVertex2f(.06519, .39269);//M
	glVertex2f(.15306, .3060);//H1
	glVertex2f(.0774, .6135);//L
	glEnd();

	//t3
	glBegin(GL_TRIANGLES);
	//140, 64, 189
	glColor3f(140 / 255.0f, 64.0f / 255.0f, 189.0f / 255.0f);
	glVertex2f(.15306, .3060);//H1
	glVertex2f(.0774, .6135);//L
	glVertex2f(.3, .4);//I1
	glEnd();

	//t4
	glBegin(GL_TRIANGLES);
	glColor3f(255 / 255.0f, 0 / 255.0f, 255 / 255.0f);
	glVertex2f(.0774, .6135);//L
	glVertex2f(.3, .4);//I1
	glVertex2f(.33, .4315);//K
	glEnd();

	//t5
	glBegin(GL_TRIANGLES);
	//81, 25, 117
	glColor3f(81 / 255.0f, 25 / 255.0f, 117 / 255.0f);
	glVertex2f(.15306, .3060);//H1
	glVertex2f(.3, .4);//I1
	glVertex2f(.3329, .1987);//J1
	glEnd();

	//p1
	glBegin(GL_POLYGON);
	//22, 1, 36
	glColor3f(22.0f / 255.0f, 1.0f / 255.0f, 36.0f / 255.0f);
	glVertex2f(.1, .3);//N
	glVertex2f(.15306, .3060);//H1
	glVertex2f(.31975, 0);//K1
	glVertex2f(.24287, 0);//B2
	glEnd();

	//p2
	glBegin(GL_POLYGON);
	// 38, 4, 61
	glColor3f(38.0f / 255.0f, 4.0f / 255.0f, 61.0f / 255.0f);
	glVertex2f(.15306, .3060);//H1
	glVertex2f(.3329, .1987);//J1
	glVertex2f(.3574, 0);//O
	glVertex2f(.31975, 0);//K1
	glEnd();






	//Crystal 3

	//t1
	glBegin(GL_TRIANGLES);
	//44, 6, 69
	glColor3f(44 / 255.0f, 6 / 255.0f, 69.0f / 255.0f);
	glVertex2f(.3096, .6032);//G
	glVertex2f(.3531, .7513);//F
	glVertex2f(.3741, .5730);//C1
	glEnd();

	//t2
	glBegin(GL_TRIANGLES);
	//81, 25, 117
	glColor3f(81 / 255.0f, 25 / 255.0f, 117 / 255.0f);
	glVertex2f(.5, 1);//E
	glVertex2f(.3531, .7513);//F
	glVertex2f(.3741, .5730);//C1
	glEnd();

	//t3
	glBegin(GL_TRIANGLES);
	//140, 64, 189
	glColor3f(140 / 255.0f, 64.0f / 255.0f, 189.0f / 255.0f);

	glVertex2f(.5, 1);//E

	glVertex2f(.533, .6069);//D1
	glVertex2f(.3741, .5730);//C1
	glEnd();

	//t4
	glBegin(GL_TRIANGLES);
	//174, 114, 212
	glColor3f(174 / 255.0f, 114.0f / 255.0f, 212.0f / 255.0f);
	glVertex2f(.6361, .6206);//J
	glVertex2f(.5, 1);//E
	glVertex2f(.533, .6069);//D1
	glEnd();

	//t5
	glBegin(GL_TRIANGLES);
	//81, 25, 117
	glColor3f(81 / 255.0f, 25 / 255.0f, 117 / 255.0f);
	glVertex2f(.3741, .5730);//C1
	glVertex2f(.533, .6069);//D1
	glVertex2f(.502, .3584);//F1
	glEnd();

	//p1
	glBegin(GL_POLYGON);
	//22, 1, 36
	glColor3f(22.0f / 255.0f, 1.0f / 255.0f, 36.0f / 255.0f);
	glVertex2f(.3741, .5730);//C1
	glVertex2f(.4, 0);//E1
	glVertex2f(.3574, 0);//H
	glVertex2f(.3096, .6032);//G
	glEnd();

	//p2
	glBegin(GL_POLYGON);
	// 38, 4, 61
	glColor3f(38.0f / 255.0f, 4.0f / 255.0f, 61.0f / 255.0f);
	glVertex2f(.3741, .5730);//C1
	glVertex2f(.502, .3584);//F1
	glVertex2f(.5, 0);//G1
	glVertex2f(.4, 0);//E1
	glEnd();

	//p3
	glBegin(GL_POLYGON);
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(.533, .6069);//D1
	glVertex2f(.502, .3584);//F1
	glVertex2f(.5, 0);//G1
	glVertex2f(.6, 0);//I
	glVertex2f(.6361, .6206);//J
	glEnd();




	//Crystal 4
	glBegin(GL_POLYGON);
	//15, 1, 26
	glColor3f(15.0f / 255.0f, 1.0f / 255.0f, 26.0f / 255.0f);
	glVertex2f(.5292, 0);//U
	glVertex2f(.7, 0);//A1
	glVertex2f(.9478, .2021);//Z
	glVertex2f(.94785, .42013);//W
	glVertex2f(.67799, .3025);//V
	glEnd();

	//t1
	glBegin(GL_TRIANGLES);
	//168,139,189
	glColor3f(168 / 255.0f, 139.0f / 255.0f, 189.0f / 255.0f);
	glVertex2f(.94785, .42013);//W
	glColor3f(131 / 255.0f, 80.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(.67799, .3025);//V
	glVertex2f(.7092, .2619);//O1
	glEnd();

	//t2
	glBegin(GL_TRIANGLES);
	//80,36,108
	glColor3f(131 / 255.0f, 80.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(.94785, .42013);//W
	glColor3f(80 / 255.0f, 36 / 255.0f, 108.0f / 255.0f);
	glVertex2f(.88469, .2098);//N1
	glVertex2f(.7092, .2619);//O1
	glEnd();

	//t3
	glBegin(GL_TRIANGLES);
	glColor3f(131 / 255.0f, 80.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(.94785, .42013);//W

	//58, 12, 87
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(.88469, .2098);//N1
	glVertex2f(.9478, .2021);//Z
	glEnd();

	//t4
	glBegin(GL_TRIANGLES);
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(.7643, .1359);//Q1
	glVertex2f(.88469, .2098);//N1
	glVertex2f(.7092, .2619);//O1
	glEnd();

	//p1
	glBegin(GL_POLYGON);
	//58, 12, 87
	glColor3f(58 / 255.0f, 12 / 255.0f, 87.0f / 255.0f);
	glVertex2f(.67799, .3025);//V
	glVertex2f(.7092, .2619);//O1
	glVertex2f(.576, 0);//P1
	glVertex2f(.5292, 0);//U
	glEnd();

	//p2
	glBegin(GL_POLYGON);
	// 27, 5, 42
	glColor3f(27.0f / 255.0f, 5.0f / 255.0f, 42.0f / 255.0f);
	glVertex2f(.7643, .1359);//Q1
	glVertex2f(.7092, .2619);//O1
	glVertex2f(.576, 0);//P1
	glVertex2f(.6365, 0);//S1
	glEnd();



	glPopMatrix();
}

void obstacles() {
	int x;
	int y;
	int land = 0;

	//Land 0
	glPushMatrix();
	glTranslated(moveGround[land], 0, 0);
	x = obstacleCoordinate[land][0].x;
	drawObstacle(x);
	glPopMatrix();

	//Land 1
	land = 1;
	glPushMatrix();
	glTranslated(moveGround[land], 0, 0);
	x = obstacleCoordinate[land][0].x;
	drawObstacle(x);
	glPopMatrix();

	//Land 2
	land = 2;

	glPushMatrix();
	glTranslated(moveGround[land], 0, 0);
	x = obstacleCoordinate[land][0].x;
	drawObstacle(x);
	glPopMatrix();

}

void drawCoin(int x, int y) {
	GLUquadric* quadric = gluNewQuadric();

	glPushMatrix();
	glTranslated(x, y, 0);

	if (showHitbox) {
		//Hitbox
		glBegin(GL_QUADS);
		glColor3f(255.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f);
		glVertex2f(0, 0);//S1 x = 320
		glVertex2f(20, 0);//T1
		glVertex2f(20, 20);//U1
		glVertex2f(0, 20);//V1
		glEnd();
	}

	glPushMatrix();
	glTranslated(10, 10, 0);
	//74, 34, 138
	glColor4f(74.0f / 255.0f, 34 / 255.0f, 138.0f / 255.0f, .8);
	gluDisk(quadric, 0, 10, 100, 1);
	glPopMatrix();

	glBegin(GL_POLYGON);
	//171, 176, 245
	glColor3f(171.0f / 255.0f, 176 / 255.0f, 245.0f / 255.0f);
	glVertex2f(7, 12);//D2
	glVertex2f(0, 10);//E2
	glVertex2f(7, 8);//V1
	glVertex2f(10, 0);//G2
	glVertex2f(10, 20);//C2
	glEnd();

	glPushMatrix();
	glTranslatef(10, 10, 0);
	glScaled(.5, .5, 1);
	glTranslatef(-10, -10, 0);

	glBegin(GL_POLYGON);
	//212, 215, 252
	glColor3f(212.0f / 255.0f, 215.0f / 255.0f, 252.0f / 255.0f);
	glVertex2f(7, 12);//D2
	glVertex2f(0, 10);//E2
	glVertex2f(7, 8);//V1
	glVertex2f(10, 0);//G2
	glVertex2f(10, 20);//C2
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glRotated(180, 0, 1, 0);
	glTranslatef(-10, 0, 0);

	glBegin(GL_POLYGON);
	glColor3f(171.0f / 255.0f, 176 / 255.0f, 245.0f / 255.0f);
	glVertex2f(7, 12);//D2
	glVertex2f(0, 10);//E2
	glVertex2f(7, 8);//V1
	glVertex2f(10, 0);//G2
	glVertex2f(10, 20);//C2
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 10, 0);
	glRotatef(180, 0, 1, 0);
	glScaled(.5, .5, 1);
	glTranslatef(-10, -10, 0);

	glBegin(GL_POLYGON);
	glColor3f(212.0f / 255.0f, 215.0f / 255.0f, 252.0f / 255.0f);
	glVertex2f(7, 12);//D2
	glVertex2f(0, 10);//E2
	glVertex2f(7, 8);//V1
	glVertex2f(10, 0);//G2
	glVertex2f(10, 20);//C2
	glEnd();
	glPopMatrix();


	glPopMatrix();
}

void collectableCoin(int x, int y, int land, int coin) {
	if (coinAvailable[land][coin]) {
		drawCoin(x, y);
	}
}

void coins() {
	int x;
	int y;
	int land = 0;
	int coinNum = 0;

	//Land 0
	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();

	coinNum++;
	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();


	//Land 1
	land = 1;
	coinNum = 0;

	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();

	coinNum++;
	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();


	//Land 2
	land = 2;
	coinNum = 0;

	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();

	coinNum++;
	glPushMatrix();
	glTranslated(moveCoin[land][coinNum], 0, 0);
	x = coinCoordinate[land][coinNum].x;
	y = coinCoordinate[land][coinNum].y;
	collectableCoin(x, y, land, coinNum);
	glPopMatrix();

}


void HealthBar() {
	GLUquadric* quadric = gluNewQuadric();
	glPushMatrix();
	glTranslated(35, 338, 0);
	glColor3f(.8, 0, 0);

	glPushMatrix();
	glScaled(.5, .8, 1);
	glTranslated(0, 10, 0);
	gluDisk(quadric, 0, 10, 100, 1);
	glPopMatrix();

	glPushMatrix();
	glScaled(health, .8, 1);

	glPushMatrix();
	glTranslated(200, 10, 0);
	glScaled(.5, 1, 1);
	gluDisk(quadric, 0, 10, 100, 1);
	glPopMatrix();

	glBegin(GL_QUADS);
	glVertex2d(0, 0); //O
	glVertex2d(0, 20); //R
	glVertex2d(200, 20); //Q
	glVertex2d(200, 0); //P
	glEnd();

	glPopMatrix();
	glPopMatrix();


	//Heart
	glPushMatrix();
	glTranslated(7, 336, 0);
	glScaled(20, 18, 1);

	glColor3f(.8, 0, 0);

	glPushMatrix();
	glTranslated(.75, .75, 0);
	gluDisk(quadric, 0, .25, 100, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.25, .75, 0);
	gluDisk(quadric, 0, .25, 100, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.5, .6, 0);
	gluDisk(quadric, 0, .05, 100, 1);
	glPopMatrix();

	glBegin(GL_TRIANGLES);
	glVertex2d(.5, 0); //I
	glVertex2d(.95, .6); //J
	glVertex2d(.048, .6); //Q
	glEnd();

	glPopMatrix();
	glPopMatrix();
}

void scoreBar() {

	//Bar
	GLUquadric* quadric = gluNewQuadric();
	glPushMatrix();
	glTranslated(35, 305, 0);
	glColor3f(171.0f / 255.0f, 176 / 255.0f, 245.0f / 255.0f);

	glPushMatrix();
	glScaled(.5, .8, 1);
	glTranslated(0, 10, 0);
	gluDisk(quadric, 0, 10, 100, 1);
	glPopMatrix();


	glScaled(score, .8, 1);

	glPushMatrix();
	glTranslated(200, 10, 0);
	glScaled(.5, 1, 1);
	gluDisk(quadric, 0, 10, 100, 1);
	glPopMatrix();

	glBegin(GL_QUADS);
	glVertex2d(0, 0); //O
	glVertex2d(0, 20); //R
	glVertex2d(200, 20); //Q
	glVertex2d(200, 0); //P

	glEnd();

	glPopMatrix();

	//Icon
	glPushMatrix();

	drawCoin(7, 303);

	glPopMatrix();
}


void groundTile(int x, int y) {

	//23, 0, 22
	glPushMatrix();
	glTranslated(x, y, 0);
	glBegin(GL_QUADS);
	glColor3f(23.0f / 255.0f, 0.0f / 255.0f, 22.0f / 255.0f);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glVertex2f(100, 70);
	glVertex2f(0, 70);
	glEnd();

	glBegin(GL_POLYGON);
	//37, 21, 64
	glColor3f(37.0f / 255.0f, 21.0f / 255.0f, 64.0f / 255.0f);
	glVertex2f(0, 70);//T 
	glVertex2f(100, 70);//U
	glVertex2f(100, 62);//N1
	glVertex2f(90, 55);//M1
	glVertex2f(85, 59);//L1
	glVertex2f(70, 53);//k1
	glVertex2f(60, 53);//J1
	glVertex2f(50, 60);//I1
	glVertex2f(30, 54);//D1
	glVertex2f(20, 59);//B1
	glVertex2f(10, 55);//A1
	glVertex2f(6, 55);//Z
	glVertex2f(0, 62.5);//W
	glEnd();

	glPopMatrix();
}

void ground(int x) {
	int originPoint = x;
	int width = 100;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
	originPoint += width;

	groundTile(originPoint, 0);
}

void land() {
	//Fill Gaps
	if (fillGaps) {
		glPushMatrix();
		glTranslated(moveGround[1], 0, 0);
		groundTile(-100, 0);
		groundTile(700, 0);
		glPopMatrix();
	}

	//Land 0
	glPushMatrix();
	glTranslated(moveGround[0], 0, 0);
	ground(-700);
	glPopMatrix();

	//Land 1
	glPushMatrix();
	glTranslated(moveGround[1], 0, 0);
	ground(0);
	glPopMatrix();

	//Land 2
	glPushMatrix();
	glTranslated(moveGround[2], 0, 0);
	ground(700);
	glPopMatrix();

	coins();
	obstacles();

	//moving to the right
	if (moveGround[1] <= -700.0 && move_right) {
		moveGround[1] = 700.0;
		coinAvailable[1][0] = true;
		coinAvailable[1][1] = true;

		moveCoin[1][0] = 700.0;
		moveCoin[1][1] = 700.0;
		coinCoordinate[1][0].x = randomValue(coinWidth, windowWidth - obstacleWidth - coinWidth);
		coinCoordinate[1][0].x = randomValue(coinWidth, windowWidth - obstacleWidth - coinWidth);

	}
	else if (moveGround[2] <= -1400 && move_right) {
		moveGround[2] = 0.0;
		coinAvailable[2][0] = true;
		coinAvailable[2][1] = true;

		moveCoin[2][0] = 0.0;
		moveCoin[2][1] = 0.0;
		coinCoordinate[2][0].x = randomValue(windowWidth + coinWidth, 2 * windowWidth - obstacleWidth - coinWidth);
		coinCoordinate[2][0].x = randomValue(windowWidth + coinWidth, 2 * windowWidth - obstacleWidth - coinWidth);

		moveGround[0] = 0.0;
		coinAvailable[0][0] = true;
		coinAvailable[0][1] = true;
		moveCoin[0][0] = 0.0;
		moveCoin[0][1] = 0.0;
	}

	//moving to the left
	if (moveGround[1] >= 700.0 && move_left) {
		moveGround[1] = -700.0;
		coinAvailable[1][0] = true;
		coinAvailable[1][1] = true;

		moveCoin[1][0] = -700.0;
		moveCoin[1][1] = -700.0;
		coinCoordinate[1][0].x = randomValue(coinWidth, windowWidth - obstacleWidth - coinWidth);
		coinCoordinate[1][0].x = randomValue(coinWidth, windowWidth - obstacleWidth - coinWidth);

	}
	else if (moveGround[0] >= 1400 && move_left) {
		moveGround[0] = 0.0;
		coinAvailable[0][0] = true;
		coinAvailable[0][1] = true;

		moveCoin[0][0] = 0.0;
		moveCoin[0][1] = 0.0;
		coinCoordinate[0][0].x = randomValue(-windowWidth + coinWidth, -obstacleWidth - coinWidth);
		coinCoordinate[0][0].x = randomValue(-windowWidth + coinWidth, -obstacleWidth - coinWidth);

		moveGround[2] = 0.0;
		coinAvailable[2][0] = true;
		coinAvailable[2][1] = true;
		moveCoin[2][0] = 0.0;
		moveCoin[2][1] = 0.0;
	}
}

void Stars() {
	glColor3d(83.0f / 255.0f, 4.0f / 255.0f, 97.0f / 255.0f);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex3f(50.0, 254.0, 0);
	glVertex3f(20.0, 104.0, 0);
	glVertex3f(50.0, 254.0, 0);
	glVertex3f(385.0, 106.0, 0);
	glVertex3f(358.0, 254.0, 0);
	glVertex3f(344.0, 565.0, 0);
	glVertex3f(381.0, 453.0, 0);
	glVertex3f(204.0, 254.0, 0);
	glVertex3f(220.0, 100.0, 0);
	glVertex3f(60.0, 539.0, 0);
	glVertex3f(10.0, 254.0, 0);
	glVertex3f(29.0, 568.0, 0);
	glVertex3f(191.0, 597.0, 0);
	glVertex3f(171.0, 366.0, 0);
	glVertex3f(110.0, 406.0, 0);
	glVertex3f(314.0, 435.0, 0);
	glVertex3f(215.0, 374.0, 0);
	glVertex3f(150.0, 295.0, 0);
	glVertex3f(195.0, 254.0, 0);
	glVertex3f(312.0, 568.0, 0);
	glVertex3f(126.0, 373.0, 0);
	glVertex3f(60.0, 99.0, 0);
	glVertex3f(10.0, 75.0, 0);
	glVertex3f(1.0, 10.0, 0);
	glVertex3f(300.0, 565.0, 0);
	glVertex3f(90.0, 62.0, 0);
	glVertex3f(301.0, 594.0, 0);
	glVertex3f(390.0, 10.0, 0);
	glVertex3f(395.0, 100.0, 0);
	glVertex3f(370.0, 88.0, 0);
	glVertex3f(323.0, 75.0, 0);
	glVertex3f(568.0, 273.0, 0);
	glVertex3f(217.0, 105.0, 0);
	glVertex3f(321, 90, 0);
	glVertex3f(673, 161, 0);
	glVertex3f(617, 334, 0);
	glVertex3f(550, 188, 0);
	glVertex3f(462, 351, 0);
	glVertex3f(447, 197, 0);
	glEnd();

	glColor3f(0.78f, 0.69f, 0.83f);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex3f(227.0, 554.0, 0);
	glVertex3f(91.0, 91.0, 0);
	glVertex3f(95.0, 5.0, 0);
	glVertex3f(74.0, 10.0, 0);
	glVertex3f(126.0, 373.0, 0);
	glVertex3f(60.0, 99.0, 0);
	glVertex3f(10.0, 75.0, 0);
	glVertex3f(1.0, 10.0, 0);
	glVertex3f(300.0, 120, 0);
	glVertex3f(90.0, 62.0, 0);
	glVertex3f(520, 303, 0);
	glVertex3f(497, 388, 0);
	glVertex3f(620, 303, 0);
	glEnd();

}

void moonLight() {
	float scale = 3;

	//217, 203, 245

	glPushMatrix();
	glTranslated(630, 336, 0);
	glScaled(42, 42, 1);
	glScaled(scale, scale, 1);

	glBegin(GL_POLYGON);
	glColor4f(217.0f / 255.0f, 203.0f / 255.0f, 245.0f / 255.0f, 0.3);
	glVertex2f(0, 0);//A

	glColor4f(0, 0, 0, 0);
	glVertex2f(0, 1);//A'
	glVertex2f(.866, .5);//F
	glVertex2f(.866, -.5);//E
	glVertex2f(0, -1);//D
	glVertex2f(-.866, -.5);//C
	glVertex2f(-.866, .5);//B
	glVertex2f(0, 1);//A

	glEnd();

	glPopMatrix();
}

void moon() {
	GLUquadric* quadric = gluNewQuadric();

	if (light) {
		moonLight();
	}

	//191, 171, 206
	glPushMatrix();
	glColor3f(0.75f, 0.67f, 0.81f);
	glTranslated(630, 336, 0);
	gluDisk(quadric, 0, 42, 100, 1);
	glPopMatrix();



}

void charactar() {
	GLUquadric* quadric = gluNewQuadric();
	glPushMatrix();
	glTranslated(characterX, characterY, 0);
	glScaled(1, 1, 1);

	if (showHitbox) {
		//hit box
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0, characterHeight);//L
		glVertex2f(characterWidth, characterHeight);//K
		glVertex2f(characterWidth, 0);//J
		glVertex2f(0, 0);//I
		glEnd();
	}


	/*-----Character------*/

	//body
	glBegin(GL_POLYGON);
	//85, 20, 140
	glColor3f(85.0f / 255.0f, 20.0f / 255.0f, 140.0f / 255.0f);
	glVertex2f(27.39, 67.1);//G1
	glVertex2f(17.8, 66.1);//Q
	glVertex2f(13.7, 60.3);//P
	glVertex2f(11.18, 52.15);//O
	glVertex2f(8.95, 43.78);//N
	glVertex2f(6.16, 31.69);//M
	glVertex2f(4.88, 22);//E

	//55,10,94
	glColor3f(55.0f / 255.0f, 10.0f / 255.0f, 94.0f / 255.0f);
	glVertex2f(2.28, 0);//H
	glVertex2f(27.39, 0);//I
	glEnd();

	glPushMatrix();
	glTranslated(27.39, 0, 0);
	glRotated(180, 0, 1, 0);
	glTranslated(-27.39, 0, 0);

	glBegin(GL_POLYGON);
	//95, 33, 148
	glColor3f(95.0f / 255.0f, 33.0f / 255.0f, 148.0f / 255.0f);
	glVertex2f(27.39, 67.1);//G1
	glVertex2f(17.8, 66.1);//Q
	glVertex2f(13.7, 60.3);//P
	glVertex2f(11.18, 52.15);//O
	glVertex2f(8.95, 43.78);//N
	glVertex2f(6.16, 31.69);//M
	glVertex2f(4.88, 22);//E

	//55,10,94
	glColor3f(55.0f / 255.0f, 10.0f / 255.0f, 94.0f / 255.0f);
	glVertex2f(2.28, 0);//H
	glVertex2f(27.39, 0);//I
	glEnd();
	glPopMatrix();

	glBegin(GL_TRIANGLES);
	//38, 0, 29
	glColor3f(38.0f / 255.0f, 0.0f / 255.0f, 29.0f / 255.0f);
	glVertex2f(27.39, 59.2);//G1
	glVertex2f(27.39, 0);//I1
	glVertex2f(7.75, 0);//F1
	glEnd();

	glPushMatrix();
	glTranslatef(27.39, 0, 0);
	glRotated(180, 0, 1, 0);
	glTranslatef(-27.39, 0, 0);

	glBegin(GL_TRIANGLES);
	glColor3f(38.0f / 255.0f, 0.0f / 255.0f, 29.0f / 255.0f);
	glVertex2f(27.39, 59.2);//G1
	glVertex2f(27.39, 0);//I1
	glVertex2f(7.75, 0);//F1
	glEnd();
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslated(27.72, 76.125, 0);
	glScaled(1.3, 1.3, 1);
	glTranslated(-27.72, -76.125, 0);

	glBegin(GL_POLYGON);
	//182, 178, 191
	glColor3f(182.0f / 255.0f, 178.0f / 255.0f, 191.0f / 255.0f);
	glVertex2f(27.7, 62.29);//R
	glVertex2f(27.7, 77.29);//C1
	glVertex2f(24.6, 78.9);//W
	glVertex2f(17.39, 89.96);//Z
	glVertex2f(18.6, 78.8);//A1
	glVertex2f(21.12, 67.5);//B1
	glEnd();

	glPushMatrix();
	glTranslated(27.72, 0, 0);
	glRotated(180, 0, 1, 0);
	glTranslated(-27.72, 0, 0);

	glBegin(GL_POLYGON);
	//182,178,191
	glColor3f(182.0f / 255.0f, 178.0f / 255.0f, 191.0f / 255.0f);
	glVertex2f(21.12, 67.5);//B1
	glVertex2f(27.7, 62.29);//R
	glVertex2f(27.7, 77.29);//C1
	glVertex2f(24.6, 78.9);//W

	//202, 199, 209
	glColor3f(202.0f / 255.0f, 199.0f / 255.0f, 209.0f / 255.0f);
	glVertex2f(17.39, 89.96);//Z
	glVertex2f(18.6, 78.8);//A1

	glEnd();
	glPopMatrix();

	//Eyes
	glPushMatrix();
	glTranslated(23.84, 73, 0);
	glScaled(.8, 1.3, 1);

	glColor3f(0, 0, 0);
	gluDisk(quadric, 0, 2.49, 100, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(27.72, 0, 0);
	glRotated(180, 0, 1, 0);
	glTranslated(-27.72, 0, 0);

	glTranslated(23.84, 73, 0);
	glScaled(.8, 1.3, 1);

	glColor3f(0, 0, 0);
	gluDisk(quadric, 0, 2.49, 100, 1);
	glPopMatrix();





	glPopMatrix();


	glPopMatrix();
}

void checkCollissionGround() {
	if (characterMoveY + 70 <= 70) {
		groundCollision = true;
	}
	else {
		groundCollision = false;
	}
}

void checkCollectCoin(int land, int coin) {

	int x = coinCoordinate[land][coin].x;
	int y = coinCoordinate[land][coin].y;

	int newX = x + coinWidth;
	int newY = y + coinWidth;

	bool checkX = ((moveCoin[land][coin] + x <= characterHitBox.newX) && (moveCoin[land][coin] + x >= characterLocation.x)) || // left of the coin
		(moveCoin[land][coin] + newX <= characterHitBox.newX) && (moveCoin[land][coin] + newX >= characterLocation.x); // right of the coin
	bool checkY = (characterMoveY + 70 <= newY);
	bool collect = checkX && checkY;

	if (collect) {
		coinCollected = true;
		coinAvailable[land][coin] = false;
		moveCoin[land][coin] = 10000;
	}
}

void checkCollissionObstacle(int land) {
	int obstacleX = obstacleCoordinate[land][0].x;
	int obstacleY = obstacleCoordinate[land][0].y;

	int obstacleNewX = obstacleX + obstacleWidth;
	int obstacleNewY = obstacleY + obstacleHeight;


	bool checkLeft = (characterHitBox.newX <= moveGround[land] + obstacleNewX) &&
		(characterHitBox.newX >= moveGround[land] + obstacleX);

	bool checkRight = (characterLocation.x <= moveGround[land] + obstacleNewX) &&
		(characterLocation.x >= moveGround[land] + obstacleX);

	bool checkX = checkLeft || checkRight;
	bool checkY = (characterMoveY + 70 <= obstacleNewY);
	bool collsion = checkX && checkY;

	if (collsion && hit < 1) {
		damage = true;

		if (checkLeft) {
			repelLeft = true;
		}
		else {
			repelRight = true;
		}

		hit++;
	}
}


void coinObjects() {
	Coordinate coin_L0_C0;
	Coordinate coin_L0_C1;
	Coordinate coin_L1_C0;
	Coordinate coin_L1_C1;
	Coordinate coin_L2_C0;
	Coordinate coin_L2_C1;

	coin_L0_C0.x = randomValue(-windowWidth, -obstacleWidth - coinWidth);
	coin_L0_C1.x = randomValue(-windowWidth, -obstacleWidth - coinWidth);
	coin_L1_C0.x = randomValue(0, windowWidth - obstacleWidth - coinWidth);
	coin_L1_C1.x = randomValue(0, windowWidth - obstacleWidth - coinWidth);
	coin_L2_C0.x = randomValue(windowWidth, 2 * windowWidth - obstacleWidth - coinWidth);
	coin_L2_C1.x = randomValue(windowWidth, 2 * windowWidth - obstacleWidth - coinWidth);

	coin_L0_C0.y = 70;
	coin_L0_C1.y = 70;
	coin_L1_C0.y = 70;
	coin_L1_C1.y = 70;
	coin_L2_C0.y = 70;
	coin_L2_C1.y = 70;

	coinCoordinate[0][0] = coin_L0_C0;
	coinCoordinate[0][1] = coin_L0_C1;

	coinCoordinate[1][0] = coin_L1_C0;
	coinCoordinate[1][1] = coin_L1_C1;

	coinCoordinate[2][0] = coin_L2_C0;
	coinCoordinate[2][1] = coin_L2_C1;

	//hitBox
	for (int land = 0; land < 3; land++) {
		for (int coin = 0; coin < 3; coin++) {
			coinHitBox[land][coin].coordinate = coinCoordinate[land][coin];
			coinHitBox[land][coin].width = coinWidth;
			coinHitBox[land][coin].height = coinWidth;
		}
	}
}

void CharacterObject() {
	characterLocation.x = characterX;
	characterLocation.y = characterY;

	characterHitBox.coordinate = characterLocation;
	characterHitBox.height = characterHeight;
	characterHitBox.width = characterWidth;

	characterHitBox.newX = characterLocation.x + characterWidth;
	characterHitBox.newY = characterLocation.y + characterHeight;
}

void obstacleObject() {
	Coordinate obstacle_L0_C0;
	Coordinate obstacle_L1_C0;
	Coordinate obstacle_L2_C0;

	obstacle_L0_C0.x = -obstacleWidth;
	obstacle_L1_C0.x = windowWidth - obstacleWidth;
	obstacle_L2_C0.x = 2 * windowWidth - obstacleWidth;

	obstacle_L0_C0.y = 70;
	obstacle_L1_C0.y = 70;
	obstacle_L2_C0.y = 70;

	obstacleCoordinate[0][0] = obstacle_L0_C0;
	obstacleCoordinate[1][0] = obstacle_L1_C0;
	obstacleCoordinate[2][0] = obstacle_L2_C0;

	//hitBox
	for (int land = 0; land < 3; land++) {
		obstacleHitBox[land][0].coordinate = obstacleCoordinate[land][0];
		obstacleHitBox[land][0].width = obstacleWidth;
		obstacleHitBox[land][0].height = obstacleHeight;
	}

}

void ButtonObject() {
	ButtonCoordinate.x = 290;
	ButtonCoordinate.y = 170;

	ButtonHitBox.coordinate = ButtonCoordinate;
	ButtonHitBox.height = 40;
	ButtonHitBox.width = 130;

	ButtonHitBox.newX = ButtonCoordinate.x + 130;
	ButtonHitBox.newY = ButtonCoordinate.y + 40;
}


void buttonColor() {
	if (ChangeButtonColor) {
		//93, 72, 163
		glColor3f(93.0f / 255.0f, 72.0f / 255.0f, 163.0f / 255.0f);
	}
	else {
		glColor3f(37.0f / 255.0f, 25.0f / 255.0f, 78.0f / 255.0f);
	}
}

void drawButton(char* string) {
	int buttonX = ButtonCoordinate.x;
	int buttonY = ButtonCoordinate.y;

	int buttonNewX = ButtonHitBox.newX;
	int buttonNewY = ButtonHitBox.newY;

	glPushMatrix();
	glTranslated(-10, 0, 0);

	glBegin(GL_QUADS);
	buttonColor();
	glVertex2d(buttonX, buttonY);
	glVertex2d(buttonNewX, buttonY);
	glVertex2d(buttonNewX, buttonNewY);
	glVertex2d(buttonX, buttonNewY);
	glEnd();

	glColor3f(1, 0, 0);
	drawString(buttonX + 10, buttonY + 10, string, GLUT_BITMAP_TIMES_ROMAN_24);
	glPopMatrix();
}


void startScene() {
	Stars();
	drawButton("Start Game");
}

void gameScene() {
	Stars();

	moon();

	HealthBar();

	scoreBar();

	land();

	//character
	glPushMatrix();
	glTranslatef(0, characterMoveY, 0);
	charactar();
	glPopMatrix();
}

void gameOverScene() {
	drawButton("Game Over");
}

void showScene() {
	switch (Scene)
	{
	case 0:
		startScene();
		break;
	case 1:
		gameScene();
		break;
	case 2:
		gameOverScene();
		break;
	default:
		break;
	}
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	showScene();

	glFlush();
}


void moveRight(float speed) {
	moveGround[0] -= speed;
	moveGround[1] -= speed;
	moveGround[2] -= speed;

	moveCoin[0][0] -= speed;
	moveCoin[0][1] -= speed;

	moveCoin[1][0] -= speed;
	moveCoin[1][1] -= speed;

	moveCoin[2][0] -= speed;
	moveCoin[2][1] -= speed;
}

void moveLeft(float speed) {
	moveGround[0] += speed;
	moveGround[1] += speed;
	moveGround[2] += speed;

	moveCoin[0][0] += speed;
	moveCoin[0][1] += speed;

	moveCoin[1][0] += speed;
	moveCoin[1][1] += speed;

	moveCoin[2][0] += speed;
	moveCoin[2][1] += speed;
}

void jump_timer(int value) {
	if (jump && jumpForce > 0) {
		characterMoveY += jumpForce;
		jumpForce += gravity;
	}

	if (jumpForce <= 0 && !groundCollision) {
		jump = false;
		characterMoveY += jumpForce;
		jumpForce += gravity;
		checkCollissionGround();
	}

	if (groundCollision) {
		characterMoveY = 0;
		jumpForce = defaultJumpForce;
		groundCollision = false;
	}

	glutTimerFunc(15, jump_timer, 0);
	glutPostRedisplay();
}

void move_timer(int value) {
	if (move_right) {
		moveRight(characterSpeed);
	}
	else if (move_left) {
		moveLeft(characterSpeed);
	}

	checkCollectCoin(0, 0);
	checkCollectCoin(0, 1);
	checkCollectCoin(1, 0);
	checkCollectCoin(1, 1);
	checkCollectCoin(2, 0);
	checkCollectCoin(2, 1);

	checkCollissionObstacle(0);
	checkCollissionObstacle(1);
	checkCollissionObstacle(2);

	glutTimerFunc(15, move_timer, 0);
	glutPostRedisplay();
}

void health_timer(int value) {

	if (damage)
	{
		health -= damageTaken;
		damage = false;
	}

	if (health == 0)
	{
		health = 1;
		Scene = 2;
	}


	glutTimerFunc(15, health_timer, 0);
	glutPostRedisplay();
}

void Score_timer(int value) {

	if (coinCollected)
	{
		score += scoreIncrease;
		coinCollected = false;
	}

	if (score > 1)
	{
		score = 0;
	}


	glutTimerFunc(15, Score_timer, 0);
	glutPostRedisplay();
}

void repel_timer(int value) {
	if (repelForce != 0) {
		if (repelLeft) {
			moveLeft(repelForce);
			repelForce += repelAcceleration;
			characterSpeed = 0;
		}
		else if (repelRight) {

			moveRight(repelForce);
			repelForce += repelAcceleration;
			characterSpeed = 0;
		}

		if (repelForce <= 0) {
			repelLeft = false;
			repelRight = false;
			repelForce = defaultRepelForce;
			characterSpeed = 7;
			hit = 0;
		}
	}

	glutTimerFunc(15, repel_timer, 0);
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
	//Movment
	if (Scene == 1) {
		switch (key)
		{
		case 'd': move_right = true;
			break;
		case'a': move_left = true;
			break;

		case 'w': jump = true;
			break;

		case's': characterMoveY -= characterSpeed;
			break;

		case'r':
			if (health < 1.0) {
				health += increaseHealth;
			}
			break;

		case'h':
			if (!showHitbox) {
				showHitbox = true;
			}
			else {
				showHitbox = false;
			}

			break;

		case'f':
			if (!fillGaps) {
				fillGaps = true;
			}
			else {
				fillGaps = false;
			}

			break;

		case'g':
			if (!light) {
				light = true;
			}
			else {
				light = false;
			}

			break;

		default:
			break;
		}
	}

	//Scene Control
	switch (key)
	{
	case 'p':
		Scene = 0;
		break;
	case '[':
		Scene = 1;
		break;
	case ']':
		Scene = 2;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'd':
		move_right = false;
		break;
	case'a': move_left = false;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void cursur(int button, int state, int mouseX, int mouseY) {
	mouseY = windowHeight - mouseY;

	bool checkX = (mouseX <= ButtonHitBox.newX) &&
		(mouseX >= ButtonCoordinate.x);

	bool checkY = (mouseY <= ButtonHitBox.newY) &&
		(mouseY >= ButtonCoordinate.y);

	bool collsion = checkX && checkY;

	if (collsion) {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (Scene == 0) {
				Scene = 1;
			}
			else if (Scene == 2) {
				exit(EXIT_SUCCESS);
			}
			break;

		default:
			break;
		}

	}
	glutPostRedisplay();
}

void PassiveMotion(int mouseX, int mouseY) {
	mouseY = windowHeight - mouseY;

	bool checkX = (mouseX <= ButtonHitBox.newX) &&
		(mouseX >= ButtonCoordinate.x);

	bool checkY = (mouseY <= ButtonHitBox.newY) &&
		(mouseY >= ButtonCoordinate.y);

	bool collsion = checkX && checkY;

	if (collsion) {
		ChangeButtonColor = true;
	}
	else {
		ChangeButtonColor = false;
	}

	glutPostRedisplay();
}

void main(int argc, char** argr) {

	srand(time(NULL));

	coinObjects();
	CharacterObject();
	obstacleObject();
	ButtonObject();

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(150, 100);

	glutCreateWindow("Zenith: A Cosmic Odyssey");
	glutDisplayFunc(Display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboard_up);
	glutMouseFunc(cursur);
	glutPassiveMotionFunc(PassiveMotion);

	glutTimerFunc(0, jump_timer, 0);
	glutTimerFunc(0, move_timer, 0);
	glutTimerFunc(0, repel_timer, 0);
	glutTimerFunc(0, Score_timer, 0);
	glutTimerFunc(0, health_timer, 0);

	//5, 0, 15
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(5.0f / 255.0f, 0.0f / 255.0f, 15.0f / 255.0f, 0.0f);
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);

	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutMainLoop();
}