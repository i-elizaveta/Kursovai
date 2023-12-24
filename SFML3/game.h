
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
using namespace std;


class Game {
public:
	Game(int width_, int height_);

	void display_grid(sf::RenderWindow& window) const;
	void update();
	void reset();
private:
	int count_neighboors(int m_origin, int n_origin) const;
	void apply_rules(int neighboors, int m_origin, int n_origin);

	void init_vasuals();
	void seed_grid();
	int width;
	int height;
	vector<vector<bool>> grid_current;
	vector<vector<bool>> grid_next;
	vector<sf::Vertex> grid_visual;
	mt19937 rng;
	sf::Color visual_alive = sf::Color::White;
	sf::Color visual_dead = sf::Color::Black;
};