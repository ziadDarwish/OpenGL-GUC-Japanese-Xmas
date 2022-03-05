#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;
namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

float timeElapsed = 30.0;
int presentCounter = 0;
float eyeX = 0.1;
float eyeY = 0.1;
float eyeZ = 0.1;

float refX = 0.0;
float refY = 0.0;
float refZ = 0.0;

float upX = 0.0;
float upY = 1.0;
float upZ = 0.0;

bool win = false;
bool lose = false;

float keyZ = 0.2;
float keyX = 0.5;
float turnRight = 0.0;
float turnCheecksRight = 0.008;
bool present1 = false;
bool present2 = false;
bool present3 = false;

float direction = -0.01;
float countg = 0.1;
float smcount = 0.1;

float zDiff = 0.01;
float xDiff = 0.0;

float mouthPos = 0.0;

float tailPart1 = 0.01;
float tailPart2 = 0.03;


float tailPart1Z = 0.0;
float tailPart2Z = 0.0;



float conePosition = 0.01;
float conePosition2 = 0.00;

bool tpressed = false;
bool ypressed = false;
bool upressed = false;
bool opressed = false;

float eyedir = 0.01;

float mouthdir =0.019;

double xcord1[5] = {0.12,0.625,0.06,0.71,0.44};
double xcord2[5] = {0.42,0.775,0.25 ,0.79,0.46};


float zcord1[5] = {0.65,0.625,0.25,0.31,0.08};
float zcord2[5] = {0.85,0.775,0.45,0.39,0.12};

float angle = 0;
float xaxis = 1;
float yaxis = 1;
float zaxis = 1;


float winangle = 0;
float winXaxis = 1;
float winYaxis = 1;
float winZaxis = 1;



float lanternangle = 0;
float lanternXaxis = 1;
float lanternYaxis = 1;
float lanternZaxis = 1;

bool lannternSwing = false;

float smSwing = 0;
bool smbool = false;


float sc = 1.0;

float scCount = 0.01;

float woodXscale = 0.5;
float woodYscale =1;
float woodZscale =0.5;


float woodY = 0.08;
float woodY2 = 0.025;

float ballY = 0.52;
float decY1 = 0.45;
float decY2 = 0.35;
float decY3 = 0.2;

float winX = 0.25;
float winY = 0.75;
float winZ = 0.25;

float openWindow = 0.0;


float red = 1.0;
float green = 1.0;
float blue = 1.0;


float red2 = 1.0;
float green2 = 0.0;
float blue2 = 0.0;


void drawBitmapText(string text, float x, float y, float z)
{

	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(x, y, z);
	for (int i = 0; i < text.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
}


void drawTimer() {
	string timeString = "Time : " + patch::to_string(int(timeElapsed)) + " s";
	drawBitmapText(timeString, winX, winY, winZ);
}

void drawWin() {
	string score = "CONGRATS YOU WIN";
	drawBitmapText(score, winX, winY, winZ);

}


void drawLose() {
	string score = "TIME IS UP. YOU LOST. MERRY CHRISTMAS";
	drawBitmapText(score, winX, winY, winZ);

}
void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}
void DrawCircle(float cx, float cy, float cz, float r, int num_segments, float red, float g, float b) {
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);

	glColor3d(red, g, b);

	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex3f(x + cx, y + cy, cz);//output vertex 

	}
	glPopMatrix();
	glEnd();
}
void drawTrapazoid(float x, float y, float z,float d, float l, float h) {

	glPushMatrix();
	glTranslatef(0.0f, 0.45f, -0.0025f);
	//ROOF PYRAMID
	//glRotatef(degree, 1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.0, 0);
	glVertex3f(x,y,z);
	glVertex3f(x+l, y - h, d - z);
	glVertex3f(x+l, y - h, d + z);


	glColor3f(0.7, 0.0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x - l, y - h, d + z);
	glVertex3f(l + x, y - h, d + z);

	glColor3f(0.7, 0.0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x - l, y - h, d + z);
	glVertex3f(x - l, y - h, z - d);

	glColor3f(0.7, 0.0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x - l, y-h, z-d);
	glVertex3f(x + l, y-h, z-d);

	glColor3f(0.7, 0.0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x + l, y - h, z + d);
	glVertex3f(x + l, y - h, z - d);

	/*******************************
	

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.40f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.30f + z);

	//*******************************
	
	
	*/
	glEnd();
	glPopMatrix();

}

