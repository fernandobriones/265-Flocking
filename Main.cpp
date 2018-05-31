#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Flock System.h"
#include "Global.h"

sf::RenderWindow window;

int main()
{
	 window.create(sf::VideoMode(screenWidth, screenHeight), "SFML works!");

	 Flock Birds;
	 sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		float dt = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		Birds.update(dt);
		Birds.draw();
		window.display();
		

	}

	return 0;
}

