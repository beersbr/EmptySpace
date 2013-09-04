#include "Entity.h"


Entity::Entity(void)
{
}


Entity::~Entity(void)
{
}

bool Entity::colliding(Entity* a, Entity* b)
{
	if((a->pos.x - a->size.x/2) > (b->pos.x + b->size.x/2))
		return false;
	if((a->pos.x + a->size.x/2) < (b->pos.x - b->size.x/2))
		return false;
	if((a->pos.y + a->size.y/2) < (b->pos.y - b->size.y/2))
		return false;
	if((a->pos.y - a->size.y/2) > (b->pos.y + b->size.y/2))
		return false;
	if((a->pos.z + a->size.z/2) < (b->pos.z - b->size.z/2))
		return false;
	if((a->pos.z - a->size.z/2) > (b->pos.z + b->size.z/2))
		return false;

	return true;
 }

void Entity::setColliding(bool ic)
{

}

void Entity::onDie()
{

}