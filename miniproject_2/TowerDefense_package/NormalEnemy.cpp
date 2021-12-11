#include <string>
#include <allegro5/base.h>
#include <cmath>
#include "NormalEnemy.hpp"
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include "enemy_bullet1.hpp"
//Enemy(std::string img, float x, float y, float radius, float speed_x,float speed_y, float hp, int money,float coolDown);
NormalEnemy::NormalEnemy(int x, int y) : Enemy("play/enemy-1.png", x, y, 10, 50,0, 5, 5,0.8) {
    // TODO 2 (6/8): You can imitate the 2 files: 'NormalEnemy.hpp', 'NormalEnemy.cpp' to create a new enemy.
}
void NormalEnemy::CreateBullet()
{
    Engine::Point diff = Engine::Point(-1,0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new enemy_bullet1(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
    
}
