tool
class_name PropertyInfoFactory
extends Reference

static func from_dict(p_dict: Dictionary) -> Reference:
	var name: String = p_dict.name if p_dict.has("name") else ""
	var type: int = p_dict.type if p_dict.has("type") else TYPE_NIL
	var hint: int = p_dict.hint if p_dict.has("hint") else PROPERTY_HINT_NONE
	var hint_string: String = p_dict.hint_string if p_dict.has("hint_string") else ""
	var usage: int = p_dict.usage if p_dict.has("usage") else PROPERTY_USAGE_DEFAULT
	return PropertyInfo.new(name, type, hint, hint_string, usage)


static func new_nil(p_name: String) -> Reference:
	return PropertyInfo.new(p_name, TYPE_NIL, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR)


static func new_group(p_name: String, p_prefix: String = "") -> Reference:
	return PropertyInfo.new(p_name, TYPE_NIL, PROPERTY_HINT_NONE, p_prefix, PROPERTY_USAGE_GROUP)


static func new_array(p_name: String, p_hint: int = PROPERTY_HINT_NONE, p_hint_string: String = "", p_usage: int = PROPERTY_USAGE_DEFAULT) -> Reference:
	return PropertyInfo.new(p_name, TYPE_ARRAY, p_hint, p_hint_string, p_usage)


static func new_dictionary(p_name: String, p_hint: int = PROPERTY_HINT_NONE, p_hint_string: String = "", p_usage: int = PROPERTY_USAGE_DEFAULT) -> Reference:
	return PropertyInfo.new(p_name, TYPE_DICTIONARY, p_hint, p_hint_string, p_usage)


static func new_resource(p_name: String, p_hint_string: String = "", p_usage: int = PROPERTY_USAGE_DEFAULT) -> Reference:
	return PropertyInfo.new(p_name, TYPE_OBJECT, PROPERTY_HINT_RESOURCE_TYPE, p_hint_string, p_usage)


static func new_editor_only(p_name: String):
	return PropertyInfo.new(p_name, TYPE_NIL, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_SCRIPT_VARIABLE)


static func new_storage_only(p_name: String):
	return PropertyInfo.new(p_name, TYPE_NIL, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_SCRIPT_VARIABLE)
