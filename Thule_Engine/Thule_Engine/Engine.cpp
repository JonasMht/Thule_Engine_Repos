#include "Engine.h"

/*Static functions*/

/*Initializer functions*/
void Engine::initWindow()
{
    //Create a SFML window using options from the window.ini file

    std::ifstream ifs("Config/window.ini");
    
    std::string title = "Thule Engine";
    sf::VideoMode window_bounds(800,600); //base opening window bounds
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;


    if (ifs.is_open())
    {
        // copy window.init data
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

	this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);


}

void Engine::initKeys()
{

    //init supported keys from supported_keys.ini file
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key_name;
        int key_value;

        while (ifs >> key_name >> key_value)
        {
            this->supportedKeys[key_name] = key_value;
        }
    }
    ifs.close();

    //DEBUG -> REMOVE LATER

    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }

}

void Engine::initStates()
{
    //this->states.push(new MainMenuState(this->window, &this->supportedKeys)); // will add a new state
    this->states.push(new EngineState(this->window, &this->supportedKeys)); // will add a new state
}

/*Constructors Destructors*/

Engine::Engine() //Constructor
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Engine::~Engine() //Destructor
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top(); // remove all states
        this->states.pop();
    }
}

/*Functions*/

void Engine::endApplication()
{
    std::cout << "Ending Application\n";

}

void Engine::updateDelta()
{
    //Update the delta variable with the time one frame takes (all updates).
    this->delta = this->deltaClock.restart().asSeconds();
}

void Engine::updateEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();

        //Test for mouse scroll
        if (this->event.type == sf::Event::MouseWheelMoved)
        {
            this->states.top()->onMouseScroll(event.mouseWheel.delta, this->delta);
        }
        if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            this->window->setView(sf::View(visibleArea));
            this->states.top()->onWindowResize();
            std::cout << "window resize\n";
        }
    }
}

void Engine::update()
{
    this->updateEvents();

    if (!this->states.empty()) //The top state gets update
    {
        this->states.top()->update(this->delta);

        if (this->states.top()->getQuitState())
        {
            //could save here!
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        //Application end
        this->endApplication();
        this->window->close();
    }
}

void Engine::render()
{
    this->window->clear(sf::Color::Black);
    
    //Render items
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Engine::run()
{
    while (this->window->isOpen())
    {
        this->updateDelta();
        this->update();
        this->render();
    }
}