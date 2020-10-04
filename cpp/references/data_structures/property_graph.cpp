
#include "property_graph.hpp"
#include "error_macros.hpp"

using namespace godot;

// ############################################################## //
// ####################### PROPERTY VERTEX ###################### //
// ############################################################## //

Set<String> &PropertyVertex::get_label_set() {
	return ((PropertyGraph *)_list_digraph)->_vertex_data[_handle].labels;
}

HashMap<String, Variant> &PropertyVertex::get_property_map() {
	return ((PropertyGraph *)_list_digraph)->_vertex_data[_handle].properties;
}

// ## PropertyVertex (GDScript) ################################# //

bool PropertyVertex::_set(String p_property, Variant p_value) {
	ERR_FAIL_COND_V(!_has_property(p_property), false);
	_set_property(p_property, p_value);
	return true;
}

Variant PropertyVertex::_get(String p_property) {
	ERR_FAIL_COND_V(!_has_property(p_property), Variant());
	return _get_property(p_property);
}

void PropertyVertex::_set_labels(Variant p_labels) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_labels.get_type() != Variant::ARRAY);
	set_labels(p_labels);
}

void PropertyVertex::_insert_labels(Variant p_labels) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_labels.get_type() != Variant::ARRAY);
	insert_labels(p_labels);
}

void PropertyVertex::_erase_labels(Variant p_labels) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_labels.get_type() != Variant::ARRAY);
	erase_labels(p_labels);
}

Array PropertyVertex::_get_labels() {
	Array ret;
	ERR_FAIL_COND_V(!is_valid(), ret);
	return get_labels(ret);
}

void PropertyVertex::_set_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	set_properties(p_data);
}

void PropertyVertex::_merge_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	merge_properties(p_data);
}

void PropertyVertex::_insert_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	insert_properties(p_data);
}

void PropertyVertex::_erase_properties(Variant p_names) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_names.get_type() != Variant::ARRAY);
	erase_properties(p_names);
}

Dictionary PropertyVertex::_get_properties() {
	Dictionary ret;
	ERR_FAIL_COND_V(!is_valid(), ret);
	return get_properties(ret);
}

// ## PropertyVertex (GDNative) ################################# //

void PropertyVertex::_init() {}

void PropertyVertex::_register_methods() {
	register_method("_set", &PropertyVertex::_set);
	register_method("_get", &PropertyVertex::_get);

	register_method("set_labels", &PropertyVertex::_set_labels);
	register_method("insert_labels", &PropertyVertex::_insert_labels);
	register_method("erase_labels", &PropertyVertex::_erase_labels);
	register_method("get_labels", &PropertyVertex::_get_labels);

	register_method("set_properties", &PropertyVertex::_set_properties);
	register_method("merge_properties", &PropertyVertex::_merge_properties);
	register_method("insert_properties", &PropertyVertex::_insert_properties);
	register_method("erase_properties", &PropertyVertex::_erase_properties);
	register_method("get_properties", &PropertyVertex::_get_properties);
}

PropertyVertex::PropertyVertex() {
}
PropertyVertex::~PropertyVertex() {
}

// ############################################################## //
// ####################### PROPERTY ARC ######################### //
// ############################################################## //

HashMap<String, Variant> &PropertyArc::get_property_map() {
	return ((PropertyGraph *)_list_digraph)->_arc_data[_handle].properties;
}

// ## PropertyArc (GDScript) #################################### //

bool PropertyArc::_set(String p_property, Variant p_value) {
	ERR_FAIL_COND_V(!_has_property(p_property), false);
	_set_property(p_property, p_value);
	return true;
}

Variant PropertyArc::_get(String p_property) {
	ERR_FAIL_COND_V(!_has_property(p_property), Variant());
	return _get_property(p_property);
}

void PropertyArc::_set_label(Variant p_label) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_label.get_type() != Variant::STRING);
	set_label(p_label);
}

void PropertyArc::_set_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	set_properties(p_data);
}

void PropertyArc::_merge_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	merge_properties(p_data);
}

void PropertyArc::_insert_properties(Variant p_data) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	insert_properties(p_data);
}

void PropertyArc::_erase_properties(Variant p_names) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_names.get_type() != Variant::ARRAY);
	erase_properties(p_names);
}

Dictionary PropertyArc::_get_properties() {
	Dictionary ret;
	ERR_FAIL_COND_V(!is_valid(), ret);
	return get_properties(ret);
}

// ## PropertyArc (GDNative) #################################### //

void PropertyArc::set_label(const String &p_label) {
	ERR_FAIL_COND(!is_valid());
	((PropertyGraph *)_list_digraph)->_arc_data[_handle].label = p_label;
}

String PropertyArc::get_label() const {
	ERR_FAIL_COND_V(!is_valid(), String());
	return ((PropertyGraph *)_list_digraph)->_arc_data[_handle].label;
}

void PropertyArc::_init() {}

void PropertyArc::_register_methods() {
	register_method("_set", &PropertyArc::_set);
	register_method("_get", &PropertyArc::_get);

	register_method("set_label", &PropertyArc::_set_label);
	register_method("get_label", &PropertyArc::get_label);

	register_method("set_properties", &PropertyArc::_set_properties);
	register_method("merge_properties", &PropertyArc::_merge_properties);
	register_method("insert_properties", &PropertyArc::_insert_properties);
	register_method("erase_properties", &PropertyArc::_erase_properties);
	register_method("get_properties", &PropertyArc::_get_properties);
}

PropertyArc::PropertyArc() {
}
PropertyArc::~PropertyArc() {
}

// ############################################################## //
// ######################## PROPERTY GRAPH ###################### //
// ############################################################## //

