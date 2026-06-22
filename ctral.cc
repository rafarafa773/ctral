// SPDX-License-Identifier: GPL-3.0-or-later
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <random>
#define VELOCITY 5

int main() {
	float intensifcacao = 1;
	sf::RenderWindow window(sf::VideoMode({1920, 1080}), "sfml brutal");
	sf::RectangleShape shape({100, 100});
	bool enemie_dying = false;
	sf::CircleShape circle1(10);
	circle1.setFillColor(sf::Color::Yellow);
	std::vector<sf::RectangleShape> enemie;
	sf::Image image1("100x100_true.png");
	sf::Font fiont("arial.ttf");
	sf::Text text1(fiont, "hello!\nwasd and press space to shot", 50);
	bool hello_active = true;
	sf::Clock ballClock;
	bool showing_my_balls = false;
	text1.setFillColor(sf::Color::Red);
	window.setFramerateLimit(60);
	sf::Texture texture1("100x100_true.png");
	window.setIcon(image1);
	shape.setTexture(&texture1);
	shape.setPosition({300.f, 200.f});

	std::random_device rd;
	std::mt19937 gerador(rd());
	std::uniform_real_distribution<float> distribuicao(0, 400);

	sf::RectangleShape initial_enemy;
	initial_enemy.setSize({100.f, 100.f});
	initial_enemy.setFillColor(sf::Color::White);
	initial_enemy.setPosition({distribuicao(gerador), distribuicao(gerador)});
	enemie.push_back(initial_enemy);

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} 
			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) { 
				if (keyPressed->code == sf::Keyboard::Key::Space) {
					circle1.setPosition(sf::Vector2f{shape.getPosition().x + 120, (shape.getPosition().y + shape.getSize().y / 2) - 10.f});
					showing_my_balls = !showing_my_balls;
					ballClock.restart();
				}
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			shape.move(sf::Vector2f(0.f, -VELOCITY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			shape.move(sf::Vector2f(0.f, VELOCITY));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			shape.move(sf::Vector2f(-VELOCITY, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			shape.move(sf::Vector2f(VELOCITY, 0));
		}
		
		std::random_device rd;
		std::mt19937 gerador(rd());
		std::uniform_real_distribution<float> distribuicao(0, 1980);

		window.clear(sf::Color::Black);
		if(showing_my_balls) {
			if(ballClock.getElapsedTime().asSeconds() < 1.f) {
				circle1.move(sf::Vector2f{5.f, 0.f});
				window.draw(circle1);
			} else {
				showing_my_balls = false;
			}
		}
		for(size_t num_of_enemy = 0; num_of_enemy < enemie.size(); ++num_of_enemy) {	
			if (circle1.getGlobalBounds().findIntersection(enemie[num_of_enemy].getGlobalBounds())) {
				enemie_dying = true;
			}
		}
		for(auto& e : enemie) {
			e.setSize({100.f, 100.f});
			e.setFillColor(sf::Color::White);
		}
		if(enemie_dying) {
			sf::RectangleShape new_enemy;
			new_enemy.setSize({100.f, 100.f});
			new_enemy.setFillColor(sf::Color::White);
			new_enemy.setPosition({distribuicao(gerador), distribuicao(gerador)});
			for (int c = 0; c < 1; c++) {
				enemie.push_back(new_enemy);
			}
		
			for(size_t num_of_enemy = 0; num_of_enemy < enemie.size(); ++num_of_enemy) {	
				enemie[num_of_enemy].setPosition({(distribuicao(gerador)), (distribuicao(gerador))});
				window.draw(enemie[num_of_enemy]);
			}
			enemie_dying = false;
		} else {
			for(size_t num_of_enemy = 0; num_of_enemy < enemie.size(); ++num_of_enemy) {	
				window.draw(enemie[num_of_enemy]);
			}
				
		}
		window.draw(shape);
		window.draw(text1);
		window.display();
	}
	return 0;
}
