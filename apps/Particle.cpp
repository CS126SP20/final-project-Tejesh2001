#include "Particle.h"

#include <Box2D/Box2d.h>
#include <cinder/app/AppBase.h>

#include "CoordinateConversions.h"
#include "ProjectWideVariables.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

namespace particles {
	
	Particle::Particle() {
	}

	
	void Particle::setup(vec2 boxSize) {
		size = boxSize;
		if (global::color_change == 0)
			color = ci::ColorA(1, ci::Rand::randFloat(0,.5), 0, 1);

		else
			color = ci::ColorA(ci::Rand::randFloat(0,.5), 0, 1, 1);
	}

	void Particle::update() {
	    age_++;
	    if (age_ > kLifespan) {
	      is_dead_ = true;
	      age_ = 0;
	    }
	}

	void Particle::draw() {
		//cinder::gl::color(color);
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
}