bool collision(float x, float z ) {
	int i = 0;
	while (i<4) {
		if (x>=xcord1[i] && x<=xcord2[i]) {
			if (z >= zcord1[i] && z <= zcord2[i]) {
				return true;
			}
		}
		i = i + 1;
	}
	return false;

}
void drawFence3() {

	//DrawCircle(0.1, 0.2, 0.02, 0.03, 20, 1, 0, 0);

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(1, 0.2, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(1.0, 0.4, 0.02);
	glutSolidCube(1);
	glPopMatrix();

	float i = 0.2;
	int i2 = 0;
	while (i < 1) {


		glPushMatrix();
		glColor3f(red,green,blue);
		if (i2 % 2 == 0) {
			glTranslated(0.8 + i, 0.22, 0.02);
			glRotated(-90, 0.0, 1.0, 0.0);
		}
		else {
			glTranslated(0.9 + i, 0.25, 0.01);
			glRotated(-90, 0.0, 1.0, 0.0);
		}

		glutSolidSphere(0.005, 5, 15);
		glPopMatrix();

		i = i + 0.04;
		i2 = i2 + 1;

	}

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.99, 0.2, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(0.15, 0.15, 0.005);
	glutSolidCube(1);
	glPopMatrix();


	float i3 = 0.0;

	while (i3 < 1) {
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(1, 0.2, i3);
		glRotated(-90, 0.0, 1.0, 0.0);
		glScaled(0.015, 0.4, 0.02);
		glutWireCube(1);
		glPopMatrix();
		i3 = i3 + 0.015;

	}
	float i4 = 0.0;
	while (i4 < 1) {

		drawTrapazoid(1.0, 0, i4, 0.02, 0.02, 0.05);
		i4 = i4 + 0.02;
	}

}

void drawFence2() {

	DrawCircle(0.1, 0.2, 0.02, 0.03, 20, red,green,blue);

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.0, 0.2, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(1.0, 0.4, 0.02);
	glutSolidCube(1);
	glPopMatrix();

	float i = 0.2;
	int i2 = 0;
	while (i < 1) {


		glPushMatrix();
		glColor3f(red2, green2, blue2);
		if (i2 % 2 == 0) {
			glTranslated(0 + i, 0.22, 0.01);
			glRotated(-90, 0.0, 1.0, 0.0);
		}
		else {
			glTranslated(0 + i, 0.25, 0.01);
			glRotated(-90, 0.0, 1.0, 0.0);
		}

		glutSolidSphere(0.005, 5, 15);
		glPopMatrix();

		i = i + 0.04;
		i2 = i2 + 1;

	}

	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslated(0.01, 0.2, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(0.15, 0.15, 0.005);
	glutSolidCube(1);
	glPopMatrix();


	float i3 = 0.0;

	while (i3 < 1) {
		glPushMatrix();
		glColor3f(red, green, blue);
		glTranslated(0.0, 0.2,i3);
		glRotated(-90, 0.0, 1.0, 0.0);
		glScaled(0.015, 0.4, 0.02);
		glutWireCube(1);
		glPopMatrix();
		i3 = i3 + 0.015;

	}

	float i4 = 0;

	while (i4 < 1) {

		drawTrapazoid(0.0, 0, i4, 0.02, 0.02, 0.05);
		i4 = i4 + 0.02;
	}

}
void drawFence() {

	DrawCircle(0.1, 0.2, 0.02, 0.03, 20, red2, green2, blue2);

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.5, 0.2, 0.0);
	glScaled(1.0, 0.4, 0.02);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0.7, 0);
	glTranslated(0.5, 0.35, 0.05);
	glutSolidTorus(0.005, 0.015, 32, 32);
	glPopMatrix();

	float i = 0.2;
	int i2 = 0;
	while (i<1) {


		glPushMatrix();
		glColor3f(red2, green2, blue2);
		if (i2%2==0) {
			glTranslated(0 + i, 0.22, 0.01);
		}
		else {
			glTranslated(0 + i, 0.25, 0.01);
		}
		
		glutSolidSphere(0.005, 5, 15);
		glPopMatrix();

		i = i + 0.04;
		i2 = i2 + 1;

	}

	glPushMatrix();
	glColor3f(red, green, blue);
	glTranslated(0.1, 0.2, 0.01);
	glScaled(0.15, 0.15, 0.005);
	glutSolidCube(1);
	glPopMatrix();


	float i3 = 0.0;

	while (i3<1) {


		glPushMatrix();
		glColor3f(red, green, blue);
		glTranslated(0.008+i3, 0.2, 0.001);
		glScaled(0.015, 0.4, 0.02);
		glutWireCube(1);
		glPopMatrix();

		i3 = i3 + 0.015;

	}

	float i4 = 0;

	while (i4 < 1) {

		drawTrapazoid(i4,0,0,0.02,0.02,0.05);
		i4 = i4 + 0.02;
	}

}


