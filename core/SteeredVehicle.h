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

#ifndef _SteeredVehicle_h
#define _SteeredVehicle_h

#include "Vehicle.h"
#include "ofMath.h"


class SteeredVehicle : public Vehicle {
	
private:
	
	float wanderAngle1;
	float wanderAngle2;
	
	
protected:
	
	ofVec3f steeringForce;
	ofVec3f getOffset();
	ofVec3f getRandVec();
	
	
public:
	
	float maxForce;
	float wanderDistance;
	float wanderRadius;
	float wanderRange;
	float inSightDist;
	float tooCloseDist;
	float pathThreshold;
	bool pathLoop;
	int pathIndex;
	
	
	SteeredVehicle(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : Vehicle(_x, _y, _z)
	{
		maxForce = 1.0f;
		wanderAngle1 = ofRandom(0.0f, 360.0f);
		wanderAngle2 = ofRandom(0.0f, 360.0f);
		wanderDistance = 10.0f;
		wanderRadius = 5.0f;
		wanderRange = 10.0f;
		pathIndex = 0;
		pathThreshold = 20.0f;
		pathLoop = false;
		inSightDist = 120.0f;
		tooCloseDist = 20.0f;
	}
	
	
	void addForce(const ofVec3f vec);
	void update();
	void seek(const ofVec3f& target);
	void flee(const ofVec3f& target);
	void arrive(const ofVec3f& target);
	void pursue(const Vehicle& target);
	void evade(const Vehicle& target);
	void wander();
	void patrol(const vector<ofVec3f> paths);
	//void avoid();
	void randomWalk();
	bool inSight(const ofVec3f& target);
	bool tooClose(const ofVec3f& target);
	
	
	template<typename Type> void flock(vector<Type>& vehicles)
	{
		ofVec3f averageVelocity;
		ofVec3f averagePosition;
		int inSightCnt = 0;
		
		averageVelocity.set(velocity);
		
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getId() == getId()) continue;
			if (!inSight(vehicles[i].position)) continue;
			
			averageVelocity += vehicles[i].velocity;
			averagePosition += vehicles[i].position;
			inSightCnt++;
			
			if (tooClose(vehicles[i].position))
			{
				flee(vehicles[i].position);
			}
		}
		
		if (inSightCnt > 0)
		{
			averagePosition *= 1.0f / inSightCnt;
			seek(averagePosition);
			averageVelocity *= 1.0f / inSightCnt;
			steeringForce += averageVelocity - velocity;
		}
	}
};

#endif
