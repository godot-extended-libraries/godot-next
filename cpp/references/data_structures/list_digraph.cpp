#include "list_digraph.hpp"
#include "error_macros.hpp"

using namespace godot;

/* ############################################################## */
/* ######################### LIST DIGRAPH ####################### */
/* ############################################################## */

bool ListDigraph::_iter_init() {
	_vertex_it = LemonNodeIt(_graph);
	return _vertex_it != lemon::INVALID;
}

bool ListDigraph::_iter_next() {
	++_vertex_it;
	return _vertex_it != lemon::INVALID;
}

VertexID ListDigraph::_iter_get() {
	return LemonDigraph::id(_vertex_it);
}

bool ListDigraph::_set(String p_property, Variant p_value) {
	PoolStringArray sections = p_property.split("/");
	ERR_FAIL_COND_V(sections.size() != 2, false);
	String type = sections[0];
	int index = sections[1].to_int();
	if (type == "vertex") {
		ERR_FAIL_COND_V(!vertex_is_valid(index), false);
		set_data(ListDigraph::VERTEX, index, p_value);
		return true;
	} else if (type == "arc") {
		ERR_FAIL_COND_V(!arc_is_valid(index), false);
		set_data(ListDigraph::ARC, index, p_value);
		return true;
	}
	return false;
}

Variant ListDigraph::_get(String p_property) {
	PoolStringArray sections = p_property.split("/");
	ERR_FAIL_COND_V(sections.size() != 2, false);
	String type = sections[0];
	int index = sections[1].to_int();
	if (type == "vertex") {
		ERR_FAIL_COND_V(!vertex_is_valid(index), false);
		return get_data(ListDigraph::VERTEX, index);
	} else if (type == "arc") {
		ERR_FAIL_COND_V(!arc_is_valid(index), false);
		return get_data(ListDigraph::ARC, index);
	}
	return false;
}

// Graph (GDScript)

PoolIntArray ListDigraph::add_vertices(Array p_data) {
	PoolIntArray ret;
	for (int i = 0; i < p_data.size(); i++) {
		LemonNode vertex = _graph.addNode();
		_vertex_map.set(vertex, p_data[i]);

		ret.append(LemonDigraph::id(vertex));
	}
	return ret;
}
PoolIntArray ListDigraph::_add_vertices(Variant p_data) {
	PoolIntArray err;
	ERR_FAIL_COND_V(p_data.get_type() != Variant::ARRAY, err);
	return add_vertices(p_data.operator Array());
}

void ListDigraph::_erase_vertex(Variant p_vertex) {
	ERR_FAIL_COND(p_vertex.get_type() != Variant::INT);
	erase_vertex(p_vertex);
}

void ListDigraph::erase_vertices(PoolIntArray p_vertices) {
	for (int i = 0; i < p_vertices.size(); i++) {
		VertexID id = p_vertices[i];
		LemonNode node = LemonDigraph::nodeFromId(id);
		ERR_CONTINUE(!_graph.valid(node));
		_graph.erase(node);
	}
}
void ListDigraph::_erase_vertices(Variant p_vertices) {
	ERR_FAIL_COND(p_vertices.get_type() != Variant::POOL_INT_ARRAY);
	erase_vertices(p_vertices.operator godot::PoolIntArray());
}

void ListDigraph::_reserve_vertices(Variant p_amount){
	ERR_FAIL_COND(p_amount.get_type() != Variant::INT);
	reserve_vertices(p_amount.operator int());
}

PoolIntArray ListDigraph::_get_vertices() {
	PoolIntArray ret;
	for (LemonNodeIt it(_graph); it != lemon::INVALID; ++it) {
		ret.append(LemonDigraph::id(it));
	}
	return ret;
}

ArcID ListDigraph::_add_arc(Variant p_source, Variant p_target) {
	ERR_FAIL_COND_V(p_source.get_type() != Variant::INT, -1);
	ERR_FAIL_COND_V(p_target.get_type() != Variant::INT, -1);
	return add_arc(p_source, p_target);
}

