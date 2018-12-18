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
var selected_item: FileSystemItem

var loading: bool

class FileSystemItem:
	extends HBoxContainer
	var path: String
	var mode: int
	
	var btn: Button
	
	func init(p_index: int, p_path: String, p_mode: int, p_parent):
		path = p_path
		btn = Button.new()
		match p_mode:
			FileDialog.MODE_OPEN_FILE:
				mode = FileSystemTypes.FILE
				btn.text = "File " + str(p_index)
			FileDialog.MODE_OPEN_DIR:
				mode = FileSystemTypes.DIR
				btn.text = "Dir " + str(p_index)
		add_child(btn)
		#warning-ignore:unused_return_value
		btn.connect("pressed", p_parent, "_on_fs_btn_pressed", [self])
		btn.size_flags_horizontal = SIZE_EXPAND_FILL;
	
	func set_data(p_path: String):
		path = p_path;
		match mode:
			FileSystemTypes.FILE:
				btn.text = "File: " + p_path.get_file();
			FileSystemTypes.DIR:
				btn.text = "Dir: " + p_path.get_file();
		btn.set_tooltip(p_path);
	
	func get_data() -> String:
		return path;


func _init(p_title: String = "", p_type: int = FileSystemTypes.DIR):
	set_title(p_title);
	set_item_script(FileSystemItem);
	
	fd = FileDialog.new()
	match p_type:
		FileSystemTypes.FILE:
			fd.mode = FileDialog.MODE_OPEN_FILE
			fd.connect("file_selected", self, "_on_item_selected");
		FileSystemTypes.DIR:
			fd.mode = FileDialog.MODE_OPEN_DIR
			fd.connect("dir_selected", self, "_on_item_selected");
		_:
			assert false and "Bad p_type supplied to FileSystemItemList.new()"
	fd.dialog_hide_on_ok = true;
	add_child(fd);

func _enter_tree():
	fd.owner = owner;

func _item_inserted(p_index: int, p_control: Control):
	assert p_control
	p_control.init(p_index, "", fd.mode, self);
	p_control.size_flags_horizontal = SIZE_EXPAND_FILL;
	
	if not loading:
		save_data();

func _item_removed(p_index: int, p_control: Control):
	save_data();

func _item_dragged(p_control: Control):
	save_data();

func _on_item_selected(path: String):
	selected_item.set_data(path);
	save_data();

func _on_fs_btn_pressed(p_item: FileSystemItem):
	selected_item = p_item;
	fd.popup_centered_ratio(0.75);

func get_file_dialog() -> FileDialog:
	return fd;

func load_data():
	loading = true;
	clear_items();
	var array = _object.get(_property_name);
	if array != null:
		for data in array:
			var item = _insert_item(-1);
			item.set_data(data);
	loading = false;

func save_data():
	var _array = [];
	for node in content.get_children():
		var data = node.get_node("Item") as FileSystemItem;
		_array.push_back(data.get_data());
	_object.set(_property_name, _array);
