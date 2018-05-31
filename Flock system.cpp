#include "Flock System.h"
#include "Global.h"

void Flock::draw()
{
	for (size_t i = 0; i < birdList.size(); i++)
	{
		birdList[i].Draw();
	}
	window.draw(toggleStatus);
}

void Flock::update(float dt)
{
	if (!Keyboard::isKeyPressed(Keyboard::Num1) && !Keyboard::isKeyPressed(Keyboard::Num2) && !Keyboard::isKeyPressed(Keyboard::Num3))
	{
		isKeyPressed = false;
		
	}

	if (Keyboard::isKeyPressed(Keyboard::Num1) && !isKeyPressed)
	{
		toggleSeparation = (toggleSeparation == 0)?1:0;	
		if (toggleSeparation == 1)
			toggleStatus.setString("Separation: ON");
		else if (toggleSeparation == 0)
			toggleStatus.setString("Separation: OFF");
		isKeyPressed = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num2) && !isKeyPressed)
	{
		toggleAlingment = (toggleAlingment == 0) ? 1 : 0;
		if (toggleAlingment == 1)
			toggleStatus.setString("Alignment: ON");
		else if (toggleAlingment == 0)
			toggleStatus.setString("Alignment: OFF");
		isKeyPressed = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Num3) && !isKeyPressed)
	{
		toggleCohesion = (toggleCohesion == 0) ? 1 : 0;
		if (toggleCohesion == 1)
			toggleStatus.setString("Cohesion: ON");
		else if (toggleCohesion == 0)
			toggleStatus.setString("Cohesion: OFF");
		isKeyPressed = true;
	}



	Vector2i mousePos = Mouse::getPosition(window);
	target.x = (float)mousePos.x;
	target.y = (float)mousePos.y;
	//printf("Positionx: %d\n", target.x);
	
 
	if (Mouse::isButtonPressed(Mouse::Left) && !isMousePressed)
	{
		birdList.push_back(Bird(Vector2f(target.x, target.y), this));
		printf("Size: %d\n", birdList.size());
		isMousePressed = true;
	}
	if (Mouse::isButtonPressed(Mouse::Right) && !isMousePressed)
	{
		if (birdList.size() > 0)
		{
			birdList.pop_back();
			printf("Size: %d\n", birdList.size());
			isMousePressed = true;
		}
	}

	if (!Mouse::isButtonPressed(Mouse::Left) && !Mouse::isButtonPressed(Mouse::Right))
	{
		isMousePressed = false;
	}
	for (int i = 0; i < birdList.size(); i++)
	{
		birdList[i].update(dt);
	}
}

Flock::Flock()
{
	font.loadFromFile("BAUHS93.TTF");
	toggleStatus.setFont(font);
}