void drawGround(double thickness) {
	glPushMatrix();
	glColor3f(0.0, 0.5, 0.2);
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void key(unsigned char k, int x, int y) {

	if (k == 'W') {
	//	eyeZ += 0.01;
		refZ += 0.01;

		winX = 0.25;
		winY = 0.75;
		winZ = 0.25;
	}
	if (k == 'S') {
		//eyeZ -= 0.01;
		refZ -= 0.01;
		winX = 0.25;
		winY = 0.75;
		winZ = 0.25;
	}
	if (k == 'A') {
		//eyeX -= 0.01;
		refX += 0.01;
		winX = 0.25;
		winY = 0.75;
		winZ = 0.25;
	}
	if (k == 'D') {
		//eyeX += 0.01;
		refX -= 0.01;
		winX = 0.25;
		winY = 0.75;
		winZ = 0.25;
	}
	if (!lose) {

		if (k == 'm') {
			eyeX = 0.1;
			eyeY = 0.1;
			eyeZ = 0.5;
			refX = 0.0;
			refY = 0.0;
			refZ = 0.5;
			upX = 0.0;
			upY = 1.0;
			upZ = 0.0;
			winX = 0.25;
			winY = 0.75;
			winZ = 0.25;

		}
		if (k == 'n') {

			eyeX = 0.5;
			eyeY = 0.5;
			eyeZ = 0.5;

			refX = 0.5;
			refY = 0.0;
			refZ = 0.5;

			upX = 1.0;
			upY = 0.0;
			upZ = 0.0;

			winX = 0.45;
			winY = 0.45;
			winZ = 0.25;
		}
		if (k == 'b') {

			eyeX = 0.5;
			eyeY = 0.2;
			eyeZ = 0.3;
			refX = 0.5;
			refY = 0.0;
			refZ = 0.0;
			upX = 0.0;
			upY = 1.0;
			upZ = 0.0;

			winX = 0.45;
			winY = 0.45;
			winZ = 0.25;

		}
		if (k == 'w') {
			direction = -0.01;
			eyedir = 0.012;
			mouthdir = 0.019;
			turnRight = 0.0;
			turnCheecksRight = 0.0;
			conePosition = 0.01;
			conePosition2 = 0.0;
			zDiff = 0.01;
			xDiff = 0.00;
			angle = 0;
			xaxis = 1;
			yaxis = 1;
			zaxis = 1;
			tailPart1 = 0.01;
			tailPart2 = 0.03;
			tailPart1Z = 0.0;
			tailPart2Z = 0.0;
			mouthPos = 0.0;
			if (!collision(keyX, keyZ + 0.01) && keyZ + 0.01 < 1) {
				keyZ += 0.01;
			}
		}
		if (k == 's') {
			direction = 0.01;
			eyedir = -0.012;
			mouthdir = -0.019;
			turnRight = 0.0;
			turnCheecksRight = 0.0;
			conePosition = 0.01;
			conePosition2 = 0.0;
			zDiff = 0.01;
			xDiff = 0.00;
			angle = 0;
			xaxis = 1;
			yaxis = 1;
			zaxis = 1;
			tailPart1 = 0.01;
			tailPart2 = 0.03;
			tailPart1Z = 0.0;
			tailPart2Z = 0.0;
			mouthPos = 0.0;
			if (!collision(keyX, keyZ - 0.01) && keyZ - 0.01 > 0.03) {
				keyZ -= 0.01;
			}
		}
		if (k == 'a') {

			turnRight = -0.01;
			turnCheecksRight = -0.013;
			conePosition = 0.0;
			conePosition2 = 0.01;
			eyedir = 0;
			zDiff = 0.0;
			xDiff = -0.01;
			direction = -0.01;
			angle = 90;
			xaxis = 0;
			yaxis = 1;
			zaxis = 0;
			tailPart1 = 0.02;
			tailPart2 = 0.02;
			tailPart1Z = 0.02;
			tailPart2Z = 0.01;
			mouthPos = -0.02;
			mouthdir = 0.0;


			if (!collision(keyX - 0.01, keyZ) && keyX - 0.01 > 0.03) {
				keyX -= 0.01;
			}
		}
		if (k == 'd') {
			turnRight = 0.01;
			turnCheecksRight = 0.013;
			conePosition = 0.0;
			conePosition2 = 0.01;
			eyedir = 0;
			zDiff = 0.0;
			xDiff = 0.01;
			direction = -0.01;
			angle = 90;
			xaxis = 0;
			yaxis = 1;
			zaxis = 0;
			tailPart1 = -0.02;
			tailPart2 = -0.02;
			tailPart1Z = -0.01;
			tailPart2Z = -0.00;
			mouthPos = 0.02;
			mouthdir = 0.0;

			if (!collision(keyX + 0.01, keyZ) && keyX + 0.01 < 0.97) {
				keyX += 0.01;
			}
		}
		if (k == 't') {
			tpressed = !tpressed;
			if (tpressed) {
				lanternangle = 0.5;
			}
			else {
				lanternangle = 0.0;
			}
		}
		if (k == 'y') {
			ypressed = !ypressed;
			if (ypressed) {
				smSwing = 0.5;
			}
			else {
				smSwing = 0.0;
			}
		}
		if (k == 'u') {
			upressed = !upressed;
			if (upressed) {
				sc = 1.0;
				ballY = 0.52;
				woodY = 0.08;
				decY1 = 0.45;
				decY2 = 0.35;
				decY3 = 0.2;

			}
			else {
				sc = 0.4;
				ballY = 0.22;
				woodY = 0.025;
				decY1 = 0.17;
				decY2 = 0.14;
				decY3 = 0.08;

			}
		}
		if (k == 'o') {
			opressed = !opressed;
			if (opressed) {
				winangle = 90;
				winXaxis = 0;
				winYaxis = 1;
				winZaxis = 0;
				openWindow = 0.05;
			}
			else {
				winangle = 0;
				winXaxis = 1;
				winYaxis = 1;
				winZaxis = 1;
				openWindow = 0.0;
			}

		}
		if ((keyZ > 0.50 && keyZ < 0.55) && ((keyX > 0.40 && keyX < 0.50)) && !present1) {
			present1 = true;
			presentCounter += 1;
		}

		if ((keyZ > 0.85 && keyZ < 0.95) && ((keyX > 0.05 && keyX < 0.15)) && !present2) {
			present2 = true;
			presentCounter += 1;
		}

		if ((keyX > 0.85 && keyX < 0.95) && ((keyZ > 0.00 && keyZ < 0.10)) && !present3) {
			present3 = true;
			presentCounter += 1;
		}
		if (presentCounter == 3) {
			win = true;
		}
	}
	glutPostRedisplay();

}


void drawYin(float cx, float cy, float cz, float r, int num_segments) {
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);

	glColor3d(1.0, 1.0, 1.0);

	for (int ii = 0; ii < num_segments/2; ii++) {
		float theta =0.17+ 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex3f(x + cx, y + cy, cz);//output vertex 
	}
	glPopMatrix();
	glEnd();

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);

	glColor3d(0.0, 0.0,	0.0);

	for (int ii = 0; ii < num_segments / 2; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = -1* r * sinf(theta);//calculate the y component 
		glVertex3f(x + cx, y + cy+0.01, cz);//output vertex 
		
	}
	
	glPopMatrix();
	glEnd();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1.5);
	//gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, refX, refY, refZ, upX, upY, upZ);
}

