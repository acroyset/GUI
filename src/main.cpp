#include <iostream>
#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "Text.h"
#include "VStack.h"
#include "HStack.h"

namespace Color {
	inline const sf::Color Red    {255, 100, 120};
	inline const sf::Color Green  {0, 200, 170};
	inline const sf::Color Blue   {0, 140, 190};
	inline const sf::Color Yellow {255, 210, 110};
	inline const sf::Color Black  {57, 57, 57};
	inline const sf::Color White  {255, 255, 255};
	inline const sf::Color Grey   {160, 160, 160};
}

sf::Color opacity(sf::Color c, sf::Uint8 a) {
	return {c.r, c.g, c.b, a};
}

void setViewToWindow(sf::RenderWindow& window) {
	auto s = window.getSize();
	sf::View v(sf::FloatRect(0.f, 0.f, float(s.x), float(s.y)));
	window.setView(v);
}


int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML GUI", sf::Style::Default, settings);
	setViewToWindow(window);
	window.setFramerateLimit(365);

	sf::Font font;
	if (!font.loadFromFile("/System/Library/Fonts/SFNSRounded.ttf")) {
		std::cerr << "Error loading font\n";
		return -1;
	}

	std::string text1 = "Hello world!";
	auto* textObj1 = new Text(text1, Color::White, font, 30);
	textObj1->setBgColor(Color::Red);
	textObj1->setPadding(8);
	textObj1->setCornerRadius(32);
	textObj1->setTextPadding(32);

	std::string text2 = "Text 2";
	auto* textObj2 = new Text(text2, Color::White, font, 30);
	textObj2->setBgColor(Color::Blue);
	textObj2->setPadding(8);
	textObj2->setCornerRadius(32);
	textObj2->setTextPadding(32);

	std::string text3 = "Text 3";
	auto* textObj3 = new Text(text3, Color::White, font, 30);
	textObj3->setBgColor(Color::Green);
	textObj3->setPadding(8);
	textObj3->setCornerRadius(32);
	textObj3->setTextPadding(32);

	std::string graph1Title = "Graph Title";
	auto* textObj4 = new Text(graph1Title, Color::White, font, 30);
	textObj4->setTextPadding(32);

	std::vector<sf::Vector2f> data {{0,0}};
	auto* graph1 = new Graph(data, 500, 500, textObj4);
	graph1->setBgColor(Color::Yellow);
	graph1->setPadding(8);
	graph1->setCornerRadius(32);

	auto* VStack1 = new VStack();
	VStack1->addItem(textObj1);
	VStack1->addItem(textObj2);
	VStack1->addItem(textObj3);

	auto* HStack1 = new HStack();
	HStack1->addItem(VStack1);
	HStack1->addItem(graph1);
	HStack1->setPadding(8);

	float x = 0;

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}

			if (event.type == sf::Event::Resized) {
				setViewToWindow(window);
			}
		}

		float dt = clock.restart().asSeconds();
		text2 = "Fps: " + std::to_string(int(1/dt));
		text3 = "Data Points: " + std::to_string(data.size());

		x += dt;
		data.emplace_back(x, pow(1+0.035/365, 365*x)-1);


		window.clear(sf::Color(90, 90, 90));

		HStack1->update(sf::Vector2f(0,0));
		HStack1->draw(window);

		window.display();
	}
}
