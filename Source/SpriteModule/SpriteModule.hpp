#pragma once

#include "BaseModule/BaseModule.hpp"
#include "SpriteModule/Animation.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

using AnimationId = int32_t;

class SpriteModule : public BaseModule
{
public:
    AnimationId                createAnimation(const std::string& configFilePath);
    std::shared_ptr<Animation> getAnimation(AnimationId id) const;

    void update(float deltaTime, sf::Window* window) override;

    void terminate() override;

private:
    std::unordered_map<AnimationId, std::shared_ptr<Animation>> m_animations;
    AnimationId                                                 animId = -1;
};