void drawSnowman() {
	//SNOWMAN BEGIN
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.25, 0.03, 0.35);
	glutSolidSphere(0.03, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.25, 0.07, 0.35);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.25, 0.1, 0.35);
	glutSolidSphere(0.015, 15, 15);
	glPopMatrix();


	// HAT 
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.25, 0.11, 0.35);
	glRotated(90.0, 1, 0, 0);
	glRotated(40.0, 0.0, 1.0, 0.0);
	glScaled(1, 1, 0.6);

	glutSolidTorus(0.007, 0.008, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0.23, 0.14, 0.35);
	//glRotated(-20.0, 0.0, 1.0, 0.0);
	glutSolidSphere(0.005, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.25, 0.115, 0.35);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(-40.0, 0.0, 1.0, 0.0);
	glutSolidCone(0.015, 0.027, 15, 15);
	glPopMatrix();


	// EYES AND HANDS

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.26, 0.11, 0.36);
	glutSolidSphere(0.003, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.26, 0.11, 0.34);
	glutSolidSphere(0.003, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.5, 0);
	glTranslated(0.26, 0.105, 0.35);
	glRotated(90.0, 0, 1, 0);
	glutSolidCone(0.005, 0.02, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.1, 0, 0);
	glTranslated(0.25, 0.08, 0.32);
	glRotated(60.0, 0, 0, 1);
	glRotated(-70.0, 1, 0, 0);
	glRotated(smSwing, 1, 0, 1);
	glScaled(0.002, 0.05, 0.005);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.1, 0, 0);
	glTranslated(0.25, 0.08, 0.39);
	glRotated(40.0, 0, 0, 1);
	glRotated(80.0, 1, 0, 0);
	glRotated(smSwing, 1, 0, 1);
	glScaled(0.002, 0.05, 0.005);
	glutSolidCube(1.0);
	glPopMatrix();

}

