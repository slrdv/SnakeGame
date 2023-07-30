#pragma once

#include <cmath>

namespace CoreUtils
{
    // https://en.wikipedia.org/wiki/Field_of_view_in_video_games
    inline double calcHFov(double vFovRad, double viewportWidth, double viewportHeight)
    {
        return 2.0 * std::atan(std::tan(vFovRad * 0.5) * viewportWidth / viewportHeight);
    }

    inline double calcVFov(double hFovRad, double viewportWidth, double viewportHeight)
    {
        return 2.0 * std::atan(std::tan(hFovRad * 0.5) * viewportHeight / viewportWidth);
    }

    /**
     * Calculates isosceles triangle height
     * @param base isosceles triangle base
     * @param aRad vertex angle in radians
     * @return double isosceles triangle height
     */
    inline double calcIsoscelesH(double base, double aRad)
    {
        // h = (base * 0.5) / tg(a * 0.5)
        return base * 0.5 / std::tan(aRad * 0.5);
    }

}  // namespace CoreUtils
