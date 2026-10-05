#pragma once
#include "scene.hpp"
//#include "hero.hpp"



namespace dominion {


	class MenuScene : public Scene {

		private:
//			Hero hero{};

		public:
			MenuScene() ;
			~MenuScene() = default;

			void update() override;
			void render() override;
			void fixedUpdate() override;
			std::shared_ptr<Scene> change() override;





	};

}

