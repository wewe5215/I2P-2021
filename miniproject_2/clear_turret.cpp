//
//  clear_turret.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/5.
//

#include "clear_turret.hpp"
#include <allegro5/base.h>
#include <cmath>
#include <string>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Enemy.hpp"
#include "Collider.hpp"
#include "GameEngine.hpp"
#include "IObject.hpp"
#include "IScene.hpp"

//Turret(/*std::string imgBase,*/std::string imgTurret, float x, float y,/* float radius,*/ int price, float coolDown,float hp);
const int Clear_Turret::Price = 0;
Clear_Turret::Clear_Turret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
    Turret("play/turret-5.png", x, y,0, 0,1) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
        CollisionRadius=4;
        isFunctionT=true;
}
void Clear_Turret:: CreateBullet() {}
//copy the code in enemy::draw
void Clear_Turret:: Draw() const
{
    //void al_draw_circle(float cx, float cy, float r, ALLEGRO_COLOR color,float thickness)
    Sprite::Draw();//or the turret may disappear
   
    
}
void Clear_Turret::OnExplode(Turret* turret){}
void Clear_Turret::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if(!Enabled)return;
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->TowerGroup->GetObjects()) {
        Turret* turret = dynamic_cast<Turret*>(it);
        if (!turret->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
            turret->Hit(INFINITY);
            return;
        }
    }
    getPlayScene()->TowerGroup->RemoveObject(objectIterator);
    getPlayScene()->mapState[Position.y/getPlayScene()->BlockSize][Position.x/getPlayScene()->BlockSize]=getPlayScene()->TILE_DIRT;
    // Check if out of boundary.
   
}
