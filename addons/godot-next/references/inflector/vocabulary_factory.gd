class_name VocabularyFactory
extends Vocabulary

# author: xdgamestudios (adapted from C# .NET Humanizer, licensed under MIT)
# license: MIT

static func build_default_vocabulary() -> Vocabulary:
	var vocabulary = Vocabulary.new()

	# Plural rules.
	vocabulary._plurals = [
		Rule.new("$", "s"),
		Rule.new("s$", "s"),
		Rule.new("(ax|test)is$", "$1es"),
		Rule.new("(octop|vir|alumn|fung|cact|foc|hippopotam|radi|stimul|syllab|nucle)us$", "$1i"),
		Rule.new("(alias|bias|iris|status|campus|apparatus|virus|walrus|trellis)$", "$1es"),
		Rule.new("(buffal|tomat|volcan|ech|embarg|her|mosquit|potat|torped|vet)o$", "$1oes"),
		Rule.new("([dti])um$", "$1a"),
		Rule.new("sis$", "ses"),
		Rule.new("([lr])f$", "$1ves"),
		Rule.new("([^f])fe$", "$1ves"),
		Rule.new("(hive)$", "$1s"),
		Rule.new("([^aeiouy]|qu)y$", "$1ies"),
		Rule.new("(x|ch|ss|sh)$", "$1es"),
		Rule.new("(matr|vert|ind|d)ix|ex$", "$1ices"),
		Rule.new("([m|l])ouse$", "$1ice"),
		Rule.new("^(ox)$", "$1en"),
		Rule.new("(quiz)$", "$1zes"),
		Rule.new("(buz|blit|walt)z$", "$1zes"),
		Rule.new("(hoo|lea|loa|thie)f$", "$1ves"),
		Rule.new("(alumn|alg|larv|vertebr)a$", "$1ae"),
		Rule.new("(criteri|phenomen)on$", "$1a")
	]

	# Singular rules.
	vocabulary._singulars = [
		Rule.new("s$", ""),
		Rule.new("(n)ews$", "$1ews"),
		Rule.new("([dti])a$", "$1um"),
		Rule.new("(analy|ba|diagno|parenthe|progno|synop|the|ellip|empha|neuro|oa|paraly)ses$", "$1sis"),
		Rule.new("([^f])ves$", "$1fe"),
		Rule.new("(hive)s$", "$1"),
		Rule.new("(tive)s$", "$1"),
		Rule.new("([lr]|hoo|lea|loa|thie)ves$", "$1f"),
		Rule.new("(^zomb)?([^aeiouy]|qu)ies$", "$2y"),
		Rule.new("(s)eries$", "$1eries"),
		Rule.new("(m)ovies$", "$1ovie"),
		Rule.new("(x|ch|ss|sh)es$", "$1"),
		Rule.new("([m|l])ice$", "$1ouse"),
		Rule.new("(o)es$", "$1"),
		Rule.new("(shoe)s$", "$1"),
		Rule.new("(cris|ax|test)es$", "$1is"),
		Rule.new("(octop|vir|alumn|fung|cact|foc|hippopotam|radi|stimul|syllab|nucle)i$", "$1us"),
		Rule.new("(alias|bias|iris|status|campus|apparatus|virus|walrus|trellis)es$", "$1"),
		Rule.new("^(ox)en", "$1"),
		Rule.new("(matr|d)ices$", "$1ix"),
		Rule.new("(vert|ind)ices$", "$1ex"),
		Rule.new("(quiz)zes$", "$1"),
		Rule.new("(buz|blit|walt)zes$", "$1z"),
		Rule.new("(alumn|alg|larv|vertebr)ae$", "$1a"),
		Rule.new("(criteri|phenomen)a$", "$1on"),
		Rule.new("([b|r|c]ook|room|smooth)ies$", "$1ie")
	]

	# Irregular rules.
	vocabulary.add_irregular("person", "people")
	vocabulary.add_irregular("man", "men")
	vocabulary.add_irregular("human", "humans")
	vocabulary.add_irregular("child", "children")
	vocabulary.add_irregular("sex", "sexes")
	vocabulary.add_irregular("move", "moves")
	vocabulary.add_irregular("goose", "geese")
	vocabulary.add_irregular("wave", "waves")
	vocabulary.add_irregular("die", "dice")
	vocabulary.add_irregular("foot", "feet")
	vocabulary.add_irregular("tooth", "teeth")
	vocabulary.add_irregular("curriculum", "curricula")
	vocabulary.add_irregular("database", "databases")
	vocabulary.add_irregular("zombie", "zombies")
	vocabulary.add_irregular("personnel", "personnel")

	vocabulary.add_irregular("is", "are", true)
	vocabulary.add_irregular("that", "those", true)
	vocabulary.add_irregular("this", "these", true)
	vocabulary.add_irregular("bus", "buses", true)
	vocabulary.add_irregular("staff", "staff", true)

	# Uncountables.
	vocabulary._uncountables = [
		"equipment",
		"information",
		"corn",
		"milk",
		"rice",
		"money",
		"species",
		"series",
		"fish",
		"sheep",
		"deer",
		"aircraft",
		"oz",
		"tsp",
		"tbsp",
		"ml",
		"l",
		"water",
		"waters",
		"semen",
		"sperm",
		"bison",
		"grass",
		"hair",
		"mud",
		"elk",
		"luggage",
		"moose",
		"offspring",
		"salmon",
		"shrimp",
		"someone",
		"swine",
		"trout",
		"tuna",
		"corps",
		"scissors",
		"means",
		"mail"
	]

	return vocabulary
