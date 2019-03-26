
#include "error_macros.hpp"
#include "property_graph.hpp"

using namespace godot;

bool PropertyGraph::_set(String p_property, Variant p_value) {
	PoolStringArray sections = p_property.split("/");
	ERR_FAIL_COND_V(sections.size() > 4, false);

	if (sections.size() < 3)
		return ListDigraph::_set(p_property, p_value);
	
	String type = sections[0];
	int index = sections[1].to_int();
	String kind = sections[2];
	if (type == "vertex") {
		if (kind == "labels") {
			Dictionary dict;
			dict[index] = p_value;
			update_vertices_labels(GraphOp::OP_SET, dict);
			return true;
		} else if (kind == "properties") {
			Dictionary dict;
			dict[index] = p_value;
			update_properties(GraphComponent::VERTEX, GraphOp::OP_SET, dict);
			return true;
		}
	} else if (type == "arc") {
		if (kind == "label") {
			insert_label(GraphComponent::ARC, index, p_value);
			return true;
		} else if (kind == "properties") {
			Dictionary dict;
			dict[index] = p_value;
			update_properties(GraphComponent::ARC, GraphOp::OP_SET, dict);
			return true;
		}
	}
	return false;
}

Variant PropertyGraph::_get(String p_property) {
	PoolStringArray sections = p_property.split("/");
	ERR_FAIL_COND_V(sections.size() > 4, false);

	if (sections.size() < 3)
		return ListDigraph::_get(p_property);
	
	String type = sections[0];
	int index = sections[1].to_int();
	String kind = sections[2];
	if (type == "vertex") {
		LemonNode node = LemonDigraph::nodeFromId(index);
		ERR_FAIL_COND_V(!_graph.valid(node), Variant());
		if (kind == "labels") {
			Array ret;
			Set<String> &labels = _vertex_data[node].labels;
			Set<String>::iterator a_label;
			for (a_label = labels.begin(); a_label != labels.end(); ++a_label) {
				ret.append(*a_label);
			}
			return ret;
		} else if (kind == "properties") {
			Dictionary ret;
			LemonNode node = LemonDigraph::nodeFromId(index);
			HashMap<String, Variant> &properties = _vertex_data[node].properties;
			HashMap<String, Variant>::iterator a_property;
			for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
				ret[a_property->first] = a_property->second;
			}
			return ret;
		}
	} else if (type == "arc") {
		LemonArc arc = LemonDigraph::arcFromId(index);
		ERR_FAIL_COND_V(!_graph.valid(arc), Variant());
		if (kind == "label") {
			return _arc_data[arc].label;
		} else if (kind == "properties") {
			Dictionary ret;
			HashMap<String, Variant> &properties = _arc_data[arc].properties;
			HashMap<String, Variant>::iterator a_property;
			for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
				ret[a_property->first] = a_property->second;
			}
			return ret;
		}
	}
	return Variant();
}

/* Graph (GDScript) */

void PropertyGraph::_set_property(Variant p_type, Variant p_id, Variant p_name, Variant p_value) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	ERR_FAIL_COND(p_name.get_type() != Variant::STRING);
	set_property((GraphComponent)p_type.operator int(), p_id, p_name, p_value);
}

Variant PropertyGraph::_get_property(Variant p_type, Variant p_id, Variant p_name) {
	ERR_FAIL_COND_V(p_type.get_type() != Variant::INT, Variant());
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, Variant());
	ERR_FAIL_COND_V(p_name.get_type() != Variant::STRING, Variant());
	return get_property((GraphComponent)p_type.operator int(), p_id, p_name);
}

bool PropertyGraph::_has_property(Variant p_type, Variant p_id, Variant p_name) {
	ERR_FAIL_COND_V(p_type.get_type() != Variant::INT, false);
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, false);
	ERR_FAIL_COND_V(p_name.get_type() != Variant::STRING, false);
	return has_property((GraphComponent)p_type.operator int(), p_id, p_name);
}

void PropertyGraph::_insert_property(Variant p_type, Variant p_id, Variant p_name, Variant p_value) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	ERR_FAIL_COND(p_name.get_type() != Variant::STRING);
	insert_property((GraphComponent)p_type.operator int(), p_id, p_name, p_value);
}

