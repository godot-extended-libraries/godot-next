class_name Vec3
extends Resource
# author: aaronfranke
# license: MIT
# description: Adds more constants for Vector3.
# notes:
#	- Also includes all of Godot's Vector3 constants.

const ZERO = Vector3(0, 0, 0)
const ONE = Vector3(1, 1, 1)
const RIGHT = Vector3(1, 0, 0)
const BACK_RIGHT = Vector3(1, 0, 1)
const BACK = Vector3(0, 0, 1)
const BACK_LEFT = Vector3(-1, 0, 1)
const LEFT = Vector3(-1, 0, 0)
const FORWARD_LEFT = Vector3(-1, 0, -1)
const FORWARD = Vector3(0, 0, -1)
const FORWARD_RIGHT = Vector3(1, 0, -1)

const DIR_CARDINAL = [
	RIGHT,
	BACK,
	LEFT,
	FORWARD,
]

const DIR = [
	RIGHT,
	BACK_RIGHT,
	BACK,
	BACK_LEFT,
	LEFT,
	FORWARD_LEFT,
	FORWARD,
	FORWARD_RIGHT,
]

const RIGHT_NORM = Vector3(1, 0, 0)
const BACK_RIGHT_NORM = Vector3(0.7071067811865475244, 0, 0.7071067811865475244)
const BACK_NORM = Vector3(0, 0, 1)
const BACK_LEFT_NORM = Vector3(-0.7071067811865475244, 0, 0.7071067811865475244)
const LEFT_NORM = Vector3(-1, 0, 0)
const FORWARD_LEFT_NORM = Vector3(-0.7071067811865475244, 0, -0.7071067811865475244)
const FORWARD_NORM = Vector3(0, 0, -1)
const FORWARD_RIGHT_NORM = Vector3(0.7071067811865475244, 0, -0.7071067811865475244)

const DIR_NORM = [
	RIGHT_NORM,
	BACK_RIGHT_NORM,
	BACK_NORM,
	BACK_LEFT_NORM,
	LEFT_NORM,
	FORWARD_LEFT_NORM,
	FORWARD_NORM,
	FORWARD_RIGHT_NORM,
]

const E = Vector3(1, 0, 0)
const SE = Vector3(1, 0, 1)
const S = Vector3(0, 0, 1)
const SW = Vector3(-1, 0, 1)
const W = Vector3(-1, 0, 0)
const NW = Vector3(-1, 0, -1)
const N = Vector3(0, 0, -1)
const NE = Vector3(1, 0, -1)

const E_NORM = Vector3(1, 0, 0)
const SE_NORM = Vector3(0.7071067811865475244, 0, 0.7071067811865475244)
const S_NORM = Vector3(0, 0, 1)
const SW_NORM = Vector3(-0.7071067811865475244, 0, 0.7071067811865475244)
const W_NORM = Vector3(-1, 0, 0)
const NW_NORM = Vector3(-0.7071067811865475244, 0, -0.7071067811865475244)
const N_NORM = Vector3(0, 0, -1)
const NE_NORM = Vector3(0.7071067811865475244, 0, -0.7071067811865475244)

# These are always normalized, because tan(22.5 degrees) is not rational.
const SEE = Vector3(0.9238795325112867561, 0, 0.3826834323650897717)
const SSE = Vector3(0.3826834323650897717, 0, 0.9238795325112867561)
const SSW = Vector3(-0.3826834323650897717, 0, 0.9238795325112867561)
const SWW = Vector3(-0.9238795325112867561, 0, 0.3826834323650897717)
const NWW = Vector3(-0.9238795325112867561, 0, -0.3826834323650897717)
const NNW = Vector3(-0.3826834323650897717, 0, -0.9238795325112867561)
const NNE = Vector3(0.3826834323650897717, 0, -0.9238795325112867561)
const NEE = Vector3(0.9238795325112867561, 0, -0.3826834323650897717)

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

const UP = Vector3(0, 1, 0)
const UP_RIGHT = Vector3(1, 1, 0)
const UP_BACK_RIGHT = Vector3(1, 1, 1)
const UP_BACK = Vector3(0, 1, 1)
const UP_BACK_LEFT = Vector3(-1, 1, 1)
const UP_LEFT = Vector3(-1, 1, 0)
const UP_FORWARD_LEFT = Vector3(-1, 1, -1)
const UP_FORWARD = Vector3(0, 1, -1)
const UP_FORWARD_RIGHT = Vector3(1, 1, -1)

const DOWN = Vector3(0, -1, 0)
const DOWN_RIGHT = Vector3(1, -1, 0)
const DOWN_BACK_RIGHT = Vector3(1, -1, 1)
const DOWN_BACK = Vector3(0, -1, 1)
const DOWN_BACK_LEFT = Vector3(-1, -1, 1)
const DOWN_LEFT = Vector3(-1, -1, 0)
const DOWN_FORWARD_LEFT = Vector3(-1, -1, -1)
const DOWN_FORWARD = Vector3(0, -1, -1)
const DOWN_FORWARD_RIGHT = Vector3(1, -1, -1)

const UP_NORM = Vector3(0, 1, 0)
const UP_RIGHT_NORM = Vector3(0.7071067811865475244, 0.7071067811865475244, 0)
const UP_BACK_RIGHT_NORM = Vector3(0.5773502691896257645, 0.5773502691896257645, 0.5773502691896257645)
const UP_BACK_NORM = Vector3(0, 0.7071067811865475244, 0.7071067811865475244)
const UP_BACK_LEFT_NORM = Vector3(-0.5773502691896257645, 0.5773502691896257645, 0.5773502691896257645)
const UP_LEFT_NORM = Vector3(-0.7071067811865475244, 0.7071067811865475244, 0)
const UP_FORWARD_LEFT_NORM = Vector3(-0.5773502691896257645, 0.5773502691896257645, -0.5773502691896257645)
const UP_FORWARD_NORM = Vector3(0, 0.7071067811865475244, -0.7071067811865475244)
const UP_FORWARD_RIGHT_NORM = Vector3(0.5773502691896257645, 0.5773502691896257645, -0.5773502691896257645)

const DOWN_NORM = Vector3(0, -1, 0)
const DOWN_RIGHT_NORM = Vector3(0.7071067811865475244, -0.7071067811865475244, 0)
const DOWN_BACK_RIGHT_NORM = Vector3(0.5773502691896257645, -0.5773502691896257645, 0.5773502691896257645)
const DOWN_BACK_NORM = Vector3(0, -0.7071067811865475244, 0.7071067811865475244)
const DOWN_BACK_LEFT_NORM = Vector3(-0.5773502691896257645, -0.5773502691896257645, 0.5773502691896257645)
const DOWN_LEFT_NORM = Vector3(-0.7071067811865475244, -0.7071067811865475244, 0)
const DOWN_FORWARD_LEFT_NORM = Vector3(-0.5773502691896257645, -0.5773502691896257645, -0.5773502691896257645)
const DOWN_FORWARD_NORM = Vector3(0, -0.7071067811865475244, -0.7071067811865475244)
const DOWN_FORWARD_RIGHT_NORM = Vector3(0.5773502691896257645, -0.5773502691896257645, -0.5773502691896257645)