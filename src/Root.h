//
// Created by Andreas Royset on 1/23/26.
//

#ifndef ROOT_H
#define ROOT_H
#include "View.h"

class Root {

	sf::RenderWindow& window;

	std::vector<View*> views;

	public:

	Root(sf::RenderWindow& window) : window(window){}

	void addView(View* view) {
		views.push_back(view);
	}

	void update(float dt) {
		auto windowSize = window.getSize();

		// Get mouse position relative to the window
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

		// Check if left mouse button is pressed
		bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		for (View* view : views) {
			view->setWidth(windowSize.x);
			view->setHeight(windowSize.y);
			view->update({0,0}, dt, mousePos, mousePressed);
		}
	}

	void draw() {
		for (View* view : views) {
			view->draw(window);
		}
	}
};


#endif //ROOT_H