void PropertyGraph::_erase_property(Variant p_type, Variant p_id, Variant p_name) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	ERR_FAIL_COND(p_name.get_type() != Variant::STRING);
	erase_property((GraphComponent)p_type.operator int(), p_id, p_name);
}

void PropertyGraph::_insert_label(Variant p_type, Variant p_id, Variant p_label) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	ERR_FAIL_COND(p_label.get_type() != Variant::STRING);
	insert_label((GraphComponent)p_type.operator int(), p_id, p_label);
}

bool PropertyGraph::_has_label(Variant p_type, Variant p_id, Variant p_label) {
	ERR_FAIL_COND_V(p_type.get_type() != Variant::INT, false);
	ERR_FAIL_COND_V(p_id.get_type() != Variant::INT, false);
	ERR_FAIL_COND_V(p_label.get_type() != Variant::STRING, false);
	return has_label((GraphComponent)p_type.operator int(), p_id, p_label);
}

void PropertyGraph::_erase_label(Variant p_type, Variant p_id, Variant p_label) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id.get_type() != Variant::INT);
	ERR_FAIL_COND(p_label.get_type() != Variant::STRING);
	erase_label((GraphComponent)p_type.operator int(), p_id, p_label);
}

void PropertyGraph::update_vertices_labels(int64_t p_op, Dictionary p_id_to_labels) {
	LemonNode node;
	Array ids = p_id_to_labels.keys();
	switch (p_op)
	{
	case PropertyGraph::OP_SET:
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);
			node = LemonDigraph::nodeFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(node));

			ERR_CONTINUE(p_id_to_labels[ids[i]].get_type() != Variant::ARRAY);
			Array labels = p_id_to_labels[ids[i]];

			_vertex_data[node].labels.clear();
			for (int j = 0; j < labels.size(); ++i) {
				ERR_CONTINUE(labels[j].get_type() != Variant::STRING);
				String label = labels[j];

				ERR_CONTINUE(!label.is_valid_identifier())
				_vertex_data[node].labels.insert(label);
			}
		}
	case PropertyGraph::OP_MERGE:
	case PropertyGraph::OP_INSERT:
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);
			node = LemonDigraph::nodeFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(node));

			ERR_CONTINUE(p_id_to_labels[ids[i]].get_type() != Variant::ARRAY);
			Array labels = p_id_to_labels[ids[i]];

			for (int j = 0; j < labels.size(); ++i) {
				ERR_CONTINUE(labels[j].get_type() != Variant::STRING);
				String label = labels[j];

				ERR_CONTINUE(!label.is_valid_identifier())
				_vertex_data[node].labels.insert(label);
			}
		}
	default:
		break;
	}
}
void PropertyGraph::_update_vertices_labels(Variant p_op, Variant p_id_to_labels) {
	ERR_FAIL_COND(p_op.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id_to_labels.get_type() != Variant::DICTIONARY);
	update_vertices_labels(p_op, p_id_to_labels);
}

Dictionary PropertyGraph::get_vertices_labels(Array p_vertices) {
	Dictionary ret;
	LemonNode node;
	for (int i = 0; i < p_vertices.size(); ++i) {
		ERR_CONTINUE(p_vertices[i].get_type() != Variant::INT);

		int id = p_vertices[i];
		node = LemonDigraph::nodeFromId(id);
		ERR_CONTINUE(!_graph.valid(node));

		Array ret_labels;
		Set<String> &labels = _vertex_data[node].labels;
		Set<String>::iterator a_label;
		for (a_label = labels.begin(); a_label != labels.end(); ++a_label ) {
			ret_labels.append(*a_label);
		}
		ret[id] = ret_labels;
	}
	return ret;
}
Dictionary PropertyGraph::_get_vertices_labels(Variant p_vertices) {
	ERR_FAIL_COND_V(p_vertices.get_type() != Variant::ARRAY, Dictionary());
	return get_vertices_labels(p_vertices);
}

