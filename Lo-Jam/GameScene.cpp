#include "GameScene.h"
#include "Camera.h"
#include "GameObject.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <random>
#include <list>
#include "MusicPlayer.h"
#include "DoorMachine.h"

struct HealthOrb : public GameObject {
	sf::CircleShape orb;

	HealthOrb(sf::Vector2f spawnLocation) : GameObject("healthOrb") {
		orb = sf::CircleShape(30);
		orb.setFillColor(sf::Color::Green);
		orb.setOutlineThickness(2);
		orb.setOrigin(orb.getGlobalBounds().width / 2, orb.getGlobalBounds().height / 2);

		this->setOrigin(orb.getGlobalBounds().width / 2, orb.getGlobalBounds().height / 2);
		this->setPosition(spawnLocation);
		orb.setPosition(spawnLocation);
	}

	bool Collided(const GameObject* g) override {
		const sf::FloatRect collider1 = orb.getGlobalBounds();
		const sf::FloatRect collider2 = g->getGlobalBounds();

		if (collider1.intersects(collider2)) {
			return true;
		}

		return false;
	}

	void OnTriggerEnter(GameObject* g) override {
		if (g->getID().compare("player") == 0) {
			dynamic_cast<Player*>(g)->heal(4);
		}
	}

	void Draw(sf::RenderWindow* pWindow) {
		pWindow->draw(orb);
	}
};

std::vector<HealthOrb*> healthOrbs;

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

GameScene::GameScene(sf::RenderWindow* window_) : window(window_)
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

	MusicPlayer::PlayBackgroundMusic();

	player = new Player("player");
	player->scale(3, 3);

	spawnEnemy();

	camera = new Camera(window);
	camera->SetAsMainView();
	camera->SetFollowTarget(player);


	//---- UI ---//
	sf::Vector2f viewSize = camera->GetView().getSize();

	//Health
	healthBar = new InterfaceProgressBar(0, viewSize.x / 2, 100, viewSize.x / 2, viewSize.y * 0.95, Interface::BOT_CENTER);
	healthBar->SetProgressText(std::to_string(static_cast<int>(player->getHealth())) + "/" + std::to_string(static_cast<int>(player->getHealth())));
	healthBar->SetTextColor(sf::Color::White);

	//Death Notification Box
	deathPopup = new InterfacePanel("You died!", viewSize.x / 3, viewSize.y / 3, viewSize.x / 2, viewSize.y / 2);

	score = new InterfacePanel("0", 350, 350, viewSize.x * 0.05, viewSize.y * 0.05, Interface::TOP_LEFT);
	score->SetFontSize(250);
	intScore = 0;
	
	if (!SetBackground("Assets/ground.png")) {
		Destroy();
		return false;
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
	healthOrbs.clear();

	delete camera;
	camera = nullptr;

	delete player;
	player = nullptr;

	delete deathPopup;
	deathPopup = nullptr;

	delete score;
	score = nullptr;

	delete healthBar;
	healthBar = nullptr;

	MusicPlayer::StopBackgroundMusic();

}

void GameScene::HandleEvents(const sf::Event event) {

	camera->HandleEvents(event);

	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left) {
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

void GameScene::Update() {

	if (collisionTimer.getElapsedTime().asSeconds() >= 0.5f) {
		for (Enemy * enemy : enemies) {
			if (player->Collided(enemy) && player->getHealth() > 0) {
				player->takeDamage(10);
				MusicPlayer::PlayHurtSound();
				collisionTimer.restart();
			}
		}
		
	}


	if (worldTimer.getElapsedTime().asSeconds() >= 5) {

		if (enemies.size() < 20) {
			spawnEnemy();
		}

		worldTimer.restart();
	}

	healthBar->SetProgress(player->getHealth() / 100);

	//for (auto object : objectsInScene) {
	//	object.second->Update();
	//}

	camera->Update();
	


	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->SetPlayerPosition(player->getPosition());

		for (int j = 0; j < player->projectiles.size(); j++) {
			if (player->projectiles[j].Collided(enemies[i])) {
				player->projectiles[j].OnTriggerEnter(enemies[i]);
				player->projectiles.erase(player->projectiles.begin() + j);
			}

		}

		enemies[i]->Update();
		if (enemies[i]->checkState("dead")) {
			healthOrbs.push_back(new HealthOrb(enemies[i]->getPosition()));
			enemies.erase(enemies.begin() + i);
			intScore++;
		}
	}

	for (int i = 0; i < healthOrbs.size(); i++) {
		if (healthOrbs[i]->Collided(player)) {
			healthOrbs[i]->OnTriggerEnter(player);
			healthOrbs.erase(healthOrbs.begin() + i);
		}
	}

	score->SetText(std::to_string(intScore));
	player->Update();
	healthBar->SetProgressText(std::to_string(static_cast<int>(player->getHealth())) + "/" + std::to_string(static_cast<int>(player->getHealth())));
}

void GameScene::Render() {
	
	window->clear();
	camera->Render();
	window->draw(backgroundSprite);

	for (HealthOrb* orb : healthOrbs) {
		orb->Draw(window);
	}

	window->draw(*player);

	for (Enemy* enemy : enemies) {
		window->draw(*enemy);
	}

	for (auto projectile : player->projectiles) {
		window->draw(projectile);
	}

	//--- UI
	healthBar->Draw(window, camera->GetView());
	score->Draw(window, camera->GetView());

	if(player->checkState("dead"))
	{
		deathPopup->Draw(window, camera->GetView());
	}
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
