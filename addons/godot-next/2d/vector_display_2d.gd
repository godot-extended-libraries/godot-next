tool
class_name VectorDisplay2D
extends Node
# Displays Vector2 members in the editor via Position2D nodes.

export(String) var variable_name = ""
export(bool) var relative = true

var _old_variable_name = null
var _storage: Node2D


func _process(delta):
	if Engine.is_editor_hint():
		if not variable_name:
			if _old_variable_name != variable_name:
				_old_variable_name = variable_name
				printerr("VectorDisplay2D: Please provide a variable name.")
			return

		if not _storage:
			_storage = Node2D.new()
			get_tree().get_edited_scene_root().add_child(_storage)
			return

		for child in _storage.get_children():
			child.queue_free()

		var parent = get_parent()
		if relative:
			_storage.transform.origin = parent.global_transform.origin
		else:
			_storage.transform.origin = Vector2.ZERO

		var variable = parent.get(variable_name)
		if variable == null:
			if _old_variable_name != variable_name:
				_old_variable_name = variable_name
				printerr("VectorDisplay2D: Variable '" + variable_name + "' not found or invalid on parent node '" + get_parent().get_name() + "'.")
		elif variable is Vector2:
			_add_position_child(variable)
		elif variable is PoolVector2Array:
			for item in variable:
				_add_position_child(item)
		elif variable is Array:
			for item in variable:
				if item is Vector2:
					_add_position_child(item)


func _add_position_child(vector):
	var node = Position2D.new()
	node.transform.origin = vector
	_storage.add_child(node)
	node.set_owner(get_tree().get_edited_scene_root())
