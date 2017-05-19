#ifndef Aliens_H
#define Aliens_H

#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>

class Aliens{
    friend class Boss;                      //friend class
public:
    Aliens() {};                            //empty constructor
    Aliens(float x, float y);               //constructor get 2 float for postion (x,y)
    void print(sf::RenderWindow &window);   //print function
    bool isAlive = true;                    //check is alive
    void Kill();                            //kill function
    sf::Sprite & getSprite();               //like a getter for the sprite

private:
    //SFML sprite and texture ref: https://www.sfml-dev.org/tutorials/2.4/graphics-sprite.php
    sf::Texture photo;                      //Texture 
    sf::Sprite aliens;                      //Sprite
};

Aliens::Aliens(float x, float y){           //constructor, argument (x,y) cord
    aliens.setPosition(x, y);               //set the aliens position (x,y)

}
sf::Sprite & Aliens::getSprite(){           //getter for the sprite
    return aliens;                          //return the aliens sprite
}

void Aliens::print(sf::RenderWindow &window) {      //print function, argument is the window
    photo.loadFromFile("alien.png");	            //load the texture
    aliens.setTexture(photo);                       //set the sprite to "alien.png" (in the other words: set aliens = alien.png"
    if (isAlive) {                                  //if the alien alive = true then draw the aliens 
        window.draw(aliens);                        //draw != display, draw is like a buffer
    }
}

void Aliens::Kill() {                       //bang. GG
    isAlive = false;                        //rip
}

#endif // !Aliens_H
