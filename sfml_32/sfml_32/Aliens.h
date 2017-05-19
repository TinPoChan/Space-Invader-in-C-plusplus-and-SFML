#ifndef Aliens_H
#define Aliens_H

#include <SFML/Graphics.hpp>   
#include <SFML/Audio.hpp>

class Aliens {
    friend class Boss;                       //friend class
    friend class AliensBullet;
    friend class Intersect;
public:
    Aliens() {};                             //empty constructor
    Aliens(float x, float y);                //constructor get 2 float for postion (x,y); reason of using float: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Vector2.php
    void print(sf::RenderWindow &window);    //print function
    bool isAlive = true;                     //check is alive
    void Kill();                             //kill function
    sf::Sprite & getSprite();                //getter for the sprite

protected:
    sf::Vector2f position;                   //the object postion

private:
    //SFML sprite and texture ref: https://www.sfml-dev.org/tutorials/2.4/graphics-sprite.php
    sf::Texture photo;                       //Texture 
    sf::Sprite aliens;                       //Sprite
    //SFML playing sound ref: https://www.sfml-dev.org/tutorials/2.4/audio-sounds.php
    sf::SoundBuffer buffer;                  //Sound Buffer
    sf::Sound sound;                         //Sound

};

Aliens::Aliens(float x, float y) {           //constructor, argument (x,y) cord
    photo.loadFromFile("alien.png");	     //load the texture
    aliens.setTexture(photo);                //set the sprite to "alien.png" (in the other words: set aliens = alien.png"
    aliens.setPosition(x, y);                //set the aliens position (x,y)

}
sf::Sprite & Aliens::getSprite() {           //getter for the sprite
    return aliens;                           //return the aliens sprite
}

void Aliens::print(sf::RenderWindow &window) {      //print function, argument is the window
    if (isAlive) window.draw(aliens);               //if the alien alive = true then draw the aliens   //draw != display, draw is like a buffer
}

void Aliens::Kill() {                        //bang. GG
    buffer.loadFromFile("invaderkilled.wav");//aliens die music loaded, ref: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Music.php
    sound.setBuffer(buffer);                 //set the sound as buffer 
    sound.play();                            //play it
    isAlive = false;                         //rip
}

#endif // !Aliens_H
