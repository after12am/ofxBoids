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
	
	// parameter related to patrol
	float pathThreshold;
	bool pathLoop;
	int pathIndex;
	
	// parameter related to flock
	float inSightDist;
	float tooCloseDist;
	
	// parameter related to keep
	float keepDistance;
	
	
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
	
	// basic behavior
	void update();
	void seek(const ofVec3f& target);
	void flee(const ofVec3f& target);
	void arrive(const ofVec3f& target);
	void pursue(const Vehicle& target);
	void evade(const Vehicle& target);
	void wander();
	void patrol(const vector<ofVec3f> paths);
	void avoid();
	
	template<typename Type> void keep(vector<Type>& vehicles);
	template<typename Type> void flock(vector<Type>& vehicles);
	
	bool inSight(const Vehicle& vehicle);
	bool tooClose(const Vehicle& target);
	bool tooClose(const ofVec3f& position);
};

#endif
