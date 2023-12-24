#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


int main() {
	const int width = 1000;
	const int height = 1000;

	Game game{ width,height };
	sf::RenderWindow window(sf::VideoMode(width, height), "0", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	bool is_active = false;
	int iteration = 0;

	sf::Clock clock;
	clock.restart();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::P) {
					is_active = !is_active;

				}
			default:
				break;
			}
		}

		//Происходит очистка окна
		window.clear();
		
		float update_delta = 0.8;
		if (is_active && clock.getElapsedTime().asMicroseconds() >= update_delta)
		{
			window.setTitle(std::to_string(++iteration));
			game.update();
			clock.restart();
		}

		//Запись в окно
		game.display_grid(window);//отобразить сетку


		window.display(); //обновление

	}
}