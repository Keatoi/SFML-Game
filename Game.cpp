#include "Game.h"

void Game::InitVariables()
{
	this->Window = nullptr;
	this->score = 0;
	this->maxEnemies = 20;
	this->spawnCount = 1;
}

void Game::InitWindow()
{
	this->VidMode.height = 720;
	this->VidMode.width = 480;
	this->Window = new sf::RenderWindow(this->VidMode, "Aether-Ace Build 19", sf::Style::Titlebar | sf::Style::Close);
	this->Window->setFramerateLimit(30);
}

void Game::InitTextures()
{
	//initialise textures into the map here
	this->Textures["BULLET"] = new sf::Texture();
	this->Textures["BULLET"]->loadFromFile("Textures/Bullet.png");
	this->Textures["BOMB"] = new sf::Texture();
	this->Textures["BOMB"]->loadFromFile("Textures/Bomb.png");
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
	//Init HP text
	this->HPText.setFont(this->font);
	this->HPText.setCharacterSize(12);
	this->HPText.setFillColor(sf::Color::Green);
	//Init wave text
	this->waveCount = 1;
	this->WaveText.setFont(this->font);
	this->WaveText.setCharacterSize(12);
	this->WaveText.setFillColor(sf::Color::White);
	this->WaveText.setString("Wave: " + std::to_string(waveCount));
	this->WaveText.setPosition(0, 10);
	//Init MenuText
	this->MenuText.setFont(this->font);
	this->MenuText.setCharacterSize(18);
	this->MenuText.setFillColor(sf::Color::Red);
	this->MenuText.setOutlineColor(sf::Color::White);
	this->MenuText.setString("Press ENTR to Start or ESC to Quit");
	this->MenuText.setPosition(this->Window->getSize().x / 8, this->Window->getSize().y / 2);
	//Init GameOver Title Text
	this->GETitle.setFont(this->font);
	this->GETitle.setCharacterSize(32);
	this->GETitle.setFillColor(sf::Color::Red);
	this->GETitle.setString("Game End");
	this->GETitle.setPosition(this->Window->getSize().x / 4, this->Window->getSize().y / 4);
	//Init Game Over Score Text
	this->GEScore.setFont(this->font);
	this->GEScore.setCharacterSize(24);
	this->GEScore.setFillColor(sf::Color::White);
	this->GEScore.setPosition(this->Window->getSize().x / 4, this->Window->getSize().y / 3);
	//Init GO Exit Text
	this->GEQuit.setFont(this->font);
	this->GEQuit.setCharacterSize(18);
	this->GEQuit.setFillColor(sf::Color::Red);
	this->GEQuit.setString("Press ESC to quit or ENTR to Restart");
	this->GEQuit.setPosition(this->Window->getSize().x / 8, (this->Window->getSize().y / 2) + 10);
}

void Game::InitSound()
{
	SM.loadSound("AIDeath", "Audio/Enemy_Death.wav");
	SM.playMusic("Audio/BGMMenu.wav");
}

Game::Game()
{
	this->InitVariables();
	this->InitWindow();
	this->InitGUI();
	this->InitTextures();
	this->InitPlayer();
	this->InitEnemies();
	this->InitSound();
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
			if (this->EV.key.code == sf::Keyboard::Escape) Window->close();
			break;
		}
	}
}
//FUNCTIONS
void Game::update()
{
	switch (currState)
	{
	case GameState::EMENU:
		updateMenu();
		break;
	case GameState::EGAME:
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
		break;
	case GameState::EOVER:
		updateEnd();
			break;
	}
	if (score <= -100.f)
	{
		SM.stopMusic();
		SM.playMusic("Audio/BGMMenu.wav");
		currState = GameState::EOVER;
	}
}

