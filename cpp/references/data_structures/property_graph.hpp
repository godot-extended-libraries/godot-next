#ifndef PROPERTY_GRAPH_HPP
#define PROPERTY_GRAPH_HPP

#include <Godot.hpp>
#include <Reference.hpp>

#include "label_container_trait.hpp"
#include "list_digraph.hpp"
#include "property_container_trait.hpp"

namespace godot {
	class PropertyGraph;

	class PropertyVertex : public Vertex, public LabelContainerTrait, public PropertyContainerTrait {
		GODOT_SUBCLASS(PropertyVertex, Vertex);

		friend class PropertyGraph;

	protected:
		Set<String> &get_label_set() override;
		HashMap<String, Variant> &get_property_map() override;

		// ## PropertyVertex (GDScript) ################################# //

		bool _set(String p_property, Variant p_value);

		Variant _get(String p_property);

		void _set_labels(Variant p_labels);

		void _insert_labels(Variant p_labels);

		void _erase_labels(Variant p_labels);

		Array _get_labels();

		void _set_properties(Variant p_data);

		void _merge_properties(Variant p_data);

		void _insert_properties(Variant p_data);

		void _erase_properties(Variant p_names);

		Dictionary _get_properties();

	public:
		// ## PropertyVertex (GDNative) ################################# //

		void _init();

		static void _register_methods();

		PropertyVertex();
		~PropertyVertex();
	};

	class PropertyArc : public Arc, public PropertyContainerTrait {
		GODOT_SUBCLASS(PropertyArc, Arc);

		friend class PropertyGraph;

	protected:
		HashMap<String, Variant> &get_property_map() override;

		// ## PropertyArc (GDScript) #################################### //

		bool _set(String p_property, Variant p_value);

		Variant _get(String p_property);

		void _set_label(Variant p_label);

		void _set_properties(Variant p_data);

		void _merge_properties(Variant p_data);

		void _insert_properties(Variant p_data);

		void _erase_properties(Variant p_names);

		Dictionary _get_properties();

	public:
		// ## PropertyArc (GDNative) #################################### //

		void set_label(const String &p_label);

		String get_label() const;

		void _init();

		static void _register_methods();

		PropertyArc();
		~PropertyArc();
	};

	class PropertyGraph : public ListDigraph {
		GODOT_SUBCLASS(PropertyGraph, ListDigraph);

		friend class PropertyVertex;
		friend class PropertyArc;

	private:
		struct PropertyVertexHash {
			std::size_t operator()(const PropertyVertex &k) const {
				return k.get_id();
			}
		};
		struct PropertyArcHash {
			std::size_t operator()(const PropertyArc &k) const {
				return k.get_id();
			}
		};

		struct PropertyVertexData {
			Set<String> labels;
			HashMap<String, Variant> properties;
		};
		struct PropertyArcData {
			String label;
			HashMap<String, Variant> properties;
		};

		LemonDigraph::NodeMap<PropertyVertexData> _vertex_data;
		LemonDigraph::ArcMap<PropertyArcData> _arc_data;

	protected:
		// ## PropertyGraph (Internal) ################################## //

		template <class T, class H>
		void __set_properties(const HashMap<T, HashMap<String, Variant>, H> &p_data) {
			typename HashMap<T, HashMap<String, Variant>, H>::const_iterator comp_to_properties;

			for (comp_to_properties = p_data.begin(); comp_to_properties != p_data.end(); ++comp_to_properties) {
				T *property_compoment = (T *)&comp_to_properties->first;
				property_compoment->set_properties(comp_to_properties->second);
			}
		}

		template <class T, class H>
		void __merge_properties(const HashMap<T, HashMap<String, Variant>, H> &p_data) {
			typename HashMap<T, HashMap<String, Variant>, H>::const_iterator comp_to_properties;

			for (comp_to_properties = p_data.begin(); comp_to_properties != p_data.end(); ++comp_to_properties) {
				T *property_compoment = (T *)&comp_to_properties->first;
				property_compoment->merge_properties(comp_to_properties->second);
			}
		}

		template <class T, class H>
		void __insert_properties(const HashMap<T, HashMap<String, Variant>, H> &p_data) {
			typename HashMap<T, HashMap<String, Variant>, H>::const_iterator comp_to_properties;

			for (comp_to_properties = p_data.begin(); comp_to_properties != p_data.end(); ++comp_to_properties) {
				T *property_compoment = (T *)&comp_to_properties->first;
				property_compoment->insert_properties(comp_to_properties->second);
			}
		}

		template <class T, class H>
		void __erase_properties(const HashMap<T, Set<String>, H> &p_data) {
			typename HashMap<T, Set<String>, H>::const_iterator comp_to_names;

			for (comp_to_names = p_data.begin(); comp_to_names != p_data.end(); ++comp_to_names) {
				T *property_compoment = (T *)&comp_to_names->first;
				property_compoment->erase_properties(comp_to_names->second);
			}
		}

		virtual Ref<Vertex> get_instance(const LemonDigraph::Node &p_node) override;

		virtual Ref<Arc> get_instance(const LemonDigraph::Arc &p_arc) override;

		// ## PropertyGraph (GDScript) ################################## //

		void set_labels(const Dictionary &p_data);
		void _set_labels(Variant p_data);

		void insert_labels(const Dictionary &p_data);
		void _insert_labels(Variant p_data);

		void erase_labels(const Dictionary &p_data);
		void _erase_labels(Variant p_data);

		void set_properties(const Dictionary &p_data);
		void _set_properties(Variant p_data);

		void merge_properties(const Dictionary &p_data);
		void _merge_properties(Variant p_data);

		void insert_properties(const Dictionary &p_data);
		void _insert_properties(Variant p_data);

		void erase_properties(const Dictionary &p_data);
		void _erase_properties(Variant p_data);

	public:
		// ## PropertyGraph (GDNative) ################################## //

		void set_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data);
		void set_labels(const HashMap<PropertyArc, String, PropertyArcHash> &p_data);

		void insert_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data);

		void erase_labels(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data);

		void set_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data);
		void set_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data);

		void merge_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data);
		void merge_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data);

		void insert_properties(const HashMap<PropertyVertex, HashMap<String, Variant>, PropertyVertexHash> &p_data);
		void insert_properties(const HashMap<PropertyArc, HashMap<String, Variant>, PropertyArcHash> &p_data);

		void erase_properties(const HashMap<PropertyVertex, Set<String>, PropertyVertexHash> &p_data);
		void erase_properties(const HashMap<PropertyArc, Set<String>, PropertyArcHash> &p_data);

		void _init();

		static void _register_methods();

		PropertyGraph();
		~PropertyGraph();
	};
} // namespace godot
#endif /* !PROPERTY_GRAPH_HPP */
