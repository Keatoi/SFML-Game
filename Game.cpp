#include "Game.h"

void Game::InitVariables()
{
	this->Window = nullptr;
	this->score = 0;
	this->maxEnemies = 100;
	this->spawnCount = 1;
}

void Game::InitWindow()
{
	this->VidMode.height = 720;
	this->VidMode.width = 480;
	this->Window = new sf::RenderWindow(this->VidMode, "Test", sf::Style::Titlebar | sf::Style::Close);
	this->Window->setFramerateLimit(30);
}

void Game::InitTextures()
{
	//initialise textures into the map here
	this->Textures["BULLET"] = new sf::Texture();
	this->Textures["BULLET"]->loadFromFile("Textures/Bullet.png");
	if (!this->Textures["BULLET"]->loadFromFile("Textures/Bullet.png"))
		std::cout << "Failed to load bullet texture!\n";
}

void Game::InitEnemies()
{
	this->spawnTimerMax = 15.f;
	this->spawnTimer = spawnTimerMax;
	
}

void Game::InitPlayer()
{
	//Create a new player object and teleport to middle of screen
	this->player = new Player();
	this->player->teleport(this->Window->getSize().x / static_cast<float>(2), this->Window->getSize().x / static_cast<float>(2));
	
}

void Game::InitGUI()
{
	//Load Font
	this->font.loadFromFile("Fonts/gameFont.ttf");
	//Init Score Text;
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(12);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("Score Test");


}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitGUI();
	this->InitTextures();
	this->InitPlayer();
	this->InitEnemies();
}

Game::~Game()
{
	//prevent mem leak
	delete this->Window;
	delete this->player;
	//go through and delete every texture in the map
	for (auto& i : this->Textures)
	{
		delete i.second;
	}
	
}
const bool Game::Running()
{
	return this->Window->isOpen();
}
void Game::EventUpdate()
{
	//Event Polling (while window is still recieving events)
	while (this->Window->pollEvent(this->EV))
	{
		switch (this->EV.type)
		{
			//Close Game Window via exit button and ESC
		case sf::Event::Closed:
			this->Window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->EV.key.code == sf::Keyboard::Escape) this->Window->close();
			break;
		}
	}
}
//FUNCTIONS
void Game::update()
{
	this->EventUpdate();
	//update mouse Pos relative to window
	//std::cout << "Mouse Pos ( " << sf::Mouse::getPosition(*this->Window).x << " , " << sf::Mouse::getPosition(*this->Window).y << " ) \n";
	mousePos = sf::Mouse::getPosition(*this->Window);
	this->updateInput();
	this->updatePhysics();
	this->player->Update(deltaTime.asSeconds());
	//this->player->LookAtMouse(*this->Window);
	this->updateEnemies();
	this->updateBattle();
	this->updateGUI();
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->player->Move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->player->Move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) this->player->Move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) this->player->Move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->bCanAttack())
	{
		//create new projectile GameObject, requires a texture,texture scale, Origin X & Y, Direction X & Y and Movement Speed
		
		this->Projectiles.push_back(std::make_unique<Bullet>(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + this->player->getBounds().width /2 , player->getPos().y, 0.f, -1.f, 15.f));
		//this->Projectiles.push_back(new Bullet(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + 15.f, player->getPos().y, 0.f, -1.f, 5.f));
		//std::cout << "Bullet created, projectiles count: " << this->Projectiles.size() << std::endl;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->bCanAttack())
	{
		this->Projectiles.push_back(std::make_unique<Bullet>(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + this->player->getBounds().width / 2, player->getPos().y, 0.f, 1.f, 5.f));
	}
}

void Game::updatePhysics()
{
	
	for (auto pr = Projectiles.begin(); pr != Projectiles.end();)
	{
		//dereference the unique ptr and call the update method
		(*pr)->update();
		//Out of bounds culling (top of screen)

		if ((*pr)->getBounds().top + (*pr)->getBounds().height < 0.f)
		{
			
			pr = this->Projectiles.erase(pr);
			
		}
		else
		{
			pr++;
		}
		
	}
	//check if player is out of bounds
	//Bottom
	if (this->player->getBounds().top > this->Window->getSize().y)
	{
		this->player->sprite.setPosition(this->player->getPos().x, 0);
	}
	//Right
	if (this->player->getBounds().left > this->Window->getSize().x)
	{
		this->player->sprite.setPosition(0,this->player->getPos().y);
	}
}

void Game::spawnEnemyGroup(int count)
{
	//Position the group somewhere in the window with a 30 pixel margin on each side
	float posX = rand() % (this->Window->getSize().x - 60) + 30.f;
	for (size_t i = 0; i < count; i++)
	{
		float phase = i * 0.5f;
		//spawn each member of the group 40 pixels apart
		float y = -1.f - (i * 40.f);
		this->enemies.push_back(std::make_unique<Enemy>(0, 0.3f, 0.3f, posX, y,20.f,0.02f,i * 0.5));
		enemyCount++;
	}
}

void Game::updateEnemies()
{
	//Spawning
	spawnTimer += 0.1f;
	if (this->spawnTimer >= this->spawnTimerMax )
	{
		spawnEnemyGroup(spawnCount);
		this->spawnTimer = 0.f;//reset spawntimer back down to 0;
		spawnCount *= 2;
	}
	if (enemyCount >= maxEnemies)
	{
		//start new wave
		spawnCount, enemyCount,spawnTimer = 0.f;
		//slightly increase diff
		spawnTimerMax = std::max(0.5f, spawnTimerMax -= 0.5f);
		//TODO New Wave Transition

	}
	//update
	
	for (auto AI = enemies.begin(); AI != enemies.end();)
	{
		(*AI)->update(deltaTime);
		//Out of bounds culling (top of screen)

		if ((*AI)->getBounds().top > this->Window->getSize().y)
		{
			
			AI = enemies.erase(AI);
			
		}
		else
		{
			AI++;
		}
		
	}
	
	
}

void Game::updateBattle()
{
	for (auto ai = enemies.begin(); ai != enemies.end();)
	{
		bool enemyKill = false;
		for (auto pr = Projectiles.begin(); pr != Projectiles.end() && !enemyKill;)
		{
			if ((*ai)->getBounds().intersects((*pr)->getBounds()))
			{
				this->score += (*ai)->getPoints();
				//erase both the ai and projectile. Smart ptr so no manual deletion required.
				
				ai = enemies.erase(ai);
				
				pr = Projectiles.erase(pr);
				enemyKill = true;
			}
			else
			{
				pr++;
			}
			
		}
		if (!enemyKill)
		{
			if (this->player->getBounds().intersects((*ai)->getBounds()))
			{
				//do damage or something
			}
			ai++;
		}
		

	}

}

void Game::updateGUI()
{
	std::string scoreString = std::to_string(score);
	this->scoreText.setString(scoreString);
}

void Game::render()
{
	this->Window->clear(sf::Color::Black);//Clear last frame
	/*++++++++++++++++
	+++DRAW OBJ++++++++
	+++++++++++++++++++*/
	//this->Window->draw(TestEnemy);
	this->player->Render(*this->Window);
	for (const auto& i : this->Projectiles)
	{
		std::cout << "rendering bullet";
		i->render(this->Window);
	}
	for (const auto& i : this->enemies)
	{
		i->render(this->Window);
	}
	this->renderGUI();
	this->Window->display();//Send frame to display
}

void Game::renderGUI()
{
	this->Window->draw(this->scoreText);
}

void Game::run()
{
	sf::Clock deltaClock;
	while (Running())
	{
		update();
		render();
		deltaTime = deltaClock.restart();
	}
}
