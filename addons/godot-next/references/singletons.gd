# author: xdgamestudios
# license: MIT
# description: An API for accessing singletons
# deps:
# - singleton_cache.tres
extends Reference
class_name Singletons

##### CONSTANTS #####

const SINGLETON_CACHE = preload("res://addons/godot-next/resources/singletons/singleton_cache.tres")

##### PUBLIC METHODS #####

static func fetch(p_script: Script) -> Object:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	if not cache.has(p_script):
		var object: Object = p_script.new()
		if p_script is Resource:
			var path = _get_persistent_path(p_script)
			if path:
				var storage: Dictionary = SINGLETON_CACHE.get_storage()
				cache[p_script] = ResourceLoader.load(path) if ResourceLoader.exists(path) else object
				storage[p_script] = path
		else:
			cache[p_script] = object
	return cache[p_script]

static func erase(p_script: Script) -> bool:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	var storage: Dictionary = SINGLETON_CACHE.get_storage()
	var erased = cache.erase(p_script)
	#warning-ignore:return_value_discarded
	storage.erase(p_script)
	return erased

static func save(p_script: Script) -> void:
	var storage: Dictionary = SINGLETON_CACHE.get_storage()
	if not storage.has(p_script):
		return
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	#warning-ignore:return_value_discarded
	ResourceSaver.save(storage[p_script], cache[p_script])

static func save_all() -> void:
	var cache: Dictionary = SINGLETON_CACHE.get_cache()
	var storage: Dictionary = SINGLETON_CACHE.get_storage()
	for a_script in storage:
		#warning-ignore:return_value_discarded
		ResourceSaver.save(storage[a_script], cache[a_script])

##### PRIVATE METHODS #####

static func _get_persistent_path(p_script: Script):
	return p_script.get("SELF_RESOURCE")

