#include "Globals.h"
#include "App.h"



#include "SDL2/include/SDL.h"
#pragma comment(lib,"SDL2/lib/x64/SDL2.lib")
#pragma comment(lib,"SDL2/lib/x64/SDL2.lib")

enum main_states {
	CREATION,
	START,
	UPDATE,
	FINISH,
	EXIT
};

Application* App = NULL;

int main(int argc, char** argv) {

	int funcReturn = EXIT_FAILURE;
	main_states state = CREATION;

	while (state != EXIT) {
		switch (state) {
		case CREATION:
		
			App = new Application();
			state = START;
			break;

		case START:		
			
			if (App->Init() == false)
			{
				printf("Application Init exits with ERROR");
				state = EXIT;
			}
			else {
				state = UPDATE;
			}
			break;

		case UPDATE:
		{
			update_status update_stat = App->Update();

			if (update_stat == update_status::UPDATE_STOP) {
				printf("_____!_____Application Stop  _____!_____");
				state = main_states::EXIT; //--------------------------------when app stop how do i resume the app?
			}
			else if (update_stat == update_status::UPDATE_ERROR) {
				printf("_____!_____Application Error  _____!_____");
				state = main_states::FINISH;
			}

			break;
		}
		case FINISH:
			printf("_____!_____Application Finish  _____!_____");

			if (App->CleanUp() == false) {
				printf("_____!_____Application Finish ERROR  _____!_____");
			}
			else {
				funcReturn = EXIT_SUCCESS;
			}
			break;
		}

		

	}
	printf("APPLICATION RETURN IS        '%i'", funcReturn);
	return funcReturn;
}