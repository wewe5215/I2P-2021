//
//  potato_turret.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/5.
//

#ifndef potato_turret_hpp
#define potato_turret_hpp

#include <stdio.h>
#include "Turret.hpp"

class PotatoTurret: public Turret {
public:
    static const int Price;
    PotatoTurret(float x, float y);
    void CreateBullet() override;
    
};
#endif /* potato_turret_hpp */
