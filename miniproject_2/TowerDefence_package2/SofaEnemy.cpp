#include <string>

#include "SofaEnemy.hpp"
#include <allegro5/base.h>
#include <cmath>
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include "enemy_bullet2.hpp"
//Enemy(std::string img, float x, float y, float radius, float speed_x,float speed_y, float hp, int money,float coolDown);
SofaEnemy::SofaEnemy(int x, int y) : Enemy("play/enemy-2.png", x, y, 16, 100,0, 10, 10,0.5) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

void SofaEnemy::CreateBullet()
{
    Engine::Point diff = Engine::Point(-1,0);
    float rotation = ALLEGRO_PI / 2;
    getPlayScene()->BulletGroup->AddNewObject(new enemy_bullet2(Position , diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
    
}
