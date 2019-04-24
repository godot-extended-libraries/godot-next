#include "list_digraph.hpp"
#include "error_macros.hpp"

using namespace godot;

// ############################################################## //
// ########################### VERTEX ########################### //
// ############################################################## //

// ## Vertex (GDScript) ######################################### //

void Vertex::_contract(const Variant p_other, const Variant p_remove) {
	ERR_FAIL_COND(p_other.get_type() != Variant::OBJECT);
	ERR_FAIL_COND(p_remove.get_type() != Variant::BOOL);
	contract(p_other, p_remove);
}

Ref<Vertex> Vertex::_split(const Variant p_connect) {
	ERR_FAIL_COND_V(p_connect.get_type() != Variant::BOOL, nullptr);
	return split(p_connect);
}

Array Vertex::_get_incoming_arcs() const {
	Array ret;
	ERR_FAIL_COND_V(!_list_digraph->_graph.valid(_handle), ret);
	for (LemonDigraph::InArcIt it(_list_digraph->_graph, _handle); it != lemon::INVALID; ++it) {
		ret.append(_list_digraph->get_instance(it));
	}
	return ret;
}

Array Vertex::_get_outgoing_arcs() const {
	Array ret;
	ERR_FAIL_COND_V(!_list_digraph->_graph.valid(_handle), ret);
	for (LemonDigraph::OutArcIt it(_list_digraph->_graph, _handle); it != lemon::INVALID; ++it) {
		ret.append(_list_digraph->get_instance(it));
	}
	return ret;
}

// ## Vertex (GDNative) ######################################### //

int Vertex::get_id() const {
	return LemonDigraph::id(_handle);
}

bool Vertex::is_valid() const {
	return _list_digraph->_graph.valid(_handle);
}

void Vertex::set_data(Variant p_data) {
	_list_digraph->_vertex_map[_handle].data = p_data;
}

Variant Vertex::get_data() const {
	return _list_digraph->_vertex_map[_handle].data;
}

void Vertex::contract(Ref<Vertex> p_other, bool p_remove) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(!p_other->is_valid());

	_list_digraph->_graph.contract(_handle, p_other->get_handle(), p_remove);
}

Ref<Vertex> Vertex::split(const bool p_connect) {
	ERR_FAIL_COND_V(!is_valid(), nullptr);

	return _list_digraph->get_instance(_list_digraph->_graph.split(_handle, p_connect));
}

Vector<Ref<Arc> > Vertex::get_incoming_arcs() const {
	Vector<Ref<Arc> > ret;
	ERR_FAIL_COND_V(!_list_digraph->_graph.valid(_handle), ret);

	for (LemonDigraph::InArcIt it(_list_digraph->_graph, _handle); it != lemon::INVALID; ++it) {
		ret.push_back(_list_digraph->get_instance(it));
	}
	return ret;
}

Vector<Ref<Arc> > Vertex::get_outgoing_arcs() const {
	Vector<Ref<Arc> > ret;
	ERR_FAIL_COND_V(!_list_digraph->_graph.valid(_handle), ret);

	for (LemonDigraph::OutArcIt it(_list_digraph->_graph, _handle); it != lemon::INVALID; ++it) {
		ret.push_back(_list_digraph->get_instance(it));
	}
	return ret;
}

void Vertex::_init() {}

void Vertex::_register_methods() {
	register_method("get_id", &Vertex::get_id);
	register_method("is_valid", &Vertex::is_valid);
	register_method("set_data", &Vertex::set_data);
	register_method("get_data", &Vertex::get_data);

	register_method("contract", &Vertex::_contract);
	register_method("split", &Vertex::_split);
	register_method("get_incoming_arcs", &Vertex::_get_incoming_arcs);
	register_method("get_outgoing_arcs", &Vertex::_get_outgoing_arcs);

	register_property<Vertex, Variant>("data", &Vertex::set_data, &Vertex::get_data, Variant());
}

Vertex::Vertex() {
}
Vertex::~Vertex() {
	if (_initialized)
		_list_digraph->_vertex_map[_handle].wrapper = nullptr;
}

