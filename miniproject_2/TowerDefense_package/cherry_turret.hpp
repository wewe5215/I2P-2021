//
//  cherry_turret.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/5.
//

#ifndef cherry_turret_hpp
#define cherry_turret_hpp

#include <stdio.h>
#include "Turret.hpp"

class Cherry_Turret: public Turret {
public:
    static const int Price;
    Cherry_Turret(float x, float y);
    void CreateBullet() override;
    void Draw() const override;
    void Update(float deltaTime) override;
    virtual void OnExplode(Enemy* enemy);
};
#endif /* cherry_turret_hpp */
