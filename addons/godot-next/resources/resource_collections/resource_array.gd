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

const COLLECTION_NAME = "[ Array ]"

##### PROPERTIES #####

var _data := []

##### NOTIFICATIONS #####

func _init() -> void:
	resource_name = COLLECTION_NAME

func _get(p_property: String):
	if p_property.begins_with(PREFIX):
		var index := int(p_property.lstrip(PREFIX + "item_"))
		return _data[index] if index < _data.size() else null
	return null

func _set(p_property, p_value):
	if p_property.begins_with(PREFIX):
		var index := int(p_property.lstrip(PREFIX + "item_"))
		if not p_value:
			_data.remove(index)
			property_list_changed_notify()
		else:
			var res = _instantiate_script(p_value) if p_value is Script else p_value
			_class_type.res = res
			if res and _class_type.is_type(_type):
				_data[index] = res
		return true
	return false

func _get_property_list() -> Array:
	var list = []
	if not _type:
		return list
	
	list.append(PropertyInfo.new_group(PREFIX, PREFIX).to_dict())
	list.append(PropertyInfo.new_array(PREFIX, PROPERTY_HINT_RESOURCE_TYPE, "#%s" % _type.get_path(), PROPERTY_USAGE_DEFAULT).to_dict())
	if _data.empty():
		list.append(PropertyInfo.new_nil(PREFIX + EMPTY_ENTRY).to_dict())
	for an_index in _data.size():
		list.append(PropertyInfo.new_resource("%sitem_%s" % [PREFIX, an_index], "", PROPERTY_USAGE_EDITOR).to_dict())
	
	return list

##### OVERRIDES #####

func _add_element(script) -> void:
	_data.append(script.new())

func _refresh_data() -> void:
	if _type == null:
		clear()
		return
	var data_cache := _data.duplicate()
	for a_resource in data_cache:
		if not ClassType.new(a_resource).is_type(_type):
			_data.erase(a_resource)

##### VIRTUALS #####

##### PUBLIC METHODS #####

func clear() -> void:
	_data.clear()

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func get_data() -> Array:
	return _data