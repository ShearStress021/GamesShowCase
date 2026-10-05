#pragma once

#include "startScene.hpp"
#include <variant>


namespace dominion {

	using Scene = std::variant<std::monostate,StartScene>;

	inline void switchScenes(Scene &scene, SceneId id,TextureHandler& tex){
		switch(id){
			case SceneId::Load: scene.emplace<StartScene>(tex); break;
			case SceneId::Quit: break;

		}

	}

	template<class... Ts>
	struct overloaded : Ts... {using Ts::operator()...;};


	inline Next updateScene(Scene& scene, float dt){
		return std::visit(overloaded{
				[](std::monostate) -> Next { return {} ;},
				[dt](auto &s) -> Next { return s.update(dt); }
				}, scene);

	}

	inline void renderScene(const Scene& scene){
		std::visit(overloaded{
				[](std::monostate) {},
				[](const auto& s) {s.render();}
				},scene);
	}

}
