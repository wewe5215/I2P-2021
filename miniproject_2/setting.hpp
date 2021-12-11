//
//  setting.hpp
//  miniproject2
//
//  Created by 朱季葳 on 2021/5/23.
//

#ifndef setting_hpp
#define setting_hpp

#include <stdio.h>
#include <allegro5/allegro_audio.h>
#include <memory>
#include "IScene.hpp"

class Setting final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit Setting() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void BGMSlideOnValueChanged(float value);
    void SFXSlideOnValueChanged(float value);
};

#endif /* setting_hpp */
