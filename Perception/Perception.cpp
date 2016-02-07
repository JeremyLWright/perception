// Perception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <cassert>

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Perception :: Now you see me.");
	while (window.isOpen())
	{
		sf::Event event;
		sf::Texture texture;
		if (!texture.loadFromFile("assets/orange_bunny.png", sf::IntRect(10, 10, 32, 32)))
		{

			throw std::runtime_error("Unable to load sprites.");
		}
		sf::Sprite sprite;
		sprite.setTexture(texture);



		while (window.pollEvent(event))
		{
			window.clear();
		window.draw(sprite);
		window.display();
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
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128)
					std::cout << "Typed: " << static_cast<char>(event.text.unicode) << '\n';
				break;

			}
		}
	}

    return 0;
}

