#ifndef INTERSECT_H
#define INTERSECT_H

#include <SFML/Graphics.hpp>   
#include <Ship.h>
#include <Bullet.h>
#include <Aliens.h>
#include <AliensBullet.h>

class Intersect {
public:
    //function overloading
    static bool isTouch(Ship &, Aliens &);                  //check is the ship touch the aliens
    static bool isTouch(Bullet &, Aliens &);                //check is the bullet touch the aliens
    static bool isTouch(AliensBullet &, Ship &);            //check is the aliens bullet touch the ship
    static bool isTouch(AliensBullet &, Bullet &);          //check is the aliens bullet hit the bullet
};

bool Intersect::isTouch(Bullet &b_obj, Aliens &a_obj) {                             //Ref: https://www.sfml-dev.org/tutorials/2.4/graphics-transform.php
                                                                                    //FloatRect is a SFML class, which is let you define the bounding box
    sf::FloatRect Bullet_BoundingBox = b_obj.getSprite().getGlobalBounds();         //Bounding box for bullet    

    sf::FloatRect Alien_BoundingBox = a_obj.getSprite().getGlobalBounds();          //Bounding box for aliens           

                                                                                    //ref for intersects: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Rect.php
    return Bullet_BoundingBox.intersects(Alien_BoundingBox);                        //intersects is a FloatRect member function, which check is a touching b ( eg. a.intersects(b); )
}

bool Intersect::isTouch(Ship &s_obj, Aliens &a_obj) {
    sf::FloatRect Ship_BoundingBox = s_obj.getSprite().getGlobalBounds();           //Bounding box for ship

    sf::FloatRect Alien_BoundingBox = a_obj.getSprite().getGlobalBounds();          //Bounding box for aliens

    return Ship_BoundingBox.intersects(Alien_BoundingBox);                          //intersects is a FloatRect member function, which check is a touching b ( eg. a.intersects(b); )
}

bool Intersect::isTouch(AliensBullet &ab_obj, Ship &s_obj) {
    sf::FloatRect Ship_BoundingBox = s_obj.getSprite().getGlobalBounds();           //Bounding box for SHip

    sf::FloatRect AlienBullet_BoundingBox = ab_obj.getSprite().getGlobalBounds();   //Bounding box for alien's bullet

    return Ship_BoundingBox.intersects(AlienBullet_BoundingBox);                    //intersects is a FloatRect member function, which check is a touching b ( eg. a.intersects(b); )
}

bool Intersect::isTouch(AliensBullet &ab_obj, Bullet &b_obj) {
    sf::FloatRect AlienBullet_BoundingBox = ab_obj.getSprite().getGlobalBounds();   //Bounding box for alien's bullet

    sf::FloatRect Bullet_BoundingBox = b_obj.getSprite().getGlobalBounds();         //Bounding box for bullet 

    return Bullet_BoundingBox.intersects(AlienBullet_BoundingBox);                  //intersects is a FloatRect member function, which check is a touching b ( eg. a.intersects(b); )
}

#endif // !INTERSECT_H
