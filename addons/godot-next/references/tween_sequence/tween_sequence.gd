class_name TweenSequence
extends Reference
# author: KoBeWi
# license: MIT
# description:
#	A helper class for easier management and chaining of Tweens.
#	dynamically from code.
#
#	Example usage:
#		var seq := TweenSequence.new(get_tree())
#		seq.append($Sprite, "modulate", Color.red, 1)
#		seq.append($Sprite, "modulate", Color(1, 0, 0, 0), 1).set_delay(1)
#	This will create a Tween and automatically start it,
#	changing the Sprite to red color in one second
#	and then making it transparent after a delay.

# Tweener for tweening properties.
class PropertyTweener extends Tweener:
	var _target: Object
	var _property: NodePath
	var _from
	var _to
	var _duration: float
	var _trans: int
	var _ease: int

	var _delay: float
	var _continue := true
	var _advance := false

	func _init(target: Object, property: NodePath, to_value, duration: float) -> void:
		assert(target, "Invalid target Object.")
		_target = target
		_property = property
		_from = _target.get_indexed(property)
		_to = to_value
		_duration = duration
		_trans = Tween.TRANS_LINEAR
		_ease = Tween.EASE_IN_OUT


# Sets custom starting value for the tweener.
# By default, it starts from value at the start of this tweener.
	func from(val) -> Tweener:
		_from = val
		_continue = false
		return self


# Sets the starting value to the current value,
# i.e. value at the time of creating sequence.
	func from_current() -> Tweener:
		_continue = false
		return self


# Sets transition type of this tweener, from Tween.TransitionType.
	func set_trans(t: int) -> Tweener:
		_trans = t
		return self


# Sets ease type of this tweener, from Tween.EaseType.
	func set_ease(e: int) -> Tweener:
		_ease = e
		return self


# Sets the delay after which this tweener will start.
	func set_delay(d: float) -> Tweener:
		_delay = d
		return self


	func _start(tween: Tween) -> void:
		if not is_instance_valid(_target):
			push_warning("Target object freed, aborting Tweener.")
			return

		if _continue:
			_from = _target.get_indexed(_property)

		if _advance:
			tween.interpolate_property(_target, _property, _from, _from + _to, _duration, _trans, _ease, _delay)
		else:
			tween.interpolate_property(_target, _property, _from, _to, _duration, _trans, _ease, _delay)


# Generic tweener for creating delays in sequence.
class IntervalTweener extends Tweener:
	var _time: float

	func _init(time: float) -> void:
		_time = time


	func _start(tween: Tween) -> void:
		tween.interpolate_callback(self, _time, "_")


	func _():
		pass

# Tweener for calling methods.
class CallbackTweener extends Tweener:
	var _target: Object
	var _delay: float
	var _method: String
	var _args: Array

	func _init(target: Object, method: String, args: Array) -> void:
		assert(target, "Invalid target Object.")
		_target = target
		_method = method
		_args = args


# Set delay after which the method will be called.
	func set_delay(d: float) -> Tweener:
		_delay = d
		return self


	func _start(tween: Tween) -> void:
		if not is_instance_valid(_target):
			push_warning("Target object freed, aborting Tweener.")
			return

		tween.interpolate_callback(_target, _delay, _method,
			_get_argument(0), _get_argument(1), _get_argument(2),
			_get_argument(3), _get_argument(4))


	func _get_argument(i: int):
		if i < _args.size():
			return _args[i]
		else:
			return null


# Tweener for tweening arbitrary values using getter/setter method.
class MethodTweener extends Tweener:
	var _target: Object
	var _method: String
	var _from
	var _to
	var _duration: float
	var _trans: int
	var _ease: int

	var _delay: float

	func _init(target: Object, method: String, from_value, to_value, duration: float) -> void:
		assert(target, "Invalid target Object.")
		_target = target
		_method = method
		_from = from_value
		_to = to_value
		_duration = duration
		_trans = Tween.TRANS_LINEAR
		_ease = Tween.EASE_IN_OUT


# Sets transition type of this tweener, from Tween.TransitionType.
	func set_trans(t: int) -> Tweener:
		_trans = t
		return self


# Sets ease type of this tweener, from Tween.EaseType.
	func set_ease(e: int) -> Tweener:
		_ease = e
		return self


# Sets the delay after which this tweener will start.
	func set_delay(d: float) -> Tweener:
		_delay = d
		return self


	func _start(tween: Tween) -> void:
		if not is_instance_valid(_target):
			push_warning("Target object freed, aborting Tweener.")
			return

		tween.interpolate_method(_target, _method, _from, _to, _duration, _trans, _ease, _delay)


# Emited when one step of the sequence is finished.
signal step_finished(idx)
# Emited when a loop of the sequence is finished.
signal loop_finished()
# Emitted when whole sequence is finished. Doesn't happen with inifnite loops.
signal finished()

var _tree: SceneTree
var _tween: Tween
var _tweeners: Array

var _current_step := 0
var _loops := 0
var _autostart := true
var _started := false
var _running := false

