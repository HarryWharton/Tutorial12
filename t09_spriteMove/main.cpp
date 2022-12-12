#include <assert.h>
#include <string>

#include "SFML/Graphics.hpp"
#include "Game.h"

using namespace sf;
using namespace std;


bool LoadTexture(const string& file, Texture& tex)
{
	if (tex.loadFromFile(file))
	{
		tex.setSmooth(true);
		return true;
	}
	assert(false);
	return false;
}


int main()
{
	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "My first code");

	Texture shipTex;
	LoadTexture("data/ship.png", shipTex);

	Sprite spr(shipTex);
	IntRect texR = spr.getTextureRect();
	spr.setOrigin(texR.width / 2.f, texR.height / 2.f);
	spr.setScale(0.1f, 0.1f);
	spr.setRotation(90);
	spr.setPosition(window.getSize().x*0.05f, window.getSize().y / 2.f);

	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed) 
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close(); 
			}
		} 

		// Clear screen
		window.clear();

		Vector2u screenSz = window.getSize();

		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();
		Vector2f pos = spr.getPosition();
		const float SPEED = 250.f;
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (pos.y > (screenSz.y*0.05f))
				pos.y -= SPEED * elapsed;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (pos.y < (screenSz.y*0.95f))
				pos.y += SPEED * elapsed;
		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (pos.x > (screenSz.x*0.05f))
				pos.x -= SPEED * elapsed;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (pos.x < (screenSz.x*0.95f))
				pos.x += SPEED * elapsed;
		}

		spr.setPosition(pos);
		window.draw(spr);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}
