#include "scene.hpp"




namespace dominion {

	namespace 
	{

		constexpr float maxDT    = 0.25f;
		constexpr float fadeTime = 0.4f;
	}


	void Scene::updateStateLogic() {

		realDt = GetFrameTime();
		dt = std::min(maxDT, realDt);


	   if (fadingIn) {
		  updateFadingIn();
		  return;
	   } else if (fadingOut) {
		  updateFadingOut();
		  return;
	   }

	   update();

	}


	void Scene::updateFadingIn() {
	   fadeTimer += realDt;
	   alpha = 1.f - fadeTimer / fadeTime;

	   if (fadeTimer >= fadeTime) {
		  fadeTimer = 0.f;
		  alpha = 0.f;
		  fadingIn = false;
	   }

	}

	void Scene::updateFadingOut() {
	   fadeTimer += realDt;
	   alpha = fadeTimer / fadeTime;

	   if (fadeTimer >= fadeTime) {
		  alpha = 1.f;
		  fadingOut = false;
		  quitScene= true;
	   }

	}

}

