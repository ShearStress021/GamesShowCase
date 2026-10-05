
#pragma once

#include "scene.hpp"
#include <memory>


namespace dominion 
{
	class StartScene : public Scene {
		private:
			enum class Load{textures, count};
			float finalFadeTimer{0.f};
			float rotation{0.f};
			Load loadPhase = Load::textures;
			


		public:
			StartScene();
			~StartScene() = default;


			void update() override;
			void render() override;
			void fixedUpdate() override;

			std::shared_ptr<Scene> change() override;
			


	};
}


