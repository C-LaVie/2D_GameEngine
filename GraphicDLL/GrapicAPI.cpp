#include "GraphicAPI.h"

#include <iostream>

#include "GraphicInterface.h"

CGraphic* pManager = NULL;

namespace GraphicAPI
{

	////////////////////////////////////////////////////////////////////////////
	IGraphicAPI* GetGraphicInterface()
	{
		if (pManager == NULL)
		{
			pManager = new CGraphic;
		}

		return (IGraphicAPI*)pManager;
	}
}

