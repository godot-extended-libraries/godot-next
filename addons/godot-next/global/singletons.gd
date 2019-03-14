# author: xdgamestudios
# license: MIT
# description: An API for accessing singletons
# deps:
# - singleton_cache.tres
tool
extends Reference
class_name Singletons

##### CONSTANTS #####

const SINGLETON_CACHE = preload("res://addons/godot-next/data/singleton_cache.tres")

##### PUBLIC METHODS #####

# Look up a singleton by its script. If it doesn't exist yet, make it. If it's a Resource with a persistent file path, load it in from memory.
static func fetch(p_script: Script) -> Object:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	if not cache.has(p_script):
		if p_script is Resource:
			var path = _get_persistent_path(p_script)
			if path:
				var paths: Dictionary = SINGLETON_CACHE.get_paths()
				cache[p_script] = ResourceLoader.load(path) if ResourceLoader.exists(path) else p_script.new()
				paths[p_script] = path
			else:
				cache[p_script] = p_script.new()
		else:
			cache[p_script] = p_script.new()
	return cache[p_script]

# Returns a singleton by its class_name as a String
static func fetchs(p_name: String) -> Object:
	var ct = ClassType.new(p_name)
	if ct.res:
		return fetch(ct.res)
	return null

# Remove a singleton from the cache and any paths associated with it.
static func erase(p_script: Script) -> bool:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	var paths: Dictionary = SINGLETON_CACHE.get_paths()
	var erased = cache.erase(p_script)
	#warning-ignore:return_value_discarded
	paths.erase(p_script)
	return erased

static func save(p_script: Script) -> void:
	var paths: Dictionary = SINGLETON_CACHE.get_paths()
	if not paths.has(p_script):
		return
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	#warning-ignore:return_value_discarded
	ResourceSaver.save(paths[p_script], cache[p_script])

static func save_all() -> void:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	var paths: Dictionary = SINGLETON_CACHE.get_paths()
	for a_script in paths:
		#warning-ignore:return_value_discarded
		ResourceSaver.save(paths[a_script], cache[a_script])

##### PRIVATE METHODS #####

static func _get_persistent_path(p_script: Script):
	return p_script.get("SELF_RESOURCE")
