# author: xdgamestudios
# license: MIT
# description: A ResourceCollection implementation that manages an Array of Resources.
#              One can add multiple instances of any given Resource type.
# deps:
# - ResourceCollection
# - PropertyInfo
tool
extends ResourceCollection
class_name ResourceArray

##### CLASSES #####

##### SIGNALS #####

##### CONSTANTS #####

const DELIMITER = "_#_"

const EMPTY_ENTRY = "[ Empty ]"
const COLLECTION_NAME = "[ Array ]"

##### PROPERTIES #####

var _name: = ""
var _type: Script = null

var _data := []

##### NOTIFICATIONS #####

func _get_property_list() -> Array:
	return [ PropertyInfo.new_array("_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE).to_dict() ]

##### OVERRIDES #####

func can_contain(p_property: String) -> bool:
	if not _name or not _type:
		return false
	return p_property.begins_with(_name + DELIMITER) and not p_property.ends_with(EMPTY_ENTRY)

func add_element(script) -> void:
	_data.append(script.new())

func set_element(p_property: String, p_value) -> bool:
	var index := int(p_property.lstrip(_name + DELIMITER + "item_"))
	if not p_value:
		_data.remove(index)
	else:
		_data[index] = p_value
	return true

func get_element(p_property: String):
	var index := int(p_property.lstrip(_name + DELIMITER + "item_"))
	return _data[index] if index < _data.size() else null

func get_collection_property_list() -> Array:
	var list = []
	
	if not _name or not _type:
		return list
		
	var group_prefix = _name + DELIMITER
	var item_prefix = _name + DELIMITER + "item_"
	
	list.append(PropertyInfo.new_group("%s %s" % [_name, COLLECTION_NAME], group_prefix).to_dict())
	list.append(PropertyInfo.new_array(_name, PROPERTY_HINT_RESOURCE_TYPE, "#%s" % _type.get_path()).to_dict())
	
	if _data.empty():
		list.append(PropertyInfo.new_nil("%s%s" % [group_prefix, EMPTY_ENTRY]).to_dict())
	for idx in _data.size():
		list.append(PropertyInfo.new_resource("%s%s" % [item_prefix, idx], "", PROPERTY_USAGE_EDITOR).to_dict())
	return list

##### VIRTUALS #####

##### PUBLIC METHODS #####

func setup(p_name: String, p_type: Script) -> void:
	_name = p_name
	_type = p_type

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func get_data() -> Array:
	return _data