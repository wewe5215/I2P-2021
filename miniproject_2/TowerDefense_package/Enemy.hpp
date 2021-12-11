#ifndef ENEMY_HPP
#define ENEMY_HPP
#include <list>
#include <vector>
#include <string>

#include "Point.hpp"
#include "Sprite.hpp"

class Bullet;
class PlayScene;
class Turret;

class Enemy : public Engine::Sprite {
protected:
	Engine::Point target;
	float speed_x;
    float speed_y;
	float hp;
	int money;
    float reload=0;
    float coolDown;
    std::list<Enemy*>::iterator lockedEnemyIterator;
    PlayScene* getPlayScene();
	virtual void OnExplode();
    virtual void CreateBullet()=0;
public:
	float reachEndTime;
    bool Enabled = true;
    bool Preview = false;
    Turret* Target=nullptr;
	std::list<Turret*> lockedTurrets;
	std::list<Bullet*> lockedBullets;
	Enemy(std::string img, float x, float y, float radius, float speed_x,float speed_y, float hp, int money,float coolDown);
 	void Hit(float damage,int slow);
	void Update(float deltaTime) override;
	void Draw() const override;
};
#endif // ENEMY_HPP
