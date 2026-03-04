#pragma once
#include <list>
#include <memory>


namespace game {

	class BaseActor;

	class GameScene 
	{
		public:
			GameScene();
			virtual ~GameScene();

			virtual void loadGameResources();

			virtual void freeGameResources();

			virtual void draw();

		protected:
			std::list< std::shared_ptr<BaseActor>> actors{};

			int groundYPos{};








		
	};

}
