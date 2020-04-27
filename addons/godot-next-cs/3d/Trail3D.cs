using Godot;

public class Trail3D : ImmediateGeometry
{
    [Export] public float length = 10.0f;
    [Export] public float maxRadius = 0.5f;
    [Export] public int densityLengthwise = 25;
    [Export] public int densityAround = 5;
    [Export] public float shape = 0;
    [Export] public Godot.Collections.Array<Vector3> points = new Godot.Collections.Array<Vector3>();
    [Export] public float segmentLength = 1.0f;

    public override void _Ready()
    {
        if (length <= 0) length = 2;
        if (densityAround < 3) densityAround = 3;
        if (densityLengthwise < 2) densityLengthwise = 2;

        segmentLength = length / densityLengthwise;
        for (int i = 0; i < densityLengthwise; i++)
        {
            points.Add(GlobalTransform.origin);
        }
    }

    public override void _Process(float delta)
    {
        UpdateTrail();
        RenderTrail();
    }

    public void UpdateTrail()
    {
        int i = 0;
        Vector3 lastP = GlobalTransform.origin;
        foreach (Vector3 p in points)
        {
            Vector3 v = p; // We can't assign to foreach iterators in C#.
            float dis = v.DistanceTo(lastP);
            float segLen = segmentLength;
            if (i == 0)
            {
                segLen = 0.05f;
            }
            if (dis > segLen)
            {
                v = lastP + (v - lastP) / dis * segLen;
            }
            lastP = v;
            points[i] = v;
            i += 1;
        }
    }

    public void RenderTrail()
    {
        Clear();
        Begin(Mesh.PrimitiveType.Triangles);
        Godot.Collections.Array<Vector3> localPoints = new Godot.Collections.Array<Vector3>();
        foreach (Vector3 p in points)
        {
            localPoints.Add(p - GlobalTransform.origin);
        }
        Vector3 lastP = Vector3.Zero;
        Godot.Collections.Array<Godot.Collections.Array<Vector3>> verts = new Godot.Collections.Array<Godot.Collections.Array<Vector3>>();
        int ind = 0;
        bool firstIteration = true;
        Vector3 lastFirstVec = Vector3.Zero;
        foreach (Vector3 p in localPoints)
        {
            Godot.Collections.Array<Vector3> newLastPoints = new Godot.Collections.Array<Vector3>();
            var offset = lastP - p;
            if (offset == Vector3.Zero)
            {
                continue;
            }
            var yVec = offset.Normalized(); // get vector pointing from this point to last point
            var xVec = Vector3.Zero;
            if (firstIteration)
            {
                xVec = yVec.Cross(yVec.Rotated(Vector3.Right, 0.3f)); //cross product with random vector to get a perpendicular vector
            }
            else
            {
                xVec = yVec.Cross(lastFirstVec).Cross(yVec).Normalized(); // keep each loop at the same rotation as the previous
            }
            var width = maxRadius;
            if (shape != 0)
            {
                width = (1 - Mathf.Ease((ind + 1.0f) / densityLengthwise, shape)) * maxRadius;
            }
            Godot.Collections.Array<Vector3> segVerts = new Godot.Collections.Array<Vector3>();
            var fIter = true;
            for (int i = 0; i < densityAround; i++) // set up row of verts for each level
            {
                var newVert = p + width * xVec.Rotated(yVec, i * 2 * Mathf.Pi / densityAround).Normalized();
                if (fIter)
                {
                    lastFirstVec = newVert - p;
                    fIter = false;
                }
                segVerts.Add(newVert);
            }
            verts.Add(segVerts);
            lastP = p;
            ind += 1;
            firstIteration = false;
        }
        for (int j = 0; j < verts.Count - 1; j++)
        {

            var cur = verts[j];
            var nxt = verts[j + 1];
            for (int i = 0; i < densityAround; i++)
            {
                var nxtI = (i + 1) % densityAround;
                //order added affects normal
                AddVertex(cur[i]);
                AddVertex(cur[nxtI]);
                AddVertex(nxt[i]);
                AddVertex(cur[nxtI]);
                AddVertex(nxt[nxtI]);
                AddVertex(nxt[i]);
            }
        }
        if (verts.Count > 1)
        {
            for (int i = 0; i < densityAround; i++)
            {
                var nxt = (i + 1) % densityAround;
                AddVertex(verts[0][i]);
                AddVertex(Vector3.Zero);
                AddVertex(verts[0][nxt]);
            }

            for (int i = 0; i < densityAround; i++)
            {
                var nxt = (i + 1) % densityAround;
                AddVertex(verts[verts.Count - 1][i]);
                AddVertex(verts[verts.Count - 1][nxt]);
                AddVertex(lastP);
            }
        }
        End();
    }
}
