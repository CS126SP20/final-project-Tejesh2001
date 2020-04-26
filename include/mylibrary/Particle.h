#pragma once
#include <Box2D/Box2D.h>
#include <cinder/Timer.h>

#include "cinder/Color.h"

class Particle {
	public:
		Particle( );
		// pass in a pointer to the particle
		void setup(cinder::vec2 boxSize);
		void update();
		void draw();

		// store a pointer to the particle
		// in the physics world from the main app
               private:
		b2Body* body_;
		ci::vec2 size;
		//const int kLifespan = 50;
                int lifespan_ = 50;

               public:
                b2Body* GetBody() const;
                void SetBody(b2Body* body);
                bool IsDead() const;
                void SetIsDead(bool is_dead);

               private:
                bool is_dead_;

    };
