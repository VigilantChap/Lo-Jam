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
#include <list>
#include "MusicPlayer.h"
#include "DoorMachine.h"

//------Example of Observer
//struct observerObject1 : public GameObject, public IObserver {
//	observerObject1(std::string ID) : GameObject(ID) {};
//
//	void ObservableEvent(GameEvent& e) override {
//		
//		auto sourceName = dynamic_cast<GameObject*>(e.source)->getID();
//		if (e.type == GameEvent::Thing1) {
//			if (sourceName.compare("player") == 0) {
//				printf("ObserverObject1 says: The player sent a Thing1 event. I'm responding to that now.\n");
//			}
//			//else if another observed entity
//			//else a default response for any other entity
//		}
//
//		else printf("ObserverObect1 says: I was notified of an event type that I'm not concerned about.\n");
//	}
//};
//------ End observer


void GameScene::spawnEnemy()
{
	std::default_random_engine rgenerator(time(nullptr));
	std::normal_distribution<float> distributionX(player->getPosition().x, 1600);
	std::normal_distribution<float> distributionY(player->getPosition().y, 1600);
	enemies.push_back(new Enemy("enemy"));
	enemies.back()->scale(3, 3);
	enemies.back()->setPosition(distributionX(rgenerator), distributionY(rgenerator));
	enemies.back()->SetPlayerPosition(player->getPosition());
}

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

	MusicPlayer::PlayBackgroundMusic();

	player = new Player("player");
	player->scale(3, 3);

	spawnEnemy();
	

	camera = new Camera(window);
	camera->SetAsMainView();
	camera->SetFollowTarget(player);

	//Health
	healthBar.setSize(sf::Vector2f(camera->GetView().getSize().x / 2.0f, 100.0f));
	healthBar.setOrigin(healthBar.getSize().x / 2.0f, healthBar.getSize().y / 2.0f);
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setOutlineThickness(15);
	healthBar.setFillColor(sf::Color::Transparent);

	remainingHealth.setSize(healthBar.getSize());
	remainingHealth.setOrigin(remainingHealth.getSize().x / 2.0f, remainingHealth.getSize().y / 2.0f);
	remainingHealth.setFillColor(sf::Color::Red);
	//-- End health

	//Death Notification Box
	deathNotif.setSize(sf::Vector2f(camera->GetView().getSize().x / 3.0f, camera->GetView().getSize().y / 3.0f));
	deathNotif.setOrigin(deathNotif.getSize().x / 2.0f, deathNotif.getSize().y / 2.0f);
	deathNotif.setOutlineColor(sf::Color::Black);
	deathNotif.setOutlineThickness(15);
	deathNotif.setFillColor(sf::Color::White);

	if (!font.loadFromFile("arial.ttf")) printf("Error: cannot load font\n");

	deathNotifText = sf::Text("You died!", font);
	deathNotifText.setCharacterSize(150);
	deathNotifText.setStyle(sf::Text::Bold);
	deathNotifText.setFillColor(sf::Color::Black);
	deathNotifText.setOrigin(deathNotifText.getLocalBounds().width / 2.0f, deathNotifText.getLocalBounds().height / 2.0f);
	//-- End death notif 

	score = new InterfacePanel("0", 350, 350, 1500, 200);
	score->SetFontSize(250);
	intScore = 0;
	
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

	delete camera;
	camera = nullptr;

	delete player;
	player = nullptr;

	MusicPlayer::StopBackgroundMusic();

}

void GameScene::HandleEvents(const sf::Event event) {

	camera->HandleEvents(event);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left && !dead) {
			const sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			player->MoveTo(window->mapPixelToCoords(pixelPos));
		}

	}	

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Backspace) {
			changeScene = true;
		}

		if (event.key.code == sf::Keyboard::Space) {
			const sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			player->fire(window->mapPixelToCoords(pixelPos));
		}
	}
	
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
			if (player->Collided(enemy) && player->getHealth() > 0) {
				player->takeDamage(10);
				MusicPlayer::PlayHurtSound();
				collisionTimer.restart();
			}
		}
		
	}
	if (collisionTimer.getElapsedTime().asSeconds() >= 1.0f) {
		if (player->Collided(player->getDog()) && !dead && player->getHealth() < player->getMaxHealth()) {
			player->heal(7);
			MusicPlayer::PlayPewSound();
			collisionTimer.restart();
		}
	}


	if (worldTimer.getElapsedTime().asSeconds() >= 5) {

		if (enemies.size() < 6) {
			spawnEnemy();
		}

		worldTimer.restart();
	}

	healthBar.setPosition(
		camera->GetView().getCenter().x,
		camera->GetView().getCenter().y + camera->GetView().getSize().y / 3.5);

	remainingHealth.setPosition(healthBar.getPosition());
	UpdateHealthBar();

	//for (auto object : objectsInScene) {
	//	object.second->Update();
	//}

	camera->Update();
	

	static sf::Clock cooldown;

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->SetPlayerPosition(player->getPosition());

		for (int j = 0; j < player->projectiles.size(); j++) {
			if (player->projectiles[j].Collided(enemies[i]) && cooldown.getElapsedTime().asSeconds() > 1) {
				player->projectiles[j].OnTriggerEnter(enemies[i]);
				player->projectiles.erase(player->projectiles.begin() + j);
				cooldown.restart();
			}

		}

		enemies[i]->Update();
		if (enemies[i]->checkState("dead")) {
			enemies.erase(enemies.begin() + i);
			intScore++;
		}
	}

	std::string newScore = std::to_string(intScore);
	score->SetText(newScore);
	player->Update();
}

void GameScene::Render() {
	
	window->clear();
	camera->Render();
	window->draw(backgroundSprite);
	window->draw(*player->getDog());
	window->draw(*player);
	for (Enemy* enemy : enemies) {
		window->draw(*enemy);
	}

	for (auto projectile : player->projectiles) {
		window->draw(projectile);
	}



	//UI
	window->draw(remainingHealth);
	window->draw(healthBar);
	window->draw(deathNotif);
	window->draw(deathNotifText);
	score->Draw(window, camera->GetView());
	//------ end of UI

	window->display();
	
}

bool GameScene::SetBackground(std::string textureName)
{
	if (!backgroundTexture.loadFromFile(textureName)) {
		std::cout << "Could not load background image.\n";
		return false;
	}

	backgroundTexture.setRepeated(true);
	sf::FloatRect fBoundary(0.0f, 0.0f, camera->GetView().getSize().x, camera->GetView().getSize().y);
	sf::IntRect iBoundary(fBoundary);
	backgroundSprite = sf::Sprite(backgroundTexture, iBoundary);
backgroundSprite.scale(9, 9);
	backgroundSprite.setOrigin(backgroundSprite.getLocalBounds().width / 2.0f, backgroundSprite.getLocalBounds().height / 2.0f);
	
	
	return true;
}
