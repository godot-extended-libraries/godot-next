# author: xdgamestudios
# license: MIT
# description: A ResourceCollection implementation that manages a Set of Resources.
#              One can add only one instance of any given Resource type.
# deps:
# - ResourceCollection
# - PropertyInfo
tool
extends ResourceCollection
class_name ResourceSet

##### CLASSES #####

##### SIGNALS #####

##### CONSTANTS #####

const DELIMITER = "_?_"

const EMPTY_ENTRY = "[ Empty ]"
const COLLECTION_NAME = "[ Set ]"

##### PROPERTIES #####

var _name: = ""
var _type: Script = null

var _data := {}

##### NOTIFICATIONS #####

func _get_property_list() -> Array:
	return [ PropertyInfo.new_dictionary("_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE).to_dict() ]

##### OVERRIDES #####

func can_contain(p_property: String) -> bool:
	if not _name or not _type:
		return false
	return p_property.begins_with(_name + DELIMITER) and not p_property.ends_with(EMPTY_ENTRY)

func add_element(p_script: Script) -> void:
	var key := ClassType.new(p_script).get_name()
	if not _data.has(key):
		_data[key] = p_script.new()

func set_element(p_property: String, p_value) -> bool:
	var key := p_property.lstrip(_name + DELIMITER)
	if not p_value:
		#warning-ignore:return_value_discarded
		_data.erase(key)
	else:
		_data[key] = p_value
	return true

func get_element(p_property: String) -> Resource:
	var key := p_property.lstrip(_name + DELIMITER)
	return _data[key] if _data.has(key) else null

func get_collection_property_list() -> Array:
	var list = []
	
	if not _name or not _type:
		return list
	
	var group_prefix = _name + DELIMITER
	var item_prefix = _name + DELIMITER
	list.append(PropertyInfo.new_group("%s %s" % [_name, COLLECTION_NAME], group_prefix).to_dict())
	list.append(PropertyInfo.new_dictionary(_name, PROPERTY_HINT_RESOURCE_TYPE, "#%s" % _type.get_path(), PROPERTY_USAGE_EDITOR).to_dict())
	
	if _data.empty():
		list.append(PropertyInfo.new_nil("%s%s" % [group_prefix, EMPTY_ENTRY]).to_dict())
	for item in _data:
		list.append(PropertyInfo.new_resource("%s%s" % [item_prefix, item], "", PROPERTY_USAGE_EDITOR).to_dict())
	return list

##### VIRTUALS #####

##### PUBLIC METHODS #####

func setup(p_name: String, p_type: Script) -> void:
	_name = p_name
	_type = p_type

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func get_data() -> Dictionary:
	return _data