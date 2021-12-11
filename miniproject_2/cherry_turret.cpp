//
//  cherry_turret.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/5.
//

#include "cherry_turret.hpp"
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
const int Cherry_Turret::Price = 35;
Cherry_Turret::Cherry_Turret(float x, float y) :
    // TODO 2 (2/8): You can imitate the 2 files: 'FreezeTurret.hpp', 'FreezeTurret.cpp' to create a new turret.
    Turret("play/turret-3.png", x, y, Price, 0,1) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    CollisionRadius=150;
}
void Cherry_Turret:: CreateBullet() {}
//copy the code in enemy::draw
void Cherry_Turret:: Draw() const
{
    //void al_draw_circle(float cx, float cy, float r, ALLEGRO_COLOR color,float thickness)
    Sprite::Draw();//or the turret may disappear
    al_draw_circle(Position.x, Position.y, 150, al_map_rgb(255, 0, 0), 2);
    
}
void Cherry_Turret::OnExplode(Enemy *enemy){}
void Cherry_Turret::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    if (!Enabled)
        return;
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        if (!enemy->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
            enemy->Hit(INFINITY,0);
            
            return;
        }
    }
    this->Hit(INFINITY);
    // Check if out of boundary.
   
}
