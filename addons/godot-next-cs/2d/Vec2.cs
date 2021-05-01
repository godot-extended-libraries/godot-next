using Godot;
using Vector2Array = Godot.Collections.Array<Godot.Vector2>;

/// <summary>
/// Adds more constants for Vector2.
/// </summary>
/// <remarks>
/// Also includes all of Godot's Vector2 constants.
/// </remarks>
public static partial class Vec2
{
    public static readonly Vector2 Zero = new Vector2(0, 0);
    public static readonly Vector2 One = new Vector2(1, 1);
    public static readonly Vector2 Right = new Vector2(1, 0);
    public static readonly Vector2 DownRight = new Vector2(1, 1);
    public static readonly Vector2 Down = new Vector2(0, 1);
    public static readonly Vector2 DownLeft = new Vector2(-1, 1);
    public static readonly Vector2 Left = new Vector2(-1, 0);
    public static readonly Vector2 UpLeft = new Vector2(-1, -1);
    public static readonly Vector2 Up = new Vector2(0, -1);
    public static readonly Vector2 UpRight = new Vector2(1, -1);

    public static readonly Vector2Array DirCardinal = new Vector2Array{
        Right,
        Down,
        Left,
        Up,
    };

    public static readonly Vector2Array Dir = new Vector2Array{
        Right,
        DownRight,
        Down,
        DownLeft,
        Left,
        UpLeft,
        Up,
        UpRight,
    };

    public static readonly Vector2 RightNorm = new Vector2(1, 0);
    public static readonly Vector2 DownRightNorm = new Vector2(0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector2 DownNorm = new Vector2(0, 1);
    public static readonly Vector2 DownLeftNorm = new Vector2(-0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector2 LeftNorm = new Vector2(-1, 0);
    public static readonly Vector2 UpLeftNorm = new Vector2(-0.7071067811865475244f, -0.7071067811865475244f);
    public static readonly Vector2 UpNorm = new Vector2(0, -1);
    public static readonly Vector2 UpRightNorm = new Vector2(0.7071067811865475244f, -0.7071067811865475244f);

    public static readonly Vector2Array DirNorm = new Vector2Array{
        RightNorm,
        DownRightNorm,
        DownNorm,
        DownLeftNorm,
        LeftNorm,
        UpLeftNorm,
        UpNorm,
        UpRightNorm,
    };

    public static readonly Vector2 E = new Vector2(1, 0);
    public static readonly Vector2 SE = new Vector2(1, 1);
    public static readonly Vector2 S = new Vector2(0, 1);
    public static readonly Vector2 SW = new Vector2(-1, 1);
    public static readonly Vector2 W = new Vector2(-1, 0);
    public static readonly Vector2 NW = new Vector2(-1, -1);
    public static readonly Vector2 N = new Vector2(0, -1);
    public static readonly Vector2 NE = new Vector2(1, -1);

    public static readonly Vector2 ENorm = new Vector2(1, 0);
    public static readonly Vector2 SENorm = new Vector2(0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector2 SNorm = new Vector2(0, 1);
    public static readonly Vector2 SWNorm = new Vector2(-0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector2 WNorm = new Vector2(-1, 0);
    public static readonly Vector2 NWNorm = new Vector2(-0.7071067811865475244f, -0.7071067811865475244f);
    public static readonly Vector2 NNorm = new Vector2(0, -1);
    public static readonly Vector2 NENorm = new Vector2(0.7071067811865475244f, -0.7071067811865475244f);

    // These are always normalized, because tan(22.5 degrees) is not rational.
    public static readonly Vector2 SEE = new Vector2(0.9238795325112867561f, 0.3826834323650897717f);
    public static readonly Vector2 SSE = new Vector2(0.3826834323650897717f, 0.9238795325112867561f);
    public static readonly Vector2 SSW = new Vector2(-0.3826834323650897717f, 0.9238795325112867561f);
    public static readonly Vector2 SWW = new Vector2(-0.9238795325112867561f, 0.3826834323650897717f);
    public static readonly Vector2 NWW = new Vector2(-0.9238795325112867561f, -0.3826834323650897717f);
    public static readonly Vector2 NNW = new Vector2(-0.3826834323650897717f, -0.9238795325112867561f);
    public static readonly Vector2 NNE = new Vector2(0.3826834323650897717f, -0.9238795325112867561f);
    public static readonly Vector2 NEE = new Vector2(0.9238795325112867561f, -0.3826834323650897717f);

    public static readonly Vector2Array Dir16 = new Vector2Array{
        ENorm,
        SEE,
        SENorm,
        SSE,
        SNorm,
        SSW,
        SWNorm,
        SWW,
        WNorm,
        NWW,
        NWNorm,
        NNW,
        NNorm,
        NNE,
        NENorm,
        NEE,
    };
}
