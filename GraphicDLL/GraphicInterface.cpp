#include "GraphicInterface.h"

#include "GraphicManager.h"

CGraphicManager* pManager = NULL;


CGraphic::CGraphic()
{
	if (!pManager)
	{
		pManager = new CGraphicManager;
	}
}
CGraphic::~CGraphic()
{

}
/////////////////////////////////////////////////////////////////////////
long CGraphic::InitGraphic()
{
	if (!pManager)
	{
		pManager = new CGraphicManager;
	}

	if (pManager)
	{
		return pManager->SDL_InitGraphic();
	}

	return -1;
}


long CGraphic::CreateWind(char* Name, int Sizex, int Sizey)
{
	if (pManager)
	{
		return pManager->SDL_CreateWin(Name, Sizex, Sizey);
	}

	return -1;
}


void CGraphic::SetConfig(stWindowConfig* pConf)
{

	if (pManager)
	{
		pManager->SDL_SetConfig(pConf);
	}
}

long CGraphic::RegisterImage(unsigned long& ImageId, char* ImageName)
{
	if (pManager)
	{
		return pManager->SDL_RegisterImage(ImageId, ImageName);
	}
	return -1;
}

/*long CGraphic::RegisterTile(unsigned long& ImageId, char* ImageName, int coordX, int coordY, int TileW, int TileH)
{
if (pManager)
{
return pManager->SDL_RegisterTile(ImageId, ImageName,coordX,coordY,TileW , TileH);
}
return -1;
}*/

long CGraphic::DisplayImage(unsigned long ImageId, int x, int y,int Scale)
{
	if (pManager)
	{
		return pManager->SDL_DisplayObject(ImageId, x, y,Scale);
	}
	return -1;
}

long CGraphic::DisplayTile(unsigned long Id, int destx, int desty, int srcx, int srcy, int TileSizeW, int TileSizeH,  int Scale)
{
	if (pManager)
	{
		return pManager->SDL_DisplayTile(Id, destx, desty, srcx, srcy, TileSizeW, TileSizeH, Scale);
	}
	return -1;
}


long CGraphic::RegisterFont(unsigned long& FontId, char* FontName)
{
	if (pManager)
	{
		return pManager->SDL_RegisterFont(FontId, FontName);
	}
	return -1;
}
long CGraphic::DisplayString(unsigned long FontId, int x, int y, char* pString, Pen_Color* p)
{
	if (pManager)
	{
		return pManager->SDL_DisplayString(FontId, x, y, pString, p);
	}
	return -1;
}

void CGraphic::RenderScreen()
{
	if (pManager)
	{
		pManager->SDL_RenderScreen();
	}
}

void CGraphic::QueryTextureSize(unsigned long Id, int& W, int& H)
{
	if (pManager)
	{
		pManager->SDL_QueryTextureSize(Id, W, H);
	}
}

void CGraphic::SetDisplayCursor(bool value)
{
	if (pManager)
	{
		pManager->SDL_SetDisplayCursor( value);
	}
	
}

long CGraphic::UnRegisterFont(unsigned long FontId)
{
	if (pManager)
	{
		return pManager->SDL_UnRegisterFont(FontId);
	}
	return -1;
}

long CGraphic::UnRegisterImage(unsigned long ImageId)
{
	if (pManager)
	{
		return pManager->SDL_UnRegisterImage(ImageId);
	}
	return -1;
}