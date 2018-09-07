# FileSystemItemList
# author: willnationsdev
# brief_description: A VBoxItemList for editing lists of files or directories.
tool
extends VBoxItemList
class_name FileSystemItemList

enum FileSystemTypes {
	FILE,
	DIR
}

var fd: FileDialog

class FileSystemItem:
	extends HBoxContainer
	var path: String
	var mode: int
	
	var btn: Button
	
	func init(p_index: int, p_path: String, p_mode: int):
		path = p_path
		btn = Button.new()
		match p_mode:
			FileDialog.MODE_OPEN_FILE:
				mode = FILE
				btn.text = "File " + str(p_index)
			FileDialog.MODE_OPEN_DIR:
				mode = DIR
				btn.text = "Dir " + str(p_index)
		add_child(btn)
		#warning-ignore:unused_return_value
		btn.connect("pressed", get_parent(), "_on_fsbtn_pressed", [self])

func _init(p_title: String = "", p_type: int = FILE):
	._init(p_title, "", FileSystemItem)
	
	fd = FileDialog.new()
	match p_type:
		FILE:
			fd.mode = FileDialog.MODE_OPEN_FILE
		DIR:
			fd.mode = FileDialog.MODE_OPEN_DIR
		_:
			assert false and "Bad p_type supplied to FileSystemItemList.new()"
	fd.dialog_hide_on_ok = true
	add_child(fd)

func _enter_tree():
	fd.owner = owner

func _item_inserted(p_index: int, p_control: Control):
	assert p_control
	p_control.init(p_index, "", fd.mode)

func _on_fsbtn_pressed(p_item: FileSystemItem):
	print(p_item)
	print(p_item.path)
	p_item.fd.popup_centered_ratio(0.75)

func get_file_dialog() -> FileDialog:
	return fd