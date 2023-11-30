#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float dt);
	virtual void Render();
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	Rect RectWithPos();
	void SetCenter(D3DXVECTOR2 pos);
	D3DXVECTOR2 Center();

	D3DXVECTOR3 GetPosition();
	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRotation();
	void SetRotation(D3DXVECTOR3 rotation);

	D3DXVECTOR3 GetScale();
	void SetScale(D3DXVECTOR3 scale);

	Rect GetRect();
	void SetRect(Rect rect);

	bool GetVisible();
	void SetVisible(bool visible);

	bool GetRemoving();

	D3DXMATRIX GetWorldMatrix();
	vector<Entity*> GetChildren();

private:
	Entity * parent_;
	vector<Entity*> children_;
	D3DXVECTOR3 position_;
	D3DXVECTOR3 rotation_;
	D3DXVECTOR3 scale_;
	D3DXMATRIX matrix_;
	Rect rect_;
	bool visible_;
	bool update_enabled_;
	bool render_children_enabled_;
	bool removing_;
};

