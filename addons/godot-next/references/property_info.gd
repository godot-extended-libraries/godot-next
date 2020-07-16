tool
class_name PropertyInfo
extends Reference
# author: xdgamestudios
# license: MIT
# description:
#	A wrapper and utility class for generating PropertyInfo
#	Dictionaries, of which Object._get_property_list()
#	returns an Array.

var name: String
var type: int
var hint: int
var hint_string: String
var usage: int

func _init(p_name: String = "", p_type: int = TYPE_NIL, p_hint: int = PROPERTY_HINT_NONE, p_hint_string: String = "", p_usage: int = PROPERTY_USAGE_DEFAULT) -> void:
	name = p_name
	type = p_type
	hint = p_hint
	hint_string = p_hint_string
	usage = p_usage


func to_dict() -> Dictionary:
	return {
		"name": name,
		"type": type,
		"hint": hint,
		"hint_string": hint_string,
		"usage": usage
	}


