//
//  enemy_bullet2.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/3.
//

#include "enemy_bullet2.hpp"
#include <allegro5/base.h>
#include <random>
#include <string>

#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
class Turret;
class Enemy;
//E_Bullet(std::string img, float speed, float damage,  Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
enemy_bullet2::enemy_bullet2(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
    E_Bullet("play/bullet-8.png", 500, 1,position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    // TODO 2 (1/8): You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void enemy_bullet2::OnExplode(Turret* turret) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), turret->Position.x, turret->Position.y));
}
