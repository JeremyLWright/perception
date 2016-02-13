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

#include "Helpers/AnimatedSprite.h"
#include "Helpers/Animation.h"


int main()
{

	sf::Texture character_texture;
	sf::Texture brick_texture;
	Expects(character_texture.loadFromFile("assets/emo_physicist.png"));
	Expects(brick_texture.loadFromFile("assets/42_Bricks_Dk.png", sf::IntRect(0, 0, 64, 64)));
	brick_texture.setRepeated(true);
	
	//Setup the animations for all four directions (set spritesheet and push frames)
	Animation walking_animation_down;
	walking_animation_down.setSpriteSheet(character_texture);
	walking_animation_down.addFrame(sf::IntRect(32, 0, 32, 32));
	walking_animation_down.addFrame(sf::IntRect(64, 0, 32, 32));
	walking_animation_down.addFrame(sf::IntRect(32, 0, 32, 32));
	walking_animation_down.addFrame(sf::IntRect( 0, 0, 32, 32));

	Animation walking_animation_left;
	walking_animation_left.setSpriteSheet(character_texture);
	walking_animation_left.addFrame(sf::IntRect(32, 32, 32, 32));
	walking_animation_left.addFrame(sf::IntRect(64, 32, 32, 32));
	walking_animation_left.addFrame(sf::IntRect(32, 32, 32, 32));
	walking_animation_left.addFrame(sf::IntRect( 0, 32, 32, 32));

	Animation walking_animation_right;
	walking_animation_right.setSpriteSheet(character_texture);
	walking_animation_right.addFrame(sf::IntRect(32, 64, 32, 32));
	walking_animation_right.addFrame(sf::IntRect(64, 64, 32, 32));
	walking_animation_right.addFrame(sf::IntRect(32, 64, 32, 32));
	walking_animation_right.addFrame(sf::IntRect( 0, 64, 32, 32));

	Animation walking_animation_up;
	walking_animation_up.setSpriteSheet(character_texture);
	walking_animation_up.addFrame(sf::IntRect(32, 96, 32, 32));
	walking_animation_up.addFrame(sf::IntRect(64, 96, 32, 32));
	walking_animation_up.addFrame(sf::IntRect(32, 96, 32, 32));
	walking_animation_up.addFrame(sf::IntRect( 0, 96, 32, 32));


	Animation* currentAnimation = &walking_animation_right;

	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(0, 0);

	sf::Sprite brick_sprite;
	brick_sprite.setTexture(brick_texture);
	brick_sprite.setTextureRect(sf::IntRect{0, 64, 64 * 5, 64 * 1});
	brick_sprite.setPosition(0, 64*3);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Perception :: Now you see me.");
	window.setFramerateLimit(60);

	sf::Clock frameClock;
	double speed{80};
	bool no_key_was_pressed{true};

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
				break;
			//case sf::Event::TextEntered:
			//	if (event.text.unicode < 128)
			//	{
			//		const auto key = static_cast<char>(event.text.unicode);
			//		switch (key)
			//		{
			//		case 'w':
			//		{
			//			std::cout << "Up\n";
			//			sprite.move(sf::Vector2f(0, -2));
			//			break;
			//		}
			//		case 'a':
			//		{
			//			std::cout << "Left\n";
			//			sprite.move(sf::Vector2f(-2, 0));
			//			break;
			//		}
			//		case 'd':
			//		{
			//			std::cout << "Right\n";
			//			sprite.move(sf::Vector2f(2, 0));
			//			break;
			//		}
			//		case 's':
			//			std::cout << "Down\n";
			//			sprite.move(sf::Vector2f(0, 2));
			//			break;
			//		}


			//	}
			//	break;

			}

			sf::Time frame_time = frameClock.restart();

			sf::Vector2f movement(0, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentAnimation = &walking_animation_up;
				movement.y -= speed;
				no_key_was_pressed = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				currentAnimation = &walking_animation_down;
				movement.y += speed;
				no_key_was_pressed = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				currentAnimation = &walking_animation_left;
				movement.x -= speed;
				no_key_was_pressed = false;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				currentAnimation = &walking_animation_right;
				movement.x += speed;
				no_key_was_pressed = false;
			}
			animatedSprite.play(*currentAnimation);
			animatedSprite.move(movement * frame_time.asSeconds());

			if (no_key_was_pressed) animatedSprite.stop();
			no_key_was_pressed = true;
			animatedSprite.update(frame_time);

			window.clear();
			window.draw(animatedSprite);
			window.draw(brick_sprite);
			window.display();
		}
	}

	return 0;
}