void PropertyGraph::erase_vertices_labels(Dictionary p_id_to_labels) {
	LemonNode node;
	Array ids = p_id_to_labels.keys();
	for (int i = 0; i < ids.size(); ++i) {
		ERR_CONTINUE(ids[i].get_type() != Variant::INT);
		node = LemonDigraph::nodeFromId(ids[i]);
		ERR_CONTINUE(!_graph.valid(node));

		ERR_CONTINUE(p_id_to_labels[ids[i]].get_type() != Variant::ARRAY);
		Array labels = p_id_to_labels[ids[i]];

		for (int j = 0; j < labels.size(); ++i) {
			ERR_CONTINUE(labels[j].get_type() != Variant::STRING);
			String label = labels[j];

			ERR_CONTINUE(!label.is_valid_identifier())
			_vertex_data[node].labels.erase(label);
		}
	}
}
void PropertyGraph::_erase_vertices_labels(Variant p_id_to_labels) {
	ERR_FAIL_COND(p_id_to_labels.get_type() != Variant::DICTIONARY);
	erase_vertices_labels(p_id_to_labels);
}

void PropertyGraph::update_arcs_label(Dictionary p_id_to_labels) {
	LemonArc arc;
	Array ids = p_id_to_labels.keys();
	for (int i = 0; i < ids.size(); ++i) {
		ERR_CONTINUE(ids[i].get_type() != Variant::INT);
		arc = LemonDigraph::arcFromId(ids[i]);
		ERR_CONTINUE(!_graph.valid(arc));

		ERR_CONTINUE(p_id_to_labels[ids[i]].get_type() != Variant::STRING);
		_arc_data[arc].label = p_id_to_labels[ids[i]];
	}
}
void PropertyGraph::_update_arcs_label(Variant p_id_to_labels) {
	ERR_FAIL_COND(p_id_to_labels.get_type() != Variant::DICTIONARY);
	erase_vertices_labels(p_id_to_labels);
}

Dictionary PropertyGraph::get_arcs_label(Array p_arcs) {
	Dictionary ret;
	LemonArc arc;
	for (int i = 0; i < p_arcs.size(); ++i) {
		ERR_CONTINUE(p_arcs[i].get_type() != Variant::INT);

		int id = p_arcs[i];
		arc = LemonDigraph::arcFromId(id);
		ERR_CONTINUE(!_graph.valid(arc));

		ret[id] = _arc_data[arc].label;
	}
	return ret;
}
Dictionary PropertyGraph::_get_arcs_label(Variant p_id_to_labels) {
	ERR_FAIL_COND_V(p_id_to_labels.get_type() != Variant::ARRAY, Dictionary());
	return get_arcs_label(p_id_to_labels);
}

void PropertyGraph::update_properties(int64_t p_type, int64_t p_op, Dictionary p_id_to_properties) {
	Array ids = p_id_to_properties.keys();
	switch (p_type)
	{
	case GraphComponent::VERTEX:
	{
		LemonNode node;
		switch (p_op)
		{
		case GraphOp::OP_SET:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				node = LemonDigraph::nodeFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(node));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				_vertex_data[node].properties.clear();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					_vertex_data[node].properties[name] = properties[name];
				}
			}
			break;
		case GraphOp::OP_MERGE:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				node = LemonDigraph::nodeFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(node));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					_vertex_data[node].properties[name] = properties[name];
				}
			}
			break;
		case GraphOp::OP_INSERT:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				node = LemonDigraph::nodeFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(node));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					if (_vertex_data[node].properties.count(name) <= 0)
						_vertex_data[node].properties[name] = properties[name];
				}
			}
			break;

		default:
			break;
		}
		break;
	}
	case GraphComponent::ARC:
	{
		LemonArc arc;
		switch (p_op)
		{
		case GraphOp::OP_SET:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				arc = LemonDigraph::arcFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(arc));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				_arc_data[arc].properties.clear();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					_arc_data[arc].properties[name] = properties[name];
				}
			}
			break;
		case GraphOp::OP_MERGE:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				arc = LemonDigraph::arcFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(arc));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					_arc_data[arc].properties[name] = properties[name];
				}
			}
			break;
		case GraphOp::OP_INSERT:
			for (int i = 0; i < ids.size(); ++i) {
				ERR_CONTINUE(ids[i].get_type() != Variant::INT);

				arc = LemonDigraph::arcFromId(ids[i]);
				ERR_CONTINUE(!_graph.valid(arc));

				Variant vdict = p_id_to_properties[ids[i]];
				ERR_CONTINUE(vdict.get_type() != Variant::DICTIONARY);

				Dictionary properties = vdict;
				Array names = properties.keys();
				for (int j = 0; j < names.size(); ++j) {
					ERR_CONTINUE(names[j].get_type() != Variant::STRING);

					String name = names[j];
					ERR_CONTINUE(!name.is_valid_identifier());

					if (_arc_data[arc].properties.count(name) <= 0)
						_arc_data[arc].properties[name] = properties[name];
				}
			}
			break;

		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}