void drawTree() {

	//tree
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0.15, woodY, 0.35);
	glScaled(sc, sc, sc);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.1, 0.4, 15, 15);
	glPopMatrix();

	//wood
	glPushMatrix();
	glColor3f(0.1, 0, 0);
	glTranslated(0.15, 0.015, 0.35);
	glScaled(0.5, 1, 0.5);
	glutSolidCube(0.05);
	glPopMatrix();
	/*
	* glPushMatrix();
	glColor3f(0.1, 0, 0);
	glTranslated(0.75, 0.025, 0.35);
	glScaled(0.5, 1, 0.5);
	glScaled(0.4, 0.9, 0.4);
	glutSolidCube(0.05);
	glPopMatrix();
	*/
	//decorations
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.15, decY1, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(1*sc, 0.6*sc, 0.3*sc);
	glutSolidTorus(0.005, 0.02, 32, 32);
	glPopMatrix();

	/*glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.75, y, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(1, 0.6, 0.3);
	glScaled(0.4, 0.4, 0.4);
	glutSolidTorus(0.005, 0.02, 32, 32);
	glPopMatrix();*/


	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.15, decY2, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(2*sc, 2*sc, 1*sc);
	glutSolidTorus(0.005, 0.015, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.15, decY3, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(4*sc, 4*sc, 1*sc);
	glutSolidTorus(0.005, 0.015, 32, 32);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.9, 0.7, 0);
	glTranslated(0.15, ballY, 0.35);
	glScaled(sc, sc, sc);
	glutSolidSphere(0.01, 5, 15);
	glPopMatrix();

}


void drawTree2(float x , float y, float z) {

	//tree
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0.75, -0.15+y, 0.35);
	glScaled(0.4,0.4,0.4);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glutSolidCone(0.1, 0.4, 15, 15);
	glPopMatrix();
	//wood
	glPushMatrix();
	glColor3f(0.1, 0, 0);
	glTranslated(0.75, 0.025, 0.35);
	glScaled(0.5, 1, 0.5);
	glScaled(0.4, 0.9, 0.4);
	glutSolidCube(0.05);
	glPopMatrix();
	//decorations
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.75, y, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(1, 0.6, 0.3);
	glScaled(0.4, 0.4, 0.4);
	glutSolidTorus(0.005, 0.02, 32, 32);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.75, 0.15, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(2, 2, 1);
	glScaled(0.4, 0.4, 0.4);
	glutSolidTorus(0.005, 0.015, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.75, 0.1, 0.35);
	glRotated(90.0, 1, 0, 0);
	glScaled(4, 4, 1);
	glScaled(0.4, 0.4, 0.4);
	glutSolidTorus(0.005, 0.015, 32, 32);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.9, 0.7, 0);
	glTranslated(0.75, 0.22, 0.35);
	
	glutSolidSphere(0.005, 5, 15);
	glPopMatrix();


}

