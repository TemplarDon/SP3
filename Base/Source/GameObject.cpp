#include "GameObject.h"

GameObject::GameObject()
	: 
	m_Type(GO_NONE),
	m_Scale(1, 1, 1),
	m_Active(false),
	m_Collidable(false),
	m_Visible(true)
{
}

GameObject::~GameObject()
{
}

GAMEOBJECT_TYPE GameObject::GetType()
{
	return m_Type;
}

void GameObject::SetType(GAMEOBJECT_TYPE SetType)
{
	m_Type = SetType;
}

Vector3 GameObject::GetPosition()
{
	return m_Position;
}

void GameObject::SetPosition(Vector3 SetPos)
{
	m_Position = SetPos;
}

Vector3 GameObject::GetScale()
{
	return m_Scale;
}

void GameObject::SetScale(Vector3 SetScale)
{
	m_Scale = SetScale;
}

bool GameObject::GetActive()
{
	return m_Active;
}

void GameObject::SetActive(bool SetActive)
{
	m_Active = SetActive;
}

bool GameObject::GetCollidable()
{
	return m_Collidable;
}

void GameObject::SetCollidable(bool SetCollidable)
{
	m_Collidable = SetCollidable;
}

bool GameObject::GetVisible()
{
	return m_Visible;
}

void GameObject::SetVisible(bool SetVisible)
{
	m_Visible = SetVisible;
}

Mesh* GameObject::GetMesh()
{
	return m_ObjectMesh;
}

void GameObject::SetMesh(Mesh* SetMesh)
{
	m_ObjectMesh = SetMesh;
}

bool GameObject::EmpricalCheckCollisionWith(GameObject* OtherGo, double dt)
{
	return false;
}

float GameObject::MathematicalCheckCollisionWith(GameObject* OtherGo)
{
	return -1;
}

void GameObject::CollisionResponse(GameObject* OtherGo)
{

}

//bool GameObject::CheckCollisionWith(GameObject* go2)
//{
//    float distSquare = (this->pos - go2->pos).LengthSquared();
//    float combinedRadiusSquare = (this->scale.x + go2->scale.x)*(this->scale.y + go2->scale.y);
//
//    if (distSquare < combinedRadiusSquare)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

