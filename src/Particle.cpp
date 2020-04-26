#include "mylibrary/Particle.h"

#include <Box2D/Box2D.h>
#include <cinder/app/AppBase.h>

#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "mylibrary/CoordinateConversions.h"
#include "mylibrary/ProjectWideVariables.h"

//bool is_dead_ = false;
        Particle::Particle() {
          is_dead_ = false;
        }

	void Particle::setup(vec2 boxSize) {
		size = boxSize;
	}
	void Particle::update() {
	    if (body_->GetPosition().y > 15
              || body_->GetPosition().x >= 16 || body_->GetPosition().x <= 0.5)
          {
	     is_dead_ = true;
            // exit(3);
             // check_ = 1;
              //printf("vec2 value is %d%d\n", age_, check_);
             // exit(0);
	    }
	}

	void Particle::draw() {
		//cinder::gl::color(color);
                vec2 pos = conversions::ToScreen( body_->GetPosition() );
		float t = conversions::RadiansToDegrees( body_->GetAngle() );
		gl::pushMatrices();
		gl::translate( pos );
		gl::rotate(t);
		Rectf rect(-size.x, -size.y, size.x, size.y);
		auto load = loadImage(cinder::app::loadAsset("fire.png"));
		cinder::gl::Texture2dRef image =
                    cinder::gl::Texture2d::create(load);
		cinder::gl::draw(image, rect);
              gl::popMatrices();
	}
        b2Body* Particle::GetBody() const {
          return body_;
        }
        void Particle::SetBody(b2Body* body) {
          body_ = body;
        }

        bool Particle::IsDead() const {
          return is_dead_;
        }

        void Particle::SetIsDead(bool is_dead) {
          is_dead_ = is_dead;
        }
