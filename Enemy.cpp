#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <utility>
#include "AudioHelper.hpp"
#include "Bullet.hpp"
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "ExplosionEffect.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IScene.hpp"
#include "LOG.hpp"
#include "PlayScene.hpp"
#include "Turret.hpp"

PlayScene* Enemy::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void Enemy::OnExplode() {
	getPlayScene()->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distId(1, 3);
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 20);
	for (int i = 0; i < 10; i++) {
		// Random add 10 dirty effects.
		getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-" + std::to_string(distId(rng)) + ".png", dist(rng), Position.x, Position.y));
	}
}
Enemy::Enemy(std::string img, float x, float y, float radius, float speed_x,float speed_y, float hp, int money,float coolDown) :
	Engine::Sprite(img, x, y), speed_x(speed_x),speed_y(speed_y), hp(hp), money(money),coolDown(coolDown) {
	CollisionRadius = radius;
	reachEndTime = 0;
	Velocity = Engine::Point(speed_x , speed_y);
	target = Engine::Point(PlayScene::EndGridPointx , static_cast<int>(floor(Position.y / PlayScene::BlockSize))) * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
}
void Enemy::Hit(float damage,int slow) {
	hp -= damage;
	if (hp <= 0) {
		OnExplode();
		// Remove all turret's reference to target.
		for (auto& it: lockedTurrets)
			it->Target = nullptr;
		for (auto& it: lockedBullets)
			it->Target = nullptr;
		getPlayScene()->EarnMoney(money);
		getPlayScene()->EnemyGroup->RemoveObject(objectIterator);
		AudioHelper::PlayAudio("explosion.wav");
	}
    if(slow==1)
    {
        Velocity.x=Velocity.x/2;
        Velocity.y=Velocity.y/2;
    }
}
void Enemy::Update(float deltaTime) {
	float remainSpeed = speed_x * deltaTime;
    PlayScene* scene = getPlayScene();
    float nearturret=0;
    int dist=INFINITY;
    int temp=Position.x-Velocity.x*deltaTime;
    for(auto it :getPlayScene()->TowerGroup->GetObjects())
    {
       
        if(temp-(it->Position.x+it->Size.x)<dist&&
           (it->Position.y>=Position.y&&
           it->Position.y<Position.y+scene->BlockSize))
        {
            nearturret=it->Position.x+it->Size.x;
        }
    }
    if(Position.x-nearturret>=10)
    {
        
        Position.x -= Velocity.x * deltaTime;
        Position.y += Velocity.y * deltaTime;
    }
   
	
    if(Position.y>=790)Velocity.y=-Velocity.y;
    else if(Position.y<=50)Velocity.y=-Velocity.y;
	if(Position.x <= PlayScene::EndGridPointx * PlayScene::BlockSize + PlayScene::BlockSize / 2){
		Hit(hp,0);
		getPlayScene()->Hit();
		reachEndTime = 0;
		return;
	}
	Engine::Point vec = target - Position;
	reachEndTime = (vec.Magnitude() - remainSpeed) / speed_x;
//    Sprite::Update(deltaTime);
   
    if(!Enabled)return;
    if (Target) {

        if (Target->Position.x > Position.x&& Target->Position.y >= Position.y  && Target->Position.y < Position.y+scene->BlockSize) {
            Target->lockedEnemies.erase(lockedEnemyIterator);
            Target = nullptr;
            lockedEnemyIterator = std::list<Enemy*>::iterator();
        }
        // Shoot reload.
        reload -= deltaTime;
        if (reload <= 0) {
            // shoot.
            reload = coolDown;
            CreateBullet();
        }
    }
    if (!Target) {
        // Lock first seen target.
        // Can be improved by Spatial Hash, Quad Tree, ...
        // However simply loop through all enemies is enough for this program.
        Position.x -= Velocity.x * deltaTime;
        Position.y += Velocity.y * deltaTime;
        for (auto& it : scene->TowerGroup->GetObjects()) {
            if (it->Position.x < Position.x && it->Position.y >= Position.y  && it->Position.y < Position.y+scene->BlockSize) {
                Target = dynamic_cast<Turret*>(it);
                Target->lockedEnemies .push_back(this);
                lockedEnemyIterator = std::prev(Target->lockedEnemies.end());
                
                break;
            }
        }
    }
    
}
void Enemy::Draw() const {
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw collision radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(255, 0, 0), 2);
	}
}
