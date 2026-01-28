//
// Created by Andreas Royset on 1/24/26.
//

#ifndef TOGGLE_H
#define TOGGLE_H

#include "../Utils/Utils.h"
#include "Text.h"
#include "../Utils/View.h"

inline sf::Color interpolateColors(sf::Color c1, sf::Color c2, float t) {
    return {
        static_cast<uint8_t>(float(c1.r) * (1 - t) + float(c2.r) * t),
        static_cast<uint8_t>(float(c1.g) * (1 - t) + float(c2.g) * t),
        static_cast<uint8_t>(float(c1.b) * (1 - t) + float(c2.b) * t),
        static_cast<uint8_t>(float(c1.a) * (1 - t) + float(c2.a) * t)
        };
}

class Toggle final : public View {

    Text* textObj;

    bool state;

    Interpolated<float> togglePosition;

    float clickCooldown;

public:

    float toggleWidth;
    float toggleHeight;

    float padding = 8;
    float outlineThickness = 4;

    Toggle(bool state, float barWidth, float barHeight, Text* text) :
          state(state),
          toggleWidth(barWidth),
          toggleHeight(barHeight),
          textObj(text),
          togglePosition(state, 0.25),
          clickCooldown(0.25) {}

    void update(sf::Vector2f position, float dt, sf::Vector2f mousePos, bool mousePressed) override {
        togglePosition.update(dt);
        if (clickCooldown >= 0) clickCooldown -= dt;

        textObj->update(position + sf::Vector2f(leftPadding, topPadding), dt, mousePos, mousePressed);

        this->position = position;

        width = fmaxf(textObj->getWidth(), toggleWidth+2*padding) + leftPadding + rightPadding;
        height = textObj->getHeight() + toggleHeight + topPadding + bottomPadding + padding*2;

        toggleWidth = fmaxf(textObj->getWidth(), toggleWidth+2*padding) - 2*padding;

        handleInput(mousePos, mousePressed);
    }

    void handleInput(sf::Vector2f mousePos, bool mousePressed) {
        sf::Vector2f barPos = position + sf::Vector2f{leftPadding, topPadding} + sf::Vector2f{padding, textObj->getHeight() + padding};
        sf::Vector2f barEnd = barPos + sf::Vector2f{toggleWidth, toggleHeight};

        bool mouseOverBar = mousePos.x >= barPos.x && mousePos.x <= barEnd.x &&
                            mousePos.y >= barPos.y && mousePos.y <= barEnd.y;

        if (mousePressed && mouseOverBar && clickCooldown <= 0) {
            state = !state;

            togglePosition = state;

            clickCooldown = 0.25;
        }
    }

    void draw(sf::RenderTarget& target) override {

        float rWidth = width - leftPadding - rightPadding;
        float rHeight = height - topPadding - bottomPadding;

        drawRoundedRectangle(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, bgColor, cornerRadius);
        drawRoundedOutline(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, outlineColor, outlineColor, cornerRadius, outlineThickness);

        sf::Vector2f startPos = position + sf::Vector2f{leftPadding, topPadding} + sf::Vector2f{padding, textObj->getHeight() + padding};

        const float t = togglePosition.get();
        const sf::Color bgC = interpolateColors(
            sf::Color(57, 57, 57),
            sf::Color::White,
            t
            );

        drawRoundedRectangle(target, startPos, toggleWidth, toggleHeight, bgC, cornerRadius-padding);
        drawRoundedRectangle(target, startPos+sf::Vector2f(outlineThickness + (toggleWidth/2-outlineThickness) * togglePosition.get(), outlineThickness), (toggleWidth-2*outlineThickness)/2, toggleHeight-2*outlineThickness, bgColor, cornerRadius-padding-outlineThickness);

        textObj->draw(target);
    }

    [[nodiscard]] bool getValue() const {return state;}
};

#endif //TOGGLE_H
