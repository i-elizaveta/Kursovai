#include "game.h"
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include<cstddef>
#include<ctime>


Game::Game(int width_, int height_)
	: width{ width_ }, 
	height{ height_ },
	grid_current{},
	grid_next{},
	grid_visual{}

{
	rng.seed(1000);
	reset(); // задает начальное игровое поле
}

void Game::reset()
{
	grid_current.clear();
	grid_current.resize(static_cast<std::size_t>(height), vector<bool>(width));

	grid_next.clear();
	grid_next.resize(static_cast<std::size_t>(height), vector<bool>(width));

	init_vasuals();
	seed_grid();

}
void Game::init_vasuals() {

	grid_visual.clear();
	grid_visual.resize(width * height);
	int pos = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			grid_visual[pos].position = sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
			grid_visual[pos++].color = visual_dead;// на начале все мертвые

		}
	}
}
void Game::seed_grid() {
	std::uniform_int_distribution<int> m_axis(0, height - 1);
	std::uniform_int_distribution<int> n_axis(0, width - 1);
	std::uniform_int_distribution<int> cells(width*height/2, width*height );

	int initial_cell_nr = cells(rng);
	while (initial_cell_nr > 0) 
	{
		std::size_t  m = m_axis(rng);
		std::size_t  n = n_axis(rng);
		if (!grid_next[m][n]) {
			grid_next[m][n] = true;
			grid_visual[m * width + n].color = visual_alive;
			--initial_cell_nr;
		}



	}


}
void Game::display_grid(sf::RenderWindow& window) const
{
	window.draw(&grid_visual[0], grid_visual.size(), sf::Points);
}
void Game::update() {
	grid_current.swap(grid_next);
	for (int m = 0; m < height; ++m) {
		for (int n = 0; n < width; ++n)
		{
			apply_rules(count_neighboors(m, n), m, n);
		}
	}
}

int Game::count_neighboors(int m_origin, int n_origin)  const {
	int neighboors = 0;
	for (int m_current = m_origin - 1; m_current <= m_origin + 1; ++m_current)
	{
		for (int n_current = n_origin - 1; n_current <= n_origin + 1; ++n_current)
		{
			//Провепка выходит ли за границы экрана
			if (m_current < 0 || m_current >= height || n_current < 0 || n_current >= width)
			{
				continue;
			}
			// не нужно смотреть центр
			if (m_current == m_origin && n_current == n_origin)
			{
				continue;
			}
			//когда итый джитый равен 1 то клетка там есть 
			if (grid_current[m_current][n_current])
			{
				if (++neighboors > 3)
					return neighboors;
			}

		}
	}
	return neighboors;
}
void Game::apply_rules(int neighboors, int m, int n) {

	grid_next[m][n] = grid_current[m][n];
	//живач клетка погибает если у нее меньше 2 живых соседей
	if (grid_current[m][n] && neighboors < 2) {
		grid_next[m][n] = false;
		grid_visual[m * width + n].color = visual_dead;
	}

	//если у живой клетки 2 или 3 соседа  то она продолжает жить 
	if (grid_current[m][n] && (neighboors == 2|| neighboors == 3)) {
		grid_next[m][n] = true;
		grid_visual[m * width + n].color = visual_alive;
	}

	//живая клетка погибает так как больше трех соседей

	if (grid_current[m][n] && neighboors >3) {
		grid_next[m][n] = false;
		grid_visual[m * width + n].color = visual_dead;
	}

	//мертвая клетка если у нее 3 соседа то она оживает

	if (grid_current[m][n] &&neighboors == 3) {
		grid_next[m][n] = true;
		grid_visual[m * width + n].color = visual_alive;
	}

}

























