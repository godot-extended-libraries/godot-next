extends Node

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