// Empirical
//bool GameObject::CheckCollisionWith(GameObject* go2, double dt)
//{
//	switch (go2->type)
//	{
//	case GameObject::GO_BALL:
//	{
//		float distSquare = ((this->pos + this->vel * dt) - (go2->pos + go2->vel * dt)).LengthSquared();
//		float combinedRadiusSquare = (this->scale.x + go2->scale.x) * (this->scale.y + go2->scale.y);
//
//		Vector3 relVelocity = this->vel - go2->vel;
//		Vector3 relDisplacement = this->pos - go2->pos;
//
//		// (Forward Checking && Direction Checking)
//		if (distSquare < combinedRadiusSquare && relVelocity.Dot(relDisplacement) < 0) // For collision, relative vel and relative dis must be in opposite dir, thus dot < 0 (Solves 'siam twins' problem)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//		break;
//	}
//	case GameObject::GO_WALL:
//	{
//		Vector3 w0 = go2->pos + go2->vel * dt;
//		Vector3 b1 = this->pos + this->vel * dt;
//		Vector3 N = go2->normal;
//
//		Vector3 dir = w0 - b1;
//		if (dir.Dot(N) < 0)
//		{
//			N = -N;
//		}
//
//		Vector3 relVelocity = this->vel - go2->vel;
//		Vector3 relDisplacement = this->pos - go2->pos;
//
//		float r = this->scale.x;
//		float h = go2->scale.x;
//		float l = go2->scale.y;
//
//		//Vector3 NP = N.Cross(Vector3(0, 0, 1));
//		Vector3 NP = Vector3(-N.y, N.x); // or Vector3(N.y, -N.x);
//
//		if ((abs(dir.Dot(N)) < (r + h * 0.5f)) && (abs(dir.Dot(NP)) < (l * 0.5)) && relVelocity.Dot(relDisplacement) < 0) // Dir check between outward normal and velocity
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//
//		//return (distSquare.Dot(N) < (r + h * 0.5f) && abs(distSquare.Dot(NP)) < r + (l * 0.5));
//		break;
//	}
//
//	case GameObject::GO_PILLAR:
//	{
//		float distSquare = ((this->pos + this->vel * dt) - (go2->pos + go2->vel * dt)).LengthSquared();
//		float combinedRadiusSquare = (this->scale.x + go2->scale.x) * (this->scale.y + go2->scale.y);
//
//		Vector3 relVelocity = this->vel - go2->vel;
//		Vector3 relDisplacement = this->pos - go2->pos;
//
//		if (distSquare < combinedRadiusSquare && relVelocity.Dot(relDisplacement) < 0) // For collision, relative vel and relative dis must be in opposite dir, thus dot < 0 (Solves 'siam twins' problem)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//
//		break;
//	}
//	}
//
//}
//
//// Mathetical 
//float GameObject::CheckCollisionWith2(GameObject* go2)
//{
//	switch (go2->type)
//	{
//	case GameObject::GO_BALL:
//	{
//		Vector3 relVelocity = this->vel - go2->vel;
//		Vector3 relDisplacement = this->pos - go2->pos;
//
//		float combinedRadiusSquare = (this->scale.x + go2->scale.x);
//
//		// Direction Check
//		if (relVelocity.Dot(relDisplacement) > 0)
//		{
//			return -1;
//		}
//
//		// a = mule^2 (mule is the greek alphabet)
//		// b = 2 * mule * N (N is dir)
//		// c = N^2 - r^2
//
//		float a = relVelocity.Dot(relVelocity);
//		float b = 2 * relVelocity.Dot(relDisplacement);
//		float c = relDisplacement.Dot(relDisplacement) - combinedRadiusSquare * combinedRadiusSquare;
//
//		float discriminant = (b * b) - (4 * a * c);
//		if (discriminant < 0)
//		{
//			return -1;
//		}
//
//		// Quadratic Formula
//		float intersectTime1 = (-b - sqrt(discriminant)) / (2 * a);
//		float intersectTime2 = (-b + sqrt(discriminant)) / (2 * a);
//
//		if (intersectTime1 < 0)
//		{
//			intersectTime1 = intersectTime2;
//		}
//
//		return intersectTime1;
//		break;
//	}
//
//	case GameObject::GO_WALL:
//	{
//		Vector3 w0 = go2->pos;
//		Vector3 b1 = this->pos;
//		Vector3 N = go2->normal;
//		Vector3 dir = w0 - b1;
//
//		float r = this->scale.x;
//		float h = go2->scale.x;
//		float l = go2->scale.y;
//
//		if (dir.Dot(N) < 0)
//		{
//			N = -N;
//		}
//
//		Vector3 relVelocity = this->vel - go2->vel;
//		if (relVelocity.Dot(N) < 0)
//		{
//			return -1;
//		}
//
//		w0 -= (r + h * 0.5) * N;
//
//		float Dist = (w0 - b1).Dot(N);
//		float Speed = relVelocity.Dot(N);
//
//		float th = Dist / Speed;
//
//		Vector3 NP = Vector3(-N.y, N.x);
//
//		Vector3 w1 = w0 + (1 * 0.5f) * NP;
//		Vector3 w2 = w0 - (1 * 0.5f) * NP;
//
//		Vector3 bh = b1 + relVelocity * th;
//
//		if ((w1 - bh).Dot(w2 - bh) < 0)
//		{
//			return -1;
//		}
//		
//		return th;
//		break;
//	}
//
//	}
//}
//
//bool GameObject::CheckIsNear(GameObject* go2, float scale)
//{
//	float distSquare = (this->pos - go2->pos).LengthSquared();
//	float combinedRadiusSquare = (this->scale.x + go2->scale.x) * (this->scale.x + go2->scale.x) * scale;
//
//
//	if (distSquare < combinedRadiusSquare)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//void GameObject::CollisionResponse(GameObject* go2)
//{
//	switch (go2->m_Type)
//	{
//	case GameObject::GO_BALL:
//	{
//		// 2D Collision
//		Vector3 Dist = (this->m_Position - go2->m_Position).Normalized();
//
//		Vector3 u1 = this->m_Velocity;
//		Vector3 u2 = go2->m_Velocity;
//
//		// Proj go onto Dist (U == go, V == Dist)
//		//Vector3 go_Normal = ( (u1.Dot(Dist) * Dist ) * ( 1 / Dist.Length() * Dist.Length()));
//		Vector3 go_Normal = u1.Dot(Dist) * Dist;
//
//		// Proj go2 onto Dist
//		//Vector3 go2_Normal = ((u2.Dot(Dist) * Dist) * (1 / Dist.Length() * Dist.Length()));
//		Vector3 go2_Normal = u2.Dot(Dist) * Dist;
//
//		this->m_Velocity = u1 + ((2 * go2->m_Mass) * (go2_Normal - go_Normal)) * (1 / (this->m_Mass + go2->m_Mass));
//		go2->m_Velocity = u2 + ((2 * this->m_Mass) * (go_Normal - go2_Normal)) * (1 / (this->m_Mass + go2->m_Mass));
//		break;
//	}
//	case GameObject::GO_WALL:
//	{
//		Vector3 u1 = this->m_Velocity;
//
//		Vector3 N = go2->m_Normal;
//
//		if (u1.Dot(N) < 0)
//		{
//			N = -N;
//		}
//
//		Vector3 UN = u1.Dot(N) * N;
//		this->m_Velocity = u1 - (2 * UN);
//
//		break;
//	}
//	case GameObject::GO_PILLAR:
//	{
//		//Vector3 N = (this->pos - go2->pos).Normalized();
//
//		//Vector3 u1 = this->vel;
//
//		//this->vel = u1 - (2 * u1.Dot(N))*N;
//		//break;
//								 
//		Vector3 u1 = this->m_Velocity;
//		Vector3 N = (go2->m_Position - this->m_Position).Normalized();
//		Vector3 u1N = u1.Dot(N) * N;
//
//		this->m_Velocity = u1 - 2 * (u1N);
//		break;
//		
//	}
//
//	}
//}