# godot-next

Godot Node Extensions, AKA Godot NExt, is a Godot 3.1+ repository dedicated to collecting basic script classes that are currently unavailable in vanilla Godot.

As you might have noticed, Godot Engine's initial node offerings are general purpose and are intentionally not oriented towards particular types of games.

This repository's purpose is to create classes that fulfill a particular function and work out-of-the-box. Users should be able to use your class immediately after creating it. For nodes, don't be afraid to design ones that have an array of dynamically generated children. ;-)

Note: The repository is named after Nodes, but ultimately any general-purpose type is welcome here (References, Resources, etc.).

[Jump to Class List](https://github.com/willnationsdev/godot-next#classes)

## How to Use

1. Create or open a project.

2. Go to the Asset Library tab, search for "Godot NExt" and install the plugin.

3. Open Project Settings and go to the Plugins tab.

4. Find the `godot-next` plugin and select "Active" from the dropdown on the right-hand side.

5. You should now be able to create each new type of node in your project!

## How to Contribute

### Ideas
If you have an idea for a node that you would like to have added to the repository, create a new Issue.

### Scripts

**All** scripts must be script classes, i.e. scripts with [registered names](http://docs.godotengine.org/en/latest/getting_started/step_by_step/scripting_continued.html#register-scripts-as-classes).

**All** scripts must have the author's name at the top.

**All** credits related to any associated script code or icons should be kept in the `ATTRIBUTIONS.md` file.

**All** scripts must adhere to the relevant language's styling conventions, modeled after Godot Docs examples and the Godot Engine source code.

**All C#** scripts must be submitted to a `*-cs` branch, e.g. `master-cs`, `3.1-cs`, etc. This is to ensure that users who aren't using the Mono-enabled version of Godot do not have C# scripts present.

Submissions are **encouraged** to do the following:

1. Provide a 16x16 SVG icon for each submitted script.
2. Use statically-typed GDScript if submitting one or more GDScript files.
3. Create mirrored versions of GDScript and C# scripts between branches.
4. Add your node(s)' information to the bottom of the README, if possible (less work for maintainers).

That's it! I hope you've got ideas of what you'd like to share with others.

# Classes

|Linkable Node Name|Description|Language
|-|-|-|
|[Array2D](addons/godot-next/references/array_2d.gd)|A 2D Array class.|GDScript
|[CSVFile](addons/godot-next/references/csv_file.gd)|Similar to ConfigFile, parses a .csv file. Can generate a key-value store from rows. Supports .tsv files.|GDScript
|[Cycle](addons/godot-next/gui/cycle.gd)|Cycles through child nodes without any visibility or container effects.|GDScript
|[Trail2D](addons/godot-next/2d/trails.gd)|Creates a variable-length trail that tracks a "target" node.|GDScript
|[VBoxItemList](addons/godot-next/gui/v_box_item_list.gd)|Creates a vertical list of items that can be added or removed. Items are a user-specified Script or Scene Control.|GDScript
