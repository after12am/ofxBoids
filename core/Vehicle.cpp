//
//  Vehicle.cpp
//  ofxBoids
//
//  Created by Okami Satoshi on 12/02/29.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

#include "Vehicle.h"
#include <iostream>

// initialize instance identifier
int Vehicle::number = 0;


void Vehicle::update()
{
	velocity.limit(maxSpeed);
	position += velocity;
	
	trails.push_back(position);
	if (trails.size() > maxTrailSize) trails.erase(trails.begin());
}

void Vehicle::bounce(int w, int h, int d)
{
	if (position.x > w * .5f)
	{
		position.x = w * .5f;
		velocity.x *= -1;
	}
	else if (position.x < - w * .5f)
	{
		position.x = - w * .5f;
		velocity.x *= -1;
	}
	
	if (position.y > h * .5f)
	{
		position.y = h * .5f;
		velocity.y *= -1;
	}
	else if (position.y < - h * .5f)
	{
		position.y = - h * .5f;
		velocity.y *= -1;
	}
	
	if (position.z > d * .5f)
	{
		position.z = d * .5f;
		velocity.z *= -1;
	}
	else if (position.z < - d * .5f)
	{
		position.z = - d * .5f;
		velocity.z *= -1;
	}
}

void Vehicle::wrap(int w, int h, int d)
{
	if (position.x > w * .5f)
	{
		position.x = - w * .5f;
	}
	else if (position.x < - w * .5f)
	{
		position.x = w * .5f;
	}
	
	if (position.y > h * .5f)
	{
		position.y = - h * .5f;
	}
	else if (position.y < - h * .5f)
	{
		position.y = h * .5f;
	}
	
	if (position.z > d * .5f)
	{
		position.z = - d * .5f;
	}
	else if (position.z < - d * .5f)
	{
		position.z = d * .5f;
	}
}
