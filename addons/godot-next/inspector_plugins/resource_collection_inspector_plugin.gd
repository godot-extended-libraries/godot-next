# author: xdgamestudios
# license: MIT
# description: This script is injected into the editor upon loading the plugin.
#              Generates a custom toolbar for ResourceCollection property lists.
# deps:
# - ClassType
tool
extends EditorInspectorPlugin

##### CONSTANTS #####

const ADD_ICON = preload("res://addons/godot-next/icons/icon_add.svg")

##### PROPERTIES #####

##### NOTIFICATIONS #####

##### VIRTUALS #####

#warning-ignore:unused_argument
func can_handle(p_object) -> bool:
	return true

#warning-ignore:unused_argument
func parse_property(p_object, p_type, p_path, p_hint, p_hint_text, p_usage) -> bool:
	match p_type:
		TYPE_ARRAY, TYPE_DICTIONARY:
			if p_hint == PROPERTY_HINT_RESOURCE_TYPE and p_hint_text.begins_with("#"):
				add_custom_control(_generate_gui(p_object, p_path, p_hint_text.lstrip("#")))
				return true
	return false

##### PRIVATE METHODS #####

func _find_inheritors(p_type_path: String) -> Array:
	var ct = ClassType.new(p_type_path, true)
	var list = ct.get_deep_inheritors_list()
	var type_map = ct.get_deep_type_map()
	var scripts = []
	for a_name in list:
		scripts.append(load(type_map[a_name].path))
	return scripts

func _generate_gui(p_object: Object, p_path: String, p_type_path: String) -> Control:
	
	var hbox := HBoxContainer.new()
	
	var elements := _find_inheritors(p_type_path)
	
	var dropdown := _generate_type_dropdown(elements)
	var button := _generate_add_button()
	
	#warning-ignore:return_value_discarded
	button.connect("pressed", self, "_on_add_button_pressed", [p_object, p_path, dropdown])

	dropdown.size_flags_horizontal = HBoxContainer.SIZE_EXPAND_FILL
	
	hbox.add_child(dropdown)
	hbox.add_child(button)
	
	return hbox

func _generate_type_dropdown(p_elements: Array) -> Control:
	var dropdown := OptionButton.new()
	
	for i in p_elements.size():
		var ct = ClassType.new(p_elements[i])
		dropdown.add_item(ct.get_name(), i)
		dropdown.set_item_metadata(i, p_elements[i])
	
	return dropdown

func _generate_add_button() -> Control:
	var button = ToolButton.new()
	button.icon = ADD_ICON
	return button

##### CONNECTIONS #####

func _on_add_button_pressed(p_object: Object, p_path: String, p_dropdown: OptionButton):
	var index := p_dropdown.get_selected_id()
	var script: Script = p_dropdown.get_item_metadata(index) as Script
	
	if p_object.has_method("_add_element"):
		p_object.call("_add_element", p_path, script)
	else:
		push_warning("The ResourceCollection at <%s> does not implement '_add_element(variable: String, script: Script)'." % p_object.get_script().resource_path)
	p_object.property_list_changed_notify()
