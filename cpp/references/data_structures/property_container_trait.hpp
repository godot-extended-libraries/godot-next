#ifndef PROPERTY_HOLDER_HPP
#define PROPERTY_HOLDER_HPP

#include <Godot.hpp>

#include "hash_map.hpp"
#include "set.hpp"

namespace godot {

	class PropertyContainerTrait {
	protected:
		virtual HashMap<String, Variant> &get_property_map() = 0;

		void _set_property(String p_property, Variant p_value);

		Variant _get_property(String p_property);

		bool _has_property(String p_property);

		// ## PropertyContainerTrait (GDScript) ######################### //

		void set_properties(const Dictionary &p_data);

		void merge_properties(const Dictionary &p_data);

		void insert_properties(const Dictionary &p_data);

		void erase_properties(const Array &p_names);

		const Dictionary &get_properties(Dictionary &r_properties);

	public:
		// ## PropertyContainerTrait (GDNative) ######################### //

		void set_properties(const HashMap<String, Variant> &p_data);

		void merge_properties(const HashMap<String, Variant> &p_data);

		void insert_properties(const HashMap<String, Variant> &p_data);

		void erase_properties(const Set<String> &p_names);

		const HashMap<String, Variant> &get_properties();
	};
} // namespace godot
#endif /* !PROPERTY_HOLDER_HPP */
