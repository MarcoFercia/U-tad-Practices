#pragma once

#include"Components.h"

#include "core.h"
#include "sys.h"
#include "logica.h"
#include "Message.h"
#include "Timer.h"

void Component::ReciveMessage(Message* _msg)
{

}



//Entity
void Entity::Slot(float _elapsed)
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); ++compIt)
	{
		if (!dynamic_cast<RenderComponent*>(*compIt))
		{
			(*compIt)->Slot(_elapsed);
		}		
	}
}

void Entity::AddComponent(Component* _pComponent)
{
	m_Components.push_back(_pComponent);
}




template <class T>
T* Entity::FindComponent()
{
	for (auto compIt = m_Components.begin(); compIt != m_Components.end(); compIt++)
	{
		T* comp = dynamic_cast<T*>(*compIt);
		if (comp )
		{
			return comp;
		}
	}
	return nullptr;
}

void Entity::SendMessages(Message* _msg)
{
	
	
		for (auto compIt = this->m_Components.begin(); compIt != this->m_Components.end(); compIt++)
		{
			(*compIt)->ReciveMessage(_msg);
		}

	
}



Entity::~Entity()
{
	for (auto Iter = m_Components.begin(); Iter != m_Components.end(); Iter++)
	{
		delete* Iter;
		*Iter = nullptr;
	}
	m_Components.clear();
}


void Entity::Call()
{
	FindComponent<RenderComponent>()->CallSlot();
}

void Entity::Call2()
{
	FindComponent<PlayerControllerComponent>()->InputManager();
}


//Collision Component
CollisionComponent::CollisionComponent(Entity* _owner, vec2 _pos, float _radius, vec2 _vel)
{
	m_Owner = _owner;
	pos = _pos;
	radius = _radius;
	vel = _vel;
	collision = false;
}


