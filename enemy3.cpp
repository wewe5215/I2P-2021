//
//  enemy3.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//


#include <string>

#include "enemy3.hpp"
#include <allegro5/base.h>
#include <cmath>
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include "enemy_bullet2.hpp"
//Enemy(std::string img, float x, float y, float radius, float speed_x,float speed_y, float hp, int money,float coolDown);
Enemy3::Enemy3(int x, int y) : Enemy("play/enemy-4.png", x, y, 30, 50,50, 100, 100,0.6) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
void Enemy3::CreateBullet()
{
    Engine::Point diff = Engine::Point(-1,0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new enemy_bullet2(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
    
}
