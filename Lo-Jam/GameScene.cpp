#include "GameScene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Dog.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <random>
#include "MusicPlayer.h"

GameScene::GameScene(sf::RenderWindow * window_) : GameScene(window, "")
{

}

GameScene::GameScene(sf::RenderWindow * window_, std::string backgroundTexture) : window(window_), backgroundTextureName(backgroundTexture)
{	
}


GameScene::~GameScene()
{
}

bool GameScene::Initialize() {

	sceneName = "GameScene";

	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);

	changeScene = false;
	dead = false;
	triggered = false;

	MusicPlayer::GetInstance()->PlayBackgroundMusic();

	player = new Player("player");
	player->LoadTexture("Assets/PlayerSpriteSheet.png");
	player->scale(3, 3);
	player->updateCentre();
	
	enemies.reserve(6);
	std::default_random_engine rgenerator;
	std::normal_distribution<float> distributionX(player->getPosition().x, 600);
	std::normal_distribution<float> distributionY(player->getPosition().y, 600);
	//Ensures that destination is always towards target
	
	for (int i = 0; i < enemies.capacity(); i++) {
		enemies.push_back(new Enemy("enemy" + i));
		enemies[i]->LoadTexture("Assets/EnemySpriteSheet.png");
		enemies[i]->scale(3, 3);
		enemies[i]->updateCentre();
		enemies[i]->setPosition(distributionX(rgenerator), distributionY(rgenerator));
		enemies[i]->SetPlayerPosition(player->getPosition());
	}
	
	camera = new Camera(window);
	camera->SetAsMainView();
	camera->SetFollowTarget(player);

	//Health
	healthBar.setSize(sf::Vector2f(camera->GetView().getSize().x / 2, 100));
	healthBar.setOrigin(healthBar.getSize().x / 2, healthBar.getSize().y / 2);
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setOutlineThickness(15);
	healthBar.setFillColor(sf::Color::Transparent);

	remainingHealth.setSize(healthBar.getSize());
	remainingHealth.setOrigin(remainingHealth.getSize().x / 2, remainingHealth.getSize().y / 2);
	remainingHealth.setFillColor(sf::Color::Red);
	//-- End health

	//Death Notification Box
	deathNotif.setSize(sf::Vector2f(window->getSize().x / 1.25f, window->getSize().y / 1.25f));
	deathNotif.setOrigin(deathNotif.getSize().x / 2, deathNotif.getSize().y / 2);
	deathNotif.setOutlineColor(sf::Color::Black);
	deathNotif.setOutlineThickness(15);
	deathNotif.setFillColor(sf::Color::White);

	if (!font.loadFromFile("arial.ttf")) printf("Error: cannot load font\n");

	deathNotifText = sf::Text("You died!", font);
	deathNotifText.setCharacterSize(50);
	deathNotifText.setStyle(sf::Text::Bold);
	deathNotifText.setFillColor(sf::Color::Black);
	deathNotifText.setOrigin(deathNotifText.getLocalBounds().width / 2, deathNotifText.getLocalBounds().height / 2);
	//-- End death notif 
	
	if (backgroundTextureName != "") {
		if (!SetBackground(backgroundTextureName)) {
			Destroy();
			return false;
		}
	}

	
	
	
	return true;
}

void GameScene::Destroy() {
	for (Enemy* enemy : enemies)
	{
		delete enemy;
		enemy = nullptr;
	}

	enemies.clear();

	//camera->Destroy();
}

void GameScene::HandleEvents(const sf::Event event) {

	camera->HandleEvents(event);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && !dead) {
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			player->MoveTo(window->mapPixelToCoords(pixelPos));
		}

	}	

	//if (event.type == sf::Event::KeyPressed) {
	//	if (event.key.code == sf::Keyboard::Backspace) {
	//		changeScene = true;
	//	}
	//}
	
}

void GameScene::UpdateHealthBar() {
	remainingHealth.setSize(sf::Vector2f(player->getHealth() / 100.0f * healthBar.getSize().x, remainingHealth.getSize().y));
}

void GameScene::Update() {

	if (player->getHealth() > 0 && !dead) {
		deathNotif.setPosition(-1 * (window->getSize().x), 0);
		deathNotifText.setPosition(deathNotif.getPosition());
	}
	else if (player->getHealth() <= 0 && !dead)  {
		deathNotif.setPosition(camera->GetView().getCenter());
		deathNotifText.setPosition(deathNotif.getPosition());
		printf("You died!");
		dead = true;
	}

	if (collisionTimer.getElapsedTime().asSeconds() >= 0.5f) {
		for (Enemy * enemy : enemies) {
			if (player->Collided(enemy) && triggered && player->getHealth() > 0) {
				//testing player health --TEMPORARY--
				player->takeDamage(10);
				MusicPlayer::GetInstance()->PlayHurtSound();
				collisionTimer.restart();
				//-- end test code
			}
		}
		
	}
	if (collisionTimer.getElapsedTime().asSeconds() >= 1.0f) {
		if (player->Collided(player->getDog()) && !triggered && !dead && player->getHealth() < player->getMaxHealth()) {
			//testing player health --TEMPORARY--
			player->heal(7);
			MusicPlayer::GetInstance()->PlayPewSound();
			collisionTimer.restart();
			//-- end test code
		}
	}


	//every 10 seconds the world changes states between triggered(aggressive creatures) and peaceful
	if (worldTimer.getElapsedTime().asSeconds() >= 10) {

		if (!triggered) {
			for (Enemy* enemy : enemies) {
				enemy->isTriggered = true;
			}
			printf("Triggered!!\n");
			SetBackground("Assets/backgroundv4.png");
			triggered = true;
		}

		else {
			for (Enemy* enemy : enemies) {
				enemy->isTriggered = false;
			}
			SetBackground("Assets/backgroundv2.png");
			triggered = false;
		}

		worldTimer.restart();
	}

	healthBar.setPosition(
		camera->GetView().getCenter().x,
		camera->GetView().getCenter().y + camera->GetView().getSize().y / 3.5);

	remainingHealth.setPosition(healthBar.getPosition());
	UpdateHealthBar();

	camera->Update();
	player->Update();

	for (Enemy* enemy : enemies) {
		enemy->SetPlayerPosition(player->getPosition());

		enemy->Update();
	}
	/*tempEnemy->SetPlayerPosition(player->getPosition());
	tempEnemy->Update();*/
}

void GameScene::Render() {
	
	window->clear();
	camera->Render();
	window->draw(backgroundSprite);
	window->draw(*player->getDog());
	window->draw(*player);
	//window->draw(*tempEnemy);
	for (Enemy* enemy : enemies) {
		window->draw(*enemy);
	}
	//UI
	window->draw(remainingHealth);
	window->draw(healthBar);
	window->draw(deathNotif);
	window->draw(deathNotifText);
	//------ end of UI

	window->display();
	
}

bool GameScene::SetBackground(std::string textureName)
{
	if (!backgroundTexture.loadFromFile(textureName)) {
		std::cout << "Could not load background image.";
		return false;
	}

	backgroundTexture.setRepeated(true);
	sf::FloatRect fBoundary(0.0f, 0.0f, 5000.0f, 5000.0f);
	sf::IntRect iBoundary(fBoundary);
	backgroundSprite = sf::Sprite(backgroundTexture, iBoundary);
	backgroundSprite.setPosition(fBoundary.left - camera->GetView().getSize().x, fBoundary.top - 5000.0f + camera->GetView().getSize().y);
	
	return true;
}
