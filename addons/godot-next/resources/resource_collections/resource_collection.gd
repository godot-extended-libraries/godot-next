# author: xdgamestudios
# license: MIT
# description: An abstract base class for data structures that store Resource objects.
#              Uses a key-value store, but can also append items.
tool
extends Resource
class_name ResourceCollection

##### CLASSES #####

##### SIGNALS #####

##### CONSTANTS #####

##### PROPERTIES #####

##### NOTIFICATIONS #####

##### OVERRIDES #####

##### VIRTUALS #####

# Confirms whether a property with this format of name is compatible with the collection.
# TODO: identify a cleaner way of handling this check that is compatible with Behaviors.
func can_contain(p_property: String) -> bool:
	assert false
	return false

# Append an element to the collection.
func add_element(p_script: Script) -> void:
	assert false

# Set a new value to an element in the collection.
func set_element(p_property: String, p_value) -> bool:
	assert false
	return false

# Get a reference to an element in the collection.
func get_element(p_property: String) -> Resource:
	assert false
	return null

# Generate an Array of PropertyInfo Dictionaries based on the ResourceCollection's contents.
func get_collection_property_list() -> Array:
	assert false
	return []

##### PUBLIC METHODS #####

##### PRIVATE METHODS #####

##### CONNECTIONS #####

##### SETTERS AND GETTERS #####
