# FileSystemLink
# author: willnationsdev
# brief_description: A utility for creating links (file/directory, symbolic/hard).
# API details:
# - All methods' parameters are ordered in Unix fashion, {<target>,<linkpath>}
# - Methods are aliased so that the parameters are implied by the method name.
extends Reference
class_name FileSystemLink

enum LinkTypes {
	SOFT,
	HARD
}

enum TargetTypes {
	FILE,
	DIR,
	WINDOWS_JUNCTION
}

static func mk_hard_file(p_target: String, p_linkpath: String = "") -> int:
	return _make_link(p_target, p_linkpath, FILE, HARD)

static func mk_soft_file(p_target: String, p_linkpath: String = "") -> int:
	return _make_link(p_target, p_linkpath, FILE, SOFT)

static func mk_hard_dir(p_target: String, p_linkpath: String = "") -> int:
	return _make_link(p_target, p_linkpath, DIR, HARD)

static func mk_soft_dir(p_target: String, p_linkpath: String = "") -> int:
	return _make_link(p_target, p_linkpath, DIR, SOFT)

static func mk_windows_junction(p_target: String, p_linkpath: String = "") -> int:
	return _make_link(p_target, p_linkpath, WINDOWS_JUNCTION, SOFT)

static func _make_link(p_target: String, p_linkpath: String = "", p_target_type = FILE, p_link_type: int = SOFT) -> int:
	var params := PoolStringArray()
	var dir := Directory.new()
	var output := []
	var target := ProjectSettings.globalize_path(p_target)
	var linkpath := ProjectSettings.globalize_path(p_linkpath)
	match p_target_type:
		FILE:
			if not dir.file_exists(target):
				return ERR_FILE_NOT_FOUND
		DIR, WINDOWS_JUNCTION:
			if not dir.dir_exists(target):
				return ERR_FILE_NOT_FOUND
	match OS.get_name():
		"Windows":
			match p_link_type:
				SOFT:
					pass
				HARD:
					params.append("/H")
				_:
					printerr("Unknown link type passed to FileSystemLink.make_link: ", p_link_type)
					return ERR_INVALID_PARAMETER

			match p_target_type:
				FILE:
					pass
				DIR:
					params.append("/D")
				WINDOWS_JUNCTION:
					params.append("/J")
				_:
					printerr("Unknown target type passed to FileSystemLink.make_link: ", p_target_type)
					return ERR_INVALID_PARAMETER

			params.append(linkpath)
			params.append(target)
			OS.execute("mklink", params, true, output)
			return OK
		"X11", "OSX":
			match p_link_type:
				SOFT:
					params.append("-s")
				HARD:
					pass
				_:
					printerr("Unknown link type passed to FileSystemLink.make_link", p_link_type)
					return ERR_INVALID_PARAMETER
			
			match p_target_type:
				FILE:
					pass
				DIR:
					params.append("-d")
				WINDOWS_JUNCTION:
					printerr("Junctions are a Windows feature")
					return ERR_INVALID_PARAMETER
				_:
					printerr("Unknown target type passed to FileSystemLink.make_link: ", p_target_type)
					return ERR_INVALID_PARAMETER

			params.append(target)
			params.append(linkpath)
			OS.execute("ln", params, true, output)
			return OK
		_:
			return ERR_UNAVAILABLE