#ifndef _GRAPHIC_INTERFACE_H_
#define _GRAPHIC_INTERFACE_H_

#include "GraphicAPI.h"

using namespace GraphicAPI;
class CGraphic:public IGraphicAPI
{
	public:
		CGraphic();
		~CGraphic();
		virtual long InitGraphic();
		virtual long CreateWind(char* Name, int Sizex, int Sizey);
		virtual void SetConfig(stWindowConfig* pData);
		virtual long RegisterImage(unsigned long& ImageId, char* ImageName);
		//	virtual long RegisterTile(unsigned long& ImageId, char* ImageName, int coordX, int coordY, int TileW, int TileH);
		virtual long DisplayImage(unsigned long Id, int x, int y, int Scale = 1);
		virtual long DisplayTile(unsigned long Id, int destx, int desty, int srcx, int srcy, int TileSizeW, int TileSizeH, int Scale = 1);
		virtual void QueryTextureSize(unsigned long Id, int& W, int& H);
		//Display string part
		virtual long RegisterFont(unsigned long& FontId, char* FontName);
		virtual long DisplayString(unsigned long Id, int x, int y, char* pString, Pen_Color* pColor);
		virtual void RenderScreen();
		virtual void SetDisplayCursor(bool value);
		virtual long UnRegisterFont(unsigned long FontId);
		virtual long UnRegisterImage(unsigned long ImageId);


};

#endif //_GRAPHIC_INTERFACE_H_