void CollisionComponent::Slot(float elapsed)
{

	if (m_Owner->isActive == true)
	{



		CollisionComponent* pCollisionBall = nullptr;
		std::list<Entity*>* EntityList = LogicManager::Instance()->GetBalls();


		vec2 newpos = this->pos + (this->vel * (elapsed));


		// Collision detection.
		collision = false;
		Entity* colliding_ball = nullptr;

		for (auto Iter = EntityList->begin(); Iter != EntityList->end(); Iter++)
		{
			if (m_Owner != (*Iter)&&(*Iter)->isActive==true)
			{
				pCollisionBall = (*Iter)->FindComponent<CollisionComponent>();

				float limit2 = (this->radius + pCollisionBall->radius) * (this->radius + pCollisionBall->radius);
				if (vlen2(newpos - pCollisionBall->pos) <= limit2) {
					collision = true;
					colliding_ball = (*Iter);
					break;
				}
			}
		}
		if (!collision)
		{

		}
		else
		{
			EntColliisonMessage* pECM = new EntColliisonMessage;
			pECM->Sender = m_Owner;

			// Rebound!


			if (m_Owner->type == Entity::Identifier::Enemy)
			{
				this->vel.x = (this->vel.x * -1.f);
				this->vel.y = (this->vel.y * pECM->change);
				m_Owner->SendMessages(pECM);
				colliding_ball->SendMessages(pECM);
			}
			else if (m_Owner->type == Entity::Identifier::Bullet)
			{
				LogicManager::Instance()->DestroyBalls--;

				m_Owner->isActive = false;
				colliding_ball->isActive = false;

				if (colliding_ball->tier == 2)
				{
					int takeball = 0;

					for (auto Iter = EntityList->begin(); Iter != EntityList->end(); Iter++)
					{
						if ((*Iter)->isActive == false && takeball != 2)
						{
							(*Iter)->isActive = true;
							(*Iter)->tier = 1;


							NewParams* pNPB = new NewParams;
							pNPB->radius = 15.f;

							if (takeball == 0)
							{
								pNPB->vel.x = colliding_ball->FindComponent<CollisionComponent>()->vel.x;
								pNPB->pos.x = colliding_ball->FindComponent<CollisionComponent>()->pos.x - 30;
							}
							else
							{
								pNPB->vel.x = -colliding_ball->FindComponent<CollisionComponent>()->vel.x;
								pNPB->pos.x = colliding_ball->FindComponent<CollisionComponent>()->pos.x + 30;
							}

							pNPB->pos.y = colliding_ball->FindComponent<CollisionComponent>()->pos.y;
							pNPB->vel.y = 7.f;
							(*Iter)->SendMessages(pNPB);
							delete pNPB;

							takeball++;
						}
					}


				}

			}
			else if (m_Owner->type == Entity::Identifier::Player)
			{
				LogicManager::Instance()->hp--;
				LogicManager::Instance()->DestroyBalls--;				
				colliding_ball->isActive = false;

				

				if (colliding_ball->tier == 2)
				{
					int takeball = 0;

					for (auto Iter = EntityList->begin(); Iter != EntityList->end(); Iter++)
					{
						if ((*Iter)->isActive == false && takeball != 2)
						{
							(*Iter)->isActive = true;
							(*Iter)->tier = 1;


							NewParams* pNPB = new NewParams;
							pNPB->radius = 15.f;

							if (takeball == 0)
							{
								pNPB->vel.x = colliding_ball->FindComponent<CollisionComponent>()->vel.x;
								pNPB->pos.x = colliding_ball->FindComponent<CollisionComponent>()->pos.x - 50;
							}
							else
							{
								pNPB->vel.x = -colliding_ball->FindComponent<CollisionComponent>()->vel.x;
								pNPB->pos.x = colliding_ball->FindComponent<CollisionComponent>()->pos.x + 50;
							}
							pNPB->pos.y = colliding_ball->FindComponent<CollisionComponent>()->pos.y+20;
							pNPB->vel.y = 5.f;
							(*Iter)->SendMessages(pNPB);
							delete pNPB;

							takeball++;
						}
					}

				}

			}
			delete pECM;
		}

		if (m_Owner->type == Entity::Identifier::Enemy)
		{
			// Rebound on margins.
			if ((this->pos.x > SCR_WIDTH_COLL) || (this->pos.x < 0))
			{
				this->vel.x *= -1.0;
				LimitWorldCollisionMessage* pLWCM = new LimitWorldCollisionMessage;
				pLWCM->newvel = vel;
				m_Owner->SendMessages(pLWCM);
				delete pLWCM;
			}

			if (/*(this->pos.y > SCR_HEIGHT_COLL) ||*/ (this->pos.y < 0))
			{
				//this->vel.y *= -1;
				this->vel.y=CORE_FRand(23.f, 26.f);

				LimitWorldCollisionMessage* pLWCM = new LimitWorldCollisionMessage;
				pLWCM->newvel = vel;
				m_Owner->SendMessages(pLWCM);
				delete pLWCM;
			}
		}


		if (m_Owner->type == Entity::Identifier::Bullet)
		{
			if (this->pos.y > SCR_HEIGHT)
			{
				m_Owner->isActive = false;
			}
		}


	}
}


void CollisionComponent::ReciveMessage(Message* _msg)
{
	NewPosMessage* pNewPos = dynamic_cast<NewPosMessage*>(_msg);
	if (pNewPos)
	{
		pos = pNewPos->newpos;
		vel = pNewPos->newvel;
	}

	EntColliisonMessage* pColl = dynamic_cast<EntColliisonMessage*>(_msg);

	if (pColl)
	{

		if (m_Owner == pColl->Sender)
		{

		}
		else
		{
			vel.x = vel.x * -1.f;
			vel.y = vel.y * -1.8f;
		}

	}

	NewParams* pNew = dynamic_cast<NewParams*>(_msg);
	if (pNew)
	{
		pos = pNew->pos;
		vel = pNew->vel;
		radius = pNew->radius;

	}


}


//Movement Controller


MovementComponent::MovementComponent(Entity* _owner, vec2 _pos, vec2 _vel)
{
	m_Owner = _owner;
	pos = _pos;
	vel = _vel;
}


void MovementComponent::Slot(float elapsed)
{
	if (m_Owner->isActive == true)
	{

		if (m_Owner->type == Entity::Identifier::Enemy)
		{
			if (Collision == false)
			{

				vec2 newpos = this->pos + (this->vel * (elapsed));
				this->pos = newpos;
				
				vel.y += -1.f * elapsed;

				NewPosMessage* pNPM = new NewPosMessage;
				pNPM->newvel = vel;
				pNPM->newpos = pos;
				m_Owner->SendMessages(pNPM);
				delete pNPM;

			}
			Collision = false;
		}
		if (m_Owner->type == Entity::Identifier::Bullet)
		{
			vec2 newpos = this->pos + (this->vel * (elapsed));
			this->pos = newpos;
			NewPosMessage* pNPM = new NewPosMessage;

			pNPM->newpos = pos;
			m_Owner->SendMessages(pNPM);
			delete pNPM;
		}

	}

}

