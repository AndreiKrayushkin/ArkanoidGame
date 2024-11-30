#pragma once
#include "GameObject.h"
#include "Ball.h"

namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		Block(const sf::Vector2f& position, const sf::Color& color);
		virtual ~Block();
		void update(float timeDelta) override;
		bool checkCollision(std::shared_ptr<GameObject> gameObject);
		bool isBrokenBlock() const;
		
	private:
		bool getCollision(std::shared_ptr<GameObject> gameObject) const;
		bool isBroken = false;
	};
}