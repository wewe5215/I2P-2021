//
//  E_Bullet.cpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/6/4.
//

#include "E_Bullet.hpp"
#include "Collider.hpp"
#include "Enemy.hpp"
#include "GameEngine.hpp"
#include "Group.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Sprite.hpp"
#include "Turret.hpp"
PlayScene* E_Bullet::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}
void E_Bullet::OnExplode(Turret* turret) {
}
E_Bullet::E_Bullet(std::string img, float speed, float damage, Engine::Point position, Engine::Point forwardDirection, float rotation, Enemy* parent) :
    Sprite(img, position.x, position.y), speed(speed), damage(damage),parent(parent) {
    Velocity = forwardDirection * speed;
    Rotation = rotation;
    CollisionRadius = 4;
}
void E_Bullet::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->TowerGroup->GetObjects()) {
        Turret* turret = dynamic_cast<Turret*>(it);
        if (!turret->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, turret->Position, turret->CollisionRadius)) {
            OnExplode(turret);
            turret->Hit(damage);
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }
    // Check if out of boundary.
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
        getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