void MovementComponent::ReciveMessage(Message* _msg)
{
	EntColliisonMessage* pMessEntColl = dynamic_cast<EntColliisonMessage*>(_msg);
	if (pMessEntColl)
	{
		Collision = true;
		vel.x = vel.x * -1.f;
		vel.y = vel.y * pMessEntColl->change;
	}

	LimitWorldCollisionMessage* pMessWorldColl = dynamic_cast<LimitWorldCollisionMessage*>(_msg);
	if (pMessWorldColl)
	{
		vel = pMessWorldColl->newvel;
	}

	NewPosMessage* pNPM = dynamic_cast<NewPosMessage*>(_msg);
	if (pNPM && pNPM->Sender!=m_Owner)
	{
		pos = pNPM->newpos;
	}


	NewParams* pNew = dynamic_cast<NewParams*>(_msg);
	if (pNew)
	{
		pos = pNew->pos;
		vel = pNew->vel;
	}
}


//Render Component
RenderComponent::RenderComponent(Entity* _owner, vec2 _pos, float _radius, GLuint _gfx)
{
	m_Owner = _owner;
	pos = _pos;
	radius = _radius;
	gfx = _gfx;
	
}


void RenderComponent::CallSlot()
{
	Slot(0);
}

void RenderComponent::Slot(float elapsed)
{
	if (m_Owner->isActive == true)
	{
		CORE_RenderCenteredSprite(pos, vec2(radius * 2.f, radius * 2.f), gfx);
	}
}

void RenderComponent::ReciveMessage(Message* _msg)
{
	NewPosMessage* pNewPos = dynamic_cast<NewPosMessage*>(_msg);
	if (pNewPos)
	{	
		pos = pNewPos->newpos;
	}

	NewParams* pNew = dynamic_cast<NewParams*>(_msg);
	if (pNew)
	{
		pos = pNew->pos;
		radius = pNew->radius;
	}
}


//PlayerControllerComponent

PlayerControllerComponent::PlayerControllerComponent(Entity* _owner, vec2 _pos, vec2 _vel)
{
	m_Owner = _owner;
	pos = _pos;
	vel = _vel;
}

void PlayerControllerComponent::Slot(float elapsed)
{
	InputManager();
	//610
	//30
	NewPosMessage* pNPM = new NewPosMessage;
	pNPM->newpos = pos;
	switch (NextAction)
	{
	case PlayerControllerComponent::Actions::None:
		break;


	case PlayerControllerComponent::Actions::MRight:

		pos = pos + (vel * elapsed);
		
		if (pos.x >= 610)
		{
			pos.x = 609;
		}
		pNPM->newpos = pos;
		m_Owner->SendMessages(pNPM);
		

		break;

	case PlayerControllerComponent::Actions::MLeft:

		pos = pos - vel * elapsed;
		if (pos.x <= 30.f)
		{
			pos.x = 31.f;
		}
		pNPM->newpos = pos;
		m_Owner->SendMessages(pNPM);
		

		break;

	case PlayerControllerComponent::Actions::Fire:

		pNPM->newpos.y += 15.f;
		LogicManager::Instance()->Bullet->SendMessages(pNPM);
		LogicManager::Instance()->Bullet->isActive = true;


		break;
	default:
		break;
	}
	delete pNPM;
}



void PlayerControllerComponent::InputManager()
{
	NextAction = Actions::None;

	short MLeftKeyState = GetKeyState('A');
	short MRightKeyState = GetKeyState('D');
	short FireKeyState = GetKeyState('W');


	if ((MLeftKeyState & 0x8000) != 0 && pos.x>30.f)
	{
		NextAction = Actions::MLeft;

	}
	else if ((MRightKeyState & 0x8000) != 0 && pos.x < 610.f)
	{
		NextAction = Actions::MRight;

	}
	else if ((FireKeyState & 0x8000) != 0 && LogicManager::Instance()->Bullet->isActive==false)
	{
		NextAction = Actions::Fire;

	}
}
	




void PlayerControllerComponent::ReciveMessage(Message* _msg)
{

}