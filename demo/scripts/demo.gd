extends Node


const filepath = "user://frozen_object.json"  # for the object freezer


func _ready():
	# Array2D
	var array_2d = Array2D.new()
	array_2d.resize(3, 4)
	array_2d.set_cell(2, 3, "Array2D test")
	print(array_2d.get_cell(2, 3))

	# BitFlag
	var bit_flag_dict = {"a": 1, "b": 2}
	var bit_flag = BitFlag.new(bit_flag_dict)
	bit_flag.a = true
	print(bit_flag.get_active_keys())

	# Bitset
	var bitset = Bitset.new(5)
	bitset.set_bit(2, true)
	bitset.set_bit(3, true)
	bitset.print_bits(false)
	
	# Object Freezer
	# create a new object
	var example_object: ExampleObject = ExampleObject.new()
	
	# store specific values on it
	example_object.name = "Bob"
	example_object.job = "Taco Bell"
	example_object.age = 43
	example_object.position = Vector2(69, 420)
	
	# print those values
	print("\nObject 1:")
	example_object.print_properties()
	
	# freeze the properties of that object
	ObjectFreezer.freeze_properties(filepath, example_object)
	
	# load the properties onto a new object of the same class
	var example_object_2: ExampleObject = ExampleObject.new()
	ObjectFreezer.microwave_properties(filepath, example_object_2)
	
	# should print the same thing as the first object
	print("\nObject 2:")
	example_object_2.print_properties()
	
	
