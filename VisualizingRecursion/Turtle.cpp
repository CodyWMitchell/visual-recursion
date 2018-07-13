#include "stdafx.h"
#include "Turtle.h"
#include <math.h>
using namespace std;

# define PI           3.14159265358979323846  /* pi */

Turtle::Turtle(HDC hdc)
{
	x = 0;
	y = 0;
	turtAngle = 0;
	penEnabled = true;
	// Sets turtle's graphics
	turtHdc = hdc;
	// Sets default drawing pen
	SelectObject(turtHdc, GetStockObject(DC_PEN));
}

Turtle::~Turtle()
{
}

void Turtle::forward(double distance) {
	double dx = cos(turtAngle*(PI*2.0) / 360.0) * distance;
	double dy = sin(turtAngle*(PI*2.0) / 360.0) * distance;
	MoveToEx(turtHdc, (int)x, (int)y, (LPPOINT)NULL);
	x += dx;
	y += dy;
	if (penEnabled) {
		LineTo(turtHdc, (int)x, (int)y);
	}
}

void Turtle::goTo(double xloc, double yloc) {
	if (!penEnabled) {
		MoveToEx(turtHdc, (int)xloc, (int)yloc, (LPPOINT)NULL);
		x = xloc;
		y = yloc;
	}
	else {
		x = xloc;
		y = yloc;
		LineTo(turtHdc, (int)x, (int)y);
	}
}

void Turtle::right(double angle) {
	turtAngle += angle;
}

void Turtle::left(double angle) {
	turtAngle -= angle;
}

void Turtle::setColor(int r, int g, int b) {
	SetDCPenColor(turtHdc, RGB(r, g, b));
}

void Turtle::penUp() {
	penEnabled = false;
}

void Turtle::penDown() {
	penEnabled = true;
}

// Enter functions to be used with turtle here
void drawSpiral(Turtle myTurtle, int lineLen) {
	// Compare with ActiveCode 2
	if (lineLen > 0) {
		myTurtle.forward(lineLen);
		myTurtle.right(90);
		drawSpiral(myTurtle, lineLen - 5);
	}
}

void tree(double branchLen, Turtle t) {
	//Compare with ActiveCode 1
	if (branchLen > 5) {
		t.forward(branchLen);
		t.right(20);
		tree(branchLen - 15, t);
		t.left(40);
		tree(branchLen - 15, t);
		t.right(20);
		t.forward(-branchLen);
	}
}

// Enter turtle commands here
void turtleDraw(HDC hdc) {
	Turtle t(hdc);
	t.penUp();
	t.goTo(250, 200);
	t.penDown();
	t.setColor(255, 100, 0);

	drawSpiral(t, 100);

	t.penUp();
	t.goTo(700, 350);
	t.penDown();
	t.setColor(0, 255, 100);

	t.left(90);
	tree(75, t);
}