#include "GraphicManager.h"
#include <Windows.h>
//#include <SDL_opengl.h>

//#include <gl\GLU.h>


#define ERROR_INIT -1


using namespace std;

CGraphicManager::CGraphicManager()
{
	m_Screen = NULL;
	m_Renderer = NULL;
	m_Font = NULL;

	m_bIsInitialized = false;
	m_bIsDebug = true;

	m_vecImage.clear();
	m_vecImage.clear();

	m_ulImageId = 1;
	m_ulFontId = 1;
	m_frameLimit = 0;

}

CGraphicManager::~CGraphicManager()
{
	m_Screen = NULL;
	m_Renderer = NULL;
	m_Font = NULL;

	m_bIsInitialized = false;
	m_bIsDebug = false;

	m_vecImage.clear();
	m_vecImage.clear();

	m_ulImageId = 0;
	m_ulFontId = 0;


	// Close font
	closeFont(m_Font);

	//Cleanup SDL renderer and screen
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Screen);

	// Close SDL_TTF 
	TTF_Quit();

	// Quitte la SDL 
	SDL_Quit();
}



long CGraphicManager::SDL_InitGraphic()
{

	//Read Data from ini file
	m_bIsDebug = GetPrivateProfileIntA("Graphic", "DebugOn", 0, "..//Config//GraphicConf.ini");


	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	return 0;
}

long CGraphicManager::SDL_CreateWin(char* Name, int Sizex, int Sizey)
{
	int imgFlags = IMG_INIT_PNG;

	m_Screen = SDL_CreateWindow(Name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Sizex, Sizey,
		SDL_WINDOW_SHOWN);

	m_Renderer = SDL_CreateRenderer(m_Screen, -1, SDL_RENDERER_PRESENTVSYNC);

	if (m_Screen == NULL || m_Renderer == NULL)
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Error Init screen %d x %d: %s\n", Sizex, Sizey, SDL_GetError());
		LOG_DEBUG(LogBuff);
		return ERROR_INIT;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//OpenGl staff
	/*glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	GLfloat ratio;


	ratio = (GLfloat)800 / (GLfloat)600;

	glViewport(0, 0, (GLsizei)800, (GLsizei)600);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "SDL_image Error: %s\n", IMG_GetError());
		LOG_DEBUG(LogBuff);
		return ERROR_INIT;
	}

	// Hide the cursor 
	SDL_ShowCursor(SDL_DISABLE);

	//Initialise SDL_TTF

	if (TTF_Init() < 0)
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
		LOG_DEBUG(LogBuff);
		return ERROR_INIT;
	}

	m_Font = loadFont("..//Font//GenBasB.ttf", 32);


	return 0;
}

void CGraphicManager::SDL_SetConfig(GraphicAPI::stWindowConfig* pData)
{
	
}

long CGraphicManager::SDL_RegisterImage(unsigned long& ImageId, char* ImageName)
{

	SDL_Surface* loadedImage = NULL;
	SDL_Texture* texture = NULL;
	loadedImage = IMG_Load(ImageName);

	if (loadedImage != NULL)
	{
		texture = SDL_CreateTextureFromSurface(m_Renderer, loadedImage);

		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;

		m_vecImage.push_back( make_pair (texture, m_ulImageId ) );
		ImageId = m_ulImageId;
		++m_ulImageId;
	}
	else
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Image could not be loaded SDL_Error :  %s\n", SDL_GetError());
		LOG_DEBUG(LogBuff);
		return -1;
	}


	return 0;
}

//Not use anymore
long CGraphicManager::SDL_RegisterTile(unsigned long& ImageId, char* ImageName, int coordX, int coordY, int TileW, int TileH)
{
	return 0;
}

long CGraphicManager::SDL_DisplayObject(unsigned long Id, int x, int y, int Scale)
{
	SDL_Rect dest;

	// draw regarding the image size
	dest.x = x;// *Scale;
	dest.y = y;// *Scale;
	SDL_Texture* image = GetSDLImage(Id);

	if (image)
	{
		SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
		dest.w *= Scale;
		dest.h *= Scale;
		SDL_RenderCopy(m_Renderer, image, NULL, &dest);

		return 0;
	}
	
	return -1;
}

long CGraphicManager::SDL_DisplayTile(unsigned long Id, int destx, int desty, int srcx, int srcy, int TileSizeW, int TileSizeH, int Scale)
{
	SDL_Rect dest;
	SDL_Rect src;

	SDL_Texture* image = GetSDLImage(Id);

	if (image)
	{
		dest.x = destx;
		dest.y = desty;
		dest.w = TileSizeW*Scale;
		dest.h = TileSizeH*Scale;

		src.x = srcx;
		src.y = srcy;
		src.w = TileSizeW;
		src.h = TileSizeH;

		// draw the tile to the coordinate x,y
		SDL_RenderCopy(m_Renderer, image, &src, &dest);
		return 0;
	}
	return -1;
}

long CGraphicManager::SDL_RegisterFont(unsigned long& FontId, char* FontName)
{
	TTF_Font* font = loadFont(FontName, 32);
	if (font)
	{
		m_vecFont.push_back(make_pair(font, m_ulFontId));
		return 0;
	}
	return -1;
}
long CGraphicManager::SDL_DisplayString(unsigned long Id, int x, int y, char* pString , GraphicAPI::Pen_Color* pColor)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color foregroundColor;
	foregroundColor.a = pColor->a;
	foregroundColor.r = pColor->r;
	foregroundColor.g = pColor->g;
	foregroundColor.b = pColor->b;


	TTF_Font* font = GetSDLFont(Id);

	// 
	if (font)
	{
		surface = TTF_RenderUTF8_Blended(font, pString, foregroundColor);

		if (surface != NULL)
		{
			//Convert from Image to Texture
			texture = SDL_CreateTextureFromSurface(m_Renderer, surface);


			SDL_FreeSurface(surface);
			surface = NULL;

			// draw on screen
			dest.x = x;
			dest.y = y;

			SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
			SDL_RenderCopy(m_Renderer, texture, NULL, &dest);

			
			if (texture) SDL_DestroyTexture(texture);

			return 1;

		}
		else
		{
			char LogBuff[256] = { 0 };
			sprintf_s(LogBuff, "Error drawString: %s: %s\n", pString, TTF_GetError());
			LOG_DEBUG(LogBuff);

		}
	}
	

	return -1;
}


//Font method
TTF_Font* CGraphicManager::loadFont(char *name, int size)
{
	// Use SDL_TTF to load the font at the specified size 

	TTF_Font *font = TTF_OpenFont(name, size);

	if (font == NULL)
	{
		char LogBuff[256] = { 0 };
		sprintf_s(LogBuff, "Failed to open Font %s: %s\n", name, TTF_GetError());
		LOG_DEBUG(LogBuff);
		return NULL;
	}

	return font;
}


void CGraphicManager::closeFont(TTF_Font *font)
{
	/* Close the font once we're done with it */

	if (font != NULL)
	{
		TTF_CloseFont(font);
	}
}

