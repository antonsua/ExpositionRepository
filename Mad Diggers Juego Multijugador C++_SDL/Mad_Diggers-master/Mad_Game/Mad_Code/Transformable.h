//Mad_Diggers

#ifndef TRANSFORMABLE_H_
#define TRANSFORMABLE_H_

#include "Physical.h"
#include "Game.h"
#include "Vector2D.h"

class Transformable: public Physical
{
public:
	Transformable();
	virtual ~Transformable();

	void resizeToScale(Vector2D scale, Uint32 duration);
	void moveToPoint(Vector2D point, Uint32 duration);
	void moveSmoothToPoint(Vector2D point, Uint32 maxDuration = 2500);

	//static void moveWorldToPoint(Vector2D point, Uint32 duration); //maybe

	void cancelMovement();
	void calcelResizing();

	void setCloseEnough(double margin);
	void setMaxTime(Uint32 ms);

	bool isMoving();
	bool isResizing();

	//rewrite to apply scale
	virtual double getWidth() const;
	virtual double getHeight() const;
	void setScale(Vector2D scale) { scale_ = scale; };
	Vector2D getScale() { return scale_; };

protected:
	virtual void endMovement(bool timeOut) = 0; //called when a movement is finished
	virtual void endResizing() = 0;

	void update(Uint32 time);

	Vector2D scale_;
	void resize(Uint32 time);

	void move(Uint32 time);
	void moveSmooth(Uint32 time);
	void smoothMovement(Uint32 delta);

	void checkEndSimple();
	void checkEnd(bool checkTime);

private:
	bool move_, moveSmooth_, resize_;

	//holders
	Uint32 smoothTime_, smoothTotalTime_;
	Vector2D smoothPoint_, smoothOrigin_, smoothVel_;

	Uint32 resizeTime_;
	Vector2D resizeScale_, resiceOrigin_, resizeVel_;

	//movement
	const double thrust_ = 0.25, maxVel_ = 4, reductionFactor_ = 20;
	const double epsilon_ = 0.1; //to consider 0

	//detection
	double closeEnough_ = 15, resizeEnough_ = 0.05;
	const double minCloseEnough_ = 15;

	Uint32 maxTime_;
	const Uint32 minMaxTime_ = 50;
};

#endif /* TRANSFORMABLE_H_ */
