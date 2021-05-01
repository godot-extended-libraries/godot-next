using Godot;
using Vector3Array = Godot.Collections.Array<Godot.Vector3>;

/// <summary>
/// Adds more constants for Vector3.
/// </summary>
/// <remarks>
/// Also includes all of Godot's Vector3 constants.
/// </remarks>
public static partial class Vec3
{
    public static readonly Vector3 Zero = new Vector3(0, 0, 0);
    public static readonly Vector3 One = new Vector3(1, 1, 1);
    public static readonly Vector3 Right = new Vector3(1, 0, 0);
    public static readonly Vector3 BackRight = new Vector3(1, 0, 1);
    public static readonly Vector3 Back = new Vector3(0, 0, 1);
    public static readonly Vector3 BackLeft = new Vector3(-1, 0, 1);
    public static readonly Vector3 Left = new Vector3(-1, 0, 0);
    public static readonly Vector3 ForwardLeft = new Vector3(-1, 0, -1);
    public static readonly Vector3 Forward = new Vector3(0, 0, -1);
    public static readonly Vector3 ForwardRight = new Vector3(1, 0, -1);

    public static readonly Vector3Array DirCardinal = new Vector3Array{
        Right,
        Back,
        Left,
        Forward,
    };

    public static readonly Vector3Array Dir = new Vector3Array{
        Right,
        BackRight,
        Back,
        BackLeft,
        Left,
        ForwardLeft,
        Forward,
        ForwardRight,
    };

    public static readonly Vector3 RightNorm = new Vector3(1, 0, 0);
    public static readonly Vector3 BackRightNorm = new Vector3(0.7071067811865475244f, 0, 0.7071067811865475244f);
    public static readonly Vector3 BackNorm = new Vector3(0, 0, 1);
    public static readonly Vector3 BackLeftNorm = new Vector3(-0.7071067811865475244f, 0, 0.7071067811865475244f);
    public static readonly Vector3 LeftNorm = new Vector3(-1, 0, 0);
    public static readonly Vector3 ForwardLeftNorm = new Vector3(-0.7071067811865475244f, 0, -0.7071067811865475244f);
    public static readonly Vector3 ForwardNorm = new Vector3(0, 0, -1);
    public static readonly Vector3 ForwardRightNorm = new Vector3(0.7071067811865475244f, 0, -0.7071067811865475244f);

    public static readonly Vector3Array DirNorm = new Vector3Array{
        RightNorm,
        BackRightNorm,
        BackNorm,
        BackLeftNorm,
        LeftNorm,
        ForwardLeftNorm,
        ForwardNorm,
        ForwardRightNorm,
    };

    public static readonly Vector3 E = new Vector3(1, 0, 0);
    public static readonly Vector3 SE = new Vector3(1, 0, 1);
    public static readonly Vector3 S = new Vector3(0, 0, 1);
    public static readonly Vector3 SW = new Vector3(-1, 0, 1);
    public static readonly Vector3 W = new Vector3(-1, 0, 0);
    public static readonly Vector3 NW = new Vector3(-1, 0, -1);
    public static readonly Vector3 N = new Vector3(0, 0, -1);
    public static readonly Vector3 NE = new Vector3(1, 0, -1);

    public static readonly Vector3 ENorm = new Vector3(1, 0, 0);
    public static readonly Vector3 SENorm = new Vector3(0.7071067811865475244f, 0, 0.7071067811865475244f);
    public static readonly Vector3 SNorm = new Vector3(0, 0, 1);
    public static readonly Vector3 SWNorm = new Vector3(-0.7071067811865475244f, 0, 0.7071067811865475244f);
    public static readonly Vector3 WNorm = new Vector3(-1, 0, 0);
    public static readonly Vector3 NWNorm = new Vector3(-0.7071067811865475244f, 0, -0.7071067811865475244f);
    public static readonly Vector3 NNorm = new Vector3(0, 0, -1);
    public static readonly Vector3 NENorm = new Vector3(0.7071067811865475244f, 0, -0.7071067811865475244f);

