#include <iostream>
#include <SFML/Graphics.hpp>

#include "Graph.h"
#include "Text.h"
#include "VStack.h"
#include "HStack.h"
#include "Root.h"
#include "ValueBar.h"
#include "Slider.h"

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

	sf::VideoMode mode = sf::VideoMode(1280, 800);
	sf::RenderWindow window(mode, "SFML GUI", sf::Style::Default, settings);
	setViewToWindow(window);
	window.setFramerateLimit(120);

	sf::Font font;
	if (!font.loadFromFile("/System/Library/Fonts/SFNSRounded.ttf")) {
		std::cerr << "Error loading font\n";
		return -1;
	}

	auto* textObj1 = new Text("Hello World", Color::White, font, 30);
	textObj1->setBgColor(Color::Black);
	textObj1->setPadding(8);
	textObj1->setCornerRadius(32);
	textObj1->setTextPadding(32);
	textObj1->setOutlineColor(Color::White);
	textObj1->setOutlineThickness();

	std::string text2 = "FPS: ";
	auto* textObj2 = new Text(text2, Color::White, font, 30);
	textObj2->setBgColor(Color::Black);
	textObj2->setPadding(8);
	textObj2->setCornerRadius(32);
	textObj2->setTextPadding(32);
	textObj2->setOutlineColor(Color::White);
	textObj2->setOutlineThickness();

	std::string text3 = "Data Points: ";
	auto* textObj3 = new Text(text3, Color::White, font, 30);
	textObj3->setBgColor(Color::Black);
	textObj3->setPadding(8);
	textObj3->setCornerRadius(32);
	textObj3->setTextPadding(32);
	textObj3->setOutlineColor(Color::White);
	textObj3->setOutlineThickness();

	auto* blankTextObj = new Text("", Color::White, font, 30);

	Interpolated<float> testInterpolation1(0, 2, EASE_IN_OUT_CUBIC);
	testInterpolation1.set(1);
	float testValue1 = testInterpolation1.get();

	Interpolated<float> testInterpolation2(0, 2, EASE_IN_BACK);
	testInterpolation2.set(1);
	float testValue2 = testInterpolation2.get();

	Interpolated<float> testInterpolation3(0, 2, EASE_OUT_BACK);
	testInterpolation3.set(1);
	float testValue3 = testInterpolation3.get();

	Interpolated<float> testInterpolation4(0, 2, EASE_OUT_ELASTIC);
	testInterpolation4.set(1);
	float testValue4 = testInterpolation4.get();

	auto* textObj4 = new Text("Value", Color::White, font, 30);
	textObj4->setBgColor(Color::Black);
	textObj4->setPadding(8);
	textObj4->setCornerRadius(32);
	textObj4->setTextPadding(32);

	auto* valueBar1 = new ValueBar(testValue1, -0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar1->setBgColor(Color::Red);
	valueBar1->setPadding(8);
	valueBar1->setCornerRadius(32);

	auto* valueBar2 = new ValueBar(testValue2, -0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar2->setBgColor(Color::Yellow);
	valueBar2->setPadding(8);
	valueBar2->setCornerRadius(32);

	auto* valueBar3 = new ValueBar(testValue3, -0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar3->setBgColor(Color::Green);
	valueBar3->setPadding(8);
	valueBar3->setCornerRadius(32);

	auto* valueBar4 = new ValueBar(testValue4, -0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar4->setBgColor(Color::Blue);
	valueBar4->setPadding(8);
	valueBar4->setCornerRadius(32);

	auto* textObj5 = new Text("Speed", Color::White, font, 30);
	textObj5->setBgColor(Color::Black);
	textObj5->setPadding(8);
	textObj5->setCornerRadius(32);
	textObj5->setTextPadding(32);

	auto* slider1 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider1->setBgColor(Color::Red);
	slider1->setPadding(8);
	slider1->setCornerRadius(32);

	auto* slider2 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider2->setBgColor(Color::Yellow);
	slider2->setPadding(8);
	slider2->setCornerRadius(32);

	auto* slider3 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider3->setBgColor(Color::Green);
	slider3->setPadding(8);
	slider3->setCornerRadius(32);

	auto* slider4 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider4->setBgColor(Color::Blue);
	slider4->setPadding(8);
	slider4->setCornerRadius(32);

	std::string graph1Title = "Graph";
	auto* graphTitle = new Text(graph1Title, Color::White, font, 30);
	graphTitle->setTextPadding(32);

	std::vector<sf::Vector2f> data {};
	auto* graph1 = new Graph(data, 500, 500, graphTitle);
	graph1->setBgColor(Color::Yellow);
	graph1->setPadding(8);
	graph1->setCornerRadius(32);

	auto* VStack1 = new VStack();
	VStack1->addItem(textObj1);
	VStack1->addItem(textObj2);
	VStack1->addItem(textObj3);
	VStack1->addItem(textObj4);

	auto* VStack2 = new VStack();
	VStack2->addItem(textObj4);
	VStack2->addItem(valueBar1);
	VStack2->addItem(valueBar2);
	VStack2->addItem(valueBar3);
	VStack2->addItem(valueBar4);

	auto* VStack3 = new VStack();
	VStack3->addItem(textObj5);
	VStack3->addItem(slider1);
	VStack3->addItem(slider2);
	VStack3->addItem(slider3);
	VStack3->addItem(slider4);

	auto* HStack1 = new HStack();
	HStack1->addItem(VStack1);
	HStack1->addItem(VStack2);
	HStack1->addItem(VStack3);
	HStack1->addItem(new Spacer());
	HStack1->addItem(graph1);
	HStack1->setPadding(8);

	auto* root = new Root(window);

	root->addView(HStack1);

	float x = 0;

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::Resized) {
				setViewToWindow(window);
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				} else if (event.key.code == sf::Keyboard::Space) {
					testInterpolation1 = 1- testInterpolation1.get();
					testInterpolation2 = 1- testInterpolation2.get();
					testInterpolation3 = 1- testInterpolation3.get();
					testInterpolation4 = 1- testInterpolation4.get();
				}
			}
		}

		float dt = clock.restart().asSeconds();
		text2 = "Fps: " + std::to_string(int(1/dt));
		text3 = "Data Points: " + std::to_string(data.size());

		data.emplace_back(x, pow(1.1, x));
		x += dt;

		testInterpolation1.setTime(slider1->getValue());
		testInterpolation1.update(dt);
		testValue1 = testInterpolation1.get();

		testInterpolation2.setTime(slider2->getValue());
		testInterpolation2.update(dt);
		testValue2 = testInterpolation2.get();

		testInterpolation3.setTime(slider3->getValue());
		testInterpolation3.update(dt);
		testValue3 = testInterpolation3.get();

		testInterpolation4.setTime(slider4->getValue());
		testInterpolation4.update(dt);
		testValue4 = testInterpolation4.get();

		sf::CircleShape circle(20);
		circle.setFillColor(Color::White);

		window.clear(sf::Color(90, 90, 90));

		circle.setPosition({testInterpolation1*500+200, 650});
		circle.setFillColor(Color::Red);
		window.draw(circle);
		circle.setPosition({testInterpolation2*500+200, 700});
		circle.setFillColor(Color::Yellow);
		window.draw(circle);
		circle.setPosition({testInterpolation3*500+200, 750});
		circle.setFillColor(Color::Green);
		window.draw(circle);
		circle.setPosition({testInterpolation4*500+200, 800});
		circle.setFillColor(Color::Blue);
		window.draw(circle);

		root->update(dt);
		root->draw();

		window.display();
	}

	delete root;
}
