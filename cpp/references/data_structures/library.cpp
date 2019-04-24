#include <Godot.hpp>

#include "list_digraph.hpp"
#include "property_graph.hpp"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_tool_class<godot::Arc>();
	godot::register_tool_class<godot::Vertex>();
	godot::register_tool_class<godot::ListDigraph>();

	godot::register_tool_class<godot::PropertyArc>();
	godot::register_tool_class<godot::PropertyVertex>();
	godot::register_tool_class<godot::PropertyGraph>();
}
