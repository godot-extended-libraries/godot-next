
#include "label_container_trait.hpp"

#include "error_macros.hpp"

using namespace godot;

// ############################################################## //
// #################### LABEL CONTAINER TRAIT ################### //
// ############################################################## //

// ## LabelContainerTrait (GDScript) ############################ //

void LabelContainerTrait::set_labels(const Array &p_labels) {
	get_label_set().clear();
	insert_labels(p_labels);
}

void LabelContainerTrait::insert_labels(const Array &p_labels) {
	Set<String> &label_set = get_label_set();
	for (int i = 0; i < p_labels.size(); ++i) {
		ERR_CONTINUE(p_labels[i].get_type() != Variant::STRING);

		String a_label = p_labels[i];
		ERR_CONTINUE(!a_label.is_valid_identifier());

		label_set.insert(a_label);
	}
}

void LabelContainerTrait::erase_labels(const Array &p_labels) {
	Set<String> &label_set = get_label_set();
	for (int i = 0; i < p_labels.size(); ++i) {
		ERR_CONTINUE(p_labels[i].get_type() != Variant::STRING);

		label_set.erase(p_labels[i]);
	}
}

const Array &LabelContainerTrait::get_labels(Array &r_labels) {
	Set<String> &label_set = get_label_set();
	Set<String>::const_iterator name;
	for (name = label_set.begin(); name != label_set.end(); ++name) {
		r_labels.append(*name);
	}
	return r_labels;
}

// ## LabelContainerTrait (GDNative) ############################ //

void LabelContainerTrait::set_labels(const Set<String> &p_labels) {
	get_label_set().clear();
	insert_labels(p_labels);
}

void LabelContainerTrait::insert_labels(const Set<String> &p_labels) {
	get_label_set().insert(p_labels.begin(), p_labels.end());
}

void LabelContainerTrait::erase_labels(const Set<String> &p_labels) {
	Set<String>::const_iterator label;
	for (label = p_labels.begin(); label != p_labels.end(); ++label)
		get_label_set().erase(*label);
}

const Set<String> &LabelContainerTrait::get_labels() {
	return get_label_set();
}