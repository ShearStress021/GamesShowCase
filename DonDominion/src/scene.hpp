#pragma once
#include <memory>
#include <deque>

namespace dominion {
	class Scene;

	using ScenePtr = std::unique_ptr<Scene>;
	using Scenes = std::deque<ScenePtr>;

	class Scene {
		public:
			bool quitScene = false;

			Scene() = default;
			virtual ~Scene() = default;
			

			virtual void update() = 0;
			virtual void render() = 0;
			virtual void change(Scenes& scenes) = 0;
	};

}
