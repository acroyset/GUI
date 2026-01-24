//
// Created by Andreas Royset on 1/23/26.
//

#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

struct View {

protected:

	sf::Vector2f position{-1,-1};

	float topPadding = 0;
	float bottomPadding = 0;
	float rightPadding = 0;
	float leftPadding = 0;

	float width = 0;
	float height = 0;

	sf::Color bgColor = sf::Color::Transparent;

	float cornerRadius = 0.1;

public:
	virtual ~View() = default;

	View() = default;

	virtual void update(sf::Vector2f) = 0;
	virtual void draw(sf::RenderTarget&) const = 0;

	void setTopPadding(float topPadding = 16) { this->topPadding = topPadding; }
	void setBottomPadding(float bottomPadding = 16) { this->bottomPadding = bottomPadding; }
	void setLeftPadding(float leftPadding = 16) { this->leftPadding = leftPadding; }
	void setRightPadding(float rightPadding = 16) { this->rightPadding = rightPadding; }

	void setVerticalPadding(float verticalPadding = 16) {
		this->topPadding = verticalPadding;
		this->bottomPadding = verticalPadding;
	}
	void setHorizontalPadding(float horizontalPadding = 16) {
		this->leftPadding = horizontalPadding;
		this->rightPadding = horizontalPadding;
	}
	void setPadding(float padding = 16) {
		this->topPadding = padding;
		this->bottomPadding = padding;
		this->leftPadding = padding;
		this->rightPadding = padding;
	}

	void setCornerRadius(float cornerRadius = 8) {this->cornerRadius = cornerRadius;}

	void setBgColor(sf::Color color) {this->bgColor = color;}

	[[nodiscard]] float getWidth() const {return width;}
	[[nodiscard]] float getHeight() const {return height;}
};

#endif //VIEW_H
