#pragma once
#include <optional>
#include <raylib.h>


namespace dominion {
	enum class SceneId{Load,Quit};
	using Next = std::optional<SceneId>;
}






