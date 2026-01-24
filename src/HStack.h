//
// Created by Andreas Royset on 1/23/26.
//

#ifndef HSTACK_H
#define HSTACK_H
#include "View.h"

class HStack final : public View {
	std::vector<View*> items;

public:

	float spacing = 0;

	void update(sf::Vector2f position) override {


		int numItems = int(items.size());

		this->position = position;

		position.x += leftPadding;
		position.y += topPadding;

		float minHeightOfStack = 0.0f;

		float totalWidth = 0;

		for (int i = 0; i < numItems; i++) {
			View* item = items[i];
			item->update(position);
			float itemHeight = item->getHeight();
			float itemWidth = item->getWidth();
			totalWidth += itemWidth;

			if (itemHeight > minHeightOfStack) {
				minHeightOfStack = itemHeight;
			}

			position.x += itemWidth;
		}

		width = totalWidth + leftPadding + rightPadding;
		height = minHeightOfStack + topPadding + bottomPadding;
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

#endif //HSTACK_H
