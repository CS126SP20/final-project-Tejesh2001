#include "Particle.h"

#include <Box2D/Box2d.h>
#include <cinder/app/AppBase.h>

#include "CoordinateConversions.h"
#include "ProjectWideVariables.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

int age_ = 0;
//bool is_dead_ = false;
        Particle::Particle() {

	}

	void Particle::setup(vec2 boxSize) {
		size = boxSize;
	}

bool is_dead_ = false;
	void Particle::update() {
	    age_++;
         // printf("vec2 value is %d%d\n", age_, is_dead_);
	    if (age_ > kLifespan) {
	     is_dead_ = true;
              check_ = 1;
              //printf("vec2 value is %d%d\n", age_, check_);
             // exit(0);
	    }
	}

	void Particle::draw() {
		//cinder::gl::color(color);
                if (check_ == 1) {
                  return;
                }
                vec2 pos = conversions::ToScreen( body->GetPosition() );
		float t = conversions::RadiansToDegrees( body->GetAngle() );
		gl::pushMatrices();
		gl::translate( pos );
		gl::rotate(t);
		Rectf rect(-size.x, -size.y, size.x, size.y);
		auto load = loadImage(cinder::app::loadAsset("gold.jpg"));
		cinder::gl::Texture2dRef image =
		    cinder::gl::Texture2d::create(load);
		cinder::gl::draw(image, rect);
		gl::popMatrices();
	}


