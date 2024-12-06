#include "Game.h"

void Game::InitVariables()
{
	this->Window = nullptr;
}

void Game::InitWindow()
{
	this->VidMode.height = 480;
	this->VidMode.width = 640;
	this->Window = new sf::RenderWindow(this->VidMode, "Test", sf::Style::Titlebar | sf::Style::Close);
	this->Window->setFramerateLimit(30);
}

void Game::InitTextures()
{
	//initialise textures into the map here
	this->Textures["BULLET"] = new sf::Texture();
	this->Textures["BULLET"]->loadFromFile("Textures/Bullet.png");
}

void Game::InitEnemies()
{
	this->spawnTimerMax = 20.f;
	this->spawnTimer = spawnTimerMax;
	
}

void Game::InitPlayer()
{
	//Create a new player object
	this->player = new Player();
	
}

void Game::InitGUI()
{
	//Load Font
	this->font.loadFromFile("Font/VCR_OSD_MONO_1.001.tff");
	//Init Score Text;
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(12);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("Score Text");


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
	for (auto *i : this->Projectiles)
	{
		delete i;
	}
	for (auto* i : this->enemies)
	{
		delete i;
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
	this->player->Update();
	this->updateEnemies();
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
		this->Projectiles.push_back(new Bullet(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + this->player->getBounds().width /2 , player->getPos().y, 0.f, -1.f, 5.f));
		//this->Projectiles.push_back(new Bullet(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + 15.f, player->getPos().y, 0.f, -1.f, 5.f));
		
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->player->bCanAttack())
	{
		this->Projectiles.push_back(new Bullet(this->Textures["BULLET"], 0.5f, 0.5f, player->getPos().x + this->player->getBounds().width / 2, player->getPos().y, 0.f, 1.f, 5.f));
	}
}

void Game::updatePhysics()
{
	unsigned counter = 0;
	for (auto* projectile : this->Projectiles)
	{
		projectile->update();
		//Out of bounds culling (top of screen)

		if (projectile->getBounds().top + projectile->getBounds().height < 0.f)
		{
			delete this->Projectiles.at(counter);
			this->Projectiles.erase(this->Projectiles.begin() + counter);
			counter--;
		}
		counter++;
	}
	
}

void Game::updateEnemies()
{
	//Update enemy pos, spawning and handle combat

	spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(0, 0.3f, 0.3f, rand() % this->Window->getSize().x - 30.f , -100.f));
		this->spawnTimer = 0.f;//reset spawntimer back down to 0;
	}

	for (int i = 0; i < enemies.size();i++)
	{
		bool enemyKill = false;
		//update current enemys
		this->enemies[i]->update();
		for (size_t j = 0; j < this->Projectiles.size() && !enemyKill; j++ )
		{
			
			if (this->Projectiles[j]->getBounds().intersects(this->enemies[i]->getBounds()))
			{
				// if the bullet and enemy sprite intersect cull the enemy
				
				this->Projectiles.erase(this->Projectiles.begin() + j);
				this->enemies.erase(this->enemies.begin() + i);
				
				enemyKill = true;
				
			}
		}
		//check if below cull line by checking if the top of the enemy sprite is outside the window
		if (this->enemies[i]->getBounds().top > this->Window->getSize().y && !enemyKill)
		{
			//delete this->enemies.at(i);
			this->enemies.erase(this->enemies.begin() + i);
			enemyKill = true;
		}

	}
	
	
}

void Game::render()
{
	this->Window->clear(sf::Color::Black);//Clear last frame
	/*++++++++++++++++
	+++DRAW OBJ++++++++
	+++++++++++++++++++*/
	//this->Window->draw(TestEnemy);
	this->player->Render(*this->Window);
	for (auto* i : this->Projectiles)
	{
		i->render(this->Window);
	}
	for (auto* i : this->enemies)
	{
		i->render(this->Window);
	}
	this->Window->display();//Send frame to display
}

void Game::run()
{
	while (Running())
	{
		update();
		render();
	}
}