// ############################################################## //
// ############################# ARC ############################ //
// ############################################################## //

// ## Arc (GDScript) ############################################ //

void Arc::_set_source(Variant p_vertex) {
	ERR_FAIL_COND(p_vertex.get_type() != Variant::OBJECT);
	set_source(p_vertex);
}

void Arc::_set_target(Variant p_vertex) {
	ERR_FAIL_COND(p_vertex.get_type() != Variant::OBJECT);
	set_target(p_vertex);
}

// ## Arc (GDNative) ############################################ //

int Arc::get_id() const {
	return LemonDigraph::id(_handle);
}

bool Arc::is_valid() const {
	return _list_digraph->_graph.valid(_handle);
}

void Arc::set_data(Variant p_data) {
	_list_digraph->_arc_map[_handle].data = p_data;
}

Variant Arc::get_data() const {
	return _list_digraph->_arc_map[_handle].data;
}

void Arc::reverse() {
	ERR_FAIL_COND(!is_valid());

	_list_digraph->_graph.reverseArc(_handle);
}

Ref<Vertex> Arc::split() {
	ERR_FAIL_COND_V(!is_valid(), nullptr);

	return _list_digraph->get_instance(_list_digraph->_graph.split(_handle));
}

void Arc::set_source(Ref<Vertex> p_vertex) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_vertex->is_valid());

	_list_digraph->_graph.changeSource(_handle, p_vertex->get_handle());
}

Ref<Vertex> Arc::get_source() const {
	ERR_FAIL_COND_V(!is_valid(), nullptr);

	return _list_digraph->get_instance(_list_digraph->_graph.source(_handle));
}

void Arc::set_target(Ref<Vertex> p_vertex) {
	ERR_FAIL_COND(!is_valid());
	ERR_FAIL_COND(p_vertex->is_valid());

	_list_digraph->_graph.changeTarget(_handle, p_vertex->get_handle());
}

Ref<Vertex> Arc::get_target() const {
	ERR_FAIL_COND_V(!is_valid(), nullptr);

	return _list_digraph->get_instance(_list_digraph->_graph.target(_handle));
}

void Arc::_init() {}

void Arc::_register_methods() {
	register_method("get_id", &Arc::get_id);
	register_method("is_valid", &Arc::is_valid);
	register_method("set_data", &Arc::set_data);
	register_method("get_data", &Arc::get_data);

	register_method("reverse", &Arc::reverse);
	register_method("split", &Arc::split);
	register_method("set_source", &Arc::_set_source);
	register_method("get_source", &Arc::get_source);
	register_method("set_target", &Arc::_set_target);
	register_method("get_target", &Arc::get_target);

	register_property<Arc, Variant>("data", &Arc::set_data, &Arc::get_data, Variant());
}

Arc::Arc() {
}
Arc::~Arc() {
	if (_initialized)
		_list_digraph->_arc_map[_handle].wrapper = nullptr;
}

// ############################################################## //
// ######################## LIST DIGRAPH ######################## //
// ############################################################## //

const LemonDigraph &ListDigraph::get_graph() const {
	return _graph;
}

Ref<Vertex> ListDigraph::get_instance(const LemonDigraph::Node &p_node) {
	return __get_instance<Vertex>(p_node);
}

Ref<Arc> ListDigraph::get_instance(const LemonDigraph::Arc &p_arc) {
	return __get_instance<Arc>(p_arc);
}

// ## ListDigraph (GDScript) #################################### //

bool ListDigraph::_iter_init() {
	_vertex_it = LemonDigraph::NodeIt(_graph);
	return _vertex_it != lemon::INVALID;
}
bool ListDigraph::_iter_next() {
	++_vertex_it;
	return _vertex_it != lemon::INVALID;
}
Ref<Vertex> ListDigraph::_iter_get() {
	return get_instance(_vertex_it);
}

