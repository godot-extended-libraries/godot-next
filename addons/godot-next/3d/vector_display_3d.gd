tool
class_name VectorDisplay3D
extends Node
# Displays Vector3 members in the editor via Position3D nodes.

export(String) var variable_name = ""
export(bool) var relative = true

var _old_variable_name = null
var _storage: Spatial


func _process(delta):
	if Engine.is_editor_hint():
		if not variable_name:
			if _old_variable_name != variable_name:
				_old_variable_name = variable_name
				printerr("VectorDisplay3D: Please provide a variable name.")
			return

		if not _storage:
			_storage = Spatial.new()
			get_tree().get_edited_scene_root().add_child(_storage)
			return

		for child in _storage.get_children():
			child.queue_free()

		var parent = get_parent()
		if relative:
			_storage.transform.origin = parent.global_transform.origin
		else:
			_storage.transform.origin = Vector3.ZERO

		var variable = parent.get(variable_name)
		if variable == null:
			if _old_variable_name != variable_name:
				_old_variable_name = variable_name
				printerr("VectorDisplay3D: Variable '" + variable_name + "' not found or invalid on parent node '" + get_parent().get_name() + "'.")
		elif variable is Vector3:
			_add_position_child(variable)
		elif variable is PoolVector3Array:
			for item in variable:
				_add_position_child(item)
		elif variable is Array:
			for item in variable:
				if item is Vector3:
					_add_position_child(item)


func _add_position_child(vector):
	var node = Position3D.new()
	node.transform.origin = vector
	_storage.add_child(node)
	node.set_owner(get_tree().get_edited_scene_root())
