# godot-next

## Disclaimer

Please note that this repository has been moved to `godot-extended-libraries/godot-next`. Please visit there if you would like to track its continued development! I am still the maintainer of it within that organization.

## Description

Godot Node Extensions, AKA Godot NExt, is a Godot 3.1+ repository dedicated to collecting basic script classes that are currently unavailable in vanilla Godot.

As you might have noticed, Godot Engine's initial node offerings are general purpose and are intentionally not oriented towards particular types of games.

This repository's purpose is to create classes that fulfill a particular function and work out-of-the-box. Users should be able to use your class immediately after creating it. For nodes, don't be afraid to design ones that have an array of dynamically generated children. ;-)

Note: The repository is named after Nodes, but ultimately any general-purpose type is welcome here (References, Resources, etc.).

If you like the project, please star it. If you'd like to support its development, please [send tips to my Kofi](https://ko-fi.com/willnationsdev).

[Jump to Class List](#classes)

## How to Use

1. Download the repo directly (the AssetLib version is no longer maintained)

2. Copy the addons directory to any project you would like to use them in

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

**All C#** scripts must be submitted to a separate `addons/godot-next-cs` folder. This is to ensure that users who aren't using the Mono-enabled version of Godot do not have C# scripts present.

Submissions are **encouraged** to do the following:

1. Provide a 16x16 SVG icon for each submitted script.
2. Use statically-typed GDScript if submitting GDScript files.
3. Create mirrored versions of GDScript and C# scripts between folders.
4. Add your node(s)' information to the bottom of the README, if possible (less work for maintainers).

That's it! I hope you've got ideas of what you'd like to share with others.

# Classes

|Linkable Node Name|Description|Language
|-|-|-|
|[Array2D](addons/godot-next/references/array_2d.gd)|A 2D Array class.|GDScript
|[BitFlag](addons/godot-next/references/bit_flag.gd)|A class that allows abstracts away the complexity of handling bit flag enum types.|GDScript
|[Bitset](addons/godot-next/references/bigset.gd)|A class that allows for easily manipulated bitmasks of any size.|GDScript
|[Behavior](addons/godot-next/resources/behavior.gd)|A Resource type that automatically calls Node-like notification methods when paired with the CallbackDelegator class.|GDScript
|[CallbackDelegator](addons/godot-next/nodes/callback_delegator.gd)|A Node that manages a ResourceSet of resources and delegates Node callbacks to each instance.|GDScript
|[ClassType](addons/godot-next/references/class_type.gd)|A class abstraction, both for engine and user-defined types.|GDScript
|[CSVFile](addons/godot-next/references/csv_file.gd)|Similar to ConfigFile, parses a .csv file. Can generate a key-value store from rows. Supports .tsv files.|GDScript
|[Cycle](addons/godot-next/gui/cycle.gd)|Cycles through child nodes without any visibility or container effects.|GDScript
|[DebugLabel](addons/godot-next/gui/debug_label.gd)|A label which displays a list of property values in any `Object`-derived instance at run-time for debugging purposes.|GDScript
|[EditorTools](addons/godot-next/global/editor_tools.gd)|A utility for any features useful in the context of the Editor.|GDScript
|[FileSearch](addons/godot-next/global/file_search.gd)|A utility with helpful methods to search through one's project files (or any directory).|GDScript
|[FileSystemLink](addons/godot-next/global/file_system_link.gd)|A utility for creating links (file/directory, symbolic/hard).|GDScript
|[Geometry2D](addons/godot-next/2d/geometry_2d.gd)|A utility that draws a Shape2D using CollisionShape2D's editor plugin handles.|GDScript
|[Inflector](addons/godot-next/references/inflector.gd)|A vocabulary wrapper of inflection tools to pluralize and singularize strings.|GDScript
|[InspectorControls](addons/godot-next/global/inspector_controls.gd)|A utility for creating data-editing GUI elements.|GDScript
|[MessageDispatcher](addons/godot-next/objects/message_dispatcher.gd)|A base object that handles signaling for non predetermined signals.|GDScript
|[PhysicsLayers](addons/godot-next/global/physics_layers.gd)|A Utility class which allows easy access to your physics layers via their names in the project settings.|GDScript
|[ProjectTools](addons/godot-next/global/project_tools.gd)|A utility for any features useful in the context of a Godot Project.|GDScript
|[PropertyInfo](addons/godot-next/references/property_info.gd)|A wrapper and utility class for generating PropertyInfo Dictionaries, for use in `Object._get_property_list()`.|GDScript
|[ResourceArray](addons/godot-next/resources/resource_collections/resource_array.gd)|A ResourceCollection implementation that manages an Array of Resources.|GDScript
|[ResourceCollection](addons/godot-next/resources/resource_collections/resource_collection.gd)|An abstract base class for data structures that store Resource objects.|GDScript
|[ResourceSet](addons/godot-next/resources/resource_collections/resource_set.gd)|A ResourceCollection implementation that manages a Set of Resources.|GDScript
|[Singletons](addons/godot-next/global/singletons.gd)|A utility for caching Reference-derived singletons. Resources with a `SELF_RESOURCE` constant with a path to a `*.tres` file will be automatically loaded when accessed.|GDScript
|[Trail2D](addons/godot-next/2d/trail_2d.gd)|Creates a variable-length trail that tracks a "target" node.|GDScript
|[Trail3D](addons/godot-next/3d/trail_3d.gd)|Creates a variable-length trail on an ImmediateGeometry node.|GDScript
|[Tween Sequence](addons/godot-next/references/tween_sequence.gd)|A helper class for easier management and chaining of Tweens dynamically from code.|GDScript
|[Variant](addons/godot-next/global/variant.gd)|A utility class for handling Variants (the type wrapper for all variables in Godot's scripting API).|GDScript
|[VBoxItemList](addons/godot-next/gui/v_box_item_list.gd)|Creates a vertical list of items that can be added or removed. Items are a user-specified Script or Scene Control.|GDScript
|[DiscreteGradientTexture](addons/godot-next/resources/DiscreteGradientTexture.gd)|Creates a not interpolated texture for a gradient.|GDScript
