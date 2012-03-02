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

#include "Vehicle.h"
#include <iostream>


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
