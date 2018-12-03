#include <wormy.h>

bool Entity::collide(const Entity &other) const
{
	return x + s > other.x && x < other.x + other.s && y + s > other.y && y < other.y + other.s;
}