void PropertyGraph::_update_properties(Variant p_type, Variant p_op, Variant p_id_to_properties) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_op.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id_to_properties.get_type() != Variant::DICTIONARY);
	update_properties(p_type, p_op, p_id_to_properties);
}

Dictionary PropertyGraph::get_properties(int64_t p_type, Dictionary p_id_to_names) {
	Dictionary ret;
	Array ids = p_id_to_names.keys();
	switch (p_type)
	{
	case GraphComponent::VERTEX:
	{
		LemonNode node;
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);

			node = LemonDigraph::nodeFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(node));

			Variant varray = p_id_to_names[ids[i]];
			ERR_CONTINUE(varray.get_type() != Variant::ARRAY);

			Array names = varray;
			Dictionary properties;
			for (int j = 0; j < names.size(); ++j) {
				ERR_CONTINUE(names[j].get_type() != Variant::STRING);

				String name = names[j];
				ERR_CONTINUE(!name.is_valid_identifier());

				ERR_CONTINUE(_vertex_data[node].properties.count(name) <= 0);
				properties[name] = _vertex_data[node].properties[name];
			}
			ret[ids[i]] = properties;
		}
		break;
	}
	case GraphComponent::ARC:
	{
		LemonArc arc;
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);

			arc = LemonDigraph::arcFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(arc));

			Variant varray = p_id_to_names[ids[i]];
			ERR_CONTINUE(varray.get_type() != Variant::ARRAY);

			Array names = varray;
			Dictionary properties;
			for (int j = 0; j < names.size(); ++j) {
				ERR_CONTINUE(names[j].get_type() != Variant::STRING);

				String name = names[j];
				ERR_CONTINUE(!name.is_valid_identifier());

				ERR_CONTINUE(_arc_data[arc].properties.count(name) <= 0);
				properties[name] = _arc_data[arc].properties[name];
			}
			ret[ids[i]] = properties;
		}
	}
	default:
		break;
	}
	return ret;
}
Dictionary PropertyGraph::_get_properties(Variant p_type, Variant p_id_to_names) {
	ERR_FAIL_COND_V(p_type.get_type() != Variant::INT, Dictionary());
	ERR_FAIL_COND_V(p_id_to_names.get_type() != Variant::DICTIONARY, Dictionary());
	return get_properties(p_type, p_id_to_names);
}

void PropertyGraph::erase_properties(int64_t p_type, Dictionary p_id_to_names) {
	Array ids = p_id_to_names.keys();
	switch (p_type)
	{
	case GraphComponent::VERTEX:
	{
		LemonNode node;
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);

			node = LemonDigraph::nodeFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(node));

			Variant varray = p_id_to_names[ids[i]];
			ERR_CONTINUE(varray.get_type() != Variant::ARRAY);

			Array names = varray;
			for (int j = 0; j < names.size(); ++j) {
				ERR_CONTINUE(names[j].get_type() != Variant::STRING);

				_vertex_data[node].properties.erase(names[j]);
			}
		}
		break;
	}
	case GraphComponent::ARC:
	{
		LemonArc arc;
		for (int i = 0; i < ids.size(); ++i) {
			ERR_CONTINUE(ids[i].get_type() != Variant::INT);

			arc = LemonDigraph::arcFromId(ids[i]);
			ERR_CONTINUE(!_graph.valid(arc));

			Variant varray = p_id_to_names[ids[i]];
			ERR_CONTINUE(varray.get_type() != Variant::ARRAY);

			Array names = varray;
			for (int j = 0; j < names.size(); ++j) {
				ERR_CONTINUE(names[j].get_type() != Variant::STRING);

				_arc_data[arc].properties.erase(names[j]);
			}
		}
	}
	default:
		break;
	}
}
void PropertyGraph::_erase_properties(Variant p_type, Variant p_id_to_names) {
	ERR_FAIL_COND(p_type.get_type() != Variant::INT);
	ERR_FAIL_COND(p_id_to_names.get_type() != Variant::DICTIONARY);
	erase_properties(p_type, p_id_to_names);
}

