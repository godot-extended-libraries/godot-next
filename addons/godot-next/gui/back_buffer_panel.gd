tool
extends Control
class_name BackBufferPanel, "res://addons/godot-next/icons/icon_back_buffer.png"
# author: Tlitookilakin
# Description: Copies its render region to the render buffer for shader purposes

onready var rid = get_canvas_item() # get RID

func _ready():
	update() #first-time update

func _draw():
	var rect: Rect2 = get_global_rect()
	# screen-space coordinates are y-flipped
	rect.position.y = get_viewport_rect().size.y - rect.position.y - rect.size.y
	VisualServer.canvas_item_set_copy_to_backbuffer(rid,visible,rect)
