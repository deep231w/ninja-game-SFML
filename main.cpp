#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    

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



    // //load image
    // sf::Texture texture;
    // if(!texture.loadFromFile("nbg.jpg")){
    //     return EXIT_FAILURE;
    // }



    // sf::Vector2u textureSize= texture.getSize();
    // sf::Vector2u windowSize= window.getSize();

    // float scaleX= static_cast<float>(windowSize.x) / textureSize.x;
    // float scaleY= static_cast<float>(windowSize.y) / textureSize.y;

    // sf::Sprite sprite(texture );

    // sprite.setScale(scaleX, scaleY);

    // //add character
    // sf::Texture ninjapixel;
    // if(!ninjapixel.loadFromFile("ninjs-pixel.png")) return EXIT_FAILURE;




    const float speed= 200.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //movement ninja character
        sf::Vector2f NinjaMovement(0.f , 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) NinjaMovement.x -=0.5f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) NinjaMovement.x +=0.5f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) NinjaMovement.y -=0.2f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  NinjaMovement.y +=0.2f;

        if(NinjaMovement !=sf::Vector2f(0.f ,0.f)){
            NinjaMovement= NinjaMovement*(speed * clock.restart().asSeconds());
            ninjaSprite.move(NinjaMovement);
        }
        ninjaSprite.move(NinjaMovement);


        window.clear();
        window.draw(spriteBg1);
        window.draw(ninjaSprite);
        window.display();
    }
}
