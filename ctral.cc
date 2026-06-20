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
#define VELOCITY 5

int main() {
	sf::RenderWindow window(sf::VideoMode({900, 600}), "sfml brutal");
	sf::RectangleShape shape({100, 100});
	sf::CircleShape circle1(10);
	circle1.setFillColor(sf::Color::Yellow);
	
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
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} // close window
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
		
		window.clear(sf::Color::Black);
		if(showing_my_balls) {
			if(ballClock.getElapsedTime().asSeconds() < 1.f) {
				circle1.move(sf::Vector2f{5.f, 0.f});
				window.draw(circle1);
			} else {
				showing_my_balls = false;
			}
		}
		window.draw(shape);
		window.draw(text1);
		window.display();
	}
	return 0;
}
