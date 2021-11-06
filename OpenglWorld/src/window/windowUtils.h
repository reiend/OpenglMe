
#ifndef WINDOW_OPTION_H
#define WINDOW_OPTION_H

namespace WindowUtils {
	inline constexpr int WIDTH{ 1000 };
	inline constexpr int HEIGHT{ 800 };
	inline const char* TITLE{ "Reiend" };

	enum class WindowOption {
		OPEN,
		CLOSE,
	};
}

#endif