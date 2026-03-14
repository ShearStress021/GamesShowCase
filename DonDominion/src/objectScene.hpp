#pragma once

#include "scene.hpp"
#include "object.hpp"
#include <vector>


namespace dominion {

	class ObjectScene : public Scene 
	{
		std::vector<std::vector<Block>> blocks;
		Camera2D camera;


		public:
		   ObjectScene();
		   ~ObjectScene() = default;


		   static ScenePtr make()
		   {
			   return std::make_unique<ObjectScene>();
		   }

		   void update() override;
		   void render() override;
		   void change(Scenes& scenes) override;
	};

}



