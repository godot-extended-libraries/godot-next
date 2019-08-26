# PhysicsLayers
# author: xaguzman
# license: MIT
# description: A Utility class which allows easy access to your physics layers via their names in the project settings.
tool
extends Node

class_name PhysicsLayers

const _PHYSICS_LAYERS_BIT : Dictionary = {}
const _PHYSICS_2D_PREFIX = "2d_physics"
const _PHYSICS_3D_PREFIX = "3d_physics"

#Preload all the layer names in a cache
static func setup():
  for prefix in [_PHYSICS_2D_PREFIX, _PHYSICS_3D_PREFIX]:
    var path = "layer_names/".plus_file(prefix) 
    for i in range(1, 21):
      var layer_path = path.plus_file(str("layer_", i))     
      var layer_name = ProjectSettings.get(layer_path)
      
      if(not layer_name): 
        layer_name = str("Layer ", i)
      
      var layer_key = prefix.plus_file(layer_name)
        
      _PHYSICS_LAYERS_BIT[layer_key] = i-1

# Get the corresponding bit of the layer named <layer_name>
static func _get_physics_layer_bit(layer_name: String) -> int:
  if not _PHYSICS_LAYERS_BIT.has(layer_name):
    setup()
  
  assert _PHYSICS_LAYERS_BIT.has(layer_name)  
  return _PHYSICS_LAYERS_BIT[layer_name]
      
# Get the corresponding bit of the 2d layer named <layer_name>
static func get_physics_layer_bit_2d(layer_name: String) -> int:
  return _get_physics_layer_bit( _PHYSICS_2D_PREFIX.plus_file(layer_name))

# Get the corresponding bit of the 3d layer named <layer_name>
static func get_physics_layer_bit_3d(layer_name: String) -> int:
  return _get_physics_layer_bit( _PHYSICS_3D_PREFIX.plus_file(layer_name))

# Get the layer that corresponds to to the combination of all the passed layer names. 
static func get_physics_layer_2d(layer_names: Array) -> int:
  var res : int  = 0
  for i in range(0, layer_names.size()):
    var layer_bit = get_physics_layer_bit_2d(layer_names[i])
    res |= 1 << layer_bit
  return res

# Get the layer that corresponds to to the combination of all the passed layer names. 
static func get_physics_layer_3d(layer_names: Array) -> int:
  var res : int  = 0
  for i in range(0, layer_names.size()):
    var layer_bit = get_physics_layer_bit_3d(layer_names[i])
    res |= 1 << layer_bit
  return res