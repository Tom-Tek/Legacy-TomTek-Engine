using System.Numerics;

namespace TomTekEngine
{
    
    public class Vector2
    {

        public float x, y;

        /// <summary>
        /// Commonly used vectors when dealing with linear
        /// algebra opperations
        /// </summary>
        public static Vector2 k_Zero = new Vector2(0.0f, 0.0f);
        public static Vector2 k_One = new Vector2(1.0f, 1.0f);
        public static Vector2 k_Right = new Vector2(1.0f, 0.0f);
        public static Vector2 k_Up = new Vector2(0.0f, 1.0f);

        /// <summary>
        /// Handle construction when no X, or Y axis is passed
        /// </summary>
        public Vector2()
        {
            this.x = 0.0f;
            this.y = 0.0f;
        }

        /// <summary>
        /// Constructed using a set X and Y axis
        /// </summary>
        /// <param name="x">X axis to begin with</param>
        /// <param name="y">Y axis to begin with</param>
        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;

        }

        /// <summary>
        /// All vector algebra will be stored in the
        /// region below
        /// </summary>
    #region OPERATIONS
        public static Vector2 operator+(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x + b.x, a.y + b.y);
        }

        public static Vector2 operator-(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x - b.x, a.y - b.y);
        }

        public static Vector2 operator-(Vector2 a)
        {
            return new Vector2(-a.x, -a.y);
        }

        public static Vector2 operator*(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x * b.x, a.y * b.y);
        }

        public static Vector2 operator*(Vector2 a, float scale)
        {
            return new Vector2(a.x * scale, a.y * scale);
        }

        public static Vector2 operator *(float scale, Vector2 a)
        {
            return new Vector2(a.x * scale, a.y * scale);
        }

        public static Vector2 operator/(Vector2 a, Vector2 b)
        {
            return new Vector2(a.x / b.x, a.y / b.y);
        }

        public static Vector2 operator /(Vector2 a, float scale)
        {
            return new Vector2(a.x / scale, a.y / scale);
        }
    #endregion //OPERATIONS

        /// <summary>
        /// Gets the size of the Vector.
        /// </summary>
        /// <returns>Returns the size of the vector</returns>
        public float Magnitude()
        {
            return MathF.Sqrt(x * x + y * y);
        }

        /// <summary>
        /// Normalizes this vector to have it's magnitude
        /// become one.
        /// Normalize will fail if this == k_Zero
        /// </summary>
        /// <returns></returns>
        public Vector2 Normalize()
        {
            float m = Magnitude();
            if (m == 0.0f)
                return k_Zero;
            return this / m;
        }

        /// <summary>
        /// Returns a new vector from the sign (-1, 0, or 1) of the original's components.
        /// </summary>
        /// <returns></returns>
        public Vector2 Sign()
        {
            return new Vector2(MathF.Sign(x), MathF.Sign(y));
        }
        
        /// <summary>
        /// Returns a new vector from the absolute values of the original's components.
        /// </summary>
        /// <returns></returns>
        public Vector2 Abs()
        {
            return new Vector2(MathF.Abs(x), MathF.Abs(y));
        }

        /// <summary>
        /// Returns a scalar dot product of the two vectors.
        /// </summary>
        /// <param name="a"></param>
        /// <returns></returns>
        public float Dot(Vector2 a)
        {
            return (x * a.x + y * a.y);
        }

    }

    public class Vector3
    {

        public float x, y, z;

        /// <summary>
        /// Commonly used vectors when dealing with linear
        /// algebra opperations
        /// </summary>
        public static Vector3 k_Zero = new Vector3(0.0f, 0.0f, 0.0f);
        public static Vector3 k_One = new Vector3(1.0f, 1.0f, 1.0f);
        public static Vector3 k_Right = new Vector3(1.0f, 0.0f, 0.0f);
        public static Vector3 k_Up = new Vector3(0.0f, 1.0f, 0.0f);
        public static Vector3 k_Forward = new Vector3(0.0f, 0.0f, 1.0f);

        /// <summary>
        /// Handle construction when no X, Y, or Z axis is passed
        /// </summary>
        public Vector3()
        {
            this.x = 0.0f;
            this.y = 0.0f;
            this.z = 0.0f;
        }

        /// <summary>
        /// Constructed using a set X, Y and Z axis
        /// </summary>
        /// <param name="x">X axis to begin with</param>
        /// <param name="y">Y axis to begin with</param>
        /// <param name="z">Z axis to begin with</param>
        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        /// <summary>
        /// All vector algebra will be stored in the
        /// region below
        /// </summary>
    #region OPERATIONS
        public static Vector3 operator +(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        public static Vector3 operator -(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        public static Vector3 operator -(Vector3 a)
        {
            return new Vector3(-a.x, -a.y, -a.z);
        }

        public static Vector3 operator *(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        public static Vector3 operator *(Vector3 a, float scale)
        {
            return new Vector3(a.x * scale, a.y * scale, a.z * scale);
        }

        public static Vector3 operator *(float scale, Vector3 a)
        {
            return new Vector3(a.x * scale, a.y * scale, a.z * scale);
        }

        public static Vector3 operator /(Vector3 a, Vector3 b)
        {
            return new Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
        }

        public static Vector3 operator /(Vector3 a, float scale)
        {
            return new Vector3(a.x / scale, a.y / scale, a.z / scale);
        }
        #endregion //OPERATIONS

        /// <summary>
        /// Gets the size of the Vector.
        /// </summary>
        /// <returns>Returns the size of the vector</returns>
        public float Magnitude()
        {
            return MathF.Sqrt(x * x + y * y);
        }

        /// <summary>
        /// Normalizes this vector to have it's magnitude
        /// become one.
        /// Normalize will fail if this == k_Zero
        /// </summary>
        /// <returns></returns>
        public Vector3 Normalize()
        {
            float m = Magnitude();
            if (m == 0.0f)
                return k_Zero;
            return this / m;
        }

        /// <summary>
        /// Returns a new vector from the sign (-1, 0, or 1) of the original's components.
        /// </summary>
        /// <returns></returns>
        public Vector3 Sign()
        {
            return new Vector3(MathF.Sign(x), MathF.Sign(y), MathF.Sign(z));
        }

        /// <summary>
        /// Returns a new vector from the absolute values of the original's components.
        /// </summary>
        /// <returns></returns>
        public Vector3 Abs()
        {
            return new Vector3(MathF.Abs(x), MathF.Abs(y), MathF.Abs(z));
        }

        /// <summary>
        /// Returns a scalar dot product of the two vectors.
        /// </summary>
        /// <param name="a"></param>
        /// <returns></returns>
        public float Dot(Vector3 a)
        {
            return (x * a.x + y * a.y + z * a.z);
        }

    }

}