Array ListDigraph::add_vertices(const Array &p_data, const bool &p_return) {
	Array ret;
	for (int i = 0; i < p_data.size(); i++) {
		LemonDigraph::Node node = _graph.addNode();
		_vertex_map[node].data = p_data[i];

		if (p_return)
			ret.append(get_instance(node));
	}
	return ret;
}
Array ListDigraph::_add_vertices(Variant p_data, Variant p_return) {
	ERR_FAIL_COND_V(p_data.get_type() != Variant::ARRAY, Array());
	ERR_FAIL_COND_V(p_return.get_type() != Variant::BOOL, Array());
	return add_vertices(p_data, p_return);
}

void ListDigraph::_erase_vertex(Variant p_vertex) {
	ERR_FAIL_COND(p_vertex.get_type() != Variant::OBJECT);
	erase_vertex(p_vertex);
}

void ListDigraph::erase_vertices(const Array &p_vertices) {
	for (int i = 0; i < p_vertices.size(); i++) {
		Ref<Vertex> vertex = p_vertices[i];
		ERR_CONTINUE(!vertex->is_valid());
		_graph.erase(vertex->get_handle());
	}
}
void ListDigraph::_erase_vertices(Variant p_vertices) {
	ERR_FAIL_COND(p_vertices.get_type() != Variant::ARRAY);
	erase_vertices(p_vertices);
}

void ListDigraph::_reserve_vertices(Variant p_amount) {
	ERR_FAIL_COND(p_amount.get_type() != Variant::INT);
	reserve_vertices(p_amount);
}

Array ListDigraph::_get_vertices() {
	Array ret;
	for (LemonDigraph::NodeIt it(_graph); it != lemon::INVALID; ++it) {
		ret.append(get_instance(it));
	}
	return ret;
}

Ref<Arc> ListDigraph::_add_arc(Variant p_source, Variant p_target) {
	ERR_FAIL_COND_V(p_source.get_type() != Variant::OBJECT, nullptr);
	ERR_FAIL_COND_V(p_target.get_type() != Variant::OBJECT, nullptr);
	return add_arc(p_source, p_target);
}

Array ListDigraph::add_arcs(const Array &p_data, const bool &p_return) {
	Array ret;
	for (int i = 0; i < p_data.size(); i++) {
		Variant vdict = p_data[i];
		ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

		Dictionary dict = vdict;
		ERR_CONTINUE(!dict.has("source"));
		ERR_CONTINUE(!dict.has("target"));

		ERR_CONTINUE(dict["source"].get_type() != Variant::OBJECT);
		Ref<Vertex> source = dict["source"];
		ERR_CONTINUE(!source.is_valid());

		LemonDigraph::Node s_node = source->get_handle();
		ERR_CONTINUE(!_graph.valid(s_node));

		ERR_CONTINUE(dict["target"].get_type() != Variant::OBJECT);
		Ref<Vertex> target = dict["target"];
		ERR_CONTINUE(!target.is_valid());

		LemonDigraph::Node t_node = target->get_handle();
		ERR_CONTINUE(!_graph.valid(t_node));

		LemonDigraph::Arc arc = _graph.addArc(source->get_handle(), target->get_handle());
		_arc_map[arc].data = dict.has("data") ? dict["data"] : Variant();

		ret.append(get_instance(arc));
	}
	return ret;
}
Array ListDigraph::_add_arcs(Variant p_data, Variant p_return) {
	ERR_FAIL_COND_V(p_data.get_type() != Variant::ARRAY, Array());
	return add_arcs(p_data, p_return);
}

void ListDigraph::_erase_arc(Variant p_arc) {
	ERR_FAIL_COND(p_arc.get_type() != Variant::OBJECT);
	erase_arc(p_arc);
}

void ListDigraph::erase_arcs(const Array &p_arcs) {
	for (int i = 0; i < p_arcs.size(); i++) {
		Ref<Arc> arc = p_arcs[i];
		ERR_CONTINUE(arc.is_null());

		LemonDigraph::Arc handle = arc->get_handle();
		ERR_CONTINUE(!_graph.valid(handle));

		_graph.erase(handle);
	}
}
void ListDigraph::_erase_arcs(Variant p_arcs) {
	ERR_FAIL_COND(p_arcs.get_type() != Variant::ARRAY);
	erase_arcs(p_arcs);
}

