#include <SFML/Graphics.hpp>
#include<iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    window.setFramerateLimit(60);

    std::map<std::string , sf::Texture> textures;

    if(!textures["bg1"].loadFromFile("nbg.jpg")) return EXIT_FAILURE;

    if(!textures["ninja"].loadFromFile("ninja-pixel.png")) return EXIT_FAILURE;

    sf::Sprite spriteBg1(textures["bg1"]);
    sf::Sprite ninjaSprite(textures["ninja"]);

    //setup bg size
    sf::Vector2u textureSize=textures["bg1"].getSize();
    sf::Vector2u windowSize= window.getSize();

    float scaleX= static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY= static_cast<float>(windowSize.y) / textureSize.y;

    spriteBg1.setScale(scaleX , scaleY);

    //setup ninja character position
    ninjaSprite.setPosition(100,200);

    //ground
    sf::Vertex ground[]=
    {
        sf::Vertex(sf::Vector2f(0 ,500)),
        sf::Vertex(sf::Vector2f(800,500))
    };
    ground[0].color=sf::Color::White;
    ground[1].color=sf::Color::White;

    std::cout << ninjaSprite.getGlobalBounds().width << std::endl;

    const float speed= 200.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard ::Escape)
                window.close();
        }

        //movement ninja character
        auto bounds= ninjaSprite.getGlobalBounds();
        float left= bounds.left;
        float right= bounds.left + bounds.width;

        sf::Vector2f NinjaMovement(0.f , 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ninjaSprite.getPosition().x>0) {
            NinjaMovement.x -=10.f;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && right< window.getSize().x) {
            NinjaMovement.x +=10.f;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& ninjaSprite.getPosition().y> 0) {
            NinjaMovement.y -=10.f;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ninjaSprite.getGlobalBounds().top + ninjaSprite.getGlobalBounds().height< window.getSize().y)  {
            NinjaMovement.y +=10.f;
        }

        // if(NinjaMovement !=sf::Vector2f(0.f ,0.f)){
        //     NinjaMovement= NinjaMovement*(speed * clock.restart().asSeconds());
        //     ninjaSprite.move(NinjaMovement);
        // }
        ninjaSprite.move(NinjaMovement);


        window.clear();
        window.draw(spriteBg1);
        window.draw(ninjaSprite);
        window.draw(ground , 2 , sf::Lines);
        window.display();
    }
}