void drawHouse(float x, float y, float z) {

	glPushMatrix();
	glTranslatef(-0.1f, 0.2f, 0.4f);
	//ROOF PYRAMID
	//glRotatef(degree, 1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.1f, 0.2f, 0.2f);
	glVertex3f(0.35f+x, 0.35f+y, 0.35f+z);
	glVertex3f(0.45f+x, 0.25f+y, 0.30f+z);
	glVertex3f(0.45f+x, 0.25f+y, 0.40f+z);

	//*******************************
	glColor3f(0.1f, 0.2f, 0.1f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.40f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.40f + z);


	//*******************************
	glColor3f(0.4f, 0.35f, 0.3f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.40f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.30f + z);

	//*******************************
	glColor3f(0.45f, 0.9f, 0.3f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.30f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.30f + z);
	glEnd();
	glPopMatrix();

	//2nd layer
	//roof
	glPushMatrix();
	glColor3f(0.2, 0.4, 0);
	glTranslated(0.25, 0.3, 0.75);
	glScaled(0.3, 0.02, 0.3);
	glutSolidCube(1);
	glPopMatrix();


	//BLOCK
	//1st floor
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.0);
	glTranslated(0.25, 0.4, 0.75);
	glScaled(0.1, 0.1, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.25, 0.4, 0.75);
	glScaled(0.1, 0.1, 0.1);
	glutWireCube(1.001);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.2 , 0.1 , 0.8);
	glTranslated(0.25, 0.16, 0.85);
	glRotated(90,0,1,0);
	glScaled(0.02, 0.45, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();




	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.25, 0.16, 0.86);
	glRotated(90, 0, 1, 0);
	glScaled(0.01, 0.45, 0.01);
	glutSolidCube(0.3);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.205, 0.16, 0.86);
	glRotated(90, 0, 1, 0);
	glScaled(0.03, 0.45, 0.02);
	glutSolidCube(0.3);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.25, 0.1, 0.86);
	glRotated(90, 0, 0, 1);
	glScaled(0.04, 0.3, 0.03);
	glutSolidCube(0.3);
	glPopMatrix();


	

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.25, 0.16, 0.86);
	glRotated(90, 0, 0, 1);
	glScaled(0.007, 0.32, 0.01);
	glutSolidCube(0.3);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.294, 0.16, 0.85);
	glRotated(90, 0, 1, 0);
	glScaled(0.04, 0.46, 0.02);
	glutSolidCube(0.3);
	glPopMatrix();




	//Ground floor
	glPushMatrix();
	glColor3f(0.3, 0.4, 0.1);
	glTranslated(0.25, 0.15, 0.75);
	//glRotated(winangle, winXaxis, winYaxis, winZaxis);
	glScaled(0.15, 0.4, 0.15);
	glutSolidCube(1);
	glPopMatrix();


	

	//beams
	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.39, 0.16, 0.85);
	glScaled(0.05, 0.95, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();

	//BEAM
	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.39, 0.16, 0.65);
	glScaled(0.05, 0.95, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();

	//BRAM
	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.14, 0.16, 0.85);
	glScaled(0.05, 0.95, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();



	//window 
	glPushMatrix();
	glColor3f(0.2, 0.2, 0.2);
	glTranslated(0.324, 0.17, 0.745);
	glScaled(0.02, 0.45, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.1, 0.8);
	glTranslated(0.325, 0.17, 0.745+openWindow);
	glRotated(winangle, winXaxis, winYaxis, winZaxis);
	glScaled(0.02, 0.45, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.2, 0.1, 0.8);
	glTranslated(0.325, 0.17, 0.745+openWindow);
	glRotated(winangle, winXaxis, winYaxis, winZaxis);
	glScaled(0.02, 0.45, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.1, 0.8);
	glTranslated(0.325, 0.17, 0.745-openWindow);
	glRotated(winangle, winXaxis, winYaxis, winZaxis);
	glScaled(0.02, 0.45, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();


	//window frame.
	//THIS

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.33, 0.17, 0.745+openWindow);
	glRotated(winangle, winXaxis, winYaxis, winZaxis);
	//glRotated(90, 0, 1, 0);
	glScaled(0.01, 0.005, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.33, 0.17, 0.745-openWindow);
	glRotated(winangle, winXaxis, winYaxis, winZaxis);
	//glRotated(90, 0, 1, 0);
	glScaled(0.01, 0.005, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.325, 0.24, 0.76);
	//glRotated(winangle, winXaxis, winYaxis, winZaxis);
	glScaled(0.04, 0.06, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();



	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.325, 0.11, 0.745);
	//glRotated(winangle, winXaxis, winYaxis, winZaxis);
	//glRotated(90, 0, 1, 0);
	glScaled(0.04, 0.06, 0.3);
	glutSolidCube(0.3);
	glPopMatrix();



	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.325, 0.17, 0.74);
	glRotated(90, 1, 0, 0);
	glScaled(0.04, 0.02, 0.4);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.325, 0.17, 0.79);
	glRotated(90, 1, 0, 0);
	glScaled(0.04, 0.02, 0.5);
	glutSolidCube(0.3);
	glPopMatrix();
	//SIDE WINOW RIGHT FRAME
	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.325, 0.17, 0.7);
	glRotated(90, 1, 0, 0);
	glScaled(0.04, 0.02, 0.48);
	glutSolidCube(0.3);
	glPopMatrix();



	DrawCircle(0.25, 0.4, 0.81, 0.03, 30, 0.1, 0.3, 1);


	glPushMatrix();
	glColor3f(0.3, 0.2, 0);
	glTranslated(0.25, 0.23, 0.86);
	glRotated(90, 0, 0, 1);
	glScaled(0.04, 0.32, 0.03);
	glutSolidCube(0.3);
	glPopMatrix();




}

void drawHouseTop(float x, float y,float z) {

	glPushMatrix();
	glTranslatef(-0.1f, 0.2f, 0.4f);
	//ROOF PYRAMID
	//glRotatef(degree, 1.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.1f, 0.0f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.30f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.40f + z);

	//*******************************
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.40f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.40f + z);


	//*******************************
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.40f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.30f + z);

	//*******************************
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.35f + x, 0.35f + y, 0.35f + z);
	glVertex3f(0.25f + x, 0.25f + y, 0.30f + z);
	glVertex3f(0.45f + x, 0.25f + y, 0.30f + z);
	glEnd();
	glPopMatrix();

}


void drawHouse2(float x, float z) {
	//drawHouseTop(0,0,0.2);

	drawHouseTop(-0.05 +x,-0.1,-0.55+ z);

	glPushMatrix();
	glColor3f(1.0, 0.0, 0);
	glTranslated(0.2+x, 0.25, 0.2+z);
	glScaled(0.1, 0.02, 0.1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0);
	glTranslated(0.2+x, 0.3, 0.2+z);
	glScaled(0.05, 0.1, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0);
	glTranslated(0.2+x, 0.15, 0.2+z);
	glScaled(0.13, 0.02, 0.13);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0);
	glTranslated(0.2+x, 0.16, 0.2+z);
	glScaled(0.05, 0.3, 0.05);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1.0, 0.0, 0);
	glTranslated(0.2+x, 0.0, 0.2+z);
	glScaled(0.15, 0.02, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	

}
void drawTori() {

	//left anchor
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.47, 0.15, 0.09);
	glScaled(0.05, 0.7, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();
	//left base
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.47, 0.03, 0.09);
	glScaled(0.05, 0.1, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();

	//right anchor 
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.58, 0.15, 0.09);
	glScaled(0.05, 0.7, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();
	//right base
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.58, 0.03, 0.09);
	glScaled(0.05, 0.1, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();

	//Trapazoid


	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.525, 0.2, 0.09);
	glRotated(90.0, 0, 0, 1);
	glScaled(0.05, 0.6, 0.05);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.525, 0.26, 0.09);
	glRotated(90.0, 0, 0, 1);
	glScaled(0.07, 0.6, 0.07);
	glutSolidCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0.525, 0.22, 0.09);
	//glRotated(90.0, 0, 0, 1);
	glScaled(1.05, 2, 0.06);
	glutSolidCube(0.03);
	glPopMatrix();

	



}

