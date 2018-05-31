#include "Flock System.h";
#include "Global.h"
#include "MyMath.h"

using namespace sf;

Bird::Bird(Vector2f pos, Flock* f)
{
	position = pos;
	flock = f;
	birdShape.setPointCount(3);
	birdShape.setPoint(0, Vector2f(0,0));
	birdShape.setPoint(1, Vector2f(15, 5));
	birdShape.setPoint(2, Vector2f(0,10));


	//position = Vector2f(screenWidth / 2, screenHeight / 2);
	birdShape.setPosition(position);
	birdShape.setFillColor(Color::Green);
	printf("Positionx: %f\n", position.x);
}

void Bird::Draw()
{
	window.draw(birdShape);

}

void Bird::update(float dt)
{
	ComputeSeparation();
	ComputeAlignment();
	ComputeCohesion();
	velocity += acceleration *dt;
	position += velocity *dt;
	birdShape.setPosition (position);
	birdShape.setRotation(heading(velocity));
	acceleration = Vector2f(0, 0);

	if (position.x > screenWidth)
		position.x -= screenWidth;
	else if(position.x < 0)
		position.x += screenWidth;

	if (position.y > screenHeight)
		position.y -= screenHeight;
	else if (position.y < 0)
		position.y += screenHeight;

}

void Bird::ComputeSeparation()
{
	float count = 0;
	Vector2f desiredVel = Vector2f(0,0);
	for (int i = 0; i < flock->birdList.size(); i++)
	{
		Bird* currentBird = &flock->birdList[i];
		if (currentBird == this)
			continue;
		float d = magnitude(position - currentBird->position);
		if (d < closenessRadius)
		{
			Vector2f diff = position - currentBird->position;
			diff = normalize(diff);
			desiredVel += diff;
			count++;
		}
	}
	if (count == 0)
		return;
	desiredVel = desiredVel / count;
	desiredVel = normalize(desiredVel);
	desiredVel *= maxspeed;
	Vector2f steer = desiredVel - velocity;
	limit(steer, maxForce);
	acceleration += steer * flock->toggleSeparation;
}

void Bird::ComputeAlignment()
{
	float count = 0;
	Vector2f desiredVel = Vector2f(0, 0);
	for (int i = 0; i < flock->birdList.size(); i++)
	{
		Bird* currentBird = &flock->birdList[i];
		if (currentBird == this)
			continue;
		float d = magnitude(position - currentBird->position);
		if (d < closenessRadius)
		{
			Vector2f diff = currentBird->velocity;
			diff = normalize(diff);
			desiredVel += diff;
			count++;
		}
	}
	if (count == 0)
		return;
	desiredVel = desiredVel / count;
	desiredVel = normalize(desiredVel);
	desiredVel *= maxspeed;
	Vector2f steer = desiredVel - velocity;
	limit(steer, maxForce);
	acceleration += steer * flock->toggleAlingment;
}

void Bird::ComputeCohesion()
{
	float count = 0;
	Vector2f desiredVel = Vector2f(0, 0);
	for (int i = 0; i < flock->birdList.size(); i++)
	{
		Bird* currentBird = &flock->birdList[i];
		if (currentBird == this)
			continue;
		float d = magnitude(position - currentBird->position);
		if (d < closenessRadius)
		{
			Vector2f diff = currentBird->position;
			desiredVel += diff;
			count++;
		}
	}
	if (count == 0)
		return;
	desiredVel = desiredVel / count;
	desiredVel = desiredVel - position;
	desiredVel = normalize(desiredVel);
	desiredVel *= maxspeed;
	Vector2f steer = desiredVel - velocity;
	limit(steer, maxForce);
	acceleration += steer * 1.1f * flock->toggleCohesion;
}