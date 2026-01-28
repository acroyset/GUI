#include <iostream>
#include <SFML/Graphics.hpp>

#include "GUI/Objects/Graph.h"
#include "GUI/Objects/Text.h"
#include "GUI/Stacks/VStack.h"
#include "GUI/Stacks/HStack.h"
#include "GUI/Root.h"
#include "GUI/Objects/ValueBar.h"
#include "GUI/Objects/Slider.h"
#include "GUI/Objects/Toggle.h"

int main() {
	sf::Font font;
	if (!font.loadFromFile("/System/Library/Fonts/SFNSRounded.ttf")) {
		std::cerr << "Error loading font\n";
		return -1;
	}

	auto* textObj1 = new Text("Hello World", Color::White, font);
	textObj1->setBgColor(Color::Black);
	textObj1->setOutlineColor(Color::White);
	textObj1->setOutlineThickness();

	auto* fpsText = new Text(Color::White, font);
	fpsText->setBgColor(Color::Black);
	fpsText->setOutlineColor(Color::White);
	fpsText->setOutlineThickness();

	auto* textObj3 = new Text(Color::White, font);
	textObj3->setBgColor(Color::Black);
	textObj3->setOutlineColor(Color::White);
	textObj3->setOutlineThickness();

	auto* textObj4 = new Text("Value", Color::White, font, 30);
	textObj4->setBgColor(Color::Black);

	auto* blankTextObj = new Text(Color::White, font);


	auto* toggle1 = new Toggle(false, 300, 64, blankTextObj);
	toggle1->setBgColor(Color::Blue);
	toggle1->setPadding(8);
	toggle1->setCornerRadius(32);


	Interpolated<float> testInterpolation1(0, 2, EASE_IN_OUT_CUBIC);
	testInterpolation1.set(1);

	Interpolated<float> testInterpolation2(0, 2, EASE_IN_BACK);
	testInterpolation2.set(1);

	Interpolated<float> testInterpolation3(0, 2, EASE_OUT_BACK);
	testInterpolation3.set(1);

	Interpolated<float> testInterpolation4(0, 2, EASE_OUT_ELASTIC);
	testInterpolation4.set(1);


	auto* valueBar1 = new ValueBar(-0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar1->setBgColor(Color::Red);

	auto* valueBar2 = new ValueBar(-0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar2->setBgColor(Color::Yellow);

	auto* valueBar3 = new ValueBar(-0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar3->setBgColor(Color::Green);

	auto* valueBar4 = new ValueBar(-0.25f, 1.25f, 200, 32, blankTextObj);
	valueBar4->setBgColor(Color::Blue);

	auto* textObj5 = new Text("Speed", Color::White, font, 30);
	textObj5->setBgColor(Color::Black);


	auto* slider1 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider1->setBgColor(Color::Red);

	auto* slider2 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider2->setBgColor(Color::Yellow);

	auto* slider3 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider3->setBgColor(Color::Green);

	auto* slider4 = new Slider(1, 0, 5, 200, 32, blankTextObj);
	slider4->setBgColor(Color::Blue);


	std::string graph1Title = "Graph";
	auto* graphTitle = new Text(graph1Title, Color::White, font, 30);
	graphTitle->setTextPadding(32);

	std::vector<sf::Vector2f> data {};
	auto* graph1 = new Graph(data, 500, 500, graphTitle);
	graph1->setBgColor(Color::Yellow);
	graph1->setPadding(8);
	graph1->setCornerRadius(32);


	auto* VStack1 = new VStack({textObj1, fpsText, textObj3, toggle1});

	auto* VStack2 = new VStack({textObj4, valueBar1, valueBar2, valueBar3, valueBar4});

	auto* VStack3 = new VStack({textObj5, slider1, slider2, slider3, slider4});

	auto* HStack1 = new HStack({VStack1, VStack2, VStack3, new Spacer(), graph1});
	HStack1->setPadding(8);


	auto* root = new Root({HStack1});

	root->addEvent({
		[](sf::Event event)
			{
			return event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space;
			},
		[
			&testInterpolation1,
			&testInterpolation2,
			&testInterpolation3,
			&testInterpolation4
			]
		{
			testInterpolation1 = 1- testInterpolation1.get();
			testInterpolation2 = 1- testInterpolation2.get();
			testInterpolation3 = 1- testInterpolation3.get();
			testInterpolation4 = 1- testInterpolation4.get();
		}
	});


	float x = 0;

	sf::Clock clock;
	while (root->isOpen()) {

		float dt = clock.restart().asSeconds();
		fpsText->setText("Fps: " + std::to_string(int(1/dt)));
		textObj3->setText("Data Points: " + std::to_string(data.size()));

		data.emplace_back(x, pow(1.1, x));
		x += dt;

		testInterpolation1.setTime(slider1->getValue());
		testInterpolation1.update(dt);
		valueBar1->setValue(testInterpolation1.get());

		testInterpolation2.setTime(slider2->getValue());
		testInterpolation2.update(dt);
		valueBar2->setValue(testInterpolation2.get());

		testInterpolation3.setTime(slider3->getValue());
		testInterpolation3.update(dt);
		valueBar3->setValue(testInterpolation3.get());

		testInterpolation4.setTime(slider4->getValue());
		testInterpolation4.update(dt);
		valueBar4->setValue(testInterpolation4.get());

		sf::CircleShape circle(20);
		circle.setFillColor(Color::White);

		root->update(dt);

		root->clear();

		circle.setPosition({testInterpolation1*500+200, 650});
		circle.setFillColor(Color::Red);
		root->draw(circle);
		circle.setPosition({testInterpolation2*500+200, 700});
		circle.setFillColor(Color::Yellow);
		root->draw(circle);
		circle.setPosition({testInterpolation3*500+200, 750});
		circle.setFillColor(Color::Green);
		root->draw(circle);
		circle.setPosition({testInterpolation4*500+200, 800});
		circle.setFillColor(Color::Blue);
		root->draw(circle);

		root->draw();
		root->display();
	}

	delete root;
}
