# author: xdgamestudios
# license: MIT
# description: An abstract base class for data structures that store Resource objects.
#              Uses a key-value store, but can also append items.
tool
extends Resource
class_name ResourceCollection

##### CLASSES #####

##### SIGNALS #####

##### CONSTANTS #####

const PREFIX = "_data"
const EMPTY_ENTRY = "[ Empty ]"

##### PROPERTIES #####

var _type: Script = null
var _type_readonly: bool = false
#warning-ignore:unused_class_variable
var _class_type: ClassType = ClassType.new()

##### NOTIFICATIONS #####

func _get(p_property: String):
	if p_property == "base_type":
		return _type
	return null

func _set(p_property: String, p_value) -> bool:
	if p_property == "base_type":
		if _type == p_value:
			return true
		_type = p_value
		_refresh_data()
		property_list_changed_notify()
		return true
	return false

func _get_property_list() -> Array:
	return [ PropertyInfo.new_resource("base_type", "Script").to_dict() ] if not _type_readonly else []

##### OVERRIDES #####

##### VIRTUALS #####

# Append an element to the collection.
#warning-ignore:unused_argument
func _add_element(p_script: Script) -> void:
	assert false

# Refresh the data upon type change.
func _refresh_data() -> void:
	assert false

##### PUBLIC METHODS #####

func clear() -> void:
	assert false

##### PRIVATE METHODS #####

func _instantiate_script(p_script: Script) -> Resource:
	var res: Resource = null
	if ClassDB.is_parent_class(p_script.get_instance_base_type(), "Resource"):
		push_warning("Must assign non-Script Resource instances. Auto-instantiating the given Resource script.")
		res = p_script.new()
	else:
		push_error("Must assign non-Script Resource instances. Fallback error: cannot auto-instantiate non-Resource scripts into ResourceCollection.")
	return res

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func get_base_type() -> Script:
	return _type

func set_base_type(p_type: Script) -> void:
	if _type == p_type:
		return
	_type = p_type
	property_list_changed_notify()

func is_type_readonly() -> bool:
	return _type_readonly

func set_type_readonly(read_only: bool) -> void:
	if _type_readonly == read_only:
		return
	_type_readonly = read_only
	property_list_changed_notify()