/* Graph (GDNative) */

void PropertyGraph::set_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name, Variant p_value) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		_vertex_data[node].properties[p_name] = p_value;
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		_arc_data[arc].properties[p_name] = p_value;
		return;
	}
	}
	ERR_FAIL();
}

Variant PropertyGraph::get_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(node), Variant());
		return _vertex_data[node].properties[p_name];
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(arc), Variant());
		return _arc_data[arc].properties[p_name];
	}
	}
	ERR_FAIL_V(Variant());
}

bool PropertyGraph::has_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(node), false);
		return _vertex_data[node].properties.count(p_name) > 0;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(arc), false);
		return _arc_data[arc].properties.count(p_name) > 0;
	}
	}
	ERR_FAIL_V(false);
}

void PropertyGraph::insert_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name, Variant p_value) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		if (_vertex_data[node].properties.count(p_name) <= 0)
			_vertex_data[node].properties[p_name] = p_value;
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		if (_arc_data[arc].properties.count(p_name) <= 0)
			_arc_data[arc].properties[p_name] = p_value;
		return;
	}
	}
	ERR_FAIL();
}

void PropertyGraph::erase_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		_vertex_data[node].properties.erase(p_name);
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		_arc_data[arc].properties.erase(p_name);
		return;
	}
	}
	ERR_FAIL();
}

void PropertyGraph::insert_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		_vertex_data[node].labels.insert(p_label);
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		_arc_data[arc].label = p_label;
		return;
	}
	}
	ERR_FAIL();
}

bool PropertyGraph::has_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(node), false);
		return _vertex_data[node].labels.count(p_label) > 0;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND_V(!_graph.valid(arc), false);
		return _arc_data[arc].label == p_label;
	}
	}
	ERR_FAIL_V(false);
}

void PropertyGraph::erase_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label) {
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node = LemonDigraph::nodeFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(node));
		_vertex_data[node].labels.erase(p_label);
		return;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc = LemonDigraph::arcFromId(p_id);
		ERR_FAIL_COND(!_graph.valid(arc));
		_arc_data[arc].label = String();
		return;
	}
	}
	ERR_FAIL();
}

void PropertyGraph::update_vertices_labels(PropertyGraph::GraphOp p_op, const HashMap<int64_t, Set<String>> &p_data) {
	LemonNode node;
	HashMap<int64_t, Set<String>>::const_iterator an_id_to_labels;
	switch (p_op)
	{
	case PropertyGraph::OP_SET:
		for (an_id_to_labels = p_data.begin(); an_id_to_labels != p_data.end(); ++an_id_to_labels) {
			node = LemonDigraph::nodeFromId(an_id_to_labels->first);
			ERR_CONTINUE(!_graph.valid(node));
			_vertex_data[node].labels.clear();
			Set<String> labels = an_id_to_labels->second;
			Set<String>::iterator a_label;
			for (a_label = labels.begin(); a_label != labels.end(); ++a_label) {
				ERR_CONTINUE(!(*a_label).is_valid_identifier())
				_vertex_data[node].labels.insert(*a_label);
			}
		}
	case PropertyGraph::OP_MERGE:
	case PropertyGraph::OP_INSERT:
		for (an_id_to_labels = p_data.begin(); an_id_to_labels != p_data.end(); ++an_id_to_labels) {
			node = LemonDigraph::nodeFromId(an_id_to_labels->first);
			ERR_CONTINUE(!_graph.valid(node));
			Set<String> labels = an_id_to_labels->second;
			Set<String>::iterator a_label;
			for (a_label = labels.begin(); a_label != labels.end(); ++a_label) {
				ERR_CONTINUE(!(*a_label).is_valid_identifier())
				_vertex_data[node].labels.insert(*a_label);
			}
		}
	default:
		break;
	}
}