    // These are always normalized, because tan(22.5 degrees) is not rational.
    public static readonly Vector3 SEE = new Vector3(0.9238795325112867561f, 0, 0.3826834323650897717f);
    public static readonly Vector3 SSE = new Vector3(0.3826834323650897717f, 0, 0.9238795325112867561f);
    public static readonly Vector3 SSW = new Vector3(-0.3826834323650897717f, 0, 0.9238795325112867561f);
    public static readonly Vector3 SWW = new Vector3(-0.9238795325112867561f, 0, 0.3826834323650897717f);
    public static readonly Vector3 NWW = new Vector3(-0.9238795325112867561f, 0, -0.3826834323650897717f);
    public static readonly Vector3 NNW = new Vector3(-0.3826834323650897717f, 0, -0.9238795325112867561f);
    public static readonly Vector3 NNE = new Vector3(0.3826834323650897717f, 0, -0.9238795325112867561f);
    public static readonly Vector3 NEE = new Vector3(0.9238795325112867561f, 0, -0.3826834323650897717f);

    public static readonly Vector3Array Dir16 = new Vector3Array{
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

    public static readonly Vector3 Up = new Vector3(0, 1, 0);
    public static readonly Vector3 UpRight = new Vector3(1, 1, 0);
    public static readonly Vector3 UpBackRight = new Vector3(1, 1, 1);
    public static readonly Vector3 UpBack = new Vector3(0, 1, 1);
    public static readonly Vector3 UpBackLeft = new Vector3(-1, 1, 1);
    public static readonly Vector3 UpLeft = new Vector3(-1, 1, 0);
    public static readonly Vector3 UpForwardLeft = new Vector3(-1, 1, -1);
    public static readonly Vector3 UpForward = new Vector3(0, 1, -1);
    public static readonly Vector3 UpForwardRight = new Vector3(1, 1, -1);

    public static readonly Vector3 Down = new Vector3(0, -1, 0);
    public static readonly Vector3 DownRight = new Vector3(1, -1, 0);
    public static readonly Vector3 DownBackRight = new Vector3(1, -1, 1);
    public static readonly Vector3 DownBack = new Vector3(0, -1, 1);
    public static readonly Vector3 DownBackLeft = new Vector3(-1, -1, 1);
    public static readonly Vector3 DownLeft = new Vector3(-1, -1, 0);
    public static readonly Vector3 DownForwardLeft = new Vector3(-1, -1, -1);
    public static readonly Vector3 DownForward = new Vector3(0, -1, -1);
    public static readonly Vector3 DownForwardRight = new Vector3(1, -1, -1);

    public static readonly Vector3 UpNorm = new Vector3(0, 1, 0);
    public static readonly Vector3 UpRightNorm = new Vector3(0.7071067811865475244f, 0.7071067811865475244f, 0);
    public static readonly Vector3 UpBackRightNorm = new Vector3(0.5773502691896257645f, 0.5773502691896257645f, 0.5773502691896257645f);
    public static readonly Vector3 UpBackNorm = new Vector3(0, 0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector3 UpBackLeftNorm = new Vector3(-0.5773502691896257645f, 0.5773502691896257645f, 0.5773502691896257645f);
    public static readonly Vector3 UpLeftNorm = new Vector3(-0.7071067811865475244f, 0.7071067811865475244f, 0);
    public static readonly Vector3 UpForwardLeftNorm = new Vector3(-0.5773502691896257645f, 0.5773502691896257645f, -0.5773502691896257645f);
    public static readonly Vector3 UpForwardNorm = new Vector3(0, 0.7071067811865475244f, -0.7071067811865475244f);
    public static readonly Vector3 UpForwardRightNorm = new Vector3(0.5773502691896257645f, 0.5773502691896257645f, -0.5773502691896257645f);

    public static readonly Vector3 DownNorm = new Vector3(0, -1, 0);
    public static readonly Vector3 DownRightNorm = new Vector3(0.7071067811865475244f, -0.7071067811865475244f, 0);
    public static readonly Vector3 DownBackRightNorm = new Vector3(0.5773502691896257645f, -0.5773502691896257645f, 0.5773502691896257645f);
    public static readonly Vector3 DownBackNorm = new Vector3(0, -0.7071067811865475244f, 0.7071067811865475244f);
    public static readonly Vector3 DownBackLeftNorm = new Vector3(-0.5773502691896257645f, -0.5773502691896257645f, 0.5773502691896257645f);
    public static readonly Vector3 DownLeftNorm = new Vector3(-0.7071067811865475244f, -0.7071067811865475244f, 0);
    public static readonly Vector3 DownForwardLeftNorm = new Vector3(-0.5773502691896257645f, -0.5773502691896257645f, -0.5773502691896257645f);
    public static readonly Vector3 DownForwardNorm = new Vector3(0, -0.7071067811865475244f, -0.7071067811865475244f);
    public static readonly Vector3 DownForwardRightNorm = new Vector3(0.5773502691896257645f, -0.5773502691896257645f, -0.5773502691896257645f);
}
