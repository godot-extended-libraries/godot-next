tool
extends Resource
class_name ResourceCollection

func can_contain(p_property: String) -> bool:
	assert false
	return false

func add_element(p_script: Script) -> void:
	assert false

func set_element(p_property: String, p_value) -> bool:
	assert false
	return false

func get_element(p_property: String) -> Resource:
	assert false
	return null

func get_collection_property_list() -> Array:
	assert false
	return []