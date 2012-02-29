//
//  SteeredVehicle.h
//  ofxBoids
//
//  Created by Okami Satoshi on 12/02/29.
//  Copyright (c) 2012 Okami Satoshi. All rights reserved.
//

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
	ofVec3f getOffset(const float r, const float angle1, const float angle2);
	ofVec3f getRandVec();
	
	
public:
	
	float maxForce;
	
	float wanderDistance;
	float wanderRadius;
	float wanderRange;
	
	float pathThreshold;
	bool pathLoop;
	int pathIndex;
	
	float inSightDist;
	float tooCloseDist;
	
	//float keepDistance;
	
	
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
		keepDistance = 120.0f;
	}
	
	//void addForce(const ofVec3f vec);
	
	
	void update();
	void seek(const ofVec3f& target);
	void flee(const ofVec3f& target);
	void arrive(const ofVec3f& target);
	void pursue(const Vehicle& target);
	void evade(const Vehicle& target);
	void wander();
	void patrol(const vector<ofVec3f> paths);
	void avoid();
	bool inSight(const ofVec3f& target);
	bool tooClose(const ofVec3f& target);
	
	/*
	 // 必要か？
	template<typename Type> void keep(vector<Type>& vehicles)
	{
		// keep distance from other vehicles
		// 縦横の交点にseekするように変えても
		
		ofVec3f averageVelocity;
		ofVec3f averagePosition;
		int inSightCnt = 0;
		
		for (int i = 0; i < vehicles.size(); i++)
		{
			if (vehicles[i].getId() == getId()) continue;
			if (!inSight(vehicles[i].position)) continue;
			averageVelocity += vehicles[i].velocity;
			averagePosition += vehicles[i].position;
			if (position.distance(vehicles[i].position) < keepDistance) flee(vehicles[i].position);
			inSightCnt++;
		}
		
		if (inSightCnt > 0)
		{
			averagePosition *= (float)1 / inSightCnt;
			flee(averagePosition);
			averageVelocity *= (float)1 / inSightCnt;
			steeringForce += averageVelocity - velocity;
		}
	}*/
	
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
			
			if (tooClose(vehicles[i].position)) flee(vehicles[i].position);
			inSightCnt++;
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
