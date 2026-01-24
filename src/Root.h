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

		for (View* view : views) {
			view->setWidth(windowSize.x);
			view->setHeight(windowSize.y);
			view->update({0,0}, dt);
		}
	}

	void draw() {
		for (View* view : views) {
			view->draw(window);
		}
	}
};


#endif //ROOT_H
