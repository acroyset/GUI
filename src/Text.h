//
// Created by Andreas Royset on 1/23/26.
//

#ifndef TEXT_H
#define TEXT_H

#include "Utils.h"
#include "View.h"

class Text final : public View {

	sf::Text textObj;

public:

	std::string& text;

	sf::Color color;
	sf::Font font;

	float reserveWidth = 0;

	int charSize;

	float textPadding = 16;

	Text(std::string& text, sf::Color color, const sf::Font& font, int charSize) : text(text), color(color), font(font), charSize(charSize) {
		textObj = sf::Text(text, font, charSize);
		textObj.setFillColor(color);
		textObj.setStyle(sf::Text::Bold);
	}

	void update(sf::Vector2f position) override {
		textObj.setString(text);
		sf::FloatRect bounds = textObj.getLocalBounds();

		width = bounds.width + 2*textPadding + leftPadding + rightPadding;
		height = bounds.height + 2*textPadding + topPadding + bottomPadding;

		width = fmaxf(width, reserveWidth);
		if (width > reserveWidth) reserveWidth = width + 20;

		this->position = position;

		textObj.setPosition(position + sf::Vector2f(textPadding + leftPadding, textPadding-bounds.height/2 + topPadding));
	}

	void draw(sf::RenderTarget& target) const override {

		float rWidth = width - leftPadding - rightPadding;
		float rHeight = height - topPadding - bottomPadding;

		drawRoundedRectangle(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, bgColor, cornerRadius);

		target.draw(textObj);
	}

	void setTextPadding(float textPadding) {this->textPadding = textPadding;}
	void setReservedWidth(float reservedWidth) {this->reserveWidth = reservedWidth;}
};

#endif //TEXT_H
