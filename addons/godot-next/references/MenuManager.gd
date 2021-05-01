class_name MenuManager
extends Reference

# author: nonunknown
# license: MIT
# description: A class that handles menu selection system
# IMPORTANT: the Visual representation has to be done by user, this class handles the logic only
# showcases: https://www.youtube.com/watch?v=4H7M-MDkihs / https://www.youtube.com/watch?v=wZGu8_BvXso
# todo: Implement additional features
# usage:
#   - Initial Setup
#     1st param: The target node who is controlling the Menu (I always use self)
#     2nd param: The Options that the menu contains e.g: ["new_game","load_game","exit"]
#     optional 3rd param: Reset on last means when for example you are on exit and press down the selection goes to new_game
#     optional 4th param: Where the selection cursor starts
#     var menu:MenuManager = MenuManager.new(self, ["new_game","load_game","exit"], false )
#     - Updating:
#       call menu.update() undex _process function
#     - Events:
#       since the class uses call_deferred for target's function, its not mandatory to create the functions bellow
#       this events functions must be called where "target" is set
#     OPTION = the menu according to param 2:
#     * _on_enter_OPTION(enabled:bool) - Called when menu cursor is over it - e.g: _on_enter_new_game(enabled) or _on_enter_exit(enabled)
#     * _on_menu_selected_OPTION(enabled:bool) - Called when user select the option
#     * _on_cursor_moved(index:int) - this one is called everytime the menu cursor moves, "index" the index of 2nd param array,
#       you can use it to play a sound for example.
#     * disable_option(index:bool) - you can set an option to be disabled or enabled (useful for secret menus)
#     PS: in order to the above function work the function _on_menu_selected_OPTION and _on_enter_OPTION must have:
#     if (enabled):
#	#handle logic code here.

var _amount:int
var _reset_on_last:bool
var _current:int
var _target:Node
var _last:int
var _enabled:Array = []
var _options:Array = []

func _init(target:Node, options:Array, reset_on_last:bool = false, start:int = 0) -> void:
	_target = target
	_amount = options.size()
	_reset_on_last = reset_on_last
	_current = start
	_options = options
	_last = start
	for i in range( _options.size()):
		_enabled.append(true)

func disable_option(index):
	_enabled[index] = false

func update():
	var move = int(Input.is_action_just_pressed("ui_up")) - int(Input.is_action_just_pressed("ui_down"))
	if move > 0:
		if _current - 1 < 0:
			if _reset_on_last:
				_current = _amount - 1
		else: _current -= 1
	elif move < 0:
		if _current + 1 > _amount -1:
			if _reset_on_last:
				_current = 0
		else: _current += 1
	if !move == 0 and _last != _current:
		_target.call_deferred("_on_enter_"+_options[_current])
		_target.call_deferred("_on_cursor_moved", _current)
	elif Input.is_action_just_pressed("ui_select"):
		# print("selected menu: "+_options[_current])
		_target.call_deferred("_on_menu_selected_"+_options[_current], _enabled[_current])
	_last = _current
