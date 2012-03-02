/********************************************************************************** 
 
 Copyright (C) 2012 satoshi okami
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef _Vehicle_h
#define _Vehicle_h

#include "ofVec3f.h"


class Vehicle {

private:
	
	static int number;
	
	// instance identifier
	int id;
	
	
public:
	
	ofVec3f position;
	ofVec3f velocity;
	vector<ofVec3f> trails;
	
	float mass;
	float maxSpeed;
	float maxTrailSize;
	
	Vehicle(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		id = number++;
		mass = 1.0f;
		maxSpeed = 4.0f;
		maxTrailSize = 10;
		position.set(ofVec3f(_x, _y, _z));
	}
	
	int getId() { return id; }
	
	void update();
	void bounce(int w, int h, int d);
	void wrap(int w, int h, int d);
};

#endif
