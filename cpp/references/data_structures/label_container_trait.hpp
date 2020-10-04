#ifndef LABEL_CONTAINER_TRAIT_HPP
#define LABEL_CONTAINER_TRAIT_HPP

#include <Godot.hpp>

#include "set.hpp"

namespace godot {

	class LabelContainerTrait {
	protected:
		virtual Set<String> &get_label_set() = 0;

		// ## LabelContainerTrait (GDScript) #################################### //

		void set_labels(const Array &p_labels);

		void insert_labels(const Array &p_labels);

		void erase_labels(const Array &p_labels);

		const Array &get_labels(Array &r_labels);

	public:
		// ## LabelContainerTrait (GDNative) #################################### //

		void set_labels(const Set<String> &p_data);

		void insert_labels(const Set<String> &p_data);

		void erase_labels(const Set<String> &p_names);

		const Set<String> &get_labels();
	};
} // namespace godot
#endif /* !LABEL_CONTAINER_TRAIT_HPP */
