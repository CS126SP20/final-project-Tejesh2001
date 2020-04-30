#pragma once
#include <Box2D/Box2D.h>
#include <cinder/Timer.h>

#include "cinder/Color.h"

class Enemy {
	public:
         Enemy( );
		// pass in a pointer to the particle
		void setup(const cinder::vec2& boxSize);
		void update();
		void draw();

		// store a pointer to the particle
		// in the physics world from the main app
               private:
		b2Body* body_;
		ci::vec2 size;
		//const int kLifespan = 50;
                int lifespan_ = 50;
                int age_ = 0;
                cinder::Timer timer_ = true;

               public:
                b2Body* GetBody() const;
                void SetBody(b2Body* body);
                bool IsDead() const;
                void SetIsDead(bool is_dead);

               private:
                bool is_dead_;

    };
