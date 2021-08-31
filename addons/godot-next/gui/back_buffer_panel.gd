extends Control
class_name BackBufferPanel, "../icons/icon_back_buffer_panel.svg"
# author: Tlitookilakin
# Description: Copies its render region to the render buffer for shader purposes

onready var rid = get_canvas_item() # get RID

func _draw():
	if rid == null:
		rid = get_canvas_item()
	var rect: Rect2 = get_global_rect()
	# screen-space coordinates are y-flipped
	rect.position.y = get_viewport_rect().size.y - rect.position.y - rect.size.y
	VisualServer.canvas_item_set_copy_to_backbuffer(rid,visible,rect)
