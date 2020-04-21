#pragma once
#include "Particle.h"
#include <Box2D/Box2d.h>
#include <list>

namespace particles {
	
	class ParticleController {
	  int wave_controller{};
	public:
		ParticleController();
		// pass the physics world from the main app by reference
		void setup(b2World &my_world);
		void update();
		void draw();
		void removeAll();
                void addParticles(int amount);
                void addParticle(const cinder::ivec2 &mouse_pos);
               private:
		// store a pointer to the physics world fro the main app
		b2World *world_;
                std::list<Particle> particles;
                b2BodyDef &CreateBody(b2BodyDef &bodyDef);
        };

}