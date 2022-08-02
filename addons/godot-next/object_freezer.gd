extends Object
class_name ObjectFreezer
# author: firesquid6
# license: MIT
# description:
#	Allows users to easily freeze the properties of an object in a file to be loaded back onto another instance of the same class later.
#	Useful for basic save systems that don't require large trees of sub objects.
#	Can only encode primitive types. Anything that extends from "Object" can't be encoded.
#	Since every property is constant, and every method is static, there's no reason to ever instance this object.


const dont_store = ["script", "Script Variables"]  # list property names not to store

# converts the object's properties into a dictionary and then saves them to a text file. These can later be loaded onto an object from the same class using load_properties()
# filepath - the filepath with extention included where the object will be saved
static func freeze_properties(filepath: String, obj: Object) -> void:
	# open the file
	var file = File.new()
	file.open(filepath, File.WRITE)
	
	# store all the properties in a dictionary
	var dict := object_to_dictionary(obj)
	
	# convert the dictionary to json and store it in the file
	var json = JSON.print(dict)
	file.store_pascal_string(json)
	
	# close the file
	file.close()


# converts an object to a dictionary
# obj - the object to convert to a dictionary
static func object_to_dictionary(obj: Object) -> Dictionary:
	var dict := {}
	
	# iterate through each property in the object's property list
	for property in obj.get_property_list():
		var key = property["name"]
		if !(key in dont_store):
			# get the value of the key
			var value = obj.get(key)
			
			# check if the value is another object
			if value is Object:
				# set the value to null
				#	this could probably be expanded later to encode objects recursively by someone smarter than me 
				#	the only problem is that godot doesn't handle custom types well, and you'd need to encode the type
				#	- firesquid6
				dict[key] = null
			else:
				# if it's a normal property
				dict[key] = value
	# return the final dictionary
	return dict


# loads the object's properties saved using save_properties onto a new object.
# filepath - the filepath where the properties were saved
static func microwave_properties(filepath: String, obj: Object) -> void:
	# open the file
	var file: File = File.new()
	file.open(filepath, File.READ)
	
	# iterate through the dictionary
	var dict: Dictionary = JSON.parse(file.get_pascal_string()).result
	dictionary_to_object(dict, obj)
	
	# close the file
	file.close()


# converts a dictionary back to the original object. The base object must be created beforehand and passed as an argument
# the object must already be created
static func dictionary_to_object(dict: Dictionary, base_object: Object) -> void:
	# iterate through the keys and set the object's properties based on the keys
	for key in dict.keys():
		var value = dict[key]
		
		# some functionality to include sub-objects could be created here
		base_object.set(key, dict[key])
