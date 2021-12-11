//
//  shoot_effect.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//

#ifndef shoot_effect_hpp
#define shoot_effect_hpp

#include <stdio.h>
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"

class PlayScene;

class shootEffect : public Engine::Sprite {
protected:
    PlayScene* getPlayScene();
    float timeTicks;
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
    float timeSpan = 0.5;
public:
    shootEffect(float x, float y);
    void Update(float deltaTime) override;
};
#endif /* shoot_effect_hpp */

