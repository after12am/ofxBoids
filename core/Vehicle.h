//
//  Vehicle.h
//  ofxBoids
//
//  Created by Okami Satoshi on 12/02/29.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

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
	}
	
	int getId() { return id; }
	
	void update();
	void bounce(int w, int h, int d);
	void wrap(int w, int h, int d);
};

#endif
