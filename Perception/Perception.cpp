// Perception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Window.hpp>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Perception :: Now you see me.");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

    return 0;
}

