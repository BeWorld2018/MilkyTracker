#include "project.h"
#include "amigaversion.h"
#include "PlayerMaster.h"
#include "PlayerController.h"

#include <libraries/mui.h>
#include <proto/muimaster_lib.h>

#include <exec/types.h>
#include <utility/tagitem.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <clib/alib_protos.h>
#include <stdlib.h>
#include <stdio.h>
#define MILKYTRACKER 1
#include <MilkyPlay.h>
#include <XModule.h>
#include <SDL.h>

int main(int argc,char *argv[])
{
	Object *app,*win1, *rootObj;
	ULONG signals;
	BOOL running = TRUE;

	if (!Open_Libs())
	{
		printf("Cannot open libs\n");
		return(0);
	}

	rootObj = MUI_NewObject(MUIC_Group,
		MUIA_Group_Child, (ULONG)(MUI_NewObject(MUIC_Text,
			MUIA_Text_Contents, (ULONG)"MilkyPlayer",
			TAG_END)),
		MUIA_Group_Child, (ULONG)(MUI_NewObject(MUIC_Framedisplay,
			MUIA_FrameTitle, (ULONG)"MilkyPlayer",
			TAG_END)),
		TAG_END);
	
	win1 = MUI_NewObject(MUIC_Window,
						 MUIA_Window_Title, (ULONG)"MilkyPlayer",
						 MUIA_Window_SizeGadget, FALSE,
						 MUIA_Window_RootObject, (ULONG)(rootObj),
						 TAG_END);
	
	app = MUI_NewObject(MUIC_Application,
						MUIA_Application_Author, (ULONG)"AmigaDev Team",
						MUIA_Application_Base, (ULONG)"MilkyPlayer",
						MUIA_Application_Copyright, (ULONG)"© 2020 Marlon Beijer",
						MUIA_Application_Description, (ULONG)"MilkyPlayer in MUI.",
						MUIA_Application_Title, (ULONG)"MilkyPlayer",
						MUIA_Application_Version, (ULONG)amiga_ver,
						MUIA_Application_Window, (ULONG)(win1),
						TAG_END);

	if (!app)
	{
		printf("Cannot create application.\n");
		return(0);
	}
	SDL_Init( SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);

	XModule *module = new XModule();
	PlayerMaster *master = new PlayerMaster();
	Printf("Driver: %s\n", (ULONG)master->getCurrentDriverName());
	master->setCurrentDriverByName(master->getFirstDriverName());
	Printf("Driver: %s\n", (ULONG)master->getCurrentDriverName());
	PlayerController *controller = master->createPlayerController(true);
	
	module->loadModule("test.mod");
	//while (!module->isModuleLoaded())
	//	Printf("test2\n");
	
	controller->attachModuleEditor(module);

	Printf("test3\n");
	controller->playSong(0,0,0);

	Printf("test4\n");
	controller->continuePlaying();
	controller->resumePlayer(true);
	
	DoMethod(win1, MUIM_Notify, MUIA_Window_CloseRequest, TRUE,
			 app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

	SetAttrs(win1, MUIA_Window_Open, TRUE, TAG_DONE);

	while(running)
	{
		ULONG id = DoMethod(app,MUIM_Application_Input,&signals);

		switch(id)
		{
			case MUIV_Application_ReturnID_Quit:
				module->loadModule("test.mod");
				controller->playSong(0,0,0);
				controller->continuePlaying();
				controller->resumePlayer(true);
				if((MUI_RequestA(app,0,0,"Quit?","_Yes|_No","\33cAre you sure?",0)) == 1)
					running = FALSE;
				break;
		}
		if(running && signals) Wait(signals);
	}

	SetAttrs(win1,MUIA_Window_Open,FALSE);

	if(app) MUI_DisposeObject(app);
	delete master;
	Close_Libs();
	exit(EXIT_SUCCESS);
}