SDL_Texture* CGraphicManager::GetSDLImage(unsigned long Id)
{
	SDL_Texture* pTexture = NULL;
	if (Id < m_ulImageId)
	{
		//Seaching the SDL texture pointer
		vector < pair < SDL_Texture*, unsigned long> >::iterator l_itor = m_vecImage.begin();
		for (int i = 0; i<m_ulImageId;++i)
		{
			if (l_itor->second == Id)
			{
				pTexture =(SDL_Texture*) (l_itor)->first;
				break;
			}
			++l_itor;
		}
		
	}
	return pTexture;
}

TTF_Font* CGraphicManager::GetSDLFont(unsigned long Id)
{
	TTF_Font* pFont = NULL;
	if (Id < m_ulFontId)
	{
		//Seaching the SDL texture pointer
		pFont = m_vecFont[Id].first;
	}
	return pFont;
}

void CGraphicManager::SDL_RenderScreen()
{
	SDL_RenderPresent(m_Renderer);
	SDL_Delay(1);

	Delay(m_frameLimit);
	m_frameLimit = SDL_GetTicks() + 16;
}

void CGraphicManager::SDL_QueryTextureSize(unsigned long Id, int& W, int& H)
{
	SDL_QueryTexture(GetSDLImage(Id), NULL, NULL, &W, &H);
}

void CGraphicManager::Delay(unsigned int frameLimit)
{

	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}


void CGraphicManager::SDL_SetDisplayCursor(bool value)
{
	SDL_ShowCursor((value)?SDL_ENABLE:SDL_DISABLE);
}


long CGraphicManager::SDL_UnRegisterFont(unsigned long FontId)
{
	return -1;
}

long CGraphicManager::SDL_UnRegisterImage(unsigned long ImageId)
{
	if (ImageId < m_ulImageId)
	{
		//Seaching the SDL texture pointer
		vector < pair < SDL_Texture*, unsigned long> >::iterator l_itor = m_vecImage.begin();
		for (int i = 0; i<m_ulImageId; ++i)
		{
			if (l_itor->second == ImageId)
			{
				SDL_DestroyTexture((SDL_Texture*)(l_itor)->first);
				m_vecImage.erase(l_itor);
				return 0;
			}
			++l_itor;
		}

	}
	return -1;
}

