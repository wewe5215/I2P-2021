#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>
#include <vector>
#include "Sprite.hpp"
#include "Point.hpp"
#include "E_Bullet.hpp"
class Enemy;
class PlayScene;
class E_Bullet;
class Turret: public Engine::Sprite {
protected:
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    float hp;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;//pure!!you must include it in every turret
    virtual void OnExplode();
public:
    bool Enabled = true;
    bool Preview = false;
    bool isFunctionT=false;
    Enemy* Target = nullptr;
    std::list<Enemy*> lockedEnemies;
    std::list<E_Bullet*> lockedBullets;
    Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown,float hp);
    void Update(float deltaTime) override;
    void Hit(float damage);
    void Draw() const override;
	int GetPrice() const;
};
#endif // TURRET_HPP