var _kill_when_finised := true
var _parallel := false

# You need to provide SceneTree to be used by the sequence.
func _init(tree: SceneTree) -> void:
	_tree = tree
	_tween = Tween.new()
	_tween.set_meta("sequence", self)
	_tree.get_root().call_deferred("add_child", _tween)

	_tree.connect("idle_frame", self, "start", [], CONNECT_ONESHOT)
	_tween.connect("tween_all_completed", self, "_step_complete")

# All Tweener-creating methods will return the Tweeners for further chained usage.

# Appends a PropertyTweener for tweening properties.
func append(target: Object, property: NodePath, to_value, duration: float) -> PropertyTweener:
	var tweener := PropertyTweener.new(target, property, to_value, duration)
	_add_tweener(tweener)
	return tweener


# Appends a PropertyTweener operating on relative values.
func append_advance(target: Object, property: NodePath, by_value, duration: float) -> PropertyTweener:
	var tweener := PropertyTweener.new(target, property, by_value, duration)
	tweener._advance = true
	_add_tweener(tweener)
	return tweener


# Appends an IntervalTweener for creating delay intervals.
func append_interval(time: float) -> IntervalTweener:
	var tweener := IntervalTweener.new(time)
	_add_tweener(tweener)
	return tweener


# Appends a CallbackTweener for calling methods on target object.
func append_callback(target: Object, method: String, args := []) -> CallbackTweener:
	var tweener := CallbackTweener.new(target, method, args)
	_add_tweener(tweener)
	return tweener


# Appends a MethodTweener for tweening arbitrary values using methods.
func append_method(target: Object, method: String, from_value, to_value, duration: float) -> MethodTweener:
	var tweener := MethodTweener.new(target, method, from_value, to_value, duration)
	_add_tweener(tweener)
	return tweener


# When used, next Tweener will be added as a parallel to previous one.
# Example: sequence.parallel().append(...)
func parallel() -> Reference:
	if _tweeners.empty():
		_tweeners.append([])
	_parallel = true
	return self


# Alias to parallel(), except it won't work without first tweener.
func join() -> Reference:
	assert(!_tweeners.empty(), "Can't join with empty sequence!")
	_parallel = true
	return self


# Sets the speed scale of tweening.
func set_speed(speed: float) -> Reference:
	_tween.playback_speed = speed
	return self


# Sets how many the sequence should repeat.
# When used without arguments, sequence will run infinitely.
func set_loops(loops := -1) -> Reference:
	_loops = loops
	return self


# Whether the sequence should autostart or not.
# Enabled by default.
func set_autostart(autostart: bool) -> Reference:
	if _autostart and not autostart:
		_tree.disconnect("idle_frame", self, "start")
	elif not _autostart and autostart:
		_tree.connect("idle_frame", self, "start", [], CONNECT_ONESHOT)

	_autostart = autostart
	return self


# Starts the sequence manually, unless it's already started.
func start() -> void:
	assert(_tween, "Tween was removed!")
	assert(!_started, "Sequence already started!")
	_started = true
	_running = true
	_run_next_step()


# Returns whether the sequence is currently running.
func is_running() -> bool:
	return _running


# Pauses the execution of the tweens.
func pause() -> void:
	assert(_tween, "Tween was removed!")
	assert(_running, "Sequence not running!")
	_tween.stop_all()
	_running = false


# Resumes the execution of the tweens.
func resume() -> void:
	assert(_tween, "Tween was removed!")
	assert(!_running, "Sequence already running!")
	_tween.resume_all()
	_running = true


# Stops the sequence and resets it to the beginning.
func reset() -> void:
	assert(_tween, "Tween was removed!")
	if _running:
		pause()
	_started = false
	_current_step = 0
	_tween.reset_all()


# Frees the underlying Tween. Sequence is unusable after this operation.
func kill():
	assert(_tween, "Tween was already removed!")
	if _running:
		pause()
	_tween.queue_free()


# Whether the Tween should be freed when sequence finishes.
# Default is true. If set to false, sequence will restart on end.
func set_autokill(autokill: bool):
	_kill_when_finised = autokill


func _add_tweener(tweener: Tweener):
	assert(_tween, "Tween was removed!")
	assert(!_started, "Can't append to a started sequence!")
	if not _parallel:
		_tweeners.append([])
	_tweeners.back().append(tweener)
	_parallel = false


func _run_next_step() -> void:
	assert(!_tweeners.empty(), "Sequence has no steps!")
	var group := _tweeners[_current_step] as Array
	for tweener in group:
		tweener._start(_tween)
	_tween.start()


func _step_complete() -> void:
	emit_signal("step_finished", _current_step)
	_current_step += 1

	if _current_step == _tweeners.size():
		_loops -= 1
		if _loops == -1:
			emit_signal("finished")
			if _kill_when_finised:
				kill()
			else:
				reset()
		else:
			emit_signal("loop_finished")
			_current_step = 0
			_run_next_step()
	else:
		_run_next_step()
