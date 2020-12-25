tool
class_name PhysicsLayers
extends Resource
# author: xaguzman
# license: MIT
# description:
#	A Utility class which allows easy access to your physics
#	layers via their names in the project settings.

const _PHYSICS_LAYERS_BIT: Dictionary = {}
const _PHYSICS_2D_PREFIX = "2d_physics"
const _PHYSICS_3D_PREFIX = "3d_physics"

static func setup() -> void:
	for prefix in [_PHYSICS_2D_PREFIX, _PHYSICS_3D_PREFIX]:
		var path : String = "layer_names/".plus_file(prefix)
		for i in range(1, 21):
			var layer_path: String = path.plus_file(str("layer_", i))
			var layer_name: String = ProjectSettings.get(layer_path)

			if not layer_name:
				layer_name = str("Layer ", i)

			var layer_key: String = prefix.plus_file(layer_name)
			_PHYSICS_LAYERS_BIT[layer_key] = i - 1


# Get the corresponding bit of the layer named <layer_name>
static func _get_physics_layer_index(layer_name: String) -> int:
	if not _PHYSICS_LAYERS_BIT.has(layer_name):
		setup()

	assert (_PHYSICS_LAYERS_BIT.has(layer_name))
	return _PHYSICS_LAYERS_BIT[layer_name]


# Get the layer that corresponds to to the combination of all the passed layer names.
static func get_physics_layer(layer_names: Array, is_layer_3d := false) -> int:
	var res: int = 0
	for i in range(layer_names.size()):
		var layer_bit : int = get_physics_layer_index(layer_names[i], is_layer_3d)
		res |= 1 << layer_bit
	return res


static func get_physics_layer_index(layer_name: String, is_layer_3d := false) -> int:
	var res: int
	if is_layer_3d:
		res = _get_physics_layer_index(_PHYSICS_3D_PREFIX.plus_file(layer_name))
	else:
		res = _get_physics_layer_index(_PHYSICS_2D_PREFIX.plus_file(layer_name))

	return res
