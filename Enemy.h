#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
public:
	Enemy(sf::Vector2f position); //Construtor que ter� a posi��o inicial do objeto
	int draw(sf::RenderWindow& window); //Fun��o para desenhar o objeto
	void move(sf::Vector2f direction);
	bool contains(sf::Vector2f point); //Fun��o para verificar se h� colis�o com o objeto
	sf::Vector2f getPos();

private:
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	int size;
};
