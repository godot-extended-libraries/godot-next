# PhysicsUtil2D
# author: xaguzman
# license: MIT
# description: A Utility class which allows easy access to your physics layers (2d) via their names in the project settings.

# Works best as an autoload
extends Node2D

var _PHYSICS_LAYERS_BIT : Dictionary

#Preload all the layer names in a cache
func _ready():
    for i in range(1, 21):
        var layer_name = ProjectSettings.get(str("layer_names/2d_physics/layer_", i))
        if(not layer_name): 
            layer_name = str("Layer ", i)
        
        _PHYSICS_LAYERS_BIT[layer_name] = i-1

# Get the corresponding bit of the layer named <layer_name>
func get_physics_layer_bit(layer_name: String) -> int:
    assert _PHYSICS_LAYERS_BIT.has(layer_name)
    
    return _PHYSICS_LAYERS_BIT[layer_name]

# Get the layer that corresponds to to the combination of all the passed layer names. 
func get_physics_layer(layer_names: Array) -> int:
    var res : int  = 0
    for i in range(0, layer_names.size()):
        var layer_bit = get_physics_layer_bit(layer_names[i])
        res |= 1 << layer_bit
    return res