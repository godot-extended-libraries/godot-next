#ifndef PAIR_HPP
#define PAIR_HPP

#include <map>

namespace godot {
	template <typename K, typename V>
	using Pair = std::pair<K, V>;
} // namespace godot
#endif /* !PAIR_HPP */