Ref<Vertex> PropertyGraph::get_instance(const LemonDigraph::Node &p_node) {
	return __get_instance<PropertyVertex>(p_node);
}

Ref<Arc> PropertyGraph::get_instance(const LemonDigraph::Arc &p_arc) {
	return __get_instance<PropertyArc>(p_arc);
}

// ## PropertyGraph (GDScript) ################################## //

void PropertyGraph::set_labels(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_set_labels(p_data[ref]);
			continue;
		}

		Ref<PropertyArc> arc = ref;
		if (arc.is_valid()) {
			arc->_set_label(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void PropertyGraph::_set_labels(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	set_properties(p_data);
}

void PropertyGraph::insert_labels(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_insert_labels(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!vertex.is_valid());
	}
}
void PropertyGraph::_insert_labels(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	insert_labels(p_data);
}

void PropertyGraph::erase_labels(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_erase_labels(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!vertex.is_valid());
	}
}
void PropertyGraph::_erase_labels(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	erase_labels(p_data);
}

void PropertyGraph::set_properties(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_set_properties(p_data[ref]);
			continue;
		}

		Ref<PropertyArc> arc = ref;
		if (arc.is_valid()) {
			arc->_set_properties(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void PropertyGraph::_set_properties(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	set_properties(p_data);
}

void PropertyGraph::merge_properties(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_merge_properties(p_data[ref]);
			continue;
		}

		Ref<PropertyArc> arc = ref;
		if (arc.is_valid()) {
			arc->_merge_properties(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void PropertyGraph::_merge_properties(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	merge_properties(p_data);
}

void PropertyGraph::insert_properties(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_insert_properties(p_data[ref]);
			continue;
		}

		Ref<PropertyArc> arc = ref;
		if (arc.is_valid()) {
			arc->_insert_properties(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void PropertyGraph::_insert_properties(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	insert_properties(p_data);
}

void PropertyGraph::erase_properties(const Dictionary &p_data) {
	Array refs = p_data.keys();

	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_CONTINUE(ref.get_type() != Variant::OBJECT);

		Ref<PropertyVertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->_erase_properties(p_data[ref]);
			continue;
		}

		Ref<PropertyArc> arc = ref;
		if (arc.is_valid()) {
			arc->_erase_properties(p_data[ref]);
			continue;
		}
		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void PropertyGraph::_erase_properties(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	erase_properties(p_data);
}

// ## PropertyGraph (GDNative) ################################## //

void PropertyGraph::set_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data) {
	HashMap<PropertyVertex, Set<String>, PropertyVertexHash>::const_iterator vertex_to_labels;
	for (vertex_to_labels = p_data.begin(); vertex_to_labels != p_data.end(); ++vertex_to_labels) {
		PropertyVertex *vertex = (PropertyVertex *)&vertex_to_labels->first;
		vertex->set_labels(vertex_to_labels->second);
	}
}
void PropertyGraph::set_labels(const HashMap<PropertyArc, String, PropertyArcHash> &p_data) {
	HashMap<PropertyArc, String, PropertyArcHash>::const_iterator arc_to_label;
	for (arc_to_label = p_data.begin(); arc_to_label != p_data.end(); ++arc_to_label) {
		PropertyArc *arc = (PropertyArc *)&arc_to_label->first;
		arc->set_label(arc_to_label->second);
	}
}

void PropertyGraph::insert_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data) {
	HashMap<PropertyVertex, Set<String>, PropertyVertexHash>::const_iterator vertex_to_labels;
	for (vertex_to_labels = p_data.begin(); vertex_to_labels != p_data.end(); ++vertex_to_labels) {
		PropertyVertex *vertex = (PropertyVertex *)&vertex_to_labels->first;
		vertex->insert_labels(vertex_to_labels->second);
	}
}

void PropertyGraph::erase_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data) {
	HashMap<PropertyVertex, Set<String>, PropertyVertexHash>::const_iterator vertex_to_labels;
	for (vertex_to_labels = p_data.begin(); vertex_to_labels != p_data.end(); ++vertex_to_labels) {
		PropertyVertex *vertex = (PropertyVertex *)&vertex_to_labels->first;
		vertex->erase_labels(vertex_to_labels->second);
	}
}

void PropertyGraph::set_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data) {
	__set_properties(p_data);
}
void PropertyGraph::set_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data) {
	__set_properties(p_data);
}

void PropertyGraph::merge_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data) {
	__merge_properties(p_data);
}
void PropertyGraph::merge_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data) {
	__merge_properties(p_data);
}

void PropertyGraph::insert_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data) {
	__insert_properties(p_data);
}
void PropertyGraph::insert_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data) {
	__insert_properties(p_data);
}

void PropertyGraph::erase_properties(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data) {
	__erase_properties(p_data);
}
void PropertyGraph::erase_properties(const HashMap<PropertyArc, Set<String>, PropertyArcHash> &p_data) {
	__erase_properties(p_data);
}

void PropertyGraph::_init() {}

void PropertyGraph::_register_methods() {
	register_method("set_labels", &PropertyGraph::_set_labels);
	register_method("insert_labels", &PropertyGraph::_insert_labels);
	register_method("erase_labels", &PropertyGraph::_erase_labels);

	register_method("set_properties", &PropertyGraph::_set_properties);
	register_method("merge_properties", &PropertyGraph::_merge_properties);
	register_method("insert_properties", &PropertyGraph::_insert_properties);
	register_method("erase_properties", &PropertyGraph::_erase_properties);
}

PropertyGraph::PropertyGraph() :
		_vertex_data(get_graph()),
		_arc_data(get_graph()) {
}
PropertyGraph::~PropertyGraph() {
}