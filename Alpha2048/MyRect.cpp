#include "pch.h"
#include "MyRect.h"


MyRect::MyRect(UINT x1, UINT y1, UINT x2, UINT y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	uValue = 0;
}

MyRect::~MyRect()
{

}