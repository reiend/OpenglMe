

#ifndef WINDOW_UTILS_H
#define WINDW_UTILS_H


#include <string_view>

namespace WindowInfo {
	inline constexpr int WIDTH{ 1000 };
	inline constexpr int HEIGHT{ 800 };
	inline constexpr std::string_view WINDOW_NAME{ "Reiend" };
}

namespace WindowOption {
	enum class Option {
		CLOSE,
		OPEN,
	};
}

#endif