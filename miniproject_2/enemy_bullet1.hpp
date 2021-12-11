//
//  enemy_bullet1.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/3.
//

#ifndef enemy_bullet1_hpp
#define enemy_bullet1_hpp

#include <stdio.h>
#include "E_Bullet.hpp"
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class enemy_bullet1 : public E_Bullet{
public:
    explicit enemy_bullet1(Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent);
    void OnExplode(Turret* turret) override;
};

#endif /* enemy_bullet1_hpp */
