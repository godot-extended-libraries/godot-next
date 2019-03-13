# author: xdgamestudios
# license: MIT
# description: A resource file that is preloaded into memory to allow for accessing
#              singleton classes project wide using Singletons
extends Resource

##### PROPERTIES #####

var _cache = {};
var _storage = {};

##### PUBLIC METHODS #####

func get_cache() -> Dictionary:
	return _cache;

func get_storage() -> Dictionary:
	return _storage;