void drawLantern1(float x, float y, float z) {
	//Square Lantern
		//Bulb
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.4);
	glTranslated(0.05+x, 0.2, 0.013 + z);
	glRotated(lanternangle, 1, 0, 0);
	glutSolidSphere(0.01, 100, 100);
	glPopMatrix();
	//FRAME
	int i = 0;
	float scale = 2;
	while (i < 8) {
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslated(0.05+x, 0.2, 0.013+z);
		glRotated(lanternangle, 1, 0, 0);
		glScaled(1.0, scale, 0.8);
		glutWireCube(0.03);
		glPopMatrix();
		scale = scale - 0.25;
		i = i + 1;
	}
	//Wire
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.05+x, 0.25, 0.013 + z);
	glScaled(0.05, 2.5, 0.05);
	glutSolidCube(0.02);
	glPopMatrix();
}
void drawLantern2(float x,float y, float z) {
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(x, 0.2, 0.013 + z);
	glRotated(lanternangle,1,0,0);
   // glRotated(-45,1,0,0);
	glScaled(0.7, 2.5, 0.7);
	glutSolidCube(0.03);
	glPopMatrix();
	//FRAME
	//float i3 = 0.0;
	//Wire
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(x, 0.25,0.013 + z);
	glScaled(0.05, 2.5, 0.05);
	glutSolidCube(0.02);
	glPopMatrix();
	//JAPAN
	DrawCircle(x, 0.2, 0.024+z, 0.009, 30,1,0,0);
}
void drawPresent1() {
	if (!present1) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(0.45, 0.05, 0.5);
		glScaled(0.7, 2.5, 0.7);
		glutSolidCube(0.03);
		glPopMatrix();

		DrawCircle(0.45, 0.05, 0.512, 0.009, 30, 1, 0, 0);

	}
}
void drawPresent2() {
	if (!present2) {
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslated(0.1, 0.05, 0.9);
		glScaled(0.7, 2.5, 0.7);
		glutSolidCube(0.03);
		glPopMatrix();

		DrawCircle(0.1, 0.05, 0.912, 0.009, 30, 1, 0, 0);
	}
}
void drawPresent3() {
	if (!present3) {
		glPushMatrix();
		glColor3f(1, 1.0, 1.0);
		glTranslated(0.9, 0.05, 0.05);
		glScaled(0.7, 2.5, 0.7);
		glutSolidCube(0.03);
		glPopMatrix();

	}
}

