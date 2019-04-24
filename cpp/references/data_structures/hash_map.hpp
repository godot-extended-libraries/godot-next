#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <Godot.hpp>
#include <unordered_map>

using namespace godot;

namespace std {
	template <>
	struct hash<String> {
		size_t operator()(const String &x) const {
			return x.hash();
		}
	};
} // namespace std

namespace godot {
	template <typename K, typename V, typename H = std::hash<K> >
	using HashMap = std::unordered_map<K, V, H>;
} // namespace godot
#endif /* !HASH_MAP_HPP */
