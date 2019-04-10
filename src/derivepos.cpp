#include "derivepos.hpp"

const double DIST_TO_PLANE = 181;
const double VIEWPORT_PLANE_HEIGHT = 143.5;
const double VIEWPORT_PLANE_WIDTH = 182.5;  // Very rough estimate


double derivePosY(double screenPosY, double screenHeight)
{
    const double invPos = screenHeight - screenPosY;
    return VIEWPORT_PLANE_HEIGHT/((screenPosY/invPos) + 1.0);
}


double derivePosZ()
{
    return DIST_TO_PLANE;
}


double derivePosX(double screenPosX, double screenWidth)
{
    return VIEWPORT_PLANE_WIDTH/screenWidth * screenPosX;
}
