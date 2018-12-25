#ifndef _DEMO_BASE_H
#define _DEMO_BASE_H

//! Demo base class.
class DemoBase
{
public:
	
	virtual void init() = 0;
	virtual void deinit() = 0;
	virtual void draw(const Matrix& viewMatrix) = 0;
	virtual void stateSwitch(double x, double y) = 0;
	virtual void pauseFunction() = 0;
	virtual void frameRateControl() = 0;
	virtual void clearMap() = 0;
	virtual void mousePositionDetector(float posX, float posY) = 0;
	virtual void buttonClick() = 0;
	virtual void mouseClick() = 0;
	virtual void mouseRelease() = 0;
};

#endif
