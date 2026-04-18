#pragma once
#include <memory>
#include "raylib.h"


namespace dominion {
	class Scene {

		public:
			Scene() = default;
			virtual ~Scene() = default;


			// virtual methods
			virtual void update() = 0;
			virtual void render() = 0;
			virtual void fixedUpdate() = 0;
			virtual std::shared_ptr<Scene> change() = 0;


			// methods
			void updateStateLogic();
		    void updateFadingIn();
		    void updateFadingOut();



			bool quitScene= false;
			bool fadingIn = true;
		    bool fadingOut = false;
		    float fadeTimer = 0.0f;

			float realDt = 0.0f; // Real DT should be used for timers, whereas DT for everything else
            float dt = 0.0f;
			float alpha = 0.0f;

	};

}

