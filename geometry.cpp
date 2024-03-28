namespace geometry
{
    //(!!!) the result of some functions may depend on the variable 'FloatingPointPrecision'

    ///TERMINOLOGY

    //(bitex) :: 2D point
    //(termex) :: end point of a vector
    //(centex) :: center point of a line
    //(common vertex / common endpoint) :: a point that belongs to two different lines
    //(aligned lines) the meaning is described in the section LINES
    //(unified lines) the meaning is described in the section LINES
    //(line touching) one of the endpoints of a line-1 belongs to the set of points of line-2
    //(formator) a line between two adjacent vertices of a polygon
    //(radial) the meaning is described in the section ORIENTATIONS

    ///COORDINATE SYSTEMS

    /* three types of coordinate systems:
       - Top-Left - with origin the top-left point/corner of a 2D plane; coordinates are always positive
       - Bottom-Left - with origin the bottom-left point/corner of a 2D plane; coordinates are always positive
       - Cartesian - (OBVIOUS-MEANING); coordinates can be negative or positive */

    ///ORIENTATIONS

    /* - orientations are specified in degrees
       - every orientation can have a value between 0.0 and infinity
       - every orientation has a 'true value' or so called 'radial' which is between 0.0 and 360.0
         (EXAMPLE) the radial of an orientation 19 is 19
         (EXAMPLE) the radial of an orientation 348 is 348
         (EXAMPLE) the radial of an orientation 523 is 163 (one full turn + 163 degrees)
         (EXAMPLE) the radial of an orientation 745 is 25 (two full turns + 45 degrees)
       - each orientation has 'opposite' orientation; an orientation and it's opposite differ by 180 degrees
         (EXAMPLE) the opposite orientation of 32 is 212
         (EXAMPLE) the opposite orientation of 212 is 32
         (EXAMPLE) the opposite orientation of 95 is 275
         (EXAMPLE) the opposite orientation of 275 is 95
         (EXAMPLE) the opposite orientation of 43.67 is 223.67
       - orientation 0 is upwards
       - orientation 90 is to the right
       - orientation 180 is downwards
       - orientation 270 is to the left
       - orientation between 0.0 and 90.0 is in quadrant 1
       - orientation between 90.0 and 180.0 is in quadrant 2
       - orientation between 180.0 and 270.0 is in quadrant 3
       - orientation between 270.0 and 360.0 is in quadrant 4
       - orientation equal to 90.0 is 'Right-Aligned'
       - orientation equal to 180.0 is 'Bottom-Aligned'
       - orientation equal to 270.0 is 'Left-Aligned'
       - orientation equal to 360.0 is 'Top-Aligned' */

    ///LINES

    //lines are abstract objects; they are infinitely thin, i.e. they do not have thickness

    /* - there are 5 possible line relations:
         - two lines are parallel to each other
         - two lines intersect
         - two lines touch; touching is not an intersection; this is mathematical definition only; in reality
           an endpoint of a line will be (or not be) on a line depending on the precision of the calculations, so atleast for now
           touching MAY BE an intersection
         - two lines form a path (they have a common point); in this case there is touching as well
         - two lines are aligned - if one of the lines extend to infinity it will contain the other

         - if two lines are aligned then they do not intersect
         - if two lines are aligned then:
           (1) one of the lines can fully contain the other line
           (2) one of the lines can partially contain the other line
           (3) the lines may not share points
         - two aligned lines that share points are called 'unified' lines, respectively two aligned lines that do not share points are
           called 'non-unified' lines; two lines that form a path are not unified
         - two lines that forms a path also touch each other */

    ///

    enum class Quadrant : unsigned char
    {
        QUADRANT_1,
        QUADRANT_2,
        QUADRANT_3,
        QUADRANT_4,
        LEFT_ALIGNED,
        RIGHT_ALIGNED,
        TOP_ALIGNED,
        BOTTOM_ALIGNED
    };

    struct Bitex
    {
        double X;
        double Y;

        Bitex() = default;

        Bitex(double _x, double _y)
        {
            X = _x;
            Y = _y;
        }

        bool operator==(const Bitex& _bitex) const
        {
            return X == _bitex.X && Y == _bitex.Y;
        }

        bool operator!=(const Bitex& _bitex) const
        {
            return X != _bitex.X || Y != _bitex.Y;
        }
    };

    struct Tritex
    {
        double X;
        double Y;
        double Z;

        Tritex() = default;

        Tritex(double _x, double _y, double _z)
        {
            X = _x;
            Y = _y;
            Z = _z;
        }

        bool operator==(const Tritex& _tritex) const
        {
            return X == _tritex.X && Y == _tritex.Y && Z == _tritex.Z;
        }

        bool operator!=(const Tritex& _tritex) const
        {
            return X != _tritex.X || Y != _tritex.Y || Z != _tritex.Z;
        }
    };

    struct Vector2D
    {
        double X;
        double Y;
        double Magnitude;
        double Orientation;

        Vector2D() = default;

        Vector2D(double _x, double _y, double _magnitude, double _orientation)
        {
            X = _x;
            Y = _y;
            Magnitude = _magnitude;
            Orientation = _orientation;
        }

        bool operator==(const Vector2D& _vector) const
        {
            return X == _vector.X && Y == _vector.Y && Magnitude == _vector.Magnitude && Orientation == _vector.Orientation;
        }

        bool operator!=(const Vector2D& _vector) const
        {
            return X != _vector.X || Y != _vector.Y || Magnitude != _vector.Magnitude || Orientation != _vector.Orientation;
        }
    };

    struct Vector3D
    {
        double X;
        double Y;
        double Z;
        double Magnitude;

        Vector3D() = default;

        Vector3D(double _x, double _y, double _z, double _magnitude)
        {
            X = _x;
            Y = _y;
            Z = _z;
            Magnitude = _magnitude;
        }

        bool operator==(const Vector3D& _vector) const
        {
            return X == _vector.X && Y == _vector.Y && Z == _vector.Z && Magnitude == _vector.Magnitude;
        }

        bool operator!=(const Vector3D& _vector) const
        {
            return X != _vector.X || Y != _vector.Y || Z != _vector.Z || Magnitude != _vector.Magnitude;
        }
    };

    const double PI = 3.141592653589793;

    double FloatingPointPrecision = 0.0001; /* two floating-point values will be considered equal if the difference between them is
       less or equal than this value */

    //(PRIVATE)
    bool AreEqual(double _a, double _b, double _precision = FloatingPointPrecision)
    {
         double smaller = _a < _b ? _a : _b;
         double larger = _a > _b ? _a : _b;
         return (larger - smaller) <= _precision;
    }

    double DegreesToRadians(double _degrees)
    {
        if (_degrees < 0.0)
        {
            return 0.0;
        }
        else
        {
            return  (PI * _degrees) / 180.0;
        }
    }

    double RadiansToDegrees(double _radians)
    {
        if (_radians < 0.0)
        {
            return 0.0;
        }
        else
        {
            return (180.0 * _radians) / PI;
        }
    }

    //RadialOF(7) => 7
    //RadialOf(450) => 90
    //RadialOf(458) => 98
    //RadialOf(723) => 3
    //RadialOf(894) => 174
    //_orientation < 0 => -1
    double RadialOf(double _orientation)
    {
        if (_orientation < 0.0)
        {
            return -1;
        }
        else
        {
            return numeric::Mod(numeric::Absolute(_orientation), 360.0);
        }
    }

    //(215, 92) => 307
    //(340, 105) => 85
    //(240, 820) => 340
    //_orientation < 0 || _value < 0 => -1
    //_orientation > 0 & _value > 0 ->
    double OrientationPlus(double _orientation, double _value)
    {
        if (_orientation < 0 || _value < 0)
        {
            return -1;
        }
        else
        {
            return RadialOf(_orientation + _value);
        }
    }

    //(307, 92) => 215
    //(85, 105) => 340
    //(340, 820) => 240
    //_orientation < 0 || _value < 0 => -1
    //_orientation > 0 & _value > 0 ->
    double OrientationMinus(double _orientation, double _value)
    {
        if (_orientation < 0 || _value < 0)
        {
            return -1;
        }

        double orientation = RadialOf(_orientation) - RadialOf(_value);

        if (orientation >= 0)
        {
            return orientation;
        }
        else
        {
            return 360.0 - RadialOf(numeric::Absolute(orientation));
        }
    }

    //the coordinates are specified in Top-Left coordinate system
    //originX == pointX && originY == pointY => 0
    //originX != pointX || originY != pointY => 0..360
    double OrientationOf(double originX, double originY, double pointX, double pointY)
    {
        if (AreEqual(originX, pointX) && AreEqual(originY, pointY))
        {
            return 0.0;
        }
        ///специални случаи - 0, 90, 180 и 270 градуса
        else if (AreEqual(originX, pointX) && originY > pointY)
        {
            return 0.0;
        }
        else if (AreEqual(originY, pointY) && originX < pointX)
        {
            return 90.0;
        }
        else if (AreEqual(originX, pointX) && originY < pointY)
        {
            return 180.0;
        }
        else if (AreEqual(originY, pointY) && originX > pointX)
        {
            return 270.0;
        }
        //if _point is in first quadrant in the local coordinate system with origin the point _origin
        else if (originX < pointX && originY > pointY)
        {
            double opposite = originY - pointY;
            double adjacent = pointX - originX;
            return 90.0 - geometry::RadiansToDegrees(atan(opposite / adjacent));
        }
        //if _point is in second quadrant in the local coordinate system with origin the point _origin
        else if (originX < pointX && originY < pointY)
        {
            double opposite = pointY - originY;
            double adjacent = pointX - originX;
            return 90.0 + geometry::RadiansToDegrees(atan(opposite / adjacent));
        }
        //if _point is in third quadrant in the local coordinate system with origin the point _origin
        else if (originX > pointX && originY < pointY)
        {
            double opposite = originX - pointX;
            double adjacent = pointY - originY;
            return 180.0 + geometry::RadiansToDegrees(atan(opposite / adjacent));
        }
        //if _point is in fourth quadrant in the local coordinate system with origin the point _origin
        else if (originX > pointX && originY > pointY)
        {
            double opposite = originX - pointX;
            double adjacent = originY - pointY;
            return 270.0 + (90.0 - geometry::RadiansToDegrees(atan(opposite / adjacent)));
        }
    }

    //the coordinates are specified in Top-Left coordinate system
    //_origin == _point => 0
    //_origin != _point => 0..360
    double OrientationOf(const Bitex& _origin, const Bitex& _point)
    {
        return OrientationOf(_origin.X, _origin.Y, _point.X, _point.Y);
    }

    double DistanceOf(double x1, double y1, double x2, double y2)
    {
        if (AreEqual(x1, x2) && AreEqual(y1, y2)) return 0.0;

        using namespace numeric;

        //if Xv is aligned with Xr
        if (AreEqual(y1, y2))
        {
            return LargerOf(x1, x2) - SmallerOf(x1, x2);
        }
        //if Yv is aligned with Yr
        else if (AreEqual(x1, x2))
        {
            return LargerOf(y1, y2) - SmallerOf(y1, y2);
        }
        else
        {
            //(STATE) _b1 and _b2 are vertices of the hypotenuse of a right triangle

            double side1 = LargerOf(x1, x2) - SmallerOf(x1, x2);
            double side2 = LargerOf(y1, y2) - SmallerOf(y1, y2);

            //the length of the hypotenuse is found by using the Pythagorean theorem
            return sqrt((side1 * side1) + (side2 * side2));
        }
    }

    double DistanceOf(const Bitex& b1, const Bitex& b2)
    {
        return DistanceOf(b1.X, b1.Y, b2.X, b2.Y);
    }

    double DistanceOf(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)) + ((z2 - z1) * (z2 - z1)));
    }

    double DistanceOf(Tritex t1, Tritex t2)
    {
        return sqrt(((t2.X - t1.X) * (t2.X - t1.X)) + ((t2.Y - t1.Y) * (t2.Y - t1.Y)) + ((t2.Z - t1.Z) * (t2.Z - t1.Z)));
    }

    Bitex CentexOf(double x1, double y1, double x2, double y2)
    {
        double smallerX = numeric::SmallerOf(x1, x2);
        double smallerY = numeric::SmallerOf(y1, y2);
        double largerX = numeric::LargerOf(x1, x2);
        double largerY = numeric::LargerOf(y1, y2);
        double width = largerX - smallerX;
        double height = largerY - smallerY;
        return Bitex(smallerX + (width / 2.0), smallerY + (height / 2.0));
    }

    Bitex CentexOf(const Bitex& p1, const Bitex& p2)
    {
        double smallerX = numeric::SmallerOf(p1.X, p2.X);
        double smallerY = numeric::SmallerOf(p1.Y, p2.Y);
        double largerX = numeric::LargerOf(p1.X, p2.X);
        double largerY = numeric::LargerOf(p1.Y, p2.Y);
        double width = largerX - smallerX;
        double height = largerY - smallerY;
        return Bitex(smallerX + (width / 2.0), smallerY + (height / 2.0));
    }

    //this function uses Top-Left coordinate system
    //_origin == _point => 0
    //_origin != _point => 0..360
    Bitex TermexOf(double _originX, double _originY, double _orientation, double _magnitude)
    {
        if (_orientation < 0) return { -1, -1 };

        _orientation = geometry::RadialOf(_orientation);

        if (AreEqual(_orientation, 0.0) || AreEqual(_orientation, 360.0))
        {
            return Bitex(_originX, _originY - _magnitude);
        }
        else if (AreEqual(_orientation, 90.0))
        {
            return Bitex(_originX + _magnitude, _originY);
        }
        else if (AreEqual(_orientation, 180.0))
        {
            return Bitex(_originX, _originY + _magnitude);
        }
        else if (AreEqual(_orientation, 270.0))
        {
            return Bitex(_originX - _magnitude, _originY);
        }

        /* the hypotenuse and two angles of the triangle are known; we need to find the adjacent and opposite sides (which describe
           the X и Y positions of the termex) */

        double hypotenuse = _magnitude;

        if (_orientation < 90.0)
        {
            //cos(_bivector.Orientation) = adjacent / hypotenuse ->
            double adjacent = cos(DegreesToRadians(_orientation)) * hypotenuse;

            //sin(_bivector.Orientation) = opposite / hypotenuse ->
            double opposite = sin(DegreesToRadians(_orientation)) * hypotenuse;

            return Bitex(_originX + opposite, _originY - adjacent);
        }
        else if (_orientation > 90.0 && _orientation < 180.0)
        {
            //cos(_bivector.Orientation - 90.0) = adjacent / hypotenuse ->
            double adjacent = cos(DegreesToRadians(_orientation - 90.0)) * hypotenuse;

            //sin(_bivector.Orientation - 90.0) = opposite / hypotenuse ->
            double opposite = sin(DegreesToRadians(_orientation - 90.0)) * hypotenuse;

            return Bitex(_originX + adjacent, _originY + opposite);
        }
        else if (_orientation > 180.0 && _orientation < 270.0)
        {
            //cos(_bivector.Orientation - 180.0) = adjacent / hypotenuse ->
            double adjacent = cos(DegreesToRadians(_orientation - 180.0)) * hypotenuse;

            //sin(_bivector.Orientation - 180.0) = opposite / hypotenuse ->
            double opposite = sin(DegreesToRadians(_orientation - 180.0)) * hypotenuse;

            return Bitex(_originX - opposite, _originY + adjacent);
        }
        else if (_orientation > 270.0 && _orientation < 360.0)
        {
            //cos(_bivector.Orientation - 270.0) = adjacent / hypotenuse ->
            double adjacent = cos(DegreesToRadians(_orientation - 270.0)) * hypotenuse;

            //sin(_bivector.Orientation - 270.0) = opposite / hypotenuse ->
            double opposite = sin(DegreesToRadians(_orientation - 270.0)) * hypotenuse;

            return Bitex(_originX - adjacent, _originY - opposite);
        }
    }

    //this function uses Top-Left coordinate system
    //_origin == _point => 0
    //_origin != _point => 0..360
    Bitex TermexOf(const Bitex& _bitex, double _orientation, double _magnitude)
    {
         return TermexOf(_bitex.X, _bitex.Y, _orientation, _magnitude);
    }

    //(0.0 | 360.0) => TOP_ALIGNED
    //(90.0) => RIGHT_ALIGNED
    //(180.0) => BOTTOM_ALIGNED
    //(270.0) => LEFT_ALIGNED
    //(2.3) => QUADRANT_1
    //(92.0) => QUADRANT_2
    //(186.42) => QUADRANT_3
    //(312.5) => QUADRANT_4
    Quadrant QuadrantOf(double _orientation)
    {
        if (_orientation >= 0.0 && _orientation <= 90.0)
        {
            return Quadrant::QUADRANT_1;
        }
        else if (_orientation >= 90.0 && _orientation <= 180.0)
        {
            return Quadrant::QUADRANT_2;
        }
        else if (_orientation >= 180.0 && _orientation <= 270.0)
        {
            return Quadrant::QUADRANT_3;
        }
        else if (_orientation >= 270.0 && _orientation <= 360.0)
        {
            return Quadrant::QUADRANT_4;
        }
        else if (AreEqual(_orientation, 0.0) || AreEqual(_orientation, 360.0))
        {
            return Quadrant::TOP_ALIGNED;
        }
        else if (AreEqual(_orientation, 90.0))
        {
            return Quadrant::RIGHT_ALIGNED;
        }
        else if (AreEqual(_orientation, 180.0))
        {
            return Quadrant::BOTTOM_ALIGNED;
        }
        else if (AreEqual(_orientation, 270.0))
        {
            return Quadrant::LEFT_ALIGNED;
        }
    }

    //(120, 120) => 0
    //(60, 140) => 80
    //(140, 60) => 280
    //(110, 305) => 195
    //(290, 50) => 120
    //(290, 307) => 17
    //(290, 200) => 270
    double ClockwiseOffset(double _orientation1, double _orientation2)
    {
        Quadrant r1Quadrant = QuadrantOf(_orientation1);
        Quadrant r2Quadrant = QuadrantOf(_orientation2);
        bool r1InLeftRegion = r1Quadrant == Quadrant::QUADRANT_3 || r1Quadrant == Quadrant::QUADRANT_4 || r1Quadrant == Quadrant::LEFT_ALIGNED;
        bool r2InLeftRegion = r2Quadrant == Quadrant::QUADRANT_3 || r2Quadrant == Quadrant::QUADRANT_4 || r2Quadrant == Quadrant::LEFT_ALIGNED;

        if (AreEqual(_orientation1, _orientation2))
        {
            return 0.0;
        }
        else if (!r1InLeftRegion && !r2InLeftRegion && _orientation1 < _orientation2)
        {
            return _orientation2 - _orientation1;
        }
        else if (!r1InLeftRegion && !r2InLeftRegion && _orientation1 > _orientation2)
        {
            return 360.0 - (_orientation1 - _orientation2);
        }
        else if (!r1InLeftRegion && r2InLeftRegion)
        {
            return _orientation2 - _orientation1;
        }
        else if (r1InLeftRegion && !r2InLeftRegion)
        {
            return (360.0 - _orientation1) + _orientation2;
        }
        else if (r1InLeftRegion && r2InLeftRegion && _orientation1 < _orientation2)
        {
            return _orientation2 - _orientation1;
        }
        else if (r1InLeftRegion && r2InLeftRegion && _orientation1 > _orientation2)
        {
            return 360.0 - (_orientation1 - _orientation2);
        }
    }

    //(10, 105, 53) => true
    //(300, 58, 6) => true
    //(307, 321, 310) => true
    //(321, 307, 310) => false
    //_aor1 >= 0, _aor2 >= 0 ->
    bool AngleContains(double _aor1, double _aor2, double _orientation)
    {
        if (_aor1 < 0.0 || _aor2 < 0.0 || _orientation < 0.0) return false;

        _aor1 = RadialOf(_aor1);
        _aor2 = RadialOf(_aor2);
        _orientation = RadialOf(_orientation);

        double aor1_aor2_offset = ClockwiseOffset(_aor1, _aor2);
        double or_aor2_offset = ClockwiseOffset(_orientation, _aor2);

        return or_aor2_offset <= aor1_aor2_offset;
    }

    t2<double, double> OrientationsOf(double _angleOrientation, double _angleMagnitude)
    {
        return { OrientationMinus(_angleOrientation, _angleMagnitude / 2), OrientationPlus(_angleOrientation, _angleMagnitude / 2) };
    }

    //(MUTATE _coordinates)
    //this function uses Top-Left coordinate system
    //&_value is specified in degrees
    void Rotate(list<double>& _coordinates, double _originX, double _originY, short _value)
    {
        using geometry::OrientationPlus;
        using geometry::OrientationMinus;
        using geometry::DistanceOf;

        for (int i = 0; i < _coordinates.count(); i += 2)
        {
            double newOrientation;

            if (_value > 0.0)
            {
                newOrientation = OrientationPlus(OrientationOf(_originX, _originY, _coordinates[i], _coordinates[i + 1]), _value);
            }
            else if (_value < 0.0)
            {
                newOrientation = OrientationMinus(OrientationOf(_originX, _originY, _coordinates[i], _coordinates[i + 1]), numeric::Absolute(_value));
            }

            Bitex newPosition = geometry::TermexOf(_originX, _originY, newOrientation, DistanceOf(_originX, _originY, _coordinates[i], _coordinates[i + 1]));

            _coordinates[i] = newPosition.X;
            _coordinates[i + 1] = newPosition.Y;

            _coordinates[i] = (_coordinates[i] * cos(_value)) - (_coordinates[i + 1] * sin(_value));
            _coordinates[i + 1] = (_coordinates[i] * sin(_value)) - (_coordinates[i + 1] * cos(_value));
        }
    }

    struct Line
    {
        Bitex P1;
        Bitex P2;

        Line() = default;

        Line(double x1, double y1, double x2, double y2)
        {
            P1.X = x1;
            P1.Y = y1;
            P2.X = x2;
            P2.Y = y2;
        }

        Line(const Bitex& _p1, const Bitex& _p2)
        {
            P1 = _p1;
            P2 = _p2;
        }

        //(A, B) == (B, C) => false
        //(A, B) == (B, A) => true
        //(A, B) == (A, B) => true
        bool operator==(const Line& _line) const
        {
            if (P1 != _line.P1 && P1 != _line.P2) return false;
            if (P1 == _line.P2 && P2 == _line.P1) return true;
            if (P1 == _line.P1 && P2 == _line.P2) return true;
        }

        //(A, B) != (B, C) => true
        //(A, B) != (B, A) => false
        //(A, B) != (A, B) => false
        bool operator!=(const Line& _line) const
        {
            if (P1 != _line.P1 && P1 != _line.P2) return true;
            if (P1 == _line.P2 && P2 == _line.P1) return false;
            if (P1 == _line.P1 && P2 == _line.P2) return false;
        }

        //&this and _line are valid lines ->
        bool IsParallelTo(const Line& _line) const
        {
            Line l1 = *this;
            Line l2 = _line;

            if (l1 == l2) return true;
            if ((l1.P1 == l1.P2) || (l2.P1 == l2.P2)) return false;

            double l1_orientation = OrientationOf(l1.P1, l1.P2);
            double l2_orientation = OrientationOf(l2.P1, l2.P2);

            return AreEqual(ClockwiseOffset(l1_orientation, l2_orientation), 180.0);
        }

        //&this and _line are valid lines ->
        bool AlignWith(const Line& _line) const
        {
            Line l1 = *this;
            Line l2 = _line;

            if (l1 == l2) return true;
            if (l1.P1 == l1.P2 || l2.P1 == l2.P2) return false;

            double l1_orientation = OrientationOf(l1.P1, l1.P2);
            double l2_orientation = OrientationOf(l2.P1, l2.P2);
            double lineOffset = ClockwiseOffset(l1_orientation, l2_orientation);

            if (lineOffset != 0.0 && lineOffset != 180.0 && lineOffset != 360.0) return false;

            //(STATE) the two lines have common orientation

            //determine the centexes of the two lines
            const Bitex& l1Centex = l1.Centex();
            const Bitex& l2Centex = l2.Centex();

            if (l1Centex == l2Centex) return true;

            double centexOrientation = OrientationOf(l1Centex, l2Centex);
            double offset = ClockwiseOffset(centexOrientation, l1_orientation);

            return AreEqual(offset, 0.0) || AreEqual(offset, 180.0) || AreEqual(offset, 360.0);
        }

        //&this and _line are valid lines ->
        bool IsUnifiedWith(const Line& _line) const
        {
            Line l1 = *this;
            Line l2 = _line;

            if (l1 == l2) return true;

            if (PathWith(_line)) return false;

            if (!IsParallelTo(l2)) return false;

            double l1_half_length = l1.Length() / 2.0;
            double l2_half_length = l2.Length() / 2.0;

            return DistanceOf(l1.Centex(), l2.Centex()) < (l1_half_length + l2_half_length);
        }

        //returns true if the two lines have a common point
        bool PathWith(const Line& _line) const
        {
            Line l1 = *this;
            Line l2 = _line;

            if (l1 == l2) return false;

            return l1.P1 == l2.P1 || l1.P1 == l2.P2 || l1.P2 == l2.P1 || l1.P2 == l2.P2;
        }

        //two (equal) or (unified lines) do not intersect
        //parallel lines do not intersect
        //unified lines do not intersect
        //lines that have common vertex do not intersect
        //line touching without vertex intersection is not an intersection
        //line touching with vertex intersection is an intersection
        bool Intersect(const Line& _line) const
        {
            Line l1 = *this;
            Line l2 = _line;

            if (l1 == l2) return false;

            if (IsParallelTo(l2)) return false;

            //even if the lines are not parallel, that doesn't mean they intersect (they can only touch)

            if (PathWith(l2)) return false;

            if (IsUnifiedWith(l2)) return false;

            {   double l11_l21_orientation = OrientationOf(l1.P1, l2.P1);
                double l11_l22_orientation = OrientationOf(l1.P1, l2.P2);
                double l11_l12_orientation = OrientationOf(l1.P1, l1.P2);

                double angleMagnitude1 = ClockwiseOffset(l11_l21_orientation, l11_l22_orientation);
                double angleMagnitude2 = ClockwiseOffset(l11_l22_orientation, l11_l21_orientation);
                double aor1 = angleMagnitude1 < angleMagnitude2 ? l11_l21_orientation : l11_l22_orientation;
                double aor2 = angleMagnitude1 < angleMagnitude2 ? l11_l22_orientation : l11_l21_orientation;

                if (!AngleContains(aor1, aor2, l11_l12_orientation)) return false; }

            {   double l12_l21_orientation = OrientationOf(l1.P2, l2.P1);
                double l12_l22_orientation = OrientationOf(l1.P2, l2.P2);
                double l12_l11_orientation = OrientationOf(l1.P2, l1.P1);

                double angleMagnitude1 = ClockwiseOffset(l12_l21_orientation, l12_l22_orientation);
                double angleMagnitude2 = ClockwiseOffset(l12_l22_orientation, l12_l21_orientation);
                double aor1 = angleMagnitude1 < angleMagnitude2 ? l12_l21_orientation : l12_l22_orientation;
                double aor2 = angleMagnitude1 < angleMagnitude2 ? l12_l22_orientation : l12_l21_orientation;

                if (!AngleContains(aor1, aor2, l12_l11_orientation)) return false; }

            return true;
        }

        //&this and _line are aligned ->
        bool Contains(const Line& _line) const
        {
            double length = Length();

            if (length < _line.Length()) return false;

            Bitex centex = _line.Centex();
            double distance1 = DistanceOf(centex, P1);
            double distance2 = DistanceOf(centex, P2);

            return AreEqual(distance1 + distance2, length);
        }

        Bitex Centex() const
        {
            double smallerX = numeric::SmallerOf(P1.X, P2.X);
            double smallerY = numeric::SmallerOf(P1.Y, P2.Y);
            double largerX = numeric::LargerOf(P1.X, P2.X);
            double largerY = numeric::LargerOf(P1.Y, P2.Y);
            double width = largerX - smallerX;
            double height = largerY - smallerY;
            return Bitex(smallerX + (width / 2.0), smallerY + (height / 2.0));
        }

        double Length() const
        {
            return DistanceOf(P1, P2);
        }
    };

    //vertex coordinates describes a closed polygon ->
    list<Line> FormatorsOf(const list<double>& _coordinates)
    {
        list<Line> result;

        for (int i = 0; i < _coordinates.count() - 3; i += 2)
        {
            result.Append(Line(Bitex(_coordinates[i], _coordinates[i + 1]), Bitex(_coordinates[i + 2], _coordinates[i + 3])));
        }

        return result.Append(Line(
                Bitex(_coordinates[_coordinates.count() - 2], _coordinates[_coordinates.count() - 1]),
                Bitex(_coordinates[0], _coordinates[1])));
    }

    //vertices describe a closed polygon ->
    list<Line> SidesOf(const list<Bitex>& _vertices)
    {
        list<Line> sides;
        list<Bitex> vertices = _vertices;

        vertices.TraversalMode = TraversalMode::CIRCULAR;

        for (int i = 0; i < _vertices.count(); i++)
        {
            Bitex& b1 = vertices.current();
            Bitex& b2 = vertices.next();
            sides.Append(Line(b1, b2));
        }

        return sides;
    }

    bool CollinearityOf(const list<Bitex>& _points)
    {
        double orientation = OrientationOf(_points[0], _points[1]);

        for (int i = 0; i < _points.count() - 1; i++)
        {
            double orientation_ = OrientationOf(_points[i], _points[i + 1]);
            double clockwiseOffset = ClockwiseOffset(orientation, orientation_);

            /* ClockwiseOffset() is used because of the following case:
               _points = (20, 30) (20, 40) (20, 35) (20, 50) */
            if (clockwiseOffset != 0.0 && clockwiseOffset != 180.0 && clockwiseOffset != 360.0)
            {
                return false;
            }

            orientation = orientation_;
        }

        return true;
    }

    //fewer than 3 points => -1
    //there are some equal points => -2
    //the points are collinear => -3
    char IsPolygon(const list<Bitex>& _points)
    {
        if (_points.count() < 3) return -1;

        //check if there are equal points

        for (const Bitex& __point : _points)
        {
            for (Bitex& __point_ : _points)
            {
                if (&__point != &__point_ && __point == __point_)
                {
                    return -2;
                }
            }
        }

        //check if the points are collinear

        if (CollinearityOf(_points)) return -3;

        return 0;
    }

    //fewer than 3 points => -1
    //there are some equal points => -2
    //the points are collinear => -3
    //the shape contain unified lines => -4
    //the polygon is not simple => -5
    char IsSimplePolygon(const list<Bitex>& _points)
    {
        char result = IsPolygon(_points);

        if (result != 0) return result;

        //check if there are intersecting lines or unified lines

        list<Line> sides = SidesOf(_points);

        for (const Line& __side : sides)
        {
            for (const Line& __side_ : sides)
            {
                if (&__side == &__side_)
                {
                    continue;
                }
                else if (__side.IsUnifiedWith(__side_))
                {
                    return -4;
                }
                else if (__side.Intersect(__side_))
                {
                    __side.Intersect(__side_);
                    return -5;
                }
            }
        }

        return 0;
    }

    //fewer than 3 points => -1
    //there are some equal points => -2
    //the points are collinear => -3
    //the shape contain unified lines  => -4
    //the polygon is not simple => -5
    //the polygon is convex => 0
    //the polygon is concave => 1
    //the points form a simple polygon ->
    char IsConvexPolygon(const list<Bitex>& _points)
    {
        list<Bitex> points = _points;

        char result = IsSimplePolygon(_points);

        if (result != 0) return result;

        //if the polygon is a triangle
        if (_points.count() == 3) return 0;

        double ANGLE_SUM = (_points.count() - 2) * 180.0;
        double actualAngleSum = 0.0;

        points.TraversalMode = TraversalMode::CIRCULAR;

        for (int i = 0; i < _points.count(); i++)
        {
            Bitex& b1 = points.current();
            Bitex& b2 = points.next();
            Bitex& b3 = points.next();

            points.back(1);

            double orientation1 = OrientationOf(b1, b2);
            double orientation2 = OrientationOf(b2, b3);
            double clockwiseOffset = ClockwiseOffset(orientation1, orientation2);

            if (clockwiseOffset < 180.0)
            {
                actualAngleSum += clockwiseOffset;
            }
            else
            {
                actualAngleSum += 360.0 - clockwiseOffset;
            }
        }

        return AreEqual(ANGLE_SUM, actualAngleSum) ? 0 : 1;
    }

    //fewer than 3 points => -1
    //there are some equal points => -2
    //the points are collinear => -3
    //the shape contain unified lines  => -4
    //the polygon is not simple => -5
    //the polygon is convex => 1
    //the points form a simple polygon ->
    char IsConcavePolygon(const list<Bitex>& _points)
    {
        list<Bitex> points = _points;

        char result = IsSimplePolygon(_points);

        if (result != 0) return result;

        //if the polygon is a triangle
        if (_points.count() == 3) return 1;

        double ANGLE_SUM = (_points.count() - 2) * 180.0;
        double actualAngleSum = 0.0;

        points.TraversalMode = TraversalMode::CIRCULAR;

        for (int i = 0; i < _points.count(); i++)
        {
            Bitex& b1 = points.current();
            Bitex& b2 = points.next();
            Bitex& b3 = points.next();

            points.back(1);

            double orientation1 = OrientationOf(b1, b2);
            double orientation2 = OrientationOf(b2, b3);
            double clockwiseOffset = ClockwiseOffset(orientation1, orientation2);

            if (clockwiseOffset < 180.0)
            {
                actualAngleSum += clockwiseOffset;
            }
            else
            {
                actualAngleSum += 360.0 - clockwiseOffset;
            }
        }

        return !AreEqual(ANGLE_SUM, actualAngleSum) ? 0 : 1;
    }

    //the vertices must form simple convex or simple concave polygon
    struct Polygon
    {
    public:

        list<Bitex> Vertices;

    private:


        bool ConvexContains(const Bitex& _point) const
        {
            //for each line (_point <-> vertex) check if intersects side of the polygon

            list<Line> sides = SidesOf(Vertices);

            for (const Bitex& __vertex : Vertices)
            {
                Line line(_point, __vertex);

                for (const Line& __side : sides)
                {
                    if (line.Intersect(__side))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

    public:

        Polygon() = default;

        Polygon(const list<Bitex>& _vertices) : Vertices(_vertices) {}

        Polygon(const Polygon&) = default;

        Polygon& operator=(const Polygon&) = default;

        //[(20, 7) (9, 15) (30, 14) (16, 3)] == [(30, 14) (16, 3) (20, 7) (9, 15)] => true
        //[(20, 7) (9, 15) (30, 14) (16, 3)] == [(30, 14) (20, 7) (9, 15) (16, 3)] => false
        //[(20, 7) (9, 15) (30, 14)] == [(20, 7) (7, 15) (30, 14)] => false
        bool operator==(const Polygon& _polygon) const
        {
            if (Vertices.count() != _polygon.Vertices.count()) return false;

            list<Bitex> vertices = _polygon.Vertices;
            vertices.TraversalMode = TraversalMode::CIRCULAR;

            int correspondingIndex = _polygon.Vertices.IndexOf(Vertices[0]);

            if (correspondingIndex == -1) return false;

            vertices.set_position(correspondingIndex);

            for (int i = 0; i < Vertices.count(); i++)
            {
                if (Vertices[i] != vertices.current())
                {
                    return false;
                }

                vertices.advance(1);
            }

            return true;
        }

        //[(20, 7) (9, 15) (30, 14) (16, 3)] == [(30, 14) (16, 3) (20, 7) (9, 15)] => true
        //[(20, 7) (9, 15) (30, 14) (16, 3)] == [(30, 14) (20, 7) (9, 15) (16, 3)] => false
        //[(20, 7) (9, 15) (30, 14)] == [(20, 7) (7, 15) (30, 14)] => false
        bool operator!=(const Polygon& _polygon) const
        {
            if (Vertices.count() != _polygon.Vertices.count()) return true;

            list<Bitex> vertices = _polygon.Vertices;
            vertices.TraversalMode = TraversalMode::CIRCULAR;

            int correspondingIndex = _polygon.Vertices.IndexOf(Vertices[0]);

            if (correspondingIndex == -1) return true;

            vertices.set_position(correspondingIndex);

            for (int i = 0; i < Vertices.count(); i++)
            {
                if (Vertices[i] != vertices.current())
                {
                    return true;
                }

                vertices.advance(1);
            }

            return false;
        }
    };

    //&a and &b have common point and are not equal ->
    Bitex CommonPointOf(const Line& a, const Line& b)
    {
        if (a.P1 == b.P1)
        {
            return a.P1;
        }
        else if (a.P1 == b.P2)
        {
            return a.P1;
        }
        else if (a.P2 == b.P1)
        {
            return a.P2;
        }
        else if (a.P2 == b.P2)
        {
            return a.P2;
        }
    }

    //&a and &b have common point and are not equal ->
    t2<Bitex, Bitex> NonCommonPointsOf(const Line& a, const Line& b)
    {
        if (a.P1 == b.P1)
        {
            return { a.P2, b.P2 };
        }
        else if (a.P1 == b.P2)
        {
            return { a.P2, b.P1 };
        }
        else if (a.P2 == b.P1)
        {
            return { a.P1, b.P2 };
        }
        else if (a.P2 == b.P2)
        {
            return { a.P1, b.P1 };
        }
    }
}
