# author: xdgamestudios
# license: MIT
# description: Manages a ResourceSet of Behavior resources and delegates Node callbacks to each instance.
#              As a ResourceSet, only one Behavior of any given type is allowed on a single Behaviors node.
# deps:
# - ResourceSet
# - PropertyInfo
# - Behavior
# - ClassType
# usage:
# - Creating:
#     behaviors = Behaviors.new()
# - Adding Behaviors:
#     behaviors.add_behavior(MyBehavior) # Returns a new or pre-existing instance of the Behavior or null if given an invalid Behavior script.
# - Checking Behaviors:
#     behaviors.has_behavior(MyBehavior) # Returns true if the Behavior exists in the collection.
# - Retrieving Behaviors:
#     behaviors.get_behavior(MyBehavior) # Returns the Behavior instance of the given type or null if not in the collection.
# - Removing Behaviors:
#     behaviors.remove_behavior(MyBehavior) # Removes the Behavior from the collection. Returns true if successful. Else, returns false.
tool
extends Node
class_name Behaviors

##### PROPERTIES #####

var _behaviors: ResourceSet = null

var _callbacks: Dictionary = {
	"_ready" : {},
	"_process" : {},
	"_physics_process" : {},
	"_input" : {},
	"_unhandled_input" : {},
	"_unhandled_key_input" : {}
}

##### NOTIFICATIONS #####

func _set(p_property: String, p_value) -> bool:
	if _behaviors.can_contain(p_property):
		#warning-ignore:return_value_discarded
		_behaviors.set_element(p_property, p_value)
		property_list_changed_notify()
		return true
	return false

func _get(p_property: String):
	if _behaviors.can_contain(p_property):
		return _behaviors.get_element(p_property)
	return null

func _get_property_list() -> Array:
	if not _behaviors:
		_behaviors = ResourceSet.new()
	_behaviors.setup("_behaviors", Behavior)
	var list := []
	list.append(PropertyInfo.new_dictionary("_behaviors", 0, "", PROPERTY_USAGE_STORAGE).to_dict())
	list += _behaviors.get_collection_property_list()
	return list

func _ready() -> void:
	if not Engine.editor_hint:
		var behaviors = _behaviors.get_data()
		for behavior in behaviors.values():
			_initialize_behavior(behavior)
		
		for behavior in _callbacks["_ready"]:
			behavior._ready()
	_check_for_empty_callbacks()

func _process(delta: float) -> void:
	_handle_notification("_process", delta)

func _physics_process(delta: float) -> void:
	_handle_notification("_physics_process", delta)

func _input(event: InputEvent) -> void:
	_handle_notification("_input", event)

func _unhandled_input(event: InputEvent) -> void:
	_handle_notification("_unhandled_input", event)

func _unhandled_key_input(event: InputEventKey) -> void:
	_handle_notification("_unhandled_key_input", event)

##### VIRTUALS #####

func _add_element(p_variable: String, p_script: Script) -> void:
	var collection: ResourceCollection = get(p_variable)
	collection.add_element(p_script)

##### PUBLIC METHODS #####

func add_behavior(p_type: Script) -> Behavior:
	var behaviors = _behaviors.get_data()
	
	var ct = ClassType.new(p_type)
	if not ct.is_type(Behavior):
		return null
	if has_behavior(p_type):
		return get_behavior(p_type)
		
	var behavior: Behavior = p_type.new()
	var behavior_name: String = ct.get_script_class()
	
	behaviors[behavior_name] = behavior
	_initialize_behavior(behavior)
	
	return behavior

func get_behavior(p_type: Script) -> Behavior:
	var behaviors = _behaviors.get_data()
	return behaviors.get(ClassType.new(p_type).get_script_class(), null);

func has_behavior(p_type: Script) -> bool:
	var behaviors = _behaviors.get_data()
	return behaviors.has(ClassType.new(p_type).get_script_class())

func remove_behavior(p_type: Script) -> bool:
	var behaviors = _behaviors.get_data()
	
	var type_name := ClassType.new(p_type).get_script_class()
	if not behaviors.has(type_name):
		return false
	var behavior = behaviors[type_name]
	#warning-ignore:return_value_discarded
	behaviors.erase(type_name)
	_remove_from_callbacks(behavior)
	behavior.free()
	return true

##### PRIVATE METHODS #####

func _handle_notification(p_name: String, p_param) -> void:
    for a_behavior in _callbacks[p_name]:
        a_behavior.call(p_name, p_param)

func _initialize_behavior(p_behavior: Behavior) -> void:
	p_behavior.awake(self)
	#warning-ignore:return_value_discarded
	p_behavior.connect("script_changed", self, "_refresh_callbacks", [p_behavior])
	_add_to_callbacks(p_behavior)

func _add_to_callbacks(p_behavior: Behavior) -> void:
	for callback in _callbacks:
		if p_behavior.has_method(callback) and p_behavior.get_enabled():
			_callbacks[callback][p_behavior] = null

func _remove_from_callbacks(p_behavior: Behavior) -> void:
	for callback in _callbacks:
		_callbacks[callback].erase(p_behavior)
	_check_for_empty_callbacks()

func _check_for_empty_callbacks() -> void:
	for callback_key in _callbacks:
		match callback_key:
			"_process":
				set_process(not _callbacks[callback_key].empty())
			"_physics_process":
				set_physics_process(not _callbacks[callback_key].empty())
			"_input":
				set_process_input(not _callbacks[callback_key].empty())
			"_unhandled_input":
				set_process_unhandled_input(not _callbacks[callback_key].empty())
			"_unhandled_key_input":
				set_process_unhandled_key_input(not _callbacks[callback_key].empty())

##### CONNECTIONS #####

func _on_behavior_script_change(p_behavior: Behavior) -> void:
	_remove_from_callbacks(p_behavior)
	_add_to_callbacks(p_behavior)

##### SETTERS AND GETTERS #####