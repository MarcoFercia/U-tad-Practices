
#include "logica.h"
#include "render.h"
#include "Timer.h"
#include "sys.h"
#include "core.h"


LogicManager* LogicManager::pManager = nullptr;
RenderEngine* RenderEngine::pRenderEngine = nullptr;



extern LogicManager* MLogic;
extern RenderEngine* RenderEn;

 
int Main(void)
{	
	RenderEn->initRender();
	MLogic->initLogic();
	
  
	while (!SYS_GottaQuit()) // Controlling a request to terminate an application.
	{
		
		
		MLogic->LogicSlot();
	
		RenderEn->RenderGame();
			
		// Exchanges the front and back buffers
		SYS_Show();
		SYS_Pump();	// Process Windows messages.
		//SYS_Sleep(17);	// To force 60 fps
		
	}
	
	RenderEn->shutdownrender();

	return 0;
}






