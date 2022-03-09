#ifndef _GRAPHIC_MANAGER_H_
#define _GRAPHIC_MANAGER_H_
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GraphicAPI.h"

class CGraphicManager
{
	public:
		CGraphicManager();
		~CGraphicManager();

		long SDL_InitGraphic();
		long SDL_CreateWin(char* Name, int Sizex, int Sizey);
		void SDL_SetConfig(GraphicAPI::stWindowConfig* pData);
		long SDL_RegisterImage(unsigned long& ImageId, char* ImageName);

		long SDL_RegisterTile(unsigned long& ImageId, char* ImageName, int coordX, int coordY, int TileW, int TileH);
		long SDL_DisplayObject(unsigned long Id, int x, int y, int Scale = 1);
		long SDL_DisplayTile(unsigned long Id, int destx, int desty, int srcx, int srcy, int TileSizeW, int TileSizeH, int Scale = 1);
	//	bool GetIsInit() { return m_bIsInitialized; };

		long SDL_RegisterFont(unsigned long& FontId, char* FontName);
		long SDL_DisplayString(unsigned long Id, int x, int y, char* pString , GraphicAPI::Pen_Color* pColor);

		void SDL_RenderScreen();
		void SDL_QueryTextureSize(unsigned long Id, int& W, int& H);
		void SDL_SetDisplayCursor(bool value);

		long SDL_UnRegisterFont(unsigned long FontId);
		long SDL_UnRegisterImage(unsigned long ImageId);
	private:

		SDL_Window* m_Screen;
		SDL_Renderer* m_Renderer;
		TTF_Font* m_Font;

		//Font related
		TTF_Font *loadFont(char *name, int size);
		void closeFont(TTF_Font *font);
		void Delay(unsigned int frameLimit);
		void LoadConfig();
	//	void Delay(unsigned int frameLimit);

		bool m_bIsInitialized;
		bool m_bIsDebug;

		unsigned long m_ulImageId;
		unsigned long m_ulFontId;

		std::vector < std::pair <SDL_Texture*, unsigned long> > m_vecImage;
		std::vector < std::pair <TTF_Font*, unsigned long> > m_vecFont;

		SDL_Texture* GetSDLImage(unsigned long Id);
		TTF_Font* GetSDLFont(unsigned long Id);

		unsigned long m_frameLimit;
};


#define LOG_DEBUG(a) \
	if(m_bIsDebug) std::cout << a << std::endl;

#endif //_GRAPHIC_MANAGER_H_