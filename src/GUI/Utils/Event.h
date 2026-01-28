//
// Created by Andreas Royset on 1/27/26.
//

#ifndef EVENT_H
#define EVENT_H
#include <functional>

struct Event {
	std::function<bool(sf::Event&)> activate;
	std::function<void()> callback;
};

#endif //EVENT_H
