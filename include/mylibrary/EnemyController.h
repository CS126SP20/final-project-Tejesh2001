#pragma once
#include <Box2D/Box2D.h>

#include <list>
#include <vector>

#include "Bullet.hpp"
#include "mylibrary/Enemy.h"

class EnemyController {
        	public:
                 EnemyController();
		// pass the physics world from the main app by reference
		void setup(b2World &my_world);
		void update();
                std::list<Enemy> &GetEnemies();
		void draw();
                void AddEnemies(int amount);
               private:
		// store a pointer to the physics world fro the main app
		b2World *world_;
                std::list<Enemy> enemies;
               private:
                b2Vec2* location_for_test;

               private:
                b2BodyDef &CreateBody(b2BodyDef &bodyDef);

};
