/*
junseok.yang
assignment1
cs230
spring 2019
*/
#include <CS230/math/matrix3.hpp>
#include <CS230/math/vector2.hpp>
#include <cassert>
#include <limits>

#include <cmath>

namespace CS230
{
    matrix3::matrix3() noexcept : column0(0), column1(0), column2(0){};

    matrix3::matrix3(vector3 first_column, vector3 second_column, vector3 third_column) noexcept
        : column0(first_column), column1(second_column), column2(third_column){};

    matrix3::matrix3(float column0_row0, float column0_row1, float column0_row2, float column1_row0, float column1_row1,
                     float column1_row2, float column2_row0, float column2_row1, float column2_row2) noexcept 
		: column0(column0_row0, column0_row1, column0_row2), column1(column1_row0, column1_row1, column1_row2),
		  column2(column2_row0, column2_row1, column2_row2){};

	float matrix3::operator()(int column, int row) const noexcept
	{
		assert((column >= 0) && (column < 3));
		assert((row >= 0) && (row < 3));
		return elements[column][row];
	}

    float& matrix3::operator()(int column, int row) noexcept 
	{
		assert((column >= 0) && (column < 3));
		assert((row >= 0) && (row < 3));
		return elements[column][row];
	}

	matrix3 operator*(const matrix3& m1, const matrix3& m2) noexcept
	{
		return matrix3(
			m1(0, 0)*m2(0, 0) + m1(1, 0)*m2(0, 1) + m1(2, 0)*m2(0, 2),
			m1(0, 1)*m2(0, 0) + m1(1, 1)*m2(0, 1) + m1(2, 1)*m2(0, 2),
			m1(0, 2)*m2(0, 0) + m1(1, 2)*m2(0, 1) + m1(2, 2)*m2(0, 2),
			m1(0, 0)*m2(1, 0) + m1(1, 0)*m2(1, 1) + m1(2, 0)*m2(1, 2),
			m1(0, 1)*m2(1, 0) + m1(1, 1)*m2(1, 1) + m1(2, 1)*m2(1, 2),
			m1(0, 2)*m2(1, 0) + m1(1, 2)*m2(1, 1) + m1(2, 2)*m2(1, 2),
			m1(0, 0)*m2(2, 0) + m1(1, 0)*m2(2, 1) + m1(2, 0)*m2(2, 2),
			m1(0, 1)*m2(2, 0) + m1(1, 1)*m2(2, 1) + m1(2, 1)*m2(2, 2),
			m1(0, 2)*m2(2, 0) + m1(1, 2)*m2(2, 1) + m1(2, 2)*m2(2, 2)
		);
	}

    void operator*=(matrix3& m1, const matrix3& m2) noexcept { m1 = m1 * m2; }

	vector3 operator*(const matrix3& m, vector3 v) noexcept
	{
		vector3 multiply;
        multiply.x = m(0, 0)*v.x + m(1, 0)*v.y + m(2, 0)*v.z;
        multiply.y = m(0, 1)*v.x + m(1, 1)*v.y + m(2, 1)*v.z;
        multiply.z = m(0, 2)*v.x + m(1, 2)*v.y + m(2, 2)*v.z;
		return multiply;
	}

	matrix3 MATRIX3::transpose(const matrix3& m) noexcept
	{
        return matrix3(m(0, 0), m(1, 0), m(2, 0),
			m(0, 1), m(1, 1), m(2, 1),
			m(0, 2), m(1, 2), m(2, 2));
	}

	matrix3 MATRIX3::build_rotation(float angle_in_radians) noexcept
	{
        matrix3 rotation;
        int zero = 0;

				rotation.elements[0][0] = cos(angle_in_radians);
				rotation.elements[1][0] = -sin(angle_in_radians);
				rotation.elements[2][0] = 0;
				
				rotation.elements[0][1] = sin(angle_in_radians);
				rotation.elements[1][1] = cos(angle_in_radians);
				rotation.elements[2][1] = 0;

				rotation.elements[0][2] = 0;
				rotation.elements[1][2] = 0;
				rotation.elements[2][2] = 1;
		
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (abs(rotation.elements[i][j]) <= std::numeric_limits<float>::epsilon())
                {
                    rotation.elements[i][j] = (float)zero;
                }
            }
        }
        return (rotation);
	}

	matrix3 MATRIX3::build_identity() noexcept
	{
        return matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}

	matrix3 MATRIX3::build_scale(float scale_x, float scale_y) noexcept
	{
        return matrix3(scale_x, 0, 0, 0, scale_y, 0, 0, 0, 1);
	}

	matrix3 MATRIX3::build_scale(float scale) noexcept
	{
        return build_scale(scale, scale);
	}

	matrix3 MATRIX3::build_scale(const vector2& scale) noexcept
	{
        return build_scale(scale.x, scale.y);
	}

	matrix3 MATRIX3::build_translation(float translate_x, float translate_y) noexcept
	{
        return matrix3(1, 0, 0, 0, 1, 0, translate_x, translate_y, 1);
	}

	matrix3 MATRIX3::build_translation(const vector2& translation) noexcept
	{
        return build_translation(translation.x, translation.y);
	}
}
