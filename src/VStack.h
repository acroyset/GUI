//
// Created by Andreas Royset on 1/23/26.
//

#ifndef VSTACK_H
#define VSTACK_H
#include "View.h"

class VStack final : public View {
	std::vector<View*> items;

public:

	float spacing = 0;

	void update(sf::Vector2f position) override {

		int numItems = int(items.size());

		this->position = position;

		position.x += leftPadding;
		position.y += topPadding;

		float minWidthOfStack = 0.0f;

		float totalHeight = 0;

		for (int i = 0; i < numItems; i++) {
			View* item = items[i];
			item->update(position);
			float itemHeight = item->getHeight();
			float itemWidth = item->getWidth();
			totalHeight += itemHeight;

			if (itemWidth > minWidthOfStack) {
				minWidthOfStack = itemWidth;
			}

			position.y += itemHeight;
		}

		width = minWidthOfStack + leftPadding + rightPadding;
		height = totalHeight + topPadding + bottomPadding;
	}

	void draw(sf::RenderTarget& target) const override {

		float rWidth = width - leftPadding - rightPadding;
		float rHeight = height - topPadding - bottomPadding;

		drawRoundedRectangle(target, position + sf::Vector2f{leftPadding, topPadding}, rWidth, rHeight, bgColor, cornerRadius);

		for (const View* item : items) {
			item->draw(target);
		}
	}

	void addItem(View* item) {
		items.emplace_back(item);
	}
};

#endif //VSTACK_H
