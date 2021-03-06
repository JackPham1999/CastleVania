#include "Whip.h"
#include "Game.h"
#include "Simon.h"
#include "PlayScence.h"
#include "Torch.h"
CWhip* CWhip::__instance = NULL;
//CSimon* simon;

CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}

CWhip::CWhip() :CGameObject()
{
	_level = 1;
	/*this->x = x;
	this->y = y;*/
}
void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//vector<LPGAMEOBJECT> listObj;
	// Collision logic with items
	CGameObject::Update(dt);

	// Simple fall down
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (CSimon::GetInstance()->GetState() == SIMON_STATE_ATTACKING)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CTorch*>(e->obj))
			{
				CTorch* torch = dynamic_cast<CTorch*>(coObjects->at(i));
				float l, t, r, b, l1, t1, r1, b1;
				GetBoundingBox(l, t, r, b);
				torch->GetBoundingBox(l1, t1, r1, b1);
				if ((r >= l1 && t1 >= b && r1 >= r && b1 >= b))///theiu61 dieu kien
				{
					if (torch->GetState() != TORCH_STATE_NOT_EXIST)
						torch->SetState(TORCH_STATE_NOT_EXIST);
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{/*
	if (animation->GetCurrentFrame() < 2)
		return;*/
	if (_level == 1 || _level == 2)
	{
		left = x;
		right = x + 56;
		top = y;
		bottom = y + 20;
	}
	else
	{
		left = x;
		right = x + 100;
		top = y;
		bottom = y + 20;
	}
}

void CWhip::Render()
{
	int ani;
	int simon_trend = CSimon::GetInstance()->GetTrend();
	CSimon::GetInstance()->GetPosition(x, y);
	if (CSimon::GetInstance()->GetState() == SIMON_STATE_ATTACKING)
	{
		if (_level == 1)
		{
			if (simon_trend > 0)
			{
				ani = WHIP_LEVEL1_ANI_ATTACK_RIGHT;
				x = x - 11;
				y = y + 2;
			}
			else
			{
				ani = WHIP_LEVEL1_ANI_ATTACK_LEFT;
				x = x - 22;
				y = y + 2;
			}
		}
		else if (_level == 2)
		{
			if (simon_trend > 0)
			{
				ani = WHIP_LEVEL2_ANI_ATTACK_RIGHT;
				x = x - 8;
				y = y - 1;
			}
			else
			{
				ani = WHIP_LEVEL2_ANI_ATTACK_LEFT;
				x = x - 22;
				y = y - 1;
			}
		}
		else if (_level == 3)
		{
			if (simon_trend > 0)
			{
				ani = WHIP_LEVEL3_ANI_ATTACK_RIGHT;
				x = x - 10;
				y = y - 2;
			}
			else
			{
				ani = WHIP_LEVEL3_ANI_ATTACK_LEFT;
				x = x - 32;
				y = y + 3.5;
			}
		}
		//CSimon::GetInstance()->GetPosition(x, y);
		/*if (animations.size() > 1)
			animations[ani]->Render(x, y);*/
		int alpha = 255;
		//SetAnimationSet(7);
		animation_set->at(ani)->Render(x, y, alpha);/////////animation_set==nul

		RenderBoundingBox();
	}
}
