#pragma once

#include <iostream>
#include <vector>
#include "SpriteModule/Animation.hpp"

using AnimationId = int32_t;

class SpriteModule
{
public:

	AnimationId createAnimation(const std::string& atlasPath, const std::string& configFilePath, bool isLooping);
	std::shared_ptr<Animation> getAnimation(AnimationId id) const;
	void update(float deltaTime);

private:
	std::unordered_map<AnimationId, std::shared_ptr<Animation>> m_animations;
	AnimationId animId = -1;

};

