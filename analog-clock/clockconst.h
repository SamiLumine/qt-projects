#ifndef CLOCKCONST_H
#define CLOCKCONST_H

namespace ClockConstants
{
const int MARGIN         = 10;
const int BORDER_SPACING = 10;

const int SECOND_RECT_W = 12;
const int SECOND_RECT_H = 2;

const int HOUR_RECT_W = 24;
const int HOUR_RECT_H = 6;

const double HOUR_HAND_W = 0.75;
const double HOUR_HAND_H = 0.05;

const double MINUTE_HAND_W = 0.85;
const double MINUTE_HAND_H = 0.05;

const double SECOND_HAND_W = 0.95;
const double SECOND_HAND_H = 0.03;

const double HAND_TAPER_RATIO = 0.025;
const double SIZE_SHIFT       = 0.1;
const double CIRCLE_HAND_RAD  = 0.1;
}; // namespace ClockConstants

#endif // CLOCKCONST_H
