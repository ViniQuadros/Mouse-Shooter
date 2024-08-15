#include <vector>
#include <random>
#include "Enemy.h"

int main()
{
    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;

    // Criação da Janela
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Mouse Shooter");
    // Limita o FPS
    window.setFramerateLimit(60.0f);

    //Semente para geração de numeros aleatórios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //Vetor para armazenar inimigos
    std::vector<Enemy> enemies;
    //Velocidade do inimigo
    float speed = 70;

    //Clock para controlar tempo do spawn
    sf::Clock spawnClock;
    sf::Time spawnInterval = sf::seconds(1.0f);

    // Criação da classe que cuidará do tempo de programa
    sf::Clock clock;
    float dt;

    // Mira
    sf::Texture texture;
    if (!texture.loadFromFile("C:\\Users\\vinicius.quadros\\source\\repos\\Mouse Shooter\\images\\Aim.png"))
    {
        std::cout << "Error loading texture!" << std::endl;
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    //Background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("C:\\Users\\vinicius.quadros\\source\\repos\\Mouse Shooter\\images\\Background.png"))
    {
        std::cout << "Error loading bgTexture!" << std::endl;
        return -1;
    }
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgTexture);
    bgSprite.setOrigin(bgTexture.getSize().x / 2, bgTexture.getSize().y / 2);
    bgSprite.setPosition(sf::Vector2f(400, 300));

    //Score
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("sans.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }
    sf::Text text;
    text.setFont(font);
    text.setPosition(screenWidth / 2, 10);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);

    //Lives
    int lives = 3;
    sf::Font lifeFont;
    if (!lifeFont.loadFromFile("sans.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }
    sf::Text lifeText;
    lifeText.setFont(lifeFont);
    lifeText.setPosition(screenWidth / 2, 50);
    lifeText.setCharacterSize(30);
    lifeText.setFillColor(sf::Color::White);

    //Game Over
    sf::Font overFont;
    if (!overFont.loadFromFile("sans.ttf"))
    {
        std::cout << "Error loading font!" << std::endl;
        return -1;
    }
    sf::Text overText;
    overText.setFont(overFont);
    overText.setPosition(screenWidth / 2, screenHeight / 2);
    overText.setCharacterSize(50);
    overText.setFillColor(sf::Color::White);
    //Desenha o texto de Game Over
    overText.setString("Game Over!");
    sf::FloatRect overBounds = overText.getGlobalBounds(); //Variável para centralizar o texto
    overText.setOrigin(overBounds.width / 2.0f, overBounds.height / 2.0f); //Centraliza a origem do texto

    //Variável do jogo pausar
    bool isPaused = false;

    // Roda enquanto "window" estiver funcionando 
    while (window.isOpen())
    {
        dt = clock.restart().asSeconds();
        //std::cout << "FPS: " << 1.0f / dt << std::endl;

        // Checa todos os eventos
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Fecha a janela
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                for (auto it = enemies.begin(); it != enemies.end();)
                {

                    //Verifica se houve a interação
                    if (it->contains(mousePosition))
                    {
                        //Apaga o inimigo
                        it = enemies.erase(it);
                        score++;

                        if (score % 10 == 0)
                        {
                            speed *= 2;
                        }
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }

        if (!isPaused)
        {
            // Atualiza a posição dos inimigos e remove os que saíram da tela
            for (auto it = enemies.begin(); it != enemies.end();)
            {
                // Remove o inimigo se sua posição y for maior que a altura da tela
                if (it->getPos().y > screenHeight)
                {
                    it = enemies.erase(it);
                    lives--;

                    if (lives == 0)
                    {
                        isPaused = true;
                    }
                }
                else
                {
                    ++it;
                }
            }

            // Obter a posição do mouse
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

            // Atualizar a posição do sprite
            sprite.setPosition(worldPosition);

            //Colisão da Tela
            //Colisão Esquerda
            if (sprite.getPosition().x - texture.getSize().x / 2 < 0)
            {
                sprite.setPosition(texture.getSize().x / 2, sprite.getPosition().y);
            }
            //Colisão Topo
            if (sprite.getPosition().y - texture.getSize().y / 2 < 0)
            {
                sprite.setPosition(sprite.getPosition().x, texture.getSize().y / 2);
            }
            //Colisão Direita
            if (sprite.getPosition().x + texture.getSize().x / 2 > screenWidth)
            {
                sprite.setPosition(screenWidth - texture.getSize().x / 2, sprite.getPosition().y);
            }
            //Colisão Baixo
            if (sprite.getPosition().y + texture.getSize().y / 2 > screenHeight)
            {
                sprite.setPosition(sprite.getPosition().x, screenHeight - texture.getSize().y / 2);
            }

            if (spawnClock.getElapsedTime() >= spawnInterval)
            {
                //Gera posição aleatória na tela
                float x = static_cast<float>(std::rand() % screenWidth);

                //Cria inimigo na posição aleatória
                if (x > 10 && x < 590)
                {
                    enemies.emplace_back(sf::Vector2f(x, 50));
                }

                //Reinicia o spawn
                spawnClock.restart();
            }

            window.clear();

            //Background
            window.draw(bgSprite);

            // Desenha todos os inimigos
            for (auto& enemy : enemies)
            {
                enemy.draw(window);
                enemy.move(sf::Vector2f(0, speed * dt));
            }

            //Desenha o texto do Score
            text.setString("Score: " + std::to_string(score));
            sf::FloatRect textBounds = text.getGlobalBounds(); //Variável para centralizar o texto
            text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f); //Centraliza a origem do texto
            window.draw(text);

            //Desenha o texto das Vidas
            lifeText.setString("Lives: " + std::to_string(lives));
            sf::FloatRect livesBounds = lifeText.getGlobalBounds(); //Variável para centralizar o texto
            lifeText.setOrigin(livesBounds.width / 2.0f, livesBounds.height / 2.0f); //Centraliza a origem do texto
            window.draw(lifeText);

            //Desenha o sprite do Mouse
            window.draw(sprite);

            if (isPaused)
            {
                window.draw(overText);
            }

            window.display();
        }
    }

    return 0;
}