void Game::updateMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		//Stop music, switch to gameplay state and the start the in-game music track
		SM.stopMusic();
		this->currState = GameState::EGAME;
		SM.playMusic("Audio/BossWave.wav");
	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->bCanAttack())
	{
		this->Bombs.push_back(std::make_unique<Bomb>(this->Textures["BOMB"], 0.5f, 0.5f, player->getPos().x + this->player->getBounds().width / 2, player->getPos().y, 0.f, 1.f));
		
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
	for (auto bm = Bombs.begin(); bm != Bombs.end();)
	{
		(*bm)->update(deltaTime.asSeconds());
		if ((*bm)->isExploded())
		{
			sf::Vector2f BombPos = (*bm)->getPosition();
			float rad = (*bm)->getBlastRadius();
			for (auto em = enemies.begin(); em != enemies.end();)
			{
				float dist = distance((*em)->getPos(), (*bm)->getPosition());
				if (dist < rad)
				{
					em = enemies.erase(em);
				}
				else
				{
					em++;
				}
			}
			bm = this->Bombs.erase(bm);
			
		}
		else
		{
			bm++;
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
	// Left
	if (this->player->getBounds().left + this->player->getBounds().width < 0)
	{
		this->player->sprite.setPosition(this->Window->getSize().x, this->player->getPos().y);
	}
	// Top
	if (this->player->getBounds().top + this->player->getBounds().height < 0)
	{
		this->player->sprite.setPosition(this->player->getPos().x, this->Window->getSize().y);
	}

}

void Game::spawnEnemyGroup(int count)
{
	//Position the group somewhere in the window with a 45 pixel margin on each side
	float posX = rand() % (this->Window->getSize().x - 90) + 45.f;
	for (size_t i = 0; i < count; i++)
	{
		float phase = i * 0.5f;
		//spawn each member of the group 40 pixels apart
		float y = -1.f - (i * 40.f);
		this->enemies.push_back(std::make_unique<Enemy>(0, 0.3f, 0.3f, posX, y,20.f,0.02f,i * 0.5));
		
		
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
		spawnCount *= 2.f;
	}
	if (enemyCount >= maxEnemies)
	{
		//start new wave
		waveCount++;
		spawnCount = 1.f;
		enemyCount = waveCount;
		spawnTimer = 0.f;
		maxEnemies *= 2;
		//slightly increase diff
		spawnTimerMax = std::max(0.5f, spawnTimerMax -= 0.1f);
		//TODO New Wave Transition
		std::cout << "AI MAX: " << maxEnemies << std::endl;
		this->WaveText.setString("Wave: " + std::to_string(waveCount));
		enemies.clear();

	}
	//update
	//Update every current enemy entity
	for (auto AI = enemies.begin(); AI != enemies.end();)
	{
		//call their update function
		(*AI)->update(deltaTime);
		//Out of bounds culling 

		if ((*AI)->getBounds().top > this->Window->getSize().y)
		{
			
			AI = enemies.erase(AI);
			score -= 10;
			
			
		}
		else
		{
			AI++;
		}
		
	}
	
	
}

void Game::WaveTransition()
{
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
				SM.playSound("AIDeath");
				pr = Projectiles.erase(pr);
				enemyKill = true;
				enemyCount++;
				std::cout << "AI Dead: " << enemyCount << std::endl;
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
				this->HPText.setString(std::to_string(this->player->OnHit(10.f)));
				if (this->player->GetHP() <= 0.f)
				{
					
					//End Game
					currState = GameState::EOVER;
					SM.stopMusic();
					SM.playMusic("Audio/BGMMenu.wav");
				}
				
			}
			ai++;
		}
		

	}

}

void Game::updateGUI()
{
	std::string scoreString = std::to_string(score);
	this->scoreText.setString(scoreString);
	this->HPText.setPosition(this->player->getPos().x, this->player->getPos().y + 1.f);
	
}

void Game::updateEnd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->Window->close();
}

void Game::renderMenu()
{
	this->Window->draw(this->MenuText);

}

void Game::renderGame()
{
	this->player->Render(*this->Window);
	for (const auto& i : this->Projectiles)
	{
		//std::cout << "rendering bullet";
		i->render(this->Window);
	}
	for (const auto& i : this->enemies)
	{
		i->render(this->Window);
	}
	for (const auto& i : this->Bombs)
	{
		i->render(this->Window);
	}
	this->renderGUI();
}

void Game::RenderEnd()
{
	//Get Final Score
	this->GEScore.setString("Final Score: " + std::to_string(score));
	this->Window->draw(this->GETitle);
	this->Window->draw(this->GEScore);
	this->Window->draw(this->GEQuit);
}

void Game::render()
{
	this->Window->clear(sf::Color::Black);//Clear last frame
	/*++++++++++++++++
	+++DRAW OBJ++++++++
	+++++++++++++++++++*/
	
	switch (currState)
	{
	case(GameState::EMENU):
		renderMenu();
		break;
	case(GameState::EGAME):
		renderGame();
		break;
	case(GameState::EOVER):
		RenderEnd();
		break;
	}
	
	this->Window->display();//Send frame to display
}

void Game::renderGUI()
{
	this->Window->draw(this->scoreText);
	this->Window->draw(this->HPText);
	this->Window->draw(this->WaveText);
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

void Game::restart()
{
	this->score = 0;
	this->maxEnemies = 20;
	this->spawnCount = 1;
	currState = GameState::EMENU;
	SM.stopMusic();
	SM.playMusic("Audio/BGMMenu.wav");
}
