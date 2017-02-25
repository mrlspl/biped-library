/**
 * @file Angle.hpp
 *
 *
 * @author <a href="mailto:m.a@sharpasand.com">Mohammad Ali Sharpasand</a>
 * @author <a href="mailto:aref.moqadam@gmail.com">Aref Moqadam</a>
 * @date Feb 2014
 */


#pragma once

#include <cmath>

namespace BipedLibrary
{
    // TODO: Write unit test for this class while taking care of the extremes in
    // tests you define. Then separate implementation from declaration. The only
    // function that needs to be defined here is the template constructor.
    class Angle
    {
    public:

        Angle() : _data(0)
        {
        }

        Angle(const Angle& a) /*:_data(a._data)*/
        {
            _data = a._data;
        };

        template<typename T> //-- This is for every other types
        Angle(const T& data) : _data(data)
        {
            _normalize();
        }

        // operator float() const { return _data; }
        // NOTE: No cast operator! This can be dangerous.
        // There's an explicit function for this: toFloat.

        Angle operator-()
        {
            return Angle(_data * -1);
            // Constructor _norm() ensures _data != -pi
            // since the range is (-pi, pi].
        }

        friend Angle operator+(Angle first, Angle second)
        {
            return Angle(first._data + second._data);
        }

        friend Angle operator-(Angle first, Angle second)
        {
            return Angle(first._data - second._data);
        }

        friend Angle operator*(Angle first, Angle second)
        {
            return Angle(first._data * second._data);
        }

        friend Angle operator/(Angle first, Angle second)
        {
            return Angle(first._data / second._data);
        }

        Angle operator+=(Angle other)
        {
            _data += other._data;
            _normalize();
            return *this;
        }

        Angle operator-=(Angle other)
        {
            _data -= other._data;
            _normalize();
            return *this;
        }

        Angle operator*=(Angle other)
        {
            _data *= other._data;
            _normalize();
            return *this;
        }

        Angle operator/=(Angle other)
        {
            _data /= other._data;
            _normalize();
            return *this;
        }

        friend bool operator==(Angle first, Angle second)
        {
            return first._data == second._data;
        }

        friend bool operator!=(Angle first, Angle second)
        {
            return first._data != second._data;
        }

        // NOTE: There should be no compare operators (except equality) for this type

        inline bool isBetween(const Angle& min, const Angle& max) const
        {
            if(min._data <= max._data)
                return min._data <= _data && _data <= max._data;
            else
                return min._data <= _data || _data <= max._data;
        }

        inline bool isBetweenExclusive(const Angle& min, const Angle& max) const
        {
            if(min._data <= max._data)
                return min._data < _data && _data < max._data;
            else
                return min._data < _data || _data < max._data;
        }

        inline bool isCloserToTheFirst(Angle first, Angle second) const
        {
            return std::fabs(first._data - _data) < std::fabs(second._data - _data);
        }

        inline bool isCloserToTheSecond(const Angle& first, const Angle& second) const
        {
            return std::fabs(first._data - _data) > std::fabs(second._data - _data);
        }

        Angle abs() const
        {
            return Angle(std::fabs(_data));
        }

        int sign() const
        {
            return _data == 0 ? 0 : (_data > 0 ? 1 : -1);
            // NOTE: Sign may also change about pi/-pi.
        }

        float sin() const
        {
            return std::sin(_data);
        }

        float cos() const
        {
            return std::cos(_data);
        }

        float tan() const
        {
            return std::tan(_data);
        }

        float toDegree() const
        {
            return _data * 180 / M_PI;
        }

        float toFloat() const
        {
            return _data;
            // NOTE: Cast only explicitly.
        }

    private:
        float _data; // between (-pi, pi]

        void _normalize()
        {
            _data = _data - (ceil((_data + M_PI) / (2.0 * M_PI)) - 1) * 2.0 * M_PI;
        }

    };

}