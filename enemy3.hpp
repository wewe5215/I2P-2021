//
//  enemy3.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//

#ifndef enemy3_hpp
#define enemy3_hpp

#include <stdio.h>
#include "Enemy.hpp"

class Enemy3 : public Enemy {
public:
    Enemy3(int x, int y);
    void CreateBullet() override;
};

#endif /* enemy3_hpp */
