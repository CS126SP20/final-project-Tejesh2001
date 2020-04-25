#include "Particle.h"

#include <Box2D/Box2d.h>
#include <ciAnimatedGif.h>
#include <cinder/app/AppBase.h>

#include "CoordinateConversions.h"
#include "ProjectWideVariables.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"

//bool is_dead_ = false;
        Particle::Particle() {
          age_ = 0;
          is_dead_ = false;
          timer.start(0);
        }

	void Particle::setup(vec2 boxSize) {
		size = boxSize;
	}
	void Particle::update() {
	    age_++;
         // printf("vec2 value is %d%d\n", age_, is_dead_);
            if (timer.getSeconds() > 10 && lifespan_ > 30) {
              lifespan_ -= 20;
            }

	    if (age_ > lifespan_) {
	     is_dead_ = true;
             // check_ = 1;
              //printf("vec2 value is %d%d\n", age_, check_);
             // exit(0);
	    }
	}

	void Particle::draw() {
		//cinder::gl::color(color);
                vec2 pos = conversions::ToScreen( body->GetPosition() );
		float t = conversions::RadiansToDegrees( body->GetAngle() );
		gl::pushMatrices();
		gl::translate( pos );
		gl::rotate(t);
                //ciAnimatedGifRef  mGif;
               // mGif = ciAnimatedGif::create(cinder::app::loadAsset
               //                              ("ezgif.com-crop.gif") );
               // mGif->draw();
		Rectf rect(-size.x, -size.y, size.x, size.y);
		auto load = loadImage(cinder::app::loadAsset("fire.png"));
		cinder::gl::Texture2dRef image =
                    cinder::gl::Texture2d::create(load);
		cinder::gl::draw(image, rect);
              gl::popMatrices();
	}


