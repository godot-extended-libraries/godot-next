tool
extends Control
class_name BackBufferPanel, "res://addons/godot-next/icons/icon_back_buffer.png"

onready var rid = get_canvas_item()

func _ready():
	update()

func _draw():
	var rect: Rect2 = get_global_rect()
	rect.position.y = get_viewport_rect().size.y - rect.position.y - rect.size.y
	VisualServer.canvas_item_set_copy_to_backbuffer(rid,visible,rect)
