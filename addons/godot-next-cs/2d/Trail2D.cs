using Godot;

public class Trail2D : Line2D
{
    public enum Persistence
    {
        Off,         // Do not persist. Remove all points after the trailLength.
        Always,      // Always persist. Do not remove any points.
        Conditional, // Sometimes persist. Choose an algorithm for when to add and remove points.
    }

    public enum PersistWhen
    {
        OnMovement, // Add points during movement and remove points when not moving.
        Custom,     // Override ShouldGrow() and ShouldShrink() to define when to add/remove points.
    }

    // The target node to track
    private Node2D _target;

    // The NodePath to the target
    [Export] public NodePath targetPath = "..";
    // if not persisting, the number of points that should be allowed in the trail
    [Export] public int trailLength = 10;
    // To what degree the trail should remain in existence before automatically removing points.
    [Export] public Persistence persistence = Persistence.Off;
    // During conditional persistence, which persistence algorithm to use
    [Export] public PersistWhen persistWhen = PersistWhen.OnMovement;
    // During conditional persistence, how many points to remove per frame
    [Export] public int degenRate = 1;
    // if true, automatically set ZIndex to be one less than the 'target'
    [Export] public bool autoZIndex = true;
    // if true, will automatically setup a gradient for a gradually transparent trail
    [Export] public bool autoAlphaGradient = true;

    public override void _EnterTree()
    {
        SetAsToplevel(true);
        GlobalPosition = Vector2.Zero;
        GlobalRotation = 0;
        if (autoAlphaGradient && Gradient == null)
        {
            Gradient = new Gradient();
            Color first = DefaultColor;
            first.a = 0; // TODO: Use https://github.com/godotengine/godot/pull/31658 instead.
            Gradient.SetColor(0, first);
            Gradient.SetColor(1, DefaultColor);
        }
        _target = GetNodeOrNull<Node2D>(targetPath);
    }

    public override void _Notification(int p_what)
    {
        switch (p_what)
        {
            case Node.NotificationParented:
                if (autoZIndex)
                {
                    ZIndex = _target != null ? _target.ZIndex - 1 : 0;
                }
                break;
            case Node.NotificationUnparented:
                targetPath = @"";
                trailLength = 0;
                break;
        }
    }

    public override void _Process(float delta)
    {
        if (_target == null)
        {
            _target = GetNodeOrNull<Node2D>(targetPath);
            return;
        }

        switch (persistence)
        {
            case Persistence.Off:
                AddPoint(_target.GlobalPosition);
                while (GetPointCount() > trailLength)
                {
                    RemovePoint(0);
                }
                break;
            case Persistence.Always:
                AddPoint(_target.GlobalPosition);
                break;
            case Persistence.Conditional:
                switch (persistWhen)
                {
                    case PersistWhen.OnMovement:
                        bool moved = GetPointCount() > 0 ? GetPointPosition(GetPointCount() - 1) != _target.GlobalPosition : false;
                        if (GetPointCount() == 0 || moved)
                        {
                            AddPoint(_target.GlobalPosition);
                        }
                        else
                        {
                            for (int i = 0; i < degenRate; i++)
                            {
                                RemovePoint(0);
                            }
                        }
                        break;
                    case PersistWhen.Custom:
                        if (ShouldGrow())
                        {
                            AddPoint(_target.GlobalPosition);
                            if (ShouldShrink())
                            {
                                for (int i = 0; i < degenRate; i++)
                                {
                                    RemovePoint(0);
                                }
                            }
                            break;
                        }
                        break;
                }
                break;
        }
    }

    protected bool ShouldGrow() { return true; }
    protected bool ShouldShrink() { return true; }

    public void EraseTrail()
    {
        for (int i = 0; i < GetPointCount(); i++)
        {
            RemovePoint(0);
        }
    }

    public void SetTarget(Node2D value)
    {
        if (value != null)
        {
            if (GetPathTo(value) != targetPath)
            {
                targetPath = GetPathTo(value);
            }
        }
        else
        {
            targetPath = @"";
        }
    }

    public void SetTargetPath(NodePath value)
    {
        targetPath = value;
        _target = GetNode(value) as Node2D;
    }
}
