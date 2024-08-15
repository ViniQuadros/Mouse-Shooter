#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position)
{
	this->size = 40.f;
	this->enemySprite.setPosition(position);
}

int Enemy::draw(sf::RenderWindow& window)
{
	if (!this->enemyTexture.loadFromFile("C:\\Users\\vinicius.quadros\\source\\repos\\Mouse Shooter\\images\\EnemySquare.png"))
	{
		std::cout << "Error loading texture!" << std::endl;
		return -1;
	}
	this->enemySprite.setTexture(this->enemyTexture);
	this->enemySprite.setOrigin(this->enemyTexture.getSize().x / 2, this->enemyTexture.getSize().y / 2);
	window.draw(this->enemySprite);
}

void Enemy::move(sf::Vector2f direction)
{
	this->enemySprite.move(direction);
}

bool Enemy::contains(sf::Vector2f point)
{
	return this->enemySprite.getGlobalBounds().contains(point);;
}

sf::Vector2f Enemy::getPos()
{
	return this->enemySprite.getPosition();
}

