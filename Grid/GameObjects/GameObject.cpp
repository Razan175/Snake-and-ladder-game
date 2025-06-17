#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

GameObjectType GameObject::GetType()
{
	return Type;
}
GameObject::~GameObject()
{
}