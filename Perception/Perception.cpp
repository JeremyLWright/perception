// Perception.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <boost/version.hpp>
static_assert(BOOST_VERSION >= 106000, "Boost must be 1.60 or greater.");

#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <gsl.h>


int main()
{

	sf::Texture character_texture;
	sf::Texture brick_texture;
	Expects(character_texture.loadFromFile("assets/orange_bunny.png", sf::IntRect(10, 10, 32, 72)));
	Expects(brick_texture.loadFromFile("assets/42_Bricks_Dk.png", sf::IntRect(0, 0, 64, 64)));
	brick_texture.setRepeated(true);
	

	sf::Sprite sprite;
	sprite.setTexture(character_texture);
	sf::Sprite brick_sprite;
	brick_sprite.setTexture(brick_texture);
	brick_sprite.setTextureRect(sf::IntRect{0, 64, 64 * 5, 64 * 1});
	brick_sprite.setPosition(0, 64*3);

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
			window.draw(brick_sprite);
			window.display();
		}
	}

	return 0;
}

