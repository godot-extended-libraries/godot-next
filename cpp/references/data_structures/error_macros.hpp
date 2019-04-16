/*
 * author: xDGameStudios
 * description: A collection of error macros to provide better debug
 * information.
 */
#ifndef ERROR_MACROS_HPP
#define ERROR_MACROS_HPP

#include <Godot.hpp>

namespace godot {
	#ifndef ERR_CONTINUE
	#define ERR_CONTINUE(a)	\
	if (a) {				\
		WARN_PRINT(#a);		\
		continue;			\
	}
	#endif
} // namespace godot
#endif /* !ERROR_MACROS_HPP */