//
//  friesBullet.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//

#ifndef friesBullet_hpp
#define friesBullet_hpp

#include <stdio.h>
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class friesBullet : public Bullet {
public:
    explicit friesBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};
#endif /* friesBullet_hpp */
