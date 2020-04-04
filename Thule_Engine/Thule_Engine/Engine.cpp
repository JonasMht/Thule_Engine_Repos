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
    unsigned char antialiasingLevel = 0;
    bool vertical_sync_enabled = false;

    if (ifs.is_open())
    {
        // copy window.init data
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> antialiasingLevel;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();

    this->settings.antialiasingLevel = antialiasingLevel;

	this->window = new sf::RenderWindow(window_bounds, title,sf::Style::Default, this->settings);
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
    this->states.push(new GameState(this->window, &this->supportedKeys)); // will add a new state
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
    //Should save here!
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
        /*Moste likely event to the least likeliest event - top to bottom*/
        if (this->event.type == sf::Event::Closed)
            this->window->close();
        else if (this->event.type == sf::Event::MouseWheelScrolled)
        {
            this->states.top()->onMouseScroll(event.mouseWheelScroll.delta, this->delta);
        }
        else if (this->event.type == this->event.MouseButtonPressed)
        {
            if (this->event.mouseButton.button == sf::Mouse::Right)
                this->states.top()->onMouseRightClick();
            else if (this->event.mouseButton.button == sf::Mouse::Left)
                this->states.top()->onMouseLeftClick();
            else if (this->event.mouseButton.button == sf::Mouse::Middle)
                this->states.top()->onMouseMiddleClick();
        }
        else if (this->event.type == this->event.MouseButtonReleased)
        {
            if (this->event.mouseButton.button == sf::Mouse::Right)
                this->states.top()->onMouseRightRelease();
            else if (this->event.mouseButton.button == sf::Mouse::Left)
                this->states.top()->onMouseLeftRelease();
            else if (this->event.mouseButton.button == sf::Mouse::Middle)
                this->states.top()->onMouseMiddleRelease();
        }
        else if (event.type == sf::Event::Resized)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
            this->window->setView(sf::View(visibleArea));
            this->states.top()->onWindowResize();
            //DEBUG : REMOVE LATER
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
            //GameState should save here
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