PoolIntArray ListDigraph::add_arcs(Array p_data) {
	PoolIntArray ret;
	for (int i = 0; i < p_data.size(); i++) {
		Variant vdict = p_data[i];
		ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

		Dictionary dict = vdict.operator Dictionary();
		ERR_CONTINUE(!dict.has("source"));
		ERR_CONTINUE(!dict.has("target"));

		ERR_CONTINUE(dict["source"].get_type() != Variant::INT);
		VertexID source_id = dict["source"];
		LemonNode source = LemonDigraph::nodeFromId(source_id);
		ERR_CONTINUE(!_graph.valid(source));

		ERR_CONTINUE(dict["target"].get_type() != Variant::INT);
		VertexID target_id = dict["target"];
		LemonNode target = LemonDigraph::nodeFromId(target_id);
		ERR_CONTINUE(!_graph.valid(target));

		LemonArc arc = _graph.addArc(source, target);
		_arc_map.set(arc, dict.has("data") ? dict["data"] : Variant());

		ret.append(LemonDigraph::id(arc));
	}
	return ret;
}
PoolIntArray ListDigraph::_add_arcs(Variant p_data) {
	ERR_FAIL_COND_V(p_data.get_type() != Variant::ARRAY, PoolIntArray());
	return add_arcs(p_data.operator Array());
}

void ListDigraph::_erase_arc(Variant p_arc) {
	ERR_FAIL_COND(p_arc.get_type() != Variant::INT);
	erase_arc(p_arc);
}

void ListDigraph::erase_arcs(PoolIntArray p_arcs) {
	for (int i = 0; i < p_arcs.size(); i++) {
		ArcID id = p_arcs[i];
		LemonArc arc = LemonDigraph::arcFromId(id);
		ERR_CONTINUE(!_graph.valid(arc));
		_graph.erase(arc);
	}
}
void ListDigraph::_erase_arcs(Variant p_arcs) {
	ERR_FAIL_COND(p_arcs.get_type() != Variant::POOL_INT_ARRAY);
	erase_arcs(p_arcs.operator godot::PoolIntArray());
}

void ListDigraph::_reserve_arcs(Variant p_amount) {
	ERR_FAIL_COND(p_amount.get_type() != Variant::INT);
	reserve_arcs(p_amount.operator int());
}

PoolIntArray ListDigraph::_get_arcs() {
	PoolIntArray ret;
	for (LemonArcIt it(_graph); it != lemon::INVALID; ++it) {
		ret.append(LemonDigraph::id(it));
	}
	return ret;
}

void ListDigraph::_set_data(Variant p_type, Variant p_id, Variant p_data) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	set_data((GraphComponent)p_type.operator int(), p_id, p_data);
}

Variant ListDigraph::_get_data(Variant p_type, Variant p_id) {
	Variant err;
	ERR_FAIL_COND_V(p_type.get_type() != Variant::INT, err);
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, err);
	return get_data((GraphComponent)p_type.operator int(), p_id);
}

void ListDigraph::update_data(int p_type, Dictionary p_data) {
	Array keys = p_data.keys();
	switch (p_type)
	{
	case ListDigraph::VERTEX:
		for (int i = 0; i < keys.size(); ++i) {
			ERR_CONTINUE(keys[i].get_type() != Variant::INT);
			int p_id = keys[i];
			LemonNode node = LemonDigraph::nodeFromId(p_id);
			ERR_CONTINUE(!_graph.valid(node));
			_vertex_map.set(node, p_data[p_id]);
		}
		break;
	case ListDigraph::ARC:
		for (int i = 0; i < keys.size(); ++i) {
			ERR_CONTINUE(keys[i].get_type() != Variant::INT);
			int p_id = keys[i];
			LemonArc arc = LemonDigraph::arcFromId(p_id);
			ERR_CONTINUE(!_graph.valid(arc));
			_arc_map.set(arc, p_data[p_id]);
		}
		break;
	default:
		break;
	}
}
void ListDigraph::_update_data(Variant p_type, Variant p_data) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);
	update_data(p_type, p_data);
}

// Vertex (GDScript)

bool ListDigraph::_vertex_is_valid(const Variant p_id) {
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, false);
	return vertex_is_valid(p_id);
}

void ListDigraph::_vertex_contract(Variant p_vertex, Variant p_other, Variant p_remove) {
	ERR_FAIL_COND(p_vertex.get_type() != Variant::INT);
	ERR_FAIL_COND(p_other.get_type() != Variant::INT);
	ERR_FAIL_COND(p_remove.get_type() != Variant::BOOL);
	vertex_contract(p_vertex, p_other, p_remove);
}

VertexID ListDigraph::_vertex_split(const Variant p_vertex, const Variant p_connect) {
	ERR_FAIL_COND_V(p_vertex.get_type() != Variant::INT, -1);
	ERR_FAIL_COND_V(p_connect.get_type() != Variant::BOOL, -1);
	return vertex_split(p_vertex, p_connect);
}

