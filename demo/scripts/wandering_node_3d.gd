extends Spatial

var velocity = Vector3()
onready var center = transform.origin

func _ready():
	randomize()


func _physics_process(_delta):
	velocity += Vector3(randf() * 2 - 1, randf() - 0.5, randf() - 0.5) * 0.05
	if velocity.length_squared() > 1:
		velocity *= 0.99
	transform.origin += velocity
	transform.origin = transform.origin.linear_interpolate(center, 0.125)
