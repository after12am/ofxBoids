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

#include "SteeredVehicle.h"
#include <iostream>



void SteeredVehicle::addForce(const ofVec3f vec)
{
	steeringForce += vec;
}

void SteeredVehicle::update()
{
	steeringForce.limit(maxForce);
	steeringForce *= (float)1 / mass;
	velocity += steeringForce;
	Vehicle::update();
	steeringForce.set(0, 0, 0);
}

void SteeredVehicle::seek(const ofVec3f& target)
{
	ofVec3f desiredVelocity;
	desiredVelocity.set(target);
	desiredVelocity -= position;
	desiredVelocity.normalize();
	desiredVelocity *= maxSpeed;
	steeringForce += (desiredVelocity - velocity);
}

/*
void SteeredVehicle::seek(const ofVec3f& target, const float force)
{
	ofVec3f desiredVelocity;
	desiredVelocity.set(target);
	desiredVelocity -= position;
	desiredVelocity.normalize();
	desiredVelocity *= force;
	steeringForce += (desiredVelocity - velocity);
}*/

void SteeredVehicle::flee(const ofVec3f& target)
{
	ofVec3f desiredVelocity;
	desiredVelocity.set(target);
	desiredVelocity -= position;
	
	// if target position and this vehicle position is the same,
	// vehicle runs away to random vector.
	if (desiredVelocity.length() == 0) {
		desiredVelocity = getRandVec();
	}
	
	desiredVelocity.normalize();
	desiredVelocity *= maxSpeed;
	steeringForce -= (desiredVelocity - velocity);
}

void SteeredVehicle::arrive(const ofVec3f& target)
{
	float arrivalThreshold = maxSpeed * 10;
	
	ofVec3f desiredVelocity;
	desiredVelocity.set(target);
	desiredVelocity -= position;
	desiredVelocity.normalize();
	
	float dist = position.distance(target);
	if (dist > arrivalThreshold) desiredVelocity *= maxSpeed;
	else desiredVelocity *= (float)maxSpeed * dist / arrivalThreshold;
	
	steeringForce += desiredVelocity - velocity;
}

void SteeredVehicle::pursue(const Vehicle& target)
{
	float lookAheadTime = (float)position.distance(target.position) / maxSpeed;
	
	ofVec3f targetVelocity;
	targetVelocity.set(target.velocity);
	targetVelocity *= lookAheadTime;
	
	ofVec3f predictedTarget;
	predictedTarget.set(target.position);
	predictedTarget += targetVelocity;
	
	seek(predictedTarget);
}

void SteeredVehicle::evade(const Vehicle& target)
{
	float lookAheadTime = (float)position.distance(target.position) / maxSpeed;
	
	ofVec3f targetVelocity;
	targetVelocity.set(target.velocity);
	targetVelocity *= lookAheadTime;
	
	ofVec3f predictedTarget;
	predictedTarget.set(target.position);
	predictedTarget -= targetVelocity;
	
	flee(predictedTarget);
}

ofVec3f SteeredVehicle::getOffset()
{
	
	float a1 = (float)(wanderAngle1 * PI / 180);
	float a2 = (float)(wanderAngle2 * PI / 180);
	
	ofVec3f offset;
	offset.x = (float)(wanderRadius * sin(a1) * cos(a2));
	offset.y = (float)(wanderRadius * sin(a1) * sin(a2));
	offset.z = (float)(wanderRadius * cos(a1));
	//offset *= wanderRadius;
	
	wanderAngle1 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
	wanderAngle2 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
	
	return offset;
}

void SteeredVehicle::wander()
{
	ofVec3f center;
	ofVec3f offset;
	
	center.set(velocity);
	center.normalize();
	center *= wanderDistance;
	offset = getOffset();
	
	steeringForce += center + offset;
}

/*
void SteeredVehicle::wander(const float force)
{
	ofVec3f center;
	ofVec3f offset;
	
	center.set(velocity);
	center.normalize();
	center *= wanderDistance;
	offset = getOffset(wanderRadius, wanderAngle1, wanderAngle2);
	
	wanderAngle1 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
	wanderAngle2 += (float)(ofRandom(0, wanderRange) - (float)wanderRange * .5f);
	
	ofVec3f desiredVelocity = center + offset;
	desiredVelocity.normalize();
	desiredVelocity *= force;
	steeringForce += desiredVelocity;
}*/

void SteeredVehicle::patrol(const vector<ofVec3f> paths)
{
	bool last = pathIndex >= paths.size() - 1;
	
	if (position.distance(paths[pathIndex]) < pathThreshold)
	{
		if (last && pathLoop) pathIndex = 0;
		else if (!last) pathIndex++;
	}
	
	if (last && !pathLoop) arrive(paths[pathIndex]);
	else seek(paths[pathIndex]);
}

/*
void SteeredVehicle::avoid()
{
	
}*/

void SteeredVehicle::randomWalk()
{
	float a1 = (float)(ofRandom(0, 360) * PI / 180);
	float a2 = (float)(ofRandomuf() * 2 * PI);
	
	ofVec3f desiredVelocity;
	desiredVelocity.x = (float)(sin(a1) * cos(a2));
	desiredVelocity.y = (float)(sin(a1) * sin(a2));
	desiredVelocity.z = (float)(cos(a1));
	desiredVelocity.normalize();
	desiredVelocity *= maxSpeed;
	steeringForce += (desiredVelocity - velocity);
}

bool SteeredVehicle::inSight(const ofVec3f& target)
{
	if (position.distance(target) > inSightDist) return false;
	
	ofVec3f heading;
	heading.set(velocity);
	heading.normalize();
	
	ofVec3f difference;
	difference.set(target);
	difference -= position;
	
	if (difference.dot(heading) < 0) return false;
	return true;
}

bool SteeredVehicle::tooClose(const ofVec3f& target)
{
	return position.distance(target) < tooCloseDist;
}

ofVec3f SteeredVehicle::getRandVec()
{
	ofVec3f vec;
	
	float a1 = (float)(ofRandom(0, 360) * PI / 180);
	float a2 = (float)(ofRandomuf() * 2 * PI);
	
	vec.x = (float)(sin(a1) * cos(a2));
	vec.y = (float)(sin(a1) * sin(a2));
	vec.z = (float)(cos(a1));
	
	return vec;
}
