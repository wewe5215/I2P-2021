//
//  friesBullet.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//


#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "friesBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

class Turret;
//Bullet(std::string img, float speed, float damage,  int slow,Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
friesBullet::friesBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
    Bullet("play/bullet-4.png", 500, 1,1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    
}
void friesBullet::OnExplode(Enemy* enemy) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
