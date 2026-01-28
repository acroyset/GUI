//
// Created by Andreas Royset on 1/23/26.
//

#ifndef TEXT_H
#define TEXT_H

#include "../Utils/Utils.h"
#include "../Utils/View.h"

class Text final : public View {

	sf::Text textObj;
	std::string text;

public:

	sf::Color color;
	sf::Font font;

	float reserveWidth = 0;

	int charSize;

	float textPadding = 32;

	// Constructor for no string
    Text(sf::Color color, const sf::Font& font, int charSize = 32)
		: color(color), font(font), charSize(charSize) {
		textObj = sf::Text("", font, charSize);
		textObj.setFillColor(color);
		textObj.setStyle(sf::Text::Bold);
		setPadding(8);
		setCornerRadius(32);
	}

    // Constructor for constant string
    Text(const std::string& text, sf::Color color, const sf::Font& font, int charSize = 32)
        : text(text), color(color), font(font), charSize(charSize) {
		textObj = sf::Text(text, font, charSize);
		textObj.setFillColor(color);
		textObj.setStyle(sf::Text::Bold);
    	setPadding(8);
    	setCornerRadius(32);
    }

	void setText(const std::string& string) {
	    text = string;
    }
    std::string& getText() {
        return text;
    }

	void update(sf::Vector2f position, float dt, sf::Vector2f mousePos, bool mousePressed) override {

		textObj.setString(getText());

    	this->position = position;
    	textObj.setPosition(position + sf::Vector2f(textPadding + leftPadding, textPadding + topPadding - float(charSize)/4.0f));

    	if (getText().empty()) {
    		width = 0;
    		height = 0;
    		return;
    	}

		sf::FloatRect bounds = textObj.getGlobalBounds();
    	bounds.height = float(charSize);

		width = bounds.width + 2*textPadding + leftPadding + rightPadding;
		height = bounds.height + 2*textPadding + topPadding + bottomPadding;

		width = fmaxf(width, reserveWidth);
		if (width > reserveWidth) reserveWidth= width + 20;
	}

	void draw(sf::RenderTarget& target) override {

		float rWidth = width - leftPadding - rightPadding;
		float rHeight = height - topPadding - bottomPadding;

		drawRoundedRectangle(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, bgColor, cornerRadius);
		drawRoundedOutline(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, outlineColor, outlineColor, cornerRadius, outlineThickness);

		target.draw(textObj);
	}

	void setTextPadding(float textPadding) {this->textPadding = textPadding;}
	void setReservedWidth(float reservedWidth) {this->reserveWidth = reservedWidth;}
};

#endif //TEXT_H