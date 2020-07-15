class_name StateMachine

# author: nonunknown
# license: MIT
# description:
#	A performance-like state machine implementation
#	Focused on code organization and easy-to-use
#usage: Check godot-next/demo/state_machines/

var target:Node # the state machine owner
var parent:Node = null # in case this is a sub-statemachine
var id:int = -1
var machine:Dictionary = {
	state = null,
	last_state = null,
	funcs={
		init={},
		update={},
		exit={}
		}
	}


func _init(_target:Node):
	self.target = _target
	machine.last_state = 0

func register_state(state_const:int,name:String,has_init:bool=true,has_exit:bool=false) -> void:
	if (has_init):
		machine.funcs.init[state_const] = funcref(target,"st_init_"+name)
	machine.funcs.update[state_const] = funcref(target,"st_update_"+name)
	if (has_exit):
		machine.funcs.exit[state_const] = funcref(target,"st_exit_"+name)

func register_parent(p,state_const:int) -> void:
	parent = p
	self.id = state_const
	pass

func register_state_array(states_const:Array,names:Array) -> void:
	for i in states_const.size():
		register_state(states_const[i],names[i],true,true)

func machine_update() -> void:
	machine.funcs.update[machine.state].call_func()

func start(state:int = 0) -> void:
	machine.state = state
	machine.funcs.init[machine.state].call_func()

func change_state(to,first:bool=false) -> void:
	if !first:
		if machine.funcs.exit.has(machine.state):
			machine.funcs.exit[machine.state].call_func()
	machine.last_state = machine.state
	machine.state = to
	check_parent()
	if machine.funcs.init.has(machine.state):
		machine.funcs.init[to].call_func() #call the init function from next state

func check_parent() -> bool:
	if parent == null: return false
	if parent.get_current_state() != self.id:
		parent.change_state(self.id)
		return true
	return false

func get_current_state() -> int: return machine.state
func get_last_state() -> int: return machine.last_state
func last_state_was(st:int) -> bool: return machine.last_state == st

func state_is(state:int) -> bool: 
	if machine.state == state: 
		return true
	return false