void PropertyGraph::get_vertices_labels(const Vector<int64_t> &p_data, HashMap<int64_t, Set<String>> *r_labels) {
	LemonNode node;

	for (int i = 0; i < p_data.size(); ++i) {
		int id = p_data[i];
		node = LemonDigraph::nodeFromId(id);
		ERR_CONTINUE(!_graph.valid(node));
		(*r_labels)[id] = _vertex_data[node].labels;
	}
}

void PropertyGraph::erase_vertices_labels(const HashMap<int64_t, Set<String>> &p_data) {
	LemonNode node;
	HashMap<int64_t, Set<String>>::const_iterator an_id_to_labels;
	for (an_id_to_labels = p_data.begin(); an_id_to_labels != p_data.end(); ++an_id_to_labels) {
		node = LemonDigraph::nodeFromId(an_id_to_labels->first);
		ERR_CONTINUE(!_graph.valid(node));

		Set<String> labels = an_id_to_labels->second;
		Set<String>::iterator a_label;
		for (a_label = labels.begin(); a_label != labels.end(); ++a_label) {
			_vertex_data[node].labels.erase(*a_label);
		}
	}
}

void PropertyGraph::update_arcs_label(const HashMap<int64_t, String> &p_data) {
	LemonArc arc;
	HashMap<int64_t, String>::const_iterator an_id_to_label;
	for (an_id_to_label = p_data.begin(); an_id_to_label != p_data.end(); ++an_id_to_label) {
		arc = LemonDigraph::arcFromId(an_id_to_label->first);
		ERR_CONTINUE(!_graph.valid(arc));
		_arc_data[arc].label = an_id_to_label->second;
	}
}

void PropertyGraph::get_arcs_label(const Vector<int64_t> &p_data, HashMap<int64_t, String> *r_labels) {
	LemonArc arc;
	for (int i = 0; i < p_data.size(); ++i) {
		int id = p_data[i];
		arc = LemonDigraph::arcFromId(id);
		ERR_CONTINUE(!_graph.valid(arc));
		(*r_labels)[id] = _arc_data[arc].label;
	}
}

void PropertyGraph::update_properties(ListDigraph::GraphComponent p_type, PropertyGraph::GraphOp p_op, const HashMap<int64_t, HashMap<String, Variant>> &p_data) {
	HashMap<int64_t, HashMap<String, Variant>>::const_iterator an_id_to_properties;
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node;
		switch (p_op)
		{
		case PropertyGraph::OP_SET:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				node = LemonDigraph::nodeFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(node));
				_vertex_data[node].properties.clear();
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					_vertex_data[node].properties[a_property->first] = a_property->second;
				}
			}
			break;
		case PropertyGraph::OP_MERGE:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				node = LemonDigraph::nodeFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(node));
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					_vertex_data[node].properties[a_property->first] = a_property->second;
				}
			}
			break;
		case PropertyGraph::OP_INSERT:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				node = LemonDigraph::nodeFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(node));
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					if (_vertex_data[node].properties.count(a_property->first) <= 0)
						_vertex_data[node].properties[a_property->first] = a_property->second;
				}
			}
			break;
		default:
			break;
		}
	}
	case ListDigraph::ARC:
	{
		LemonArc arc;
		switch (p_op)
		{
		case PropertyGraph::OP_SET:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				arc = LemonDigraph::arcFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(arc));
				_arc_data[arc].properties.clear();
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					_arc_data[arc].properties[a_property->first] = a_property->second;
				}
			}
			break;
		case PropertyGraph::OP_MERGE:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				arc = LemonDigraph::arcFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(arc));
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					_arc_data[arc].properties[a_property->first] = a_property->second;
				}
			}
			break;
		case PropertyGraph::OP_INSERT:
			for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
				arc = LemonDigraph::arcFromId(an_id_to_properties->first);
				ERR_CONTINUE(!_graph.valid(arc));
				HashMap<String, Variant> properties = an_id_to_properties->second;
				HashMap<String, Variant>::iterator a_property;
				for (a_property = properties.begin(); a_property != properties.end(); ++a_property) {
					ERR_CONTINUE(!a_property->first.is_valid_identifier())
					if (_arc_data[arc].properties.count(a_property->first) <= 0)
						_arc_data[arc].properties[a_property->first] = a_property->second;
				}
			}
			break;
		default:
			break;
		}
	}
	}
	ERR_FAIL();
}

