#pragma once
#include <optional>
#include <raylib.h>


namespace dominion {
	enum class SceneId{Load,Game,Quit};
	using Next = std::optional<SceneId>;
}






