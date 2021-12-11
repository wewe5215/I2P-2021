//
//  clear_turret.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/5.
//

#ifndef clear_turret_hpp
#define clear_turret_hpp

#include <stdio.h>
#include "Turret.hpp"

class Clear_Turret: public Turret {
public:
    static const int Price;
    Clear_Turret(float x, float y);
    void CreateBullet() override;
    void Draw() const override;
    void Update(float deltaTime) override;
    virtual void OnExplode(Turret* turret);
};
#endif /* clear_turret_hpp */
