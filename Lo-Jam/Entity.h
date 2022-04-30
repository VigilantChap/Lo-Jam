#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"
#include "IObservable.h"
#include <list>

#define addState(x) states.insert_or_assign(x.getName(), new x)
#define setState(x) currentState = states.find(x)->second
#define updateState currentState->Update();



class Entity : public GameObject, public IObservable
{
	friend class Animator;

protected:
	float health;
	float maxHealth;
	sf::Vector2f destination;
	float speed;
	float maxSpeed;
	float magnitude;
	sf::Vector2f direction;

	//addresses of observers that need to be notified when this entity does a thing
	std::list<IObserver*> observers;

	//states
	bool GoingToDestination;
	bool Idling;

	std::map<std::string, Script*> states;
	Script* currentState = nullptr;

	virtual void HandleState();
	

public:
	Entity(std::string ID);
	~Entity();
	virtual void Update() override;

	template <class T>
	void ChangeState(T state) { addState(T); setState(dynamic_cast<Script>(state)); }

	void AddObserver(IObserver* observer) override { observers.push_back(observer); }
	void Remove(IObserver* observer) override { observers.remove(observer); }
	void Notify(GameEvent e) override {
		for (IObserver * observer : observers)
		{
			observer->ObservableEvent(e);
		}
	}

	inline bool checkState(const std::string& x) { return x.compare(currentState->getName()) == 0; }

	void MoveTo(sf::Vector2f destination_);

	inline void setMaxSpeed(float speed_) { speed = speed_; }
	inline float getHealth() { return health; }
	inline float getMaxHealth() { return maxHealth; }

	virtual inline void takeDamage(float value) { 
		if (health >= value) {
			health -= value;
		}

		else health = 0;	

		printf("%s took damage! Health is now %f %\n", m_ID.c_str(), health);
	}

	virtual inline void heal(float value) {
		if (health <= maxHealth - value) {
			health += value;
		}

		else health = maxHealth;
		printf("%s healed!\n", m_ID.c_str());
	}

	struct Dead_Entity : Script {
		Dead_Entity() {}

		inline const std::string getName() override { return "dead"; }

		inline void Update() override {

		}
	};

	struct Moving_Entity : Script
	{

		Entity* refEntity;

		Moving_Entity(Entity* ref) : refEntity(ref) {}

		inline const std::string getName() override { return "moving"; }

		inline void Update() override {
			refEntity->magnitude = sqrtf(powf((refEntity->destination - refEntity->getPosition()).x, 2.0f)
				+ powf((refEntity->destination - refEntity->getPosition()).y, 2.0f));

			refEntity->direction = refEntity->destination - refEntity->getPosition();
			refEntity->direction = refEntity->direction / refEntity->magnitude;


			if (refEntity->magnitude < 25) refEntity->speed = refEntity->maxSpeed / 4.0f;
			else refEntity->speed = refEntity->maxSpeed;

			if (refEntity->magnitude > 10) {
				refEntity->direction.x = std::round(refEntity->direction.x * refEntity->speed);
				refEntity->direction.y = std::round(refEntity->direction.y * refEntity->speed);
				refEntity->move(refEntity->direction);
			}
			else
			{
				refEntity->currentState = nullptr;
			}
		}

		~Moving_Entity() { }
	};

	struct Idle_Entity : public Script
	{
	public:

		Idle_Entity() {}

		const std::string getName() override { return "idle"; }

		void Update() override {

		}

		~Idle_Entity() {}
	};

};
#endif // !ENTITY_H


