#include "ECS.h"

void Entity::addGroup(Group m_Group)
{
	groupBitSet[m_Group] = true;
	manager.AddToGroup(this, m_Group);
}