void PropertyGraph::get_properties(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Vector<String>> &p_data, HashMap<int64_t, HashMap<String, Variant>> *r_properties) {
	HashMap<int64_t, Vector<String>>::const_iterator an_id_to_properties;
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node;
		for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
			node = LemonDigraph::nodeFromId(an_id_to_properties->first);
			ERR_CONTINUE(!_graph.valid(node));
			Vector<String> properties = an_id_to_properties->second;
			for (int i = 0; i < properties.size(); ++i) {
				String a_property = properties[i];
				ERR_CONTINUE(!a_property.is_valid_identifier())
				(*r_properties)[an_id_to_properties->first][a_property] = _vertex_data[node].properties[a_property];
			}
		}
		break;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc;
		for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
			arc = LemonDigraph::arcFromId(an_id_to_properties->first);
			ERR_CONTINUE(!_graph.valid(arc));
			Vector<String> properties = an_id_to_properties->second;
			for (int i = 0; i < properties.size(); ++i) {
				String a_property = properties[i];
				ERR_CONTINUE(!a_property.is_valid_identifier())
				(*r_properties)[an_id_to_properties->first][a_property] = _arc_data[arc].properties[a_property];
			}
		}
		break;
	}
	}
}

void PropertyGraph::erase_properties(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Vector<String>> &p_data) {
	HashMap<int64_t, Vector<String>>::const_iterator an_id_to_properties;
	switch (p_type)
	{
	case ListDigraph::VERTEX:
	{
		LemonNode node;
		for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
			node = LemonDigraph::nodeFromId(an_id_to_properties->first);
			ERR_CONTINUE(!_graph.valid(node));
			Vector<String> properties = an_id_to_properties->second;
			for (int i = 0; i < properties.size(); ++i) {
				String a_property = properties[i];
				ERR_CONTINUE(!a_property.is_valid_identifier())
				_vertex_data[node].properties.erase(a_property);
			}
		}
		break;
	}
	case ListDigraph::ARC:
	{
		LemonArc arc;
		for (an_id_to_properties = p_data.begin(); an_id_to_properties != p_data.end(); ++an_id_to_properties) {
			arc = LemonDigraph::arcFromId(an_id_to_properties->first);
			ERR_CONTINUE(!_graph.valid(arc));
			Vector<String> properties = an_id_to_properties->second;
			for (int i = 0; i < properties.size(); ++i) {
				String a_property = properties[i];
				ERR_CONTINUE(!a_property.is_valid_identifier())
				_arc_data[arc].properties.erase(a_property);
			}
		}
		break;
	}
	}
	ERR_FAIL();
}

void PropertyGraph::_register_methods() {
	register_method("_set", &PropertyGraph::_set);
	register_method("_get", &PropertyGraph::_get);

	register_method("set_property", &PropertyGraph::_set_property);
	register_method("get_property", &PropertyGraph::_get_property);
	register_method("has_property", &PropertyGraph::_has_property);
	register_method("insert_property", &PropertyGraph::_insert_property);
	register_method("erase_property", &PropertyGraph::_erase_property);

	register_method("insert_label", &PropertyGraph::_insert_label);
	register_method("has_label", &PropertyGraph::_has_label);
	register_method("erase_label", &PropertyGraph::_erase_label);

	register_method("update_properties", &PropertyGraph::_update_properties);
	register_method("get_properties", &PropertyGraph::_get_properties);
	register_method("erase_properties", &PropertyGraph::_erase_properties);

	register_method("update_vertices_labels", &PropertyGraph::_update_vertices_labels);
	register_method("get_vertices_labels", &PropertyGraph::_get_vertices_labels);
	register_method("erase_vertices_labels", &PropertyGraph::_erase_vertices_labels);
	register_method("update_arcs_label", &PropertyGraph::_update_arcs_label);
	register_method("get_arcs_label", &PropertyGraph::_get_arcs_label);
}

PropertyGraph::PropertyGraph() : _arc_data(_graph), _vertex_data(_graph) {
}
PropertyGraph::~PropertyGraph() {
}

void PropertyGraph::_init() {}