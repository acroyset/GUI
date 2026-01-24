//
// Created by Andreas Royset on 1/23/26.
//

#include <SFML/Graphics.hpp>
#pragma once

inline void drawRoundedRectangle(sf::RenderTarget& target, sf::Vector2f position, float width, float height, sf::Color color, float cornerRadius, int quality = 64) {
	cornerRadius = fmaxf(cornerRadius, 0.001f);

	sf::VertexArray vertices(sf::TriangleFan, quality+1);

	for (int i = 0; i < quality; i++) {
		float angle = float(i) / float(quality) * 2.0f * float(M_PI);
		sf::Vector2f pos = {cos(angle)*cornerRadius, sin(angle)*cornerRadius};

		if (pos.x < 0) pos.x += cornerRadius;
		else pos.x += width - cornerRadius;
		if (pos.y < 0) pos.y += cornerRadius;
		else pos.y += height - cornerRadius;

		pos += position;

		vertices[i].position = pos;
		vertices[i].color = color;
	}

	vertices[quality].position = vertices[0].position;
	vertices[quality].color = vertices[0].color;

	target.draw(vertices);
}

inline void drawThickLine(
	sf::RenderTarget& target,
	sf::Vector2f a,
	sf::Vector2f b,
	float thickness,
	sf::Color color
) {
	sf::Vector2f d = b - a;
	float len = std::sqrt(d.x * d.x + d.y * d.y);
	if (len == 0.f) return;

	sf::Vector2f n(-d.y / len, d.x / len);   // perpendicular normal
	sf::Vector2f off = n * (thickness * 0.5f);

	sf::VertexArray quad(sf::Triangles, 6);

	quad[0] = sf::Vertex(a + off, color);
	quad[1] = sf::Vertex(b + off, color);
	quad[2] = sf::Vertex(b - off, color);

	quad[3] = sf::Vertex(a + off, color);
	quad[4] = sf::Vertex(b - off, color);
	quad[5] = sf::Vertex(a - off, color);

	target.draw(quad);
}