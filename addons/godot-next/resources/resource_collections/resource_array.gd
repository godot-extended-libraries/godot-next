tool
class_name ResourceArray
extends ResourceCollection
# author: xdgamestudios
# license: MIT
# description:
#	A ResourceCollection implementation that manages an Array of Resources.
#	One can add multiple instances of any given Resource type.
# deps:
#	- ResourceCollection
#	- PropertyInfo

const COLLECTION_NAME = "[ Array ]"

var _data := []

func _init() -> void:
	resource_name = COLLECTION_NAME


func clear() -> void:
	_data.clear()


func get_data() -> Array:
	return _data


func _get(p_property: String):
	if p_property.begins_with(DATA_PREFIX):
		var index := int(p_property.trim_prefix(DATA_PREFIX + "item_"))
		return _data[index] if index < _data.size() else null
	return null


func _set(p_property, p_value):
	if p_property.begins_with(DATA_PREFIX):
		var index := int(p_property.trim_prefix(DATA_PREFIX + "item_"))
		if not p_value:
			_data.remove(index)
			property_list_changed_notify()
		else:
			var res = _instantiate_script(p_value) if p_value is Script else p_value
			_class_type.res = res
			if res and _class_type.is_type(_type):
				_data[index] = res
			property_list_changed_notify()
		return true
	return false


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


func _export_data_group() -> Array:
	var list := ._export_data_group()
	list.append(PropertyInfoFactory.new_storage_only("_data").to_dict())
	if _data.empty():
		list.append(PropertyInfoFactory.new_nil(DATA_PREFIX + EMPTY_ENTRY).to_dict())
	for an_index in _data.size():
		list.append(PropertyInfoFactory.new_resource("%sitem_%s" % [DATA_PREFIX, an_index], "", PROPERTY_USAGE_EDITOR).to_dict())
	return list
