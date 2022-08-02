extends Reference
class_name ExampleObject
# an example object for the demo to show how the object freezer works

var name = ""
var job = ""
var age = 0
var position = Vector2.ZERO


# prints the properties
func print_properties():
	print("My name is " + name + ". I work at " + job + " and I am " + str(age) + "years old. I am currently at " + str(position) + ".")