PoolIntArray ListDigraph::__vertex_get_incoming_arcs(VertexID p_vertex) const {
	PoolIntArray ret;
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND_V(!_graph.valid(node), ret);
	for (LemonDigraph::InArcIt it(_graph, node); it != lemon::INVALID; ++it) {
		ret.append(LemonDigraph::id(it));
	}
	return ret;
}
PoolIntArray ListDigraph::_vertex_get_incoming_arcs(Variant p_vertex) const {
	ERR_FAIL_COND_V(p_vertex.get_type() != Variant::INT, PoolIntArray());
	return __vertex_get_incoming_arcs(p_vertex);
}

PoolIntArray ListDigraph::__vertex_get_outgoing_arcs(VertexID p_vertex) const {
	PoolIntArray ret;
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND_V(!_graph.valid(node), ret);
	for (LemonDigraph::OutArcIt it(_graph, node); it != lemon::INVALID; ++it) {
		ret.append(LemonDigraph::id(it));
	}
	return ret;
}
PoolIntArray ListDigraph::_vertex_get_outgoing_arcs(Variant p_vertex) const {
	ERR_FAIL_COND_V(p_vertex.get_type() != Variant::INT, PoolIntArray());
	return __vertex_get_outgoing_arcs(p_vertex);
}

// Arc (GDScript)

bool ListDigraph::_arc_is_valid(const Variant p_id) {
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, false);
	return arc_is_valid(p_id);
}

void ListDigraph::_arc_reverse(const Variant p_arc) {
	ERR_FAIL_COND(p_arc.get_type() != Variant::INT);
	return arc_reverse(p_arc);
}

VertexID ListDigraph::_arc_split(const Variant p_arc) {
	ERR_FAIL_COND_V(p_arc.get_type() != Variant::INT, -1);
	return arc_split(p_arc);
}

void ListDigraph::_arc_set_source(const Variant p_arc, const Variant p_vertex) {
	ERR_FAIL_COND(p_arc.get_type() != Variant::INT);
	ERR_FAIL_COND(p_vertex.get_type() != Variant::INT);
	arc_set_source(p_arc, p_vertex);
}

VertexID ListDigraph::_arc_get_source(const Variant p_arc) {
	ERR_FAIL_COND_V(p_arc.get_type() != Variant::INT, -1);
	return arc_get_source(p_arc);
}

void ListDigraph::_arc_set_target(const Variant p_arc, const Variant p_vertex) {
	ERR_FAIL_COND(p_arc.get_type() != Variant::INT);
	ERR_FAIL_COND(p_vertex.get_type() != Variant::INT);
	arc_set_target(p_arc, p_vertex);
}

VertexID ListDigraph::_arc_get_target(const Variant p_arc) {
	ERR_FAIL_COND_V(p_arc.get_type() != Variant::INT, -1);
	return arc_get_target(p_arc);
}

// Graph (GDNative)

VertexID ListDigraph::add_vertex() {
	return LemonDigraph::id(_graph.addNode());
}

Vector<VertexID> ListDigraph::add_vertices(Vector<Variant> p_data) {
	Vector<VertexID> ret;
	for (int i = 0; i < p_data.size(); i++) {
		LemonNode vertex = _graph.addNode();
		_vertex_map.set(vertex, p_data[i]);

		ret.push_back(LemonDigraph::id(vertex));
	}
	return ret;
}

void ListDigraph::erase_vertex(const VertexID p_vertex) {
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND(!_graph.valid(node));
	_graph.erase(node);
}

void ListDigraph::erase_vertices(Vector<VertexID> p_vertices) {
	for (int i = 0; i < p_vertices.size(); i++) {
		LemonNode node = LemonDigraph::nodeFromId(p_vertices[i]);
		ERR_FAIL_COND(!_graph.valid(node));
		_graph.erase(node);
	}
}

void ListDigraph::reserve_vertices(int p_amount) {
	_graph.reserveNode(p_amount);
}

Vector<VertexID> ListDigraph::get_vertices() {
	Vector<VertexID> ret;
	for (LemonNodeIt it(_graph); it != lemon::INVALID; ++it) {
		ret.push_back(LemonDigraph::id(it));
	}
	return ret;
}

ArcID ListDigraph::add_arc(VertexID p_source, VertexID p_target) {
	LemonNode source = LemonDigraph::nodeFromId(p_source);
	ERR_FAIL_COND_V(!_graph.valid(source), -1);

	LemonNode target = LemonDigraph::nodeFromId(p_target);
	ERR_FAIL_COND_V(!_graph.valid(target), -1);

	LemonArc arc = _graph.addArc(source, target);
	return LemonDigraph::id(arc);
}

