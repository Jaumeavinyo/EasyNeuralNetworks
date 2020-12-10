#include "Globals.h"


enum main_states {
	CREATION,
	START,
	UPDATE,
	FINISH,
	EXIT
};

int main(int argc, char** argv) {

	int funcReturn = EXIT;
	main_states state = CREATION;

	while (state != EXIT) {
		switch (state) {
		case CREATION:
			printf("__________Application Creation__________");
			//TODO create new app
			state = START;
			break;

		case START:
			break;

		case UPDATE:
			break;

		case FINISH:
			break;

		
		}

		

	}

	return funcReturn;
}