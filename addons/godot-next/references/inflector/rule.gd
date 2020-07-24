class_name Rule
extends Reference

# author: xdgamestudios (adapted from C# .NET Humanizer, licensed under MIT)
# license: MIT

var _regex: RegEx
var _replacement: String

func _init(p_rule: String, p_replacement: String) -> void:
	_regex = RegEx.new()
	#warning-ignore:return_value_discarded
	_regex.compile(p_rule)
	_replacement = p_replacement


func apply(p_word: String):
	if not _regex.search(p_word):
		return null
	return _regex.sub(p_word, _replacement)