Vector<ArcID> ListDigraph::add_arcs(Vector<HashMap<String, Variant>> p_data) {
	Vector<ArcID> ret;
	for (int i = 0; i < p_data.size(); i++) {
		HashMap<String, Variant> dict = p_data[i];

		ERR_CONTINUE(dict.count("source") <= 0);
		ERR_CONTINUE(dict.count("target") <= 0);

		ERR_CONTINUE(dict["source"].get_type() != Variant::INT);
		VertexID source_id = dict["source"];
		LemonNode source = LemonDigraph::nodeFromId(source_id);
		ERR_CONTINUE(!_graph.valid(source));

		ERR_CONTINUE(dict["target"].get_type() != Variant::INT);
		ArcID target_id = dict["target"];
		LemonNode target = LemonDigraph::nodeFromId(target_id);
		ERR_CONTINUE(!_graph.valid(target));

		LemonArc arc = _graph.addArc(source, target);
		_arc_map.set(arc, dict.count("data") > 0 ? dict["data"] : Variant());

		ret.push_back(LemonDigraph::id(arc));
	}
	return ret;
}

void ListDigraph::erase_arc(ArcID p_arc) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND(!_graph.valid(arc));
	_graph.erase(arc);
}

void ListDigraph::erase_arcs(Vector<ArcID> p_arcs) {
	for (int i = 0; i < p_arcs.size(); i++) {
		ArcID id = p_arcs[i];
		LemonArc arc = LemonDigraph::arcFromId(id);
		ERR_CONTINUE(!_graph.valid(arc));
		_graph.erase(arc);
	}
}

void ListDigraph::reserve_arcs(int p_amount) {
	_graph.reserveArc(p_amount);
}

Vector<ArcID> ListDigraph::get_arcs() {
	Vector<ArcID> ret;
	for (LemonArcIt it(_graph); it != lemon::INVALID; ++it) {
		ret.push_back(LemonDigraph::id(it));
	}
	return ret;
}

void ListDigraph::clear() {
	_graph.clear();
}

void ListDigraph::set_data(ListDigraph::GraphComponent p_type, int64_t p_id, Variant p_data) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		_vertex_map.set(node, p_data);
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		_arc_map.set(arc, p_data);
		return;
	}
	default:
	{
		ERR_FAIL();
		break;
	}
	}
}

Variant ListDigraph::get_data(ListDigraph::GraphComponent p_type, int64_t p_id) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(node), Variant());
		return _vertex_map.operator[](node);
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(arc), Variant());
		return _arc_map.operator[](arc);
	}
	default:
	{
		ERR_FAIL();
		break;
	}
	}
}

void ListDigraph::update_data(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Variant> &p_data) {
	HashMap<int64_t, Variant>::const_iterator an_id_to_value;
	switch (p_type)
	{
	case ListDigraph::VERTEX:
		for (an_id_to_value = p_data.begin(); an_id_to_value != p_data.end(); ++an_id_to_value) {
			
			LemonNode node = LemonDigraph::nodeFromId(an_id_to_value->first);
			ERR_CONTINUE(!_graph.valid(node));
			_vertex_map.set(node, an_id_to_value->second);
		}
		break;
	case ListDigraph::ARC:
		for (an_id_to_value = p_data.begin(); an_id_to_value != p_data.end(); ++an_id_to_value) {
			LemonArc arc = LemonDigraph::arcFromId(an_id_to_value->first);
			ERR_CONTINUE(!_graph.valid(arc));
			_arc_map.set(arc, an_id_to_value->second);
		}
		break;
	default:
		break;
	}
}

// Graph (GDNative)

bool ListDigraph::vertex_is_valid(VertexID p_id) const {
	LemonNode node = LemonDigraph::nodeFromId(p_id);
	return _graph.valid(node);
}

void ListDigraph::vertex_contract(VertexID p_vertex, VertexID p_other, bool p_remove) {
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND(!_graph.valid(node));

	LemonNode other = LemonDigraph::nodeFromId(p_other);
	ERR_FAIL_COND(!_graph.valid(other));

	_graph.contract(node, other, p_remove);
}

VertexID ListDigraph::vertex_split(const VertexID p_vertex, const bool p_connect) {
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND_V(!_graph.valid(node), -1);

	return LemonDigraph::id(_graph.split(node, p_connect));
}

Vector<ArcID> ListDigraph::vertex_get_incoming_arcs(const VertexID p_vertex) const {
	Vector<ArcID> ret;
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND_V(!_graph.valid(node), ret);

	for (LemonDigraph::InArcIt it(_graph, node); it != lemon::INVALID; ++it) {
		ret.push_back(LemonDigraph::id(it));
	}
	return ret;
}

