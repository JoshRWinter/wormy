#ifndef ENTITY_H
#define ENTITY_H

struct Entity
{
	bool collide(const Entity&) const;

	float x, y, s;
};

struct Link : Entity
{
};

struct Food : Entity
{
};

#endif
