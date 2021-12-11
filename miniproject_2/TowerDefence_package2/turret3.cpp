//
//  turret3.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//


#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "friesBullet.hpp"
#include "Group.hpp"
#include "turret3.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
//Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown,float hp);
const int Turret3::Price = 80;
Turret3::Turret3(float x, float y) :
    
    Turret("play/turret-6.png", x, y, Price, 0.5,400) {
    
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret3::CreateBullet() {
    Engine::Point diff = Engine::Point(1,0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new friesBullet(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