void drawPika() {


	//EARS

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX - conePosition, 0.06, keyZ+conePosition2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.008, 0.08, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX + conePosition, 0.06, keyZ-conePosition2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.008, 0.08, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX - conePosition, 0.11, keyZ + conePosition2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.004, 0.03, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX + conePosition, 0.11, keyZ - conePosition2);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(0.004, 0.03, 15, 15);
	glPopMatrix();

	//TAIL
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX, 0.05, keyZ + direction);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.2, 0.2, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX + tailPart1, 0.07, keyZ + direction + tailPart2Z);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.3, 0.3, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX + tailPart1, 0.07, keyZ + direction + tailPart2Z);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.3, 0.3, 0.1);
	glutWireCube(0.1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX + tailPart2, 0.09, keyZ  + direction + tailPart1Z);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.4, 0.3, 0.1);
	glutSolidCube(0.1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX + tailPart2, 0.09, keyZ + direction + tailPart1Z);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.4, 0.3, 0.1);
	glutWireCube(0.1);
	glPopMatrix();


	//FACE AND EYES

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX, 0.08, keyZ);

	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();



	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslated(keyX, 0.05, keyZ);
	glScaled(1, 2, 1);
	glutSolidSphere(0.02, 15, 15);
	glPopMatrix();



	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX - zDiff + turnRight, 0.09, keyZ + eyedir +xDiff);
	glutSolidSphere(0.005, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX + zDiff + turnRight, 0.09, keyZ + eyedir - xDiff);
	glutSolidSphere(0.005, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(keyX - zDiff + turnCheecksRight, 0.08, keyZ + eyedir + xDiff);
	glRotated(angle, xaxis, yaxis, zaxis);
	glutSolidSphere(0.005, 15, 15);
	glPopMatrix();
	//BODY

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(keyX + zDiff + turnCheecksRight, 0.08, keyZ + eyedir - xDiff);
	glutSolidSphere(0.005, 15, 15);
	glPopMatrix();

	//MOUTH

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(keyX + mouthPos, 0.08, keyZ + mouthdir);
	glRotated(angle, xaxis, yaxis, zaxis);
	glScaled(0.05, 0.002, 0.02);
	glutSolidCube(0.2);
	glPopMatrix();

}
void drawLanternCable(float startPoint) {

	drawLantern2(startPoint , 0.1, 0.08);
	drawLantern1(startPoint+0.02, 0.01, 0.08);
	drawLantern2(startPoint + 0.13, 0.1, 0.08);
	drawLantern2(startPoint + 0.18, 0.1, 0.08);
	drawLantern1(startPoint + 0.18, 0.01, 0.08);
	drawLantern1(startPoint + 0.23, 0.01, 0.08);
	drawLantern2(startPoint + 0.33, 0.1, 0.08);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(startPoint + 0.22,0.27,0.092);
	glScaled(0.45, 0.005, 0.0008);
	glutSolidCube(1);
	glPopMatrix();
	/*drawLantern2(0.08, 0.1, 0.08);
	drawLantern1(0.1, 0.01, 0.08);
	drawLantern2(0.21, 0.1, 0.08);
	drawLantern2(0.26, 0.1, 0.08);
	drawLantern1(0.26, 0.01, 0.08);
	drawLantern1(0.31, 0.01, 0.08);
	drawLantern2(0.41, 0.1, 0.08);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0.3,0.164,0.092);
	glScaled(0.45, 0.005, 0.0008);
	glutSolidCube(1);
	glPopMatrix();*/



}
void Display() {
	setupLights();
	setupCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawLanternCable(0.08);
	drawLanternCable(0.62);
	drawTori();
	drawSnowman();
	drawTree();
	drawHouse(0,0,0);
	drawTree2(0.6,0.2,-0.1);
	drawHouse2(0.5,0.5);
	drawGround(0.02);
	drawFence();
	drawFence2();
	drawFence3();
	drawPika();

	if (!present1) {

		drawPresent1();
	}

	if (!present2) {

		drawPresent2();
	}
	if (!present3) {

		drawPresent3();
	}

	if (presentCounter>2 & win) {

		drawWin();
	
	}

	if (lose & !win) {
		drawLose();
	
	}
	if (!lose & !win) {
		drawTimer();
	}
	

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.6);
	glTranslated(0.5, 0.0, -0.01);
	glScaled(1.0, 3, 0.02);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glColor3f(0.0, 0.0, 0.6);
	glTranslated(-0.01, 0.0, -0.01);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(2.0, 3, 0.02);
	glutSolidCube(1);
	glPopMatrix();



	glPushMatrix();
	glColor3f(0.0, 0.0, 0.6);
	glTranslated(1.03, 0.2, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glScaled(2.0, 3, 0.02);
	glutSolidCube(1);
	glPopMatrix();



	glFlush();
}

void time(int val)//timer animation function, allows the user to pass an integer valu to the timer function.
{

	if (int(timeElapsed)  > 0 && !win && !lose) {
		timeElapsed -= 0.01;
		if (int(timeElapsed) % 2 == 0) {
			red = 1.0;
			green = 0.0;
			blue = 0.0;
			red2 = 1.0;
			green2 = 1.0;
			blue2 = 1.0;
		}
		else {
			red2 = 1.0;
			green2 = 0.0;
			blue2 = 0.0;
			red = 1.0;
			green = 1.0;
			blue = 1.0;
		}
	}
	else {
		lose = true;
	}
	
	if (tpressed) {
		lanternangle += countg;
		if (lanternangle >= 20) {
			lannternSwing = true;
		}
		if (lanternangle <= -10) {
			lannternSwing = false;
		}
		if (lanternangle < 20 && !lannternSwing) {
			countg = 0.1;
		}
		else if (lanternangle > 20 && lannternSwing) {
			countg = -0.1;
		}
	}
	if (ypressed) {
		smSwing += smcount;
		if (smSwing >= 15) {
			smbool = true;
		}
		if (smSwing <= -15) {
			smbool = false;
		}

		if (smSwing < 15 && !smbool) {
			smcount = 0.1;
		}
		else if (smSwing > 15 && smbool) {
			smcount = -0.1;
		}
	}


	
	glutPostRedisplay();						// redraw 		
	glutTimerFunc(10, time, 0);					//recall the time function after 1000 ms and pass a zero value as an input to the time func.
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1368, 768);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(key);
	glutTimerFunc(0, time, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
