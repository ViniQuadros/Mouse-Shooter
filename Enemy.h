#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
public:
	Enemy(sf::Vector2f position); //Construtor que terá a posição inicial do objeto
	int draw(sf::RenderWindow& window); //Função para desenhar o objeto
	void move(sf::Vector2f direction);
	bool contains(sf::Vector2f point); //Função para verificar se há colisão com o objeto
	sf::Vector2f getPos();

private:
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	int size;
};
