# author: xdgamestudios
# license: MIT
# description: This is an abstract base "Behavior" class for use in the "Behaviors" node class.
#              "Behaviors" manages "Behavior" resources and calls notification methods that the Behavior implements.
# usage: 
# - Supported notifications:
#     _ready() -> void
#     _process(p_delta: float) -> void
#     _physics_process(delta: float) -> void:
#     _input(event: InputEvent) -> void:
#     _unhandled_input(event: InputEvent) -> void:
#     _unhandled_key_input(event: InputEventKey) -> void:
#     Note:
#     - If present notifications, are automatically triggered by the owner class.
#     - If the behavior is disabled its notifications will not be processed. 
tool
extends Resource
class_name Behavior

##### CLASSES #####

##### SIGNALS #####

##### CONSTANTS #####

##### PROPERTIES #####

# A reference to the owning Behaviors node.
var owner = null setget _set_owner, get_owner

# Allows users to toggle processing callbacks on the owner.
var _enabled: bool = true setget set_enabled, get_enabled

##### NOTIFICATIONS #####

##### OVERRIDES #####

##### VIRTUALS #####

# Should only override if one wishes to create their own abstract Behaviors
# By default, the absence of this method is interpreted as a non-abstract type!
static func is_abstract() -> bool:
	return true

##### PUBLIC METHODS #####

# Sets up the owner instance on the Behavior.
# 'awake' name is used to match the convention in Unity's MonoBehaviour class.
func awake(p_owner) -> void:
	owner = p_owner

# Returns an instance of the stored Behavior resource.
func get_behavior(p_type: Script) -> Behavior:
	return owner.get_behavior(p_type)

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####

func set_enabled(enable: bool) -> void:
	_enabled = enable
	var method = "_add_to_callbacks" if _enabled else "_remove_from_callbacks"
	owner.call(method, self)

func get_enabled() -> bool:
	return _enabled

#warning-ignore:unused_argument
func _set_owner(owner) -> void:
	assert false

func get_owner():
	return owner
