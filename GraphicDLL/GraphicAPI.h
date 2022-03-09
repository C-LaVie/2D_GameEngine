#ifndef _GRAPHIC_API_H_
#define _GRAPHIC_API_H_
#include <iostream>


#ifdef GRAPHICDLL_EXPORTS
#define GRAPHICDLL_API __declspec(dllexport) 
#else
#define GRAPHICDLL_API __declspec(dllimport) 
#endif


#ifdef GRAPHICDLL_EXPORTS
#define _FUNCDLL_ extern "C" __declspec(dllexport) 
#else
#define _FUNCDLL_ extern "C" __declspec(dllimport) 
#endif



namespace GraphicAPI
{
	typedef struct stWindowConfig
	{
		int FPS;
		bool FullScreen;

	}stWindowConfig;

	typedef struct Pen_Color
	{
		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	} Pen_Color;


	//Pure virtual interface  graphic class
	//The pointer return by the library shall be cast into this type

	class IGraphicAPI
	{
	public:
		virtual long InitGraphic() = 0;
		virtual long CreateWind(char* Name, int Sizex, int Sizey) =0;
		virtual void SetConfig(stWindowConfig* pData) =0;
		virtual long RegisterImage(unsigned long& ImageId, char* ImageName) = 0;
		virtual long UnRegisterImage(unsigned long ImageId) = 0;
		//virtual 	long RegisterTile(unsigned long& ImageId, char* ImageName, int coordX, int coordY, int TileW, int TileH);
		virtual long DisplayImage(unsigned long Id, int x, int y, int Scale = 1) =0;
		virtual long DisplayTile(unsigned long Id, int destx, int desty, int srcx, int srcy, int TileSizeW, int TileSizeH,int Scale = 1) = 0;
		virtual void QueryTextureSize(unsigned long Id, int& W, int& H)=0;
		//Display string part
		virtual long RegisterFont(unsigned long& FontId, char* FontName) = 0;
		virtual long UnRegisterFont(unsigned long FontId) = 0;

		virtual long DisplayString(unsigned long Id, int x, int y, char* pString, Pen_Color* pColor) = 0;
		virtual void RenderScreen()=0;
		virtual void SetDisplayCursor(bool value) = 0;
	};

	//Interface function shall be load from host to get the IGraphic API pointer
	typedef IGraphicAPI* (*GETGRAPHICINTERFACE)();
	#define GETGRAPHICINTER_NAME "GetGraphicInterface"
	 _FUNCDLL_ IGraphicAPI* GetGraphicInterface();


}



#endif //_GRAPHIC_API_H_