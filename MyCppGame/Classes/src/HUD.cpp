#include "HUD.h"

USING_NS_CC;

HUD * HUD::create()
{
	HUD * hud = new HUD();
	if (hud && hud->initWithFile("GameScreen/scorehud.png"))
	{
		hud->autorelease();
		hud->initHUD();
		return hud;
	}

	CC_SAFE_DELETE(hud);
	return NULL;
}

void HUD::initHUD()
{

}