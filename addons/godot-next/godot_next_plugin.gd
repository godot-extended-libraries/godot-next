tool
extends EditorPlugin

const ResourceCollectionInspectorPlugin = preload("res://addons/godot-next/inspector_plugins/resource_collection_inspector_plugin.gd")

var resource_collection_inspector_plugin

func _enter_tree() -> void:
	resource_collection_inspector_plugin = ResourceCollectionInspectorPlugin.new()
	add_inspector_plugin(resource_collection_inspector_plugin)

func _exit_tree() -> void:
	remove_inspector_plugin(resource_collection_inspector_plugin)
