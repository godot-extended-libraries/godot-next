using Godot;

[Tool]
public class Geometry2D : CollisionShape2D
{
    private Color _color = Colors.White;
    private Vector2 _offsetPosition;

    [Export] public Color ShapeColor { get => _color; set { _color = value; Update(); } }
    [Export] public Vector2 OffsetPosition { get => _offsetPosition; set { _offsetPosition = value; Update(); } }

    public override void _Draw()
    {
        if (Shape is CircleShape2D)
        {
            DrawCircle(_offsetPosition, ((CircleShape2D)Shape).Radius, _color);
        }
        else if (Shape is RectangleShape2D)
        {
            RectangleShape2D rectangleShape = (RectangleShape2D)Shape;
            Rect2 rect = new Rect2(_offsetPosition - rectangleShape.Extents, rectangleShape.Extents * 2.0f);
            DrawRect(rect, _color);
        }
        else if (Shape is CapsuleShape2D)
        {
            CapsuleShape2D capsuleShape = (CapsuleShape2D)Shape;
            DrawCapsule(_offsetPosition, capsuleShape.Radius, capsuleShape.Height, _color);
        }
    }

    public void DrawCapsule(Vector2 capsulePosition, float capsuleRadius, float capsuleHeight, Color capsuleColor)
    {
        Vector2 upperCirclePosition = capsulePosition + new Vector2(0, capsuleHeight * 0.5f);
        DrawCircle(upperCirclePosition, capsuleRadius, capsuleColor);

        Vector2 lowerCirclePosition = capsulePosition - new Vector2(0, capsuleHeight * 0.5f);
        DrawCircle(lowerCirclePosition, capsuleRadius, capsuleColor);

        Vector2 rectPosition = capsulePosition - new Vector2(capsuleRadius, capsuleHeight * 0.5f);
        Rect2 rect = new Rect2(rectPosition, new Vector2(capsuleRadius * 2, capsuleHeight));
        DrawRect(rect, capsuleColor);
    }
}
