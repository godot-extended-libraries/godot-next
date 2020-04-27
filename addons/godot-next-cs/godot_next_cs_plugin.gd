tool
extends EditorPlugin

const DelegationInspectorPlugin = preload("res://addons/godot-next/inspector_plugins/delegation_inspector_plugin.gd")

var delegation_inspector_plugin

func _enter_tree() -> void:
	# When this plugin node enters tree, add the custom types
	add_custom_type("Geometry2D", "CollisionShape2D", preload("2d/Geometry2D.cs"), preload("icons/icon_geometry_2d.svg"))
	add_custom_type("Trail2D", "Line2D", preload("2d/Trail2D.cs"), preload("icons/icon_trail_2d.svg"))
	add_custom_type("Trail3D", "ImmediateGeometry", preload("3d/Trail3D.cs"), preload("icons/icon_trail_3d.svg"))

	Singletons._register_editor_singletons(self)
	
	delegation_inspector_plugin = DelegationInspectorPlugin.new()
	add_inspector_plugin(delegation_inspector_plugin)


func _exit_tree() -> void:
	remove_inspector_plugin(delegation_inspector_plugin)
	remove_custom_type("Trail3D")
	remove_custom_type("Trail2D")
	remove_custom_type("Geometry2D")
