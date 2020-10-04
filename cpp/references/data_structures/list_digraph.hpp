#ifndef LIST_DIGRAPH_HPP
#define LIST_DIGRAPH_HPP

#include <Godot.hpp>
#include <Reference.hpp>

#include <lemon/list_graph.h>

#include "hash_map.hpp"
#include "pair.hpp"
#include "vector.hpp"

namespace godot {

	typedef lemon::ListDigraph LemonDigraph;

	template <class T>
	struct DataWrapper {
		T *wrapper = nullptr;
		Variant data;
	};

	class ListDigraph;

	template <class T>
	class GraphComponent {
	protected:
		T _handle;
		ListDigraph *_list_digraph;
		bool _initialized;

	public:
		const T &get_handle() const {
			return _handle;
		}

		void initialize(T p_handle, ListDigraph *p_list_digraph) {
			_handle = p_handle;
			_list_digraph = p_list_digraph;
			_initialized = true;
		}

		virtual int get_id() const = 0;

		virtual bool is_valid() const = 0;

		virtual void set_data(Variant p_data) = 0;

		virtual Variant get_data() const = 0;
	};

	class Arc;

	class Vertex : public Reference, public GraphComponent<LemonDigraph::Node> {
		GODOT_CLASS(Vertex, Reference);

	protected:
		// ## Vertex (GDScript) ######################################### //

		void _contract(const Variant p_other, const Variant p_remove = true);

		Ref<Vertex> _split(const Variant p_connect = true);

		Array _get_incoming_arcs() const;

		Array _get_outgoing_arcs() const;

	public:
		// ## Vertex (GDNative) ######################################### //

		int get_id() const override;

		bool is_valid() const override;

		void set_data(Variant p_data) override;

		Variant get_data() const override;

		void contract(const Ref<Vertex> p_other, const bool p_remove = false);

		Ref<Vertex> split(const bool p_connect);

		Vector<Ref<Arc> > get_incoming_arcs() const;

		Vector<Ref<Arc> > get_outgoing_arcs() const;

		void _init();

		static void _register_methods();

		Vertex();
		~Vertex();
	};

	class Arc : public Reference, public GraphComponent<LemonDigraph::Arc> {
		GODOT_CLASS(Arc, Reference);

	protected:
		// ## Arc (GDScript) ############################################ //

		void _set_source(Variant p_vertex);

		void _set_target(Variant p_vertex);

	public:
		// ## Arc (GDNative) ############################################ //

		int get_id() const override;

		bool is_valid() const override;

		void set_data(Variant p_data) override;

		Variant get_data() const override;

		void reverse();

		Ref<Vertex> split();

		void set_source(Ref<Vertex> p_vertex);

		Ref<Vertex> get_source() const;

		void set_target(Ref<Vertex> p_vertex);

		Ref<Vertex> get_target() const;

		void _init();

		static void _register_methods();

		Arc();
		~Arc();
	};

	class ListDigraph : public Reference {
		GODOT_CLASS(ListDigraph, Reference);

		friend Vertex;
		friend Arc;

	private:
		LemonDigraph _graph;
		LemonDigraph::NodeIt _vertex_it;

		LemonDigraph::NodeMap<DataWrapper<Vertex> > _vertex_map;
		LemonDigraph::ArcMap<DataWrapper<Arc> > _arc_map;

	protected:
		// ## ListDigraph (Internal) #################################### //

		template <class B, class T, class H, class M>
		Ref<B> __create_instance(const H &p_handle, M &p_map) {
			Ref<B> ref = Ref<B>::__internal_constructor(T::_new());
			ref->initialize(p_handle, this);
			p_map[p_handle].wrapper = ref.ptr();
			return ref;
		}

		template <class T>
		Ref<Vertex> __get_instance(const LemonDigraph::Node &p_node) {
			if (_vertex_map[p_node].wrapper != nullptr) {
				return Object::cast_to<Vertex>((T *)_vertex_map[p_node].wrapper);
			}
			return __create_instance<Vertex, T>(p_node, _vertex_map);
		}

		template <class T>
		Ref<Arc> __get_instance(const LemonDigraph::Arc &p_arc) {
			if (_arc_map[p_arc].wrapper != nullptr) {
				return Object::cast_to<Arc>((T *)_arc_map[p_arc].wrapper);
			}
			return __create_instance<Arc, T>(p_arc, _arc_map);
		}

		template <typename T>
		void __update_data(const Vector<Pair<Ref<T>, Variant> > &p_data) {
			for (int i = 0; i < p_data.size(); ++i) {
				Pair<Ref<T>, Variant> comp_to_value = p_data[i];
				ERR_FAIL_COND(!comp_to_value.first.is_valid());

				comp_to_value.first->set_data(comp_to_value.second);
			}
		}

		const LemonDigraph &get_graph() const;

		virtual Ref<Vertex> get_instance(const LemonDigraph::Node &p_node);

		virtual Ref<Arc> get_instance(const LemonDigraph::Arc &p_arc);

		// ## ListDigraph (GDScript) #################################### //

		bool _iter_init();
		bool _iter_next();
		Ref<Vertex> _iter_get();

		Array add_vertices(const Array &p_data, const bool &p_return);
		Array _add_vertices(Variant p_data, Variant p_return = false);

		void _erase_vertex(Variant p_vertex);

		void erase_vertices(const Array &p_vertices);
		void _erase_vertices(Variant p_vertices);

		void _reserve_vertices(Variant p_amount);

		Array _get_vertices();

		Ref<Arc> _add_arc(Variant p_source, Variant p_target);

		Array add_arcs(const Array &p_data, const bool &p_return);
		Array _add_arcs(Variant p_data, Variant p_return = false);

		void _erase_arc(const Variant p_arc);

		void erase_arcs(const Array &p_arcs);
		void _erase_arcs(Variant p_arcs);

		void _reserve_arcs(Variant p_amount);

		Array _get_arcs();

		void update_data(const Dictionary &p_data);
		void _update_data(Variant p_data);

	public:
		// ## ListDigraph (GDNative) #################################### //

		Ref<Vertex> add_vertex();

		Vector<Ref<Vertex> > add_vertices(const Vector<Variant> &p_data, const bool p_return = false);

		void erase_vertex(Ref<Vertex> p_vertex);

		void erase_vertices(const Vector<Ref<Vertex> > &p_vertices);

		void reserve_vertices(const int p_amount);

		Vector<Ref<Vertex> > get_vertices();

		int count_vertices() const;

		Ref<Arc> add_arc(const Ref<Vertex> p_source, const Ref<Vertex> p_target);

		Vector<Ref<Arc> > add_arcs(const Vector<HashMap<String, Variant> > &p_data, const bool p_return = false);

		void erase_arc(Ref<Arc> p_arcs);

		void erase_arcs(const Vector<Ref<Arc> > &p_arcs);

		void reserve_arcs(int p_amount);

		Vector<Ref<Arc> > get_arcs();

		int count_arcs() const;

		void clear();

		void update_data(const Vector<Pair<Ref<Vertex>, Variant> > &p_data);

		void update_data(const Vector<Pair<Ref<Arc>, Variant> > &p_data);

		void _init();

		static void _register_methods();

		ListDigraph();
		~ListDigraph();
	};
} // namespace godot
#endif /* !LIST_DIGRAPH_HPP */