Vector<ArcID> ListDigraph::vertex_get_outgoing_arcs(const VertexID p_vertex) const {
	Vector<ArcID> ret;
	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND_V(!_graph.valid(node), ret);

	for (LemonDigraph::OutArcIt it(_graph, node); it != lemon::INVALID; ++it) {
		ret.push_back(LemonDigraph::id(it));
	}
	return ret;
}

// Arc (GDNative)

bool ListDigraph::arc_is_valid(ArcID p_id) const {
	LemonArc node = LemonDigraph::arcFromId(p_id);
	return _graph.valid(node);
}

void ListDigraph::arc_reverse(ArcID p_arc) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND(!_graph.valid(arc));

	_graph.reverseArc(arc);
}

VertexID ListDigraph::arc_split(ArcID p_arc) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND_V(!_graph.valid(arc), -1);

	return LemonDigraph::id(_graph.split(arc));
}

void ListDigraph::arc_set_source(const ArcID p_arc, const VertexID p_vertex) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND(!_graph.valid(arc));

	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND(!_graph.valid(node));

	_graph.changeSource(arc, node);
}

VertexID ListDigraph::arc_get_source(const ArcID p_arc) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND_V(!_graph.valid(arc), -1);

	return LemonDigraph::id(_graph.source(arc));
}

void ListDigraph::arc_set_target(const ArcID p_arc, const VertexID p_vertex) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND(!_graph.valid(arc));

	LemonNode node = LemonDigraph::nodeFromId(p_vertex);
	ERR_FAIL_COND(!_graph.valid(node));

	_graph.changeTarget(arc, node);
}

VertexID ListDigraph::arc_get_target(const ArcID p_arc) {
	LemonArc arc = LemonDigraph::arcFromId(p_arc);
	ERR_FAIL_COND_V(!_graph.valid(arc), -1);

	return LemonDigraph::id(_graph.target(arc));
}

void ListDigraph::_register_methods() {
	register_method("_iter_init", &ListDigraph::_iter_init);
	register_method("_iter_next", &ListDigraph::_iter_next);
	register_method("_iter_get", &ListDigraph::_iter_get);

	register_method("_set", &ListDigraph::_set);
	register_method("_get", &ListDigraph::_get);

	register_method("add_vertex", &ListDigraph::add_vertex);
	register_method("add_vertices", &ListDigraph::_add_vertices);
	register_method("erase_vertex", &ListDigraph::_erase_vertex);
	register_method("erase_vertices", &ListDigraph::_erase_vertices);
	register_method("reserve_vertices", &ListDigraph::_reserve_vertices);
	register_method("get_vertices", &ListDigraph::_get_vertices);

	register_method("add_arc", &ListDigraph::_add_arc);
	register_method("add_arcs", &ListDigraph::_add_arcs);
	register_method("erase_arc", &ListDigraph::_erase_arc);
	register_method("erase_arcs", &ListDigraph::_erase_arcs);
	register_method("reserve_arcs", &ListDigraph::_reserve_arcs);
	register_method("get_arcs", &ListDigraph::_get_arcs);
	
	register_method("clear", &ListDigraph::clear);

	register_method("set_data", &ListDigraph::_set_data);
	register_method("get_data", &ListDigraph::_get_data);
	register_method("update_data", &ListDigraph::_update_data);

	register_method("vertex_is_valid", &ListDigraph::vertex_is_valid);
	register_method("vertex_contract", &ListDigraph::_vertex_contract);
	register_method("vertex_split", &ListDigraph::_vertex_split);
	register_method("vertex_get_incoming_arcs", &ListDigraph::_vertex_get_incoming_arcs);
	register_method("vertex_get_outgoing_arcs", &ListDigraph::_vertex_get_outgoing_arcs);

	register_method("arc_is_valid", &ListDigraph::arc_is_valid);
	register_method("arc_reverse", &ListDigraph::_arc_reverse);
	register_method("arc_split", &ListDigraph::_arc_split);
	register_method("arc_set_source", &ListDigraph::_arc_set_source);
	register_method("arc_get_source", &ListDigraph::_arc_get_source);
	register_method("arc_set_target", &ListDigraph::_arc_set_target);
	register_method("arc_get_target", &ListDigraph::_arc_get_target);
}

ListDigraph::ListDigraph() : _arc_map(_graph), _vertex_map(_graph) {
}
ListDigraph::~ListDigraph() {
}

void ListDigraph::_init() { }