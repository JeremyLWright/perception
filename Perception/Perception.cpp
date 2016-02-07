// Perception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <SFML/Window.hpp>

int main()
{
	sf::Window window(sf::VideoMode(800, 600), "Perception :: Now you see me.");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				std::cout << "Pausing game.\n";
				break;
			case sf::Event::GainedFocus:
				std::cout << "Resuming game.\n";
			}
		}
	}

    return 0;
}

