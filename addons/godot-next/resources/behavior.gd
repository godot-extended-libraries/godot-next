tool
class_name Behavior
extends Resource
# author: xdgamestudios
# license: MIT
# description:
#	This is an abstract base "Behavior" class for use in the "Behaviors" node class.
#	"Behaviors" manages "Behavior" resources and calls notification methods that the Behavior implements.
# usage:
#	- Supported notifications:
#		_enter_tree() -> void
#		_exit_tree() -> void
#		_ready() -> void
#		_process(p_delta: float) -> void
#		_physics_process(delta: float) -> void:
#		_input(event: InputEvent) -> void:
#		_unhandled_input(event: InputEvent) -> void:
#		_unhandled_key_input(event: InputEventKey) -> void:
#	Note:
#		- If present notifications, are automatically triggered by the owner class.
#		- If the behavior is disabled its notifications will not be processed.

# A reference to the owning Behaviors node.
var owner: Node = null setget set_owner, get_owner

# Allows users to toggle processing callbacks on the owner.
var enabled: bool = true setget set_enabled, get_enabled

# This name is used to match the convention in Unity's MonoBehaviour class.
func _awake() -> void:
	pass


# This name is used to match the convention in Unity's MonoBehaviour class.
func _on_enable() -> void:
	pass


# This name is used to match the convention in Unity's MonoBehaviour class.
func _on_disable() -> void:
	pass


# Returns an instance of the stored Behavior resource from the owner.
func get_behavior(p_type: Script) -> Resource:
	return owner.get_element(p_type)


func set_enabled(p_enable: bool) -> void:
	if enabled == p_enable:
		return
	enabled = p_enable
	if p_enable:
		_on_enable()
		owner._add_to_callbacks()
	else:
		_on_disable()
		owner._remove_from_callbacks()


func get_enabled() -> bool:
	return enabled


func set_owner(p_owner: Node) -> void:
	assert(p_owner) # Must be assigned a valid owner at all times, except initially.
	owner = p_owner


func get_owner() -> Node:
	return owner


# Should only override if one wishes to create their own abstract Behaviors
# By default, the absence of this method is interpreted as a non-abstract type!
static func is_abstract() -> bool:
	return true
