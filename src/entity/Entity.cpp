#include <cmath>

#include <wormy.h>

bool Entity::collide(const Entity &other) const
{
	const float center_x1 = x + (s / 2.0f);
	const float center_y1 = y + (s / 2.0f);

	const float center_x2 = other.x + (other.s / 2.0f);
	const float center_y2 = other.y + (other.s / 2.0f);

	return win::distance(center_x1, center_y1, center_x2, center_y2) < (s / 2.0f) + (other.s / 2.0f);
}
