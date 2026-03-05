#pragma once
#include <list>
#include <memory>
#include <iostream>


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

			virtual void start();

			virtual std::shared_ptr<GameScene> update();

		protected:
			std::list< std::shared_ptr<BaseActor>> actors{};

			bool exit{};

			int groundYPos{};








		
	};

}
