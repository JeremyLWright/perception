// Perception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <boost/version.hpp>
static_assert(BOOST_VERSION <= 106000, "Boost must be 1.60 or greater.");

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

int main()
{

	sf::Texture texture;
	if (!texture.loadFromFile("assets/orange_bunny.png", sf::IntRect(10, 10, 32, 72)))
	{

		throw std::runtime_error("Unable to load sprites.");
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Perception :: Now you see me.");
	while (window.isOpen())
	{
		sf::Event event;



		while (window.pollEvent(event))
		{
			window.clear();
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
				{
					const auto key = static_cast<char>(event.text.unicode);
					switch (key)
					{
					case 'w':
					{
						std::cout << "Up\n";
						sprite.move(sf::Vector2f(0, -2));
						break;
					}
					case 'a':
					{
						std::cout << "Left\n";
						sprite.move(sf::Vector2f(-2, 0));
						break;
					}
					case 'd':
					{
						std::cout << "Right\n";
						sprite.move(sf::Vector2f(2, 0));
						break;
					}
					case 's':
						std::cout << "Down\n";
						sprite.move(sf::Vector2f(0, 2));
						break;
					}


				}
				break;

			}
			window.draw(sprite);
			window.display();
		}
	}

	return 0;
}

