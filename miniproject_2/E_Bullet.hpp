//
//  E_Bullet.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/4.
//

#ifndef E_Bullet_hpp
#define E_Bullet_hpp

#include <stdio.h>
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class E_Bullet : public Engine::Sprite {
protected:
    float speed;
    float damage;
    Enemy* parent;
    PlayScene* getPlayScene();
    virtual void OnExplode(Turret* turret);
public:
    Turret* Target = nullptr;
    explicit E_Bullet(std::string img, float speed, float damage,  Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
    void Update(float deltaTime) override;
};
#endif /* E_Bullet_hpp */
