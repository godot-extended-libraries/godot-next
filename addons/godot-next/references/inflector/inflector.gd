tool
class_name Inflector
extends Reference

# author: xdgamestudios (adapted from C# .NET Humanizer, licensed under MIT)
# license: MIT
#description: Provides inflection tools to pluralize and singularize strings.
#
#todo: Add more functionality
#
#usage:
#   - Creating Inflector:
#   	inflector = Inflector.new() # new inflector with empty vocabulary
#   	inflector = Inflector.new(vocabulary) # new inflector with vocabulary
#   	Note:
#   	- Inflector with no vocabulary will not be able to apply convertion out-of-the-box.
#   - Creating Vocabulary:
#   	vocabulary = Vocabulary.new() # creates new empty vocabulary
#   	vocabulary = VocabularyFactory.build_default_vocabulary()
#   	Note:
#   	- Empty vocabulary can be manually configured with custom rules.
#   	- Default vocabulary will apply convertions for english language.
#   - Get Vocabulary:
#   	vocabulary = inflector.get_vocabulary() # reference to the vocabulary used by the inflector.
#   - Add Rules:
#   	vocabulary.add_plural(rule, replacement) # adds convertion rule to plural
#   	vocabulary.add_singular(rule, replacement) # adds convertion rule to singular
#   	vocabulary.add_irregular(rule, replacement) # adds irregular convertion
#   	vocabulary.add_uncountable(word) # add unconvertable word
#   	Note:
#   	- 'rule' is a String with regex syntax.
#   	- 'replacement' is a String with regex systax.
#   - Using Inflector:
#   	inflector.pluralize(word, p_force = false) # returns the plural of the word
#   	inflector.singularize(word, p_force = false) # returns the singular of the word
#   	Note:
#   	- If the first parameter's state is unknown, use 'p_force = true' to force an unknown term into the desired state.

var _vocabulary: Vocabulary setget, get_vocabulary

func _init(p_vocabulary = null) -> void:
	if not p_vocabulary:
		p_vocabulary = VocabularyFactory.build_default_vocabulary()
	else:
		_vocabulary = p_vocabulary


func get_vocabulary() -> Vocabulary:
	return _vocabulary


func pluralize(p_word: String, p_force: bool = false) -> String:
	var result = apply_rules(_vocabulary.get_plurals(), p_word)

	if not p_force:
		return result

	var as_singular = apply_rules(_vocabulary.get_singulars(), p_word)
	var as_singular_as_plural = apply_rules(_vocabulary.get_plurals(), as_singular)

	if as_singular and as_singular != p_word and as_singular + "s" != p_word and as_singular_as_plural == p_word and result != p_word:
		return p_word

	return result


func singularize(p_word: String, p_force: bool = false) -> String:
	var result = apply_rules(_vocabulary.get_singulars(), p_word)

	if not p_force:
		return result

	var as_plural = apply_rules(_vocabulary.get_plurals(), p_word)
	var as_plural_as_singular = apply_rules(_vocabulary.get_singulars(), as_plural)

	if as_plural and p_word + "s" != as_plural and as_plural_as_singular == p_word and result != p_word:
		return p_word

	return result


func apply_rules(p_rules: Array, p_word: String):
	if not p_word:
		return null

	if _vocabulary.is_uncountable(p_word):
		return p_word

	var result = p_word
	for i in range(len(p_rules) - 1, -1, -1):
		result = p_rules[i].apply(p_word)
		if result:
			break

	return result
