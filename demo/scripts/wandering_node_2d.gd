extends Node2D

var velocity = Vector2()
onready var center = position

func _ready():
	randomize()


func _physics_process(_delta):
	velocity += Vector2(randf() - 0.5, randf() - 0.5)
	if velocity.length_squared() > 10:
		velocity *= 0.99
	position += velocity
	position = position.linear_interpolate(center, 0.03).round()
