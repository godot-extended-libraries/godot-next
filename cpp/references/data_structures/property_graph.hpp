#ifndef STORY_GRAPH_HPP
#define STORY_GRAPH_HPP

#include "set.hpp"
#include "list_digraph.hpp"

namespace godot {
	class PropertyGraph : public ListDigraph {
		GODOT_SUBCLASS(PropertyGraph, ListDigraph)

			struct ArcData {
				String label;
				HashMap<String, Variant> properties;
			};
			struct VertexData {
				Set<String> labels;
				HashMap<String, Variant> properties;
			};

			LemonDigraph::ArcMap<ArcData> _arc_data;
			LemonDigraph::NodeMap<VertexData> _vertex_data;

		protected:

			bool _set(String p_property, Variant p_value);

			Variant _get(String p_property);

			/* Graph (GDScript) */

			void _set_property(Variant p_type, Variant p_id, Variant p_name, Variant p_value);

			Variant _get_property(Variant p_type, Variant p_id, Variant p_name);

			bool _has_property(Variant p_type, Variant p_id, Variant p_name);

			void _insert_property(Variant p_type, Variant p_id, Variant p_name, Variant p_value);

			void _erase_property(Variant p_type, Variant p_id, Variant p_name);

			void _insert_label(Variant p_type, Variant p_id, Variant p_label);

			bool _has_label(Variant p_type, Variant p_id, Variant p_label);

			void _erase_label(Variant p_type, Variant p_id, Variant p_label);

			void update_vertices_labels(int64_t p_op, Dictionary p_id_to_labels);
			void _update_vertices_labels(Variant p_op, Variant p_id_to_labels);

			Dictionary get_vertices_labels(Array p_vertices);
			Dictionary _get_vertices_labels(Variant p_vertices);

			void erase_vertices_labels(Dictionary p_id_to_labels);
			void _erase_vertices_labels(Variant p_id_to_labels);

			void update_arcs_label(Dictionary p_id_to_labels);
			void _update_arcs_label(Variant p_id_to_labels);

			Dictionary get_arcs_label(Array p_arcs);
			Dictionary _get_arcs_label(Variant p_id_to_labels);

			void update_properties(int64_t p_type, int64_t p_op, Dictionary p_id_to_properties);
			void _update_properties(Variant p_type, Variant p_op, Variant p_id_to_properties);

			Dictionary get_properties(int64_t p_type, Dictionary p_id_to_names);
			Dictionary _get_properties(Variant p_type, Variant p_id_to_names);

			void erase_properties(int64_t p_type, Dictionary p_id_to_names);
			void _erase_properties(Variant p_type, Variant p_id_to_names);

		public:
			enum GraphOp {
				OP_SET,
				OP_MERGE,
				OP_INSERT
			};

			/* Graph (GDNative) */

			void set_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name, Variant p_value);

			Variant get_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name);

			bool has_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name);

			void insert_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name, Variant p_value);

			void erase_property(ListDigraph::GraphComponent p_type, int64_t p_id, String p_name);

			void insert_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label);

			bool has_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label);

			void erase_label(ListDigraph::GraphComponent p_type, int64_t p_id, String p_label);

			void update_vertices_labels(PropertyGraph::GraphOp p_op, const HashMap<int64_t, Set<String>> &p_data);

			void get_vertices_labels(const Vector<int64_t> &p_data, HashMap<int64_t, Set<String>> *r_labels);

			void erase_vertices_labels(const HashMap<int64_t, Set<String>> &p_data);

			void update_arcs_label(const HashMap<int64_t, String> &p_data);

			void get_arcs_label(const Vector<int64_t> &p_data, HashMap<int64_t, String> *r_labels);

			void update_properties(ListDigraph::GraphComponent p_type, PropertyGraph::GraphOp p_op, const HashMap<int64_t, HashMap<String, Variant>> &p_data);

			void get_properties(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Vector<String>> &p_data, HashMap<int64_t, HashMap<String, Variant>> *r_properties);

			void erase_properties(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Vector<String>> &p_data);

			static void _register_methods();

			PropertyGraph();
			~PropertyGraph();

			void _init();
	};
}
#endif /* !STORY_GRAPH_HPP */