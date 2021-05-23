#include "App.h"


//############  CONSTRUCTORS ############

Application::Application() {
	//here we initialize a module declared on the header, example: window = new ModuleWindow(this, true);
	window = new ModuleWindow(this,"moduleWindow", true);
	render = new ModuleRender(this, "moduleRender", true);
	
	dt = 0.01f;
	//then we add it to a list of modules in the order we want to print them
	
	AddModule(window);
	AddModule(render);
}

Application::~Application() {
	//destroy all modules here
}

//############  MAIN APP FUNCTIONS ############

bool Application::Init() {
	bool ret = true;
	
	p2List_item<Module*>* item = p_list_modules.getFirst();
	
	while (item != NULL && ret == true) { //init all modules
		ret = item->data->Init();
		item = item->next;
	}
	
	printf("Application Modules Init complete");

	item = p_list_modules.getFirst();
	
	while (item != NULL && ret == true){ //Start all modules
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

void Application::PrepareUpdate() {

}

update_status Application::Update() {

	update_status ret = update_status::UPDATE_CONTINUE;

	p2List_item<Module*>* item = p_list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate(dt);
		item = item->next;
	}

	item = p_list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->Update(dt);
		item = item->next;
	}

	item = p_list_modules.getFirst();

	while (item != NULL && ret == update_status::UPDATE_CONTINUE)
	{
		ret = item->data->PostUpdate(dt);
		item = item->next;
	}

	return ret;
}

void Application::FinishUpdate() {

}

bool Application::CleanUp() {

	bool ret = true;

	p2List_item<Module*>* item = p_list_modules.getLast(); 

	while (item != NULL && ret == true) { //will destroy from last to first (from the front to the back of the app)

		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;

}


//############  UTILITY FUNCTIONS ############

void Application::AddModule(Module* m) {
	p_list_modules.add(m);
}