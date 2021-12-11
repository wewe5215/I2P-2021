//
//  turret3.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//

#ifndef turret3_hpp
#define turret3_hpp

#include "Turret.hpp"

class Turret3: public Turret {
public:
    static const int Price;
    Turret3(float x, float y);
    void CreateBullet() override;
};
#endif /* turret3_hpp */
