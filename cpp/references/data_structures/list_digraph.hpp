#ifndef LIST_DIGRAPH_HPP
#define LIST_DIGRAPH_HPP

#include <Godot.hpp>
#include <Reference.hpp>

#include <lemon/list_graph.h>

#include "hash_map.hpp"
#include "vector.hpp"

namespace godot {

	typedef lemon::ListDigraph LemonDigraph;
	typedef LemonDigraph::Arc LemonArc;
	typedef LemonDigraph::ArcIt LemonArcIt;
	typedef LemonDigraph::Node LemonNode;
	typedef LemonDigraph::NodeIt LemonNodeIt;

	typedef int64_t ArcID;
	typedef int64_t VertexID;


	class ListDigraph : public Reference {
		GODOT_CLASS(ListDigraph, Reference)

		protected:
			LemonDigraph _graph;
			LemonNodeIt _vertex_it;

			LemonDigraph::ArcMap<Variant> _arc_map;
			LemonDigraph::NodeMap<Variant> _vertex_map;

			bool _iter_init();

			bool _iter_next();

			VertexID _iter_get();

			bool _set(String p_property, Variant p_value);

			Variant _get(String p_property);

			// Graph (GDScript)

			PoolIntArray add_vertices(Array p_data);
			PoolIntArray _add_vertices(Variant p_data);

			void _erase_vertex(Variant p_vertex);

			void erase_vertices(PoolIntArray p_vertices);
			void _erase_vertices(Variant p_vertices);

			void _reserve_vertices(Variant p_amount);

			PoolIntArray _get_vertices();

			ArcID _add_arc(Variant p_one, Variant p_other);

			PoolIntArray add_arcs(Array p_data);
			PoolIntArray _add_arcs(Variant p_data);

			void _erase_arc(Variant p_arc);

			void erase_arcs(PoolIntArray p_arcs);
			void _erase_arcs(Variant p_arcs);

			void _reserve_arcs(Variant p_amount);

			PoolIntArray _get_arcs();

			void _set_data(Variant p_type, Variant p_id, Variant p_data);

			Variant _get_data(Variant p_type, Variant p_id);

			void update_data(int p_type, Dictionary p_data);
			void _update_data(Variant p_type, Variant p_data);

			// Vertex (GDScript)

			bool _vertex_is_valid(const Variant p_id);

			void _vertex_contract(Variant p_vertex, Variant p_other, Variant p_remove = true);

			VertexID _vertex_split(const Variant p_vertex, const Variant p_connect = true);

			PoolIntArray __vertex_get_incoming_arcs(VertexID p_vertex) const;
			PoolIntArray _vertex_get_incoming_arcs(Variant p_vertex) const;

			PoolIntArray __vertex_get_outgoing_arcs(VertexID p_vertex) const;
			PoolIntArray _vertex_get_outgoing_arcs(Variant p_vertex) const;

			// Arc (GDScript)

			bool _arc_is_valid(const Variant p_id);

			void _arc_reverse(const Variant p_arc);

			VertexID _arc_split(const Variant p_arc);

			void _arc_set_source(const Variant p_arc, const Variant p_vertex);

			VertexID _arc_get_source(const Variant p_arc);

			void _arc_set_target(const Variant p_arc, const Variant p_vertex);

			VertexID _arc_get_target(const Variant p_arc);

		public:

			enum GraphComponent {
				VERTEX,
				ARC
			};

			// Graph (GDNative)

			VertexID add_vertex();

			Vector<VertexID> add_vertices(Vector<Variant> p_data);

			void erase_vertex(const VertexID p_vertex);

			void erase_vertices(Vector<VertexID> p_vertices);

			void reserve_vertices(int p_amount);

			Vector<VertexID> get_vertices();

			ArcID add_arc(VertexID p_source, VertexID p_target);

			Vector<ArcID> add_arcs(Vector<HashMap<String, Variant>> p_data);

			void erase_arc(ArcID p_arcs);

			void erase_arcs(Vector<ArcID> p_arcs);

			void reserve_arcs(int p_amount);

			Vector<ArcID> get_arcs();

			void clear();

			void set_data(ListDigraph::GraphComponent p_type, int64_t p_id, Variant p_data);

			Variant get_data(ListDigraph::GraphComponent p_type, int64_t p_id);

			void update_data(ListDigraph::GraphComponent p_type, const HashMap<int64_t, Variant> &p_data);

			// Vertex (GDNative)

			bool vertex_is_valid(VertexID p_id) const;

			void vertex_contract(VertexID p_vertex, VertexID p_other, bool p_remove = false);

			VertexID vertex_split(const VertexID p_vertex, const bool p_connect);

			Vector<ArcID> vertex_get_incoming_arcs(const VertexID p_vertex) const;

			Vector<ArcID> vertex_get_outgoing_arcs(const VertexID p_vertex) const;

			// Arc (GDNative)

			bool arc_is_valid(ArcID p_id) const;

			void arc_reverse(ArcID p_arc);

			VertexID arc_split(ArcID p_arc);

			void arc_set_source(const ArcID p_arc, const VertexID p_vertex);

			VertexID arc_get_source(const ArcID p_arc);

			void arc_set_target(const ArcID p_arc, const VertexID p_vertex);

			VertexID arc_get_target(const ArcID p_arc);

			static void _register_methods();

			ListDigraph();
			~ListDigraph();

			void _init();
	};
}
#endif /* !LIST_DIGRAPH_HPP */
