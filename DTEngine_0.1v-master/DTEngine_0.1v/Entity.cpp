#include "pch.h"
#include "Entity.h"


Entity::Entity() :
	parent_(nullptr), position_(0.0f, 0.0f, 0.0f), rotation_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f), rect_(0, 0, 0, 0), visible_(true),
	update_enabled_(true), render_children_enabled_(true),
	removing_(false)
{
}


Entity::~Entity()
{
	for (auto* child : children_)
		delete child;
}

void Entity::AddChild(Entity* child)
{
	child->parent_ = this;
	children_.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	child->removing_ = true;
}

void Entity::Update(float dt)
{
	if (!update_enabled_) return;

	for (auto* child : children_)
		child->Update(dt);

	children_.erase(remove_if(children_.begin(), children_.end(), [](Entity* child) {
		if (child->GetRemoving()) {
			delete child;
			return true;
		}
		return false;
	}), children_.end());
}

void Entity::Render()
{
	static D3DXMATRIX pos_matrix, rot_matrix, sca_matrix;

	if (!visible_) return;
	//D3DXMatrixTransformation2D(&matrix_, &scale_center_, 0, &scale_, &rotation_center_, rotation_, &pos_);

	D3DXMatrixIdentity(&matrix_);
	D3DXMatrixTranslation(&pos_matrix, position_.x, position_.y, position_.z);
	D3DXMatrixRotationYawPitchRoll(&rot_matrix, D3DXToRadian(rotation_.y), D3DXToRadian(rotation_.x), D3DXToRadian(rotation_.z));
	D3DXMatrixScaling(&sca_matrix, scale_.x, scale_.y, scale_.z);

	D3DXMatrixMultiply(&matrix_, &sca_matrix, &rot_matrix);
	D3DXMatrixMultiply(&matrix_, &matrix_, &pos_matrix);

	if (parent_)
		matrix_ *= parent_->matrix_;

	if (!render_children_enabled_) return;
	for (auto* child : children_)
		child->Render();
}

D3DXVECTOR2 Entity::Center()
{
	return D3DXVECTOR2(position_.x, position_.y) + rect_.Center();
}

Rect Entity::RectWithPos()
{
	return rect_.Offset(D3DXVECTOR2(position_.x, position_.y));
}

void Entity::SetCenter(D3DXVECTOR2 pos)
{
	pos -= rect_.Center();
	position_ = D3DXVECTOR3(pos.x, pos.y, position_.z);
}

D3DXVECTOR3 Entity::GetPosition()
{
	return position_;
}

void Entity::SetPosition(D3DXVECTOR3 pos)
{
	position_ = pos;
}

D3DXVECTOR3 Entity::GetRotation()
{
	return rotation_;
}

void Entity::SetRotation(D3DXVECTOR3 rotation)
{
	rotation_ = rotation;
}

D3DXVECTOR3 Entity::GetScale()
{
	return scale_;
}

void Entity::SetScale(D3DXVECTOR3 scale)
{
	scale_ = scale;
}

Rect Entity::GetRect()
{
	return rect_;
}

void Entity::SetRect(Rect rect)
{
	rect_ = rect;
}

bool Entity::GetVisible()
{
	return visible_;
}

void Entity::SetVisible(bool visible)
{
	visible_ = visible;
}

bool Entity::GetRemoving()
{
	return removing_;
}

D3DXMATRIX Entity::GetWorldMatrix()
{
	return matrix_;
}
vector<Entity*> Entity::GetChildren()
{
	return children_;
}