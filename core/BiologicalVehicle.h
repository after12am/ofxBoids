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

#ifndef _BiologicalVehicle_h
#define _BiologicalVehicle_h

#include "SteeredVehicle.h"


class BiologicalVehicle : public SteeredVehicle {
	
protected:
	
	float age;
	
public:
	
	float lifeSpan;
	float remainingLifePer;	// range from 1.0 (birth) to 0.0 (death)
	
	
	BiologicalVehicle(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : SteeredVehicle(_x, _y, _z) {
		
		age = 0.0;
		lifeSpan = 1.0;
		remainingLifePer = 1.0;
	}
	
	void aging(float inc);
	bool isDead();
};


#endif
