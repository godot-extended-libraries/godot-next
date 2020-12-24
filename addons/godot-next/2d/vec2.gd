class_name Vec2
extends Resource
# author: aaronfranke
# license: MIT
# description: Adds more constants for Vector2.
# notes:
#	- Also includes all of Godot's Vector2 constants.

const ZERO = Vector2(0, 0)
const ONE = Vector2(1, 1)
const RIGHT = Vector2(1, 0)
const DOWN_RIGHT = Vector2(1, 1)
const DOWN = Vector2(0, 1)
const DOWN_LEFT = Vector2(-1, 1)
const LEFT = Vector2(-1, 0)
const UP_LEFT = Vector2(-1, -1)
const UP = Vector2(0, -1)
const UP_RIGHT = Vector2(1, -1)

const DIR_CARDINAL = [
	RIGHT,
	DOWN,
	LEFT,
	UP,
]

const DIR = [
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT,
	UP,
	UP_RIGHT,
]

const RIGHT_NORM = Vector2(1, 0)
const DOWN_RIGHT_NORM = Vector2(0.7071067811865475244, 0.7071067811865475244)
const DOWN_NORM = Vector2(0, 1)
const DOWN_LEFT_NORM = Vector2(-0.7071067811865475244, 0.7071067811865475244)
const LEFT_NORM = Vector2(-1, 0)
const UP_LEFT_NORM = Vector2(-0.7071067811865475244, -0.7071067811865475244)
const UP_NORM = Vector2(0, -1)
const UP_RIGHT_NORM = Vector2(0.7071067811865475244, -0.7071067811865475244)

const DIR_NORM = [
	RIGHT_NORM,
	DOWN_RIGHT_NORM,
	DOWN_NORM,
	DOWN_LEFT_NORM,
	LEFT_NORM,
	UP_LEFT_NORM,
	UP_NORM,
	UP_RIGHT_NORM,
]

const E = Vector2(1, 0)
const SE = Vector2(1, 1)
const S = Vector2(0, 1)
const SW = Vector2(-1, 1)
const W = Vector2(-1, 0)
const NW = Vector2(-1, -1)
const N = Vector2(0, -1)
const NE = Vector2(1, -1)

const E_NORM = Vector2(1, 0)
const SE_NORM = Vector2(0.7071067811865475244, 0.7071067811865475244)
const S_NORM = Vector2(0, 1)
const SW_NORM = Vector2(-0.7071067811865475244, 0.7071067811865475244)
const W_NORM = Vector2(-1, 0)
const NW_NORM = Vector2(-0.7071067811865475244, -0.7071067811865475244)
const N_NORM = Vector2(0, -1)
const NE_NORM = Vector2(0.7071067811865475244, -0.7071067811865475244)

# These are always normalized, because tan(22.5 degrees) is not rational.
const SEE = Vector2(0.9238795325112867561, 0.3826834323650897717)
const SSE = Vector2(0.3826834323650897717, 0.9238795325112867561)
const SSW = Vector2(-0.3826834323650897717, 0.9238795325112867561)
const SWW = Vector2(-0.9238795325112867561, 0.3826834323650897717)
const NWW = Vector2(-0.9238795325112867561, -0.3826834323650897717)
const NNW = Vector2(-0.3826834323650897717, -0.9238795325112867561)
const NNE = Vector2(0.3826834323650897717, -0.9238795325112867561)
const NEE = Vector2(0.9238795325112867561, -0.3826834323650897717)

const DIR_16 = [
	E_NORM,
	SEE,
	SE_NORM,
	SSE,
	S_NORM,
	SSW,
	SW_NORM,
	SWW,
	W_NORM,
	NWW,
	NW_NORM,
	NNW,
	N_NORM,
	NNE,
	NE_NORM,
	NEE,
]
