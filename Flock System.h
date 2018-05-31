#pragma once
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "MyMath.h"

class Bird;

using namespace sf;
using namespace std;

class Flock
{
public:
	Flock();
	vector<Bird> birdList;
	void draw();
	void update(float dt);
	bool isMousePressed = false;
	float toggleAlingment=1;
	float toggleSeparation =1;
	float toggleCohesion = 1;
	Text toggleStatus;
	Font font;
	bool isKeyPressed= false;

private:
	Vector2f target;

};

class Bird
{
public:
	Bird(Vector2f pos, Flock* f);
	Flock * flock;

	void Draw();
	void update(float dt);
	void ComputeSeparation();
	void ComputeAlignment();
	void ComputeCohesion();


private:

	sf::ConvexShape birdShape;
	Vector2f position = Vector2f(0,0);
	Vector2f velocity= Vector2f(0, 0);
	Vector2f acceleration= Vector2f(0, 0);
	float maxForce = 350;
	float closenessRadius = 50;
	float maxspeed = 400;
};

