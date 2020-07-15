# State machine With sub state machines

extends Node
enum MACHINES {MAIN,SUB} #state machine IDS
enum MAIN {IDLE,PRESSED} #states of my machine
enum SUB {ANGRY,CRAZY}

var main_state_machine:StateMachine = StateMachine.new(self) #the self tells to state machine you own it.
var sub_state_machine:StateMachine = StateMachine.new(self)

func _ready():
	#You have three ways of registering the STATES enum, select which one is better for you
	
	## FIRST WAY
	# 1st arg - state ID / 2nd arg - function name to call / 3rd arg call "on enter state" / 4th arg call "on exit state"
	# main_state_machine.register_state(STATES.IDLE, "idle", true, true)
	# main_state_machine.register_state(STATES.PRESSED, "pressed", true, false)
	
	##SECOND WAY
	# 1st arg - state ID array / 2nd arg - function names array / PS: registering via array makes "OnEnter" and "OnExit" function mandatory
	# main_state_machine.register_state_array([STATES.IDLE,STATES.PRESSED],["idle","pressed"])
	
	##THIRD WAY MY FAVORITE
	# args are the same as SECOND WAY but you dont need to type anything more than this
	# when you create a new STATES enum value you dont need to update the below line, which is not true for the first two examples
	main_state_machine.register_state_array(MAIN.values(), MAIN.keys())
	sub_state_machine.register_state_array(SUB.values(), SUB.keys())
	
	#1st arg - the parent machine ref / 2nd arf - ID ; used ENUM for organization
	sub_state_machine.register_parent(main_state_machine, MACHINES.SUB)
	
	main_state_machine.start() #Start the machine
	sub_state_machine.start()

##ABOUT THE SUB STATE
# the update of sub_state_machine is called only in the update function of the state you want the sub machine to be updated
# IN this example I want to change the node mood (ANGRY,CRAZY) only when the main machine state is PRESSED

func _process(delta):
	main_state_machine.machine_update() #call update on the machine

#THIS IS THE MOST IMPORTANT
# In case you have choosen the FIRST or SECOND WAY the functions names should be as defined in 2nd arg of register_state
# in this example I've used the THIRD WAY which means the name is the same as the enum presented
# Example for 1st and 2nd WAY -> st_init_idle,st_init_pressed
# Example for 3rd WAY -> st_init_IDLE,st_init_PRESSED

# I've declared IDLE AND PROCESS in this case I have to make 6 functions (3 * STATE_ENUM_SIZE)



func st_init_IDLE():
	print("Entered IDLE")
	pass

func st_update_IDLE():
	
	if Input.is_action_just_pressed("ui_up"):
		main_state_machine.change_state(MAIN.PRESSED)
		print("changing to pressed")
	
	pass

func st_exit_IDLE():
	print("Exited IDLE")
	
	pass

func st_init_PRESSED():
	print("Entered PRESSED")
	
	pass

func st_update_PRESSED():
	sub_state_machine.machine_update()
	if Input.is_action_just_pressed("ui_down"):
		main_state_machine.change_state(MAIN.IDLE)
		print("going back to idle")
	pass

func st_exit_PRESSED():
	print("Exited PRESSED")
	pass

## === SUB STATE MACHINE FUNCTIONS

func st_init_ANGRY():
	print("I'm Angry")
	pass

func st_update_ANGRY():
	
	if Input.is_action_just_pressed("ui_right"):
		sub_state_machine.change_state(SUB.CRAZY)
			
	
	pass

func st_exit_ANGRY():
	
	pass


func st_init_CRAZY():
	print("I'm Crazy")
	pass

func st_update_CRAZY():
	if Input.is_action_just_pressed("ui_left"):
		sub_state_machine.change_state(SUB.ANGRY)
	pass

func st_exit_CRAZY():
	
	pass
