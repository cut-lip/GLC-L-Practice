#include "GL/glut.h"
#include "Canvas.h"
#include "myGLlib.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

Point2 CP = Point2(0, 0);
float CD = 0.0;

// Draw a line from CP to the new vertex
void lineTo(float x, float y)
{
	glBegin(GL_LINES);
	glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
	glVertex2f((GLfloat)x, (GLfloat)y);
	glEnd();

	CP.set(x, y);	// Update the CP
	glFlush();		// Flush the buffer
}

void lineTo(Point2 p)
{
	glBegin(GL_LINES);
	glVertex2f((GLfloat)CP.getX(), (GLfloat)CP.getY());
	glVertex2f((GLfloat)p.getX(), (GLfloat)p.getY());
	glEnd();

	CP.set(p.getX(), p.getY());	// Update the CP
	glFlush();		// Flush the buffer
}

// Update the CP
void moveTo(float x, float y)
{
	CP.set(x, y);
}

void moveTo(Point2 p)
{
	CP.set(p.getX(), p.getY());
}

// TURTLE GRAPHICS
// turn the turtle to given angle
void turnTo(float angle)
{
	// Convert radians to degrees
	CD = angle * (180.0 / 3.141592653589793238463);
}

// turn the turtle given number of degrees
void turn(float angle)
{
	// Convert radians to degrees
	CD += angle * (180.0 / 3.141592653589793238463);
}

// move turtle forward in a straight line from CP
void forward(float dist, bool isVisible)
{
	const float radPerDeg = 0.017453393;
	float x = CP.getX() + dist * cos(radPerDeg * CD);
	float y = CP.getY() + dist * sin(radPerDeg * CD);

	// Move CP
	if (isVisible)
		lineTo(x, y);
	else
		moveTo(x, y);
}

void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	// Draw middle border between classes
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(4.0);

	glBegin(GL_LINES);
	glVertex2f(0, SCREEN_HEIGHT / 2);
	glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	glEnd();
	*/

	// FIRST ATTEMPT: Just graph one point

	int scaleFactor = 10;

	std::vector<float>  data{ 5, 1, 1, 1, 2, 1, 3, 1, 1 };
	std::vector<float> normalizedData;
	for (std::vector<float>::iterator iter = data.begin(); iter < data.end(); iter++)
	{
		normalizedData.push_back(*iter / scaleFactor);
	}

	std::vector<float> angles;
	
	// Compute angles for GLC-L visualization
	for (float i : normalizedData)
	{
		angles.push_back(acos(i));
	}

 	CP = Point2(SCREEN_HEIGHT / 2 + 20, 20);

	std::vector<float>::iterator dataIt = data.begin();
	std::vector<float>::iterator anglesIt = angles.begin();

	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 1.0);
	for (dataIt; dataIt < data.end(); dataIt++, anglesIt++)
	{
		turnTo(*anglesIt);
		glPushMatrix();

		// Since everything is being transformed through the modelview matrix,
		// I want to scale it up to a reasonable scale?
		// OKAY:: !! Problem is, you have to set scaled values to the viewport coordinates. how??
		// (is z zero or one?)
		glScalef(1.0, 3.0, 1.0);
		forward(*dataIt, true);
		glPopMatrix();

		/*
		glBegin(GL_LINES);
		glVertex2d(*dataIt, *anglesIt);
		glVertex2d();
		*/
	}

	glFlush();

	//glBegin()
	/*
	// Read data file
	std::string line = "";

	std::ifstream myFile("breast-cancer-wisconsin.DATA");

	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			// Split string into a vector
			std::stringstream ss(line);
			std::istream_iterator<std::string> begin(ss);
			std::istream_iterator<std::string> end;
			std::vector<int> data(begin, end);

			// Can we use glScaled() to scale the attributes?
			// Remove label from data
			data.erase(data.begin());

			// Create temp vector for single point
			// WHY??????
			std::vector<int> temp;
			for (int i = 0; i < 10; i++) {
				temp.push_back(*data.begin());
				data.erase(data.begin());
			}

			// Graph the data point
			glBegin(GL_LINE_STRIP);
			glVertex2i(40, (150 + 23 * temp[0]));
			glVertex2i(90, (150 + 23 * temp[1]));
			glVertex2i(140, (150 + 23 * temp[2]));
			glVertex2i(190, (150 + 23 * temp[3]));
			glVertex2i(240, (150 + 23 * temp[4]));
			glVertex2i(290, (150 + 23 * temp[5]));
			glVertex2i(340, (150 + 23 * temp[6]));
			glVertex2i(390, (150 + 23 * temp[7]));
			glVertex2i(440, (150 + 23 * temp[8]));
			glVertex2i(490, (150 + 23 * temp[9]));
			glEnd();
		}
	}
	*/


	glFlush();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GLC-L");
	glutDisplayFunc(myDisplay);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glutMainLoop();
}