#ifndef BOSS_H
#define BOSS_H


#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>
#include <Aliens.h>

class Boss : public Aliens{                             //inheritance
public:
    Boss() {                                            //constructor
        getSprite().setPosition(250.0, 10.0);           //set position
        getSprite().setScale(2.5, 2.5);                 //set scale of the photo (in the other words, define the size of the photo)
    }
    void print_boss(sf::RenderWindow &window) {         //print function
        photo.loadFromFile("boss.png");                 //loading photo
        aliens.setTexture(photo);                       //setting texture
        if (isAlive) {                                  //check is boss alive
            window.draw(aliens);                        //then draw boss to the buffer
        }
    }
};


#endif BOSS_H