void ListDigraph::_reserve_arcs(Variant p_amount) {
	ERR_FAIL_COND(p_amount.get_type() != Variant::INT);
	reserve_arcs(p_amount);
}

Array ListDigraph::_get_arcs() {
	Array ret;
	for (LemonDigraph::ArcIt it(_graph); it != lemon::INVALID; ++it) {
		ret.append(get_instance(it));
	}
	return ret;
}

void ListDigraph::update_data(const Dictionary &p_data) {
	Array refs = p_data.keys();
	for (int i = 0; i < refs.size(); ++i) {
		Variant ref = refs[i];
		ERR_FAIL_COND(ref.get_type() != Variant::OBJECT);

		Ref<Vertex> vertex = ref;
		if (vertex.is_valid()) {
			vertex->set_data(p_data[ref]);
			continue;
		}

		Ref<Arc> arc = ref;
		if (arc.is_valid()) {
			arc->set_data(p_data[ref]);
			continue;
		}

		ERR_CONTINUE(!arc.is_valid() || !vertex.is_valid());
	}
}
void ListDigraph::_update_data(Variant p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	update_data(p_data);
}

// ## ListDigraph (GDNative) #################################### //

Ref<Vertex> ListDigraph::add_vertex() {
	return get_instance(_graph.addNode());
}

Vector<Ref<Vertex> > ListDigraph::add_vertices(const Vector<Variant> &p_data, bool p_return) {
	Vector<Ref<Vertex> > ret;
	for (int i = 0; i < p_data.size(); i++) {
		LemonDigraph::Node node = _graph.addNode();
		_vertex_map[node].data = p_data[i];

		if (p_return) {
			Ref<Vertex> vertex = get_instance(node);
			ret.push_back(vertex);
		}
	}
	return ret;
}

void ListDigraph::erase_vertex(Ref<Vertex> p_vertex) {
	ERR_FAIL_COND(!p_vertex.is_valid());

	LemonDigraph::Node node = p_vertex->get_handle();
	ERR_FAIL_COND(!_graph.valid(node));

	_graph.erase(node);
}

void ListDigraph::erase_vertices(const Vector<Ref<Vertex> > &p_vertices) {
	for (int i = 0; i < p_vertices.size(); i++) {
		Ref<Vertex> vertex = p_vertices[i];
		ERR_FAIL_COND(!vertex.is_valid());

		LemonDigraph::Node node = vertex->get_handle();
		ERR_FAIL_COND(!_graph.valid(node));

		_graph.erase(node);
	}
}

void ListDigraph::reserve_vertices(int p_amount) {
	_graph.reserveNode(p_amount);
}

Vector<Ref<Vertex> > ListDigraph::get_vertices() {
	Vector<Ref<Vertex> > ret;
	for (LemonDigraph::NodeIt it(_graph); it != lemon::INVALID; ++it) {
		ret.push_back(get_instance(it));
	}
	return ret;
}

int ListDigraph::count_vertices() const {
	return lemon::countNodes(_graph);
}

Ref<Arc> ListDigraph::add_arc(Ref<Vertex> p_source, Ref<Vertex> p_target) {
	ERR_FAIL_COND_V(!p_source.is_valid(), nullptr);
	LemonDigraph::Node source = p_source->get_handle();
	ERR_FAIL_COND_V(!_graph.valid(source), nullptr);

	ERR_FAIL_COND_V(!p_target.is_valid(), nullptr);
	LemonDigraph::Node target = p_target->get_handle();
	ERR_FAIL_COND_V(!_graph.valid(target), nullptr);

	LemonDigraph::Arc arc = _graph.addArc(source, target);
	return get_instance(arc);
}

Vector<Ref<Arc> > ListDigraph::add_arcs(const Vector<HashMap<String, Variant> > &p_data, const bool p_return) {
	Vector<Ref<Arc> > ret;
	for (int i = 0; i < p_data.size(); i++) {
		HashMap<String, Variant> dict = p_data[i];

		ERR_CONTINUE(dict.count("source") <= 0);
		ERR_CONTINUE(dict.count("target") <= 0);

		ERR_CONTINUE(dict["source"].get_type() != Variant::OBJECT);
		Ref<Vertex> source = dict["source"];
		ERR_CONTINUE(!source.is_valid());

		LemonDigraph::Node s_node = source->get_handle();
		ERR_CONTINUE(!_graph.valid(s_node));

		ERR_CONTINUE(dict["target"].get_type() != Variant::OBJECT);
		Ref<Vertex> target = dict["target"];
		ERR_CONTINUE(!target.is_valid());

		LemonDigraph::Node t_node = target->get_handle();
		ERR_CONTINUE(!_graph.valid(t_node));

		LemonDigraph::Arc arc = _graph.addArc(s_node, t_node);
		_arc_map[arc].data = dict.count("data") > 0 ? dict["data"] : Variant();

		if (p_return)
			ret.push_back(get_instance(arc));
	}
	return ret;
}

void ListDigraph::erase_arc(Ref<Arc> p_arc) {
	ERR_FAIL_COND(!p_arc.is_valid());

	LemonDigraph::Arc arc = p_arc->get_handle();
	ERR_FAIL_COND(!_graph.valid(arc));

	_graph.erase(arc);
}

void ListDigraph::erase_arcs(const Vector<Ref<Arc> > &p_arcs) {
	for (int i = 0; i < p_arcs.size(); i++) {
		Ref<Arc> arc = p_arcs[i];
		ERR_FAIL_COND(!arc.is_valid());

		LemonDigraph::Arc l_arc = arc->get_handle();
		ERR_CONTINUE(!_graph.valid(l_arc));

		_graph.erase(l_arc);
	}
}

void ListDigraph::reserve_arcs(int p_amount) {
	_graph.reserveArc(p_amount);
}

Vector<Ref<Arc> > ListDigraph::get_arcs() {
	Vector<Ref<Arc> > ret;
	for (LemonDigraph::ArcIt it(_graph); it != lemon::INVALID; ++it) {
		ret.push_back(get_instance(it));
	}
	return ret;
}

int ListDigraph::count_arcs() const {
	return lemon::countArcs(_graph);
}

void ListDigraph::clear() {
	_graph.clear();
}

void ListDigraph::update_data(const Vector<Pair<Ref<Vertex>, Variant> > &p_data) {
	__update_data(p_data);
}

void ListDigraph::update_data(const Vector<Pair<Ref<Arc>, Variant> > &p_data) {
	__update_data(p_data);
}

void ListDigraph::_init() {}

void ListDigraph::_register_methods() {
	register_method("_iter_init", &ListDigraph::_iter_init);
	register_method("_iter_next", &ListDigraph::_iter_next);
	register_method("_iter_get", &ListDigraph::_iter_get);

	register_method("add_vertex", &ListDigraph::add_vertex);
	register_method("add_vertices", &ListDigraph::_add_vertices);
	register_method("erase_vertex", &ListDigraph::_erase_vertex);
	register_method("erase_vertices", &ListDigraph::_erase_vertices);
	register_method("reserve_vertices", &ListDigraph::_reserve_vertices);
	register_method("get_vertices", &ListDigraph::_get_vertices);
	register_method("count_vertices", &ListDigraph::count_vertices);

	register_method("add_arc", &ListDigraph::_add_arc);
	register_method("add_arcs", &ListDigraph::_add_arcs);
	register_method("erase_arc", &ListDigraph::_erase_arc);
	register_method("erase_arcs", &ListDigraph::_erase_arcs);
	register_method("reserve_arcs", &ListDigraph::_reserve_arcs);
	register_method("get_arcs", &ListDigraph::_get_arcs);
	register_method("count_arcs", &ListDigraph::count_arcs);

	register_method("update_data", &ListDigraph::_update_data);
}

ListDigraph::ListDigraph() :
		_vertex_map(_graph),
		_arc_map(_graph) {
}
ListDigraph::~ListDigraph() {
}
