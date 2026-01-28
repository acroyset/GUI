//
// Created by Andreas Royset on 1/23/26.
//

#ifndef ROOT_H
#define ROOT_H
#include "Utils/Event.h"
#include "Utils/View.h"


inline void setViewToWindow(sf::RenderWindow& window) {
	auto s = window.getSize();
	sf::View v(sf::FloatRect(0.f, 0.f, float(s.x), float(s.y)));
	window.setView(v);
}

namespace Color {
	inline const sf::Color Red    {255, 100, 120};
	inline const sf::Color Green  {0, 200, 170};
	inline const sf::Color Blue   {0, 140, 190};
	inline const sf::Color Yellow {255, 210, 110};
	inline const sf::Color Black  {57, 57, 57};
	inline const sf::Color White  {255, 255, 255};
	inline const sf::Color Grey   {160, 160, 160};
}

inline sf::Color opacity(sf::Color c, sf::Uint8 a) {
	return {c.r, c.g, c.b, a};
}

class Root {

	sf::RenderWindow window;

	std::vector<View*> views;
	std::vector<Event> events;

	public:

	explicit Root(const std::string& title = "SFML Window", unsigned int framerateLimit = 120){
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		window.create(sf::VideoMode(1280, 800), title, sf::Style::Default, settings);

		setViewToWindow(window);
		window.setFramerateLimit(framerateLimit);
	}

	explicit Root(const std::vector<View*>& views, const std::string& title = "SFML Window", unsigned int framerateLimit = 120){
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		window.create(sf::VideoMode(1280, 800), title, sf::Style::Default, settings);

		setViewToWindow(window);
		window.setFramerateLimit(framerateLimit);

		for(const auto& view : views) {
			addView(view);
		}
	}

	void addView(View* view) {
		views.push_back(view);
	}

	void addEvent(const Event& event) {
		events.push_back(event);
	}

	void update(float dt) {

		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				continue;
			}

			if (event.type == sf::Event::Resized) {
				setViewToWindow(window);
				continue;
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					continue;
				}
			}

			for (const auto&[activate, callback] : events) {
				if (activate(event)) {
					callback();
					break;
				}
			}
		}

		auto windowSize = window.getSize();

		// Get mouse position relative to the window
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

		// Check if left mouse button is pressed
		bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		for (View* view : views) {
			view->setWidth(float(windowSize.x));
			view->setHeight(float(windowSize.y));
			view->update({0,0}, dt, mousePos, mousePressed);
		}
	}

	void draw() {
		for (View* view : views) {
			view->draw(window);
		}
	}

	void clear() {
		window.clear(sf::Color(90, 90, 90));
	}

	void display() {
		window.display();
	}

	bool isOpen () const {
		return window.isOpen();
	}

	void draw(const sf::Drawable& view) {
		window.draw(view);
	}
};


#endif //ROOT_H
