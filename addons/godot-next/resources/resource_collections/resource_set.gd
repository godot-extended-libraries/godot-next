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

const COLLECTION_NAME = "[ Set ]"

##### PROPERTIES #####

var _data := {}

##### NOTIFICATIONS #####

func _init() -> void:
	resource_name = COLLECTION_NAME

func _get(p_property: String):
	if p_property.begins_with(PREFIX):
		return _data.get(p_property.lstrip(PREFIX), null)
	return null

func _set(p_property: String, p_value) -> bool:
	if p_property.begins_with(PREFIX):
		var key = p_property.lstrip(PREFIX)
		if not p_value:
			#warning-ignore:return_value_discarded
			_data.erase(key)
			property_list_changed_notify()
			return true
		elif _data[key].get_script() == p_value.get_script():
			var res = _instantiate_script(p_value) if p_value is Script else p_value
			if res:
				_data[key] = res
		return true
	return false

func _get_property_list() -> Array:
	var list := []
	if not _type:
		return list
	
	list.append(PropertyInfo.new_group(PREFIX, PREFIX).to_dict())
	list.append(PropertyInfo.new_dictionary(PREFIX, PROPERTY_HINT_RESOURCE_TYPE, "#%s" % _type.get_path(), PROPERTY_USAGE_DEFAULT).to_dict())
	if _data.empty():
		list.append(PropertyInfo.new_nil(PREFIX + EMPTY_ENTRY).to_dict())
	for a_typename in _data:
		list.append(PropertyInfo.new_resource(PREFIX + a_typename, "", PROPERTY_USAGE_EDITOR).to_dict())
	
	return list

##### OVERRIDES #####

func _add_element(p_script: Script) -> void:
	_class_type.res = p_script
	var key := _class_type.get_name()
	if not _data.has(key):
		_data[key] = p_script.new()

func _refresh_data() -> void:
	if _type == null:
		clear()
		return
	var typenames := _data.keys()
	for a_typename in typenames:
		_class_type.res = _data[a_typename]
		if not _class_type.is_type(_type):
			#warning-ignore:return_value_discarded
			_data.erase(a_typename)

##### VIRTUALS #####

##### PUBLIC METHODS #####

func clear() -> void:
	_data.clear()

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func get_data() -> Dictionary:
	return _data