#include "property_container_trait.hpp"

#include "error_macros.hpp"

// ############################################################## //
// ################## PROPERTY CONTAINER TRAIT ################## //
// ############################################################## //

void PropertyContainerTrait::_set_property(String p_property, Variant p_value) {
	get_property_map()[p_property] = p_value;
}

Variant PropertyContainerTrait::_get_property(String p_property) {
	return get_property_map()[p_property];
}

bool PropertyContainerTrait::_has_property(String p_property) {
	return get_property_map().count(p_property);
}

// ## PropertyContainerTrait (GDScript) ######################### //

void PropertyContainerTrait::set_properties(const Dictionary &p_data) {
	get_property_map().clear();
	insert_properties(p_data);
}

void PropertyContainerTrait::merge_properties(const Dictionary &p_data) {
	HashMap<String, Variant> &prop_map = get_property_map();
	Array p_names = p_data.keys();
	for (int i = 0; i < p_names.size(); ++i) {
		ERR_CONTINUE(p_names[i].get_type() != Variant::STRING);

		String a_name = p_names[i];
		ERR_CONTINUE(!a_name.is_valid_identifier());

		prop_map[a_name] = p_data[a_name];
	}
}

void PropertyContainerTrait::insert_properties(const Dictionary &p_data) {
	HashMap<String, Variant> &prop_map = get_property_map();
	Array p_names = p_data.keys();
	for (int i = 0; i < p_names.size(); ++i) {
		ERR_CONTINUE(p_names[i].get_type() != Variant::STRING);

		String a_name = p_names[i];
		ERR_CONTINUE(!a_name.is_valid_identifier());

		if (prop_map.count(a_name))
			continue;
		prop_map[a_name] = p_data[a_name];
	}
}

void PropertyContainerTrait::erase_properties(const Array &p_names) {
	HashMap<String, Variant> &prop_map = get_property_map();
	for (int i = 0; i < p_names.size(); ++i) {
		ERR_CONTINUE(p_names[i].get_type() != Variant::STRING);

		prop_map.erase(p_names[i]);
	}
}

const Dictionary &PropertyContainerTrait::get_properties(Dictionary &r_properties) {
	HashMap<String, Variant> &prop_map = get_property_map();
	HashMap<String, Variant>::const_iterator name_to_value;
	for (name_to_value = prop_map.begin(); name_to_value != prop_map.end(); ++name_to_value) {
		r_properties[name_to_value->first] = name_to_value->second;
	}
	return r_properties;
}

// ## PropertyContainerTrait (GDNative) ######################### //

void PropertyContainerTrait::set_properties(const HashMap<String, Variant> &p_data) {
	HashMap<String, Variant>::const_iterator name_to_value;
	get_property_map().clear();
	insert_properties(p_data);
}

void PropertyContainerTrait::merge_properties(const HashMap<String, Variant> &p_data) {
	HashMap<String, Variant> &prop_map = get_property_map();
	HashMap<String, Variant>::const_iterator name_to_value;
	for (name_to_value = p_data.begin(); name_to_value != p_data.end(); ++name_to_value) {
		prop_map[name_to_value->first] = name_to_value->second;
	}
}

void PropertyContainerTrait::insert_properties(const HashMap<String, Variant> &p_data) {
	get_property_map().insert(p_data.begin(), p_data.end());
}

void PropertyContainerTrait::erase_properties(const Set<String> &p_names) {
	HashMap<String, Variant> &prop_map = get_property_map();
	Set<String>::const_iterator a_name;
	for (a_name = p_names.begin(); a_name != p_names.end(); ++a_name) {
		prop_map.erase(*a_name);
	}
}

const HashMap<String, Variant> &PropertyContainerTrait::get_properties() {
	return get_property_map();
}