class_name Vocabulary
extends Reference

# author: xdgamestudios (adapted from C# .NET Humanizer, licensed under MIT)
# license: MIT

var _plurals: Array = [] setget, get_plurals
var _singulars: Array = [] setget, get_singulars
var _uncountables: Array = [] setget, get_uncountables


func get_plurals() -> Array:
	return _plurals


func get_singulars() -> Array:
	return _singulars


func get_uncountables() -> Array:
	return _uncountables


func add_plural(p_rule: String, p_replacement: String) -> void:
	_plurals.append(Rule.new(p_rule, p_replacement))


func add_singular(p_rule: String, p_replacement: String) -> void:
	_singulars.append(Rule.new(p_rule, p_replacement))


func add_irregular(p_singular: String, p_plural: String, p_match_ending: bool = true) -> void:
	if p_match_ending:
		var sfirst = p_singular[0]
		var pfirst = p_plural[0]
		var strimmed = p_singular.trim_prefix(sfirst)
		var ptrimmed = p_plural.trim_prefix(pfirst)
		add_plural("(" + sfirst + ")" + strimmed + "$", "$1" + ptrimmed)
		add_singular("(" + pfirst + ")" + ptrimmed + "$", "$1" + strimmed)
	else:
		add_plural("^%s$" % p_singular, p_plural)
		add_singular("^%s$" % p_plural, p_singular)


func add_uncountable(p_word: String) -> void:
	_uncountables.append(p_word.to_lower())


func is_uncountable(p_word: String) -> bool:
	return _uncountables.has(p_word.to_lower())
