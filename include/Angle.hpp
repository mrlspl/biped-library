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
    
    class Angle
    {
    public:
      Angle() : _data(0) {}
      Angle(const Angle& a) /*:_data(a._data)*/ { _data = a._data; };
      template<typename T> //-- This is for every other types
      Angle(const T& data) : _data(data) { _normalize(); }


    //  operator float() const { return _data; } //-- NOTE: this casting is commented in order to prevent possible problems caused by implicit casting.
    //  operator bool()  const { return _data != 0.f; }

      Angle operator -() { return Angle(_data * -1); } // Constructor _norm() ensures _data != -pi Since the range is (-pi, pi].

      friend Angle operator +(const Angle& first, const Angle& second) { return Angle(first._data + second._data); }
      friend Angle operator -(const Angle& first, const Angle& second) { return Angle(first._data - second._data); }

      friend Angle operator *(const Angle& first, const Angle& second) { return Angle(first._data * second._data); }
      friend Angle operator /(const Angle& first, const Angle& second) { return Angle(first._data / second._data); }

      Angle operator +=(const Angle& other) { _data += other._data; _normalize(); return *this; }
      Angle operator -=(const Angle& other) { _data -= other._data; _normalize(); return *this; }
      Angle operator *=(const Angle& other) { _data *= other._data; _normalize(); return *this; }
      Angle operator /=(const Angle& other) { _data /= other._data; _normalize(); return *this; }

      friend bool operator ==(const Angle& first, const Angle& second) { return first._data == second._data; }
      friend bool operator !=(const Angle& first, const Angle& second) { return first._data != second._data; }

      // NOTE: There should be no compare operators (except equality) for this type
      // because comparing two angles doesn't mean since it has a periodic behavior.
      // [FIXME] : check this function on pi to pi boundaries
    //  inline bool isInside(const Angle& min, const Angle& max) const
    //  {
    ////    const float c1 = min(abs(tmin-t), 2*pi-abs(tmin-t));
    ////    const float c2 = min(abs(tmax-t), 2*pi-abs(tmax-t));
    ////    const float mx = min(tmax-tmin, 2*pi-(tmax-tmin));
    ////
    ////    return (min._data < max._data) ? (c1 < mx && c2 < mx) : (isBetween(max, min));
    //
    //    return (max.isBetween(min, min+M_PI)) ? (isBetween(min, max)) : (isBetween(max, min));
    //  }
    //  inline bool isInsideExclusive(const Angle& min, const Angle& max) const
    //  {
    //    return (max.isBetween(min, min+M_PI)) ? (isBetweenExclusive(min, max)) : (isBetweenExclusive(max, min));
    //  }

      inline const bool isBetween(const Angle& min, const Angle& max)       const { return (min._data <= max._data) ? (min._data <= _data && _data <= max._data) : (min._data <= _data || _data <= max._data); }
      inline const bool isBetweenExclusive(const Angle& min, const Angle& max)  const { return (min._data <= max._data) ? (min._data <  _data && _data <  max._data) : (min._data <  _data || _data <  max._data); }

      inline const bool isCloserToTheFirst(const Angle& first, const Angle& second)  const { return std::fabs(first._data - _data) < std::fabs(second._data - _data); }
      inline const bool isCloserToTheSecond(const Angle& first, const Angle& second) const { return std::fabs(first._data - _data) > std::fabs(second._data - _data); }

      const Angle abs() const { return Angle(std::fabs(_data)); }
      const int sign()  const { return _data == 0 ? 0 : (_data > 0 ? 1 : -1); } // NOTE: Sign may change both about zero and about pi/-pi.

      const float sin() const { return std::sin(_data); }
      const float cos() const { return std::cos(_data); }
      const float tan() const { return std::tan(_data); }

      const float toDegree() const { return _data * 180 / M_PI; }
      const float toFloat()  const { return _data; } //-- NOTE: Actually this is done automatically by casting over load.

    private:
      float _data;

      // between (-pi, pi]
      void _normalize()
      {
        _data = _data - (ceil((_data+M_PI)  / (2.0*M_PI)) - 1) * 2.0 * M_PI;
      }

    };

}