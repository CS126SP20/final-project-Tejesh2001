#pragma once
#include <Box2D/Box2d.h>
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
		b2Body* body;
		ci::Color color;
		ci::vec2 size;
		//const int kLifespan = 50;
                int lifespan_ = 150;
                bool is_dead_;
                int age_;
                cinder::Timer timer;

    };
	


