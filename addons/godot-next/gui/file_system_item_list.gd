# FileSystemItemList
# author: willnationsdev
# brief_description: A VBoxItemList for editing lists of files or directories.
tool
extends VBoxItemList
class_name FileSystemItemList, "res://addons/godot-next/icons/icon_file_system_item_list.svg"

##### CONSTANTS #####

enum FileSystemTypes {
	FILE,
	DIR
}

##### PROPERTIES #####

var fd: FileDialog
var selected_item: FileSystemItem

##### CLASSES #####

class FileSystemItem:
	extends HBoxContainer
	var value: String setget _set_value, _get_value
	var mode: int
	
	var btn: Button
	
	func init(p_index: int, p_path: String, p_mode: int):
		value = p_path
		btn = Button.new()
		match p_mode:
			FileDialog.MODE_OPEN_FILE:
				mode = FileSystemTypes.FILE
				btn.text = "File: [None]"
			FileDialog.MODE_OPEN_DIR:
				mode = FileSystemTypes.DIR
				btn.text = "Dir: [None]"
		add_child(btn)
		#warning-ignore:unused_return_value
		btn.connect("pressed", get_node("../../.."), "_on_fs_btn_pressed", [self])
		btn.size_flags_horizontal = SIZE_EXPAND_FILL
	
	func _set_value(p_path: String):
		value = p_path
		var text = p_path.get_file() if not p_path.empty() else "[None]"
		match mode:
			FileSystemTypes.FILE:
				btn.text = "File: " + text
			FileSystemTypes.DIR:
				btn.text = "Dir: " + text
		btn.set_tooltip(p_path)
	
	func _get_value() -> String:
		return value

##### NOTIFICATIONS #####

func _init(p_title: String = "", p_type: int = FileSystemTypes.FILE):
	set_title(p_title)
	set_item_script(FileSystemItem)
	
	fd = FileDialog.new()
	match p_type:
		FileSystemTypes.FILE:
			fd.mode = FileDialog.MODE_OPEN_FILE
			fd.connect("file_selected", self, "_on_item_selected")
		FileSystemTypes.DIR:
			fd.mode = FileDialog.MODE_OPEN_DIR
			fd.connect("dir_selected", self, "_on_item_selected")
		_:
			assert false and "Bad p_type supplied to FileSystemItemList.new()"
	fd.dialog_hide_on_ok = true
	add_child(fd)

func _enter_tree():
	fd.owner = owner

##### OVERRIDES #####

func _item_inserted(p_index: int, p_control: Control):
	assert p_control
	p_control.init(p_index, "", fd.mode)
	p_control.size_flags_horizontal = SIZE_EXPAND_FILL

##### CONNECTIONS #####

func _on_item_selected(path: String):
	selected_item.value = path
	emit_signal("data_updated", self.data)

func _on_fs_btn_pressed(p_item: FileSystemItem):
	selected_item = p_item
	fd.popup_centered_ratio(0.75)

##### SETTERS AND GETTERS #####

func get_file_dialog() -> FileDialog:
	return fd
