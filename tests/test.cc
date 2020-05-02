// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Cinder.h>
#include <cinder/Rand.h>
#include <mylibrary/engine.h>

#include <catch2/catch.hpp>
#include <mylibrary/BulletController.hpp>
#include <mylibrary/WorldCreator.hpp>
TEST_CASE("engine class", "[step function]") {
  SECTION("Check for no collision") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    myapp::Player player_(b2Vec2(400, 400));
    // myapp::MyApp game_player;
    myapp::Engine engine_(player_);
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    enemy_controller.AddEnemies(1);
    bullet_controller_.addBullet(player_.GetLoc());
    engine_.Step(world_, enemy_controller, bullet_controller_.GetBullets());
    REQUIRE(!engine_.GetIsGameOver());
  }
  SECTION("Check for collision of player and enemy") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    enemy_controller.AddEnemies(1);
    myapp::Player player_(b2Vec2(0, 0));
    myapp::Engine engine_(player_);
    bullet_controller_.addBullet(player_.GetLoc());
    engine_.Step(world_, enemy_controller, bullet_controller_.GetBullets());
    REQUIRE(engine_.GetLives() == 2);
  }
  SECTION("Check for collision of bullet and enemy") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    enemy_controller.AddEnemies(1);
    myapp::Player player_(b2Vec2(-50,0));
    myapp::Engine engine_(player_);
    bullet_controller_.addBullet((b2Vec2(0, 0)));
    engine_.FindBulletCollision(enemy_controller,
                                bullet_controller_.GetBullets());
    REQUIRE(engine_.GetGameScore() == 0);
  }
}

TEST_CASE("engine direction function", "[direction]") {
  SECTION("Check for no collision") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    myapp::Player player_(b2Vec2(400, 400));
    myapp::Engine engine_(player_);
    engine_.SetDirection(Direction::kUp);
    b2Vec2 direction = engine_.FromDirection(Direction::kUp);
    REQUIRE(direction.x == 0);
    REQUIRE(direction.y == -50);
    direction = engine_.FromDirection(Direction::kDown);
    REQUIRE(direction.x == 0);
    REQUIRE(direction.y == 50);
    direction = engine_.FromDirection(Direction::kLeft);
    REQUIRE(direction.x == -50);
    REQUIRE(direction.y == 0);
    direction = engine_.FromDirection(Direction::kRight);
    REQUIRE(direction.x == 50);
    REQUIRE(direction.y == 0);
  }
}
/*All public methods tested*/
/**********************Engine tests over*********************/


/**********************EnemyController Test*********************/

TEST_CASE("Enemy Controller", "[]") {
  SECTION("Add enemy / Get enemy") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    int check = 0;
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    enemy_controller.AddEnemies(1);
    REQUIRE(enemy_controller.GetEnemies().size() == 1);
    REQUIRE(enemy_controller.GetEnemies().front().GetBody()->GetPosition().x ==
            0);
    enemy_controller.AddEnemies(2);
    REQUIRE(enemy_controller.GetEnemies().size() == 3);
    for (auto e : enemy_controller.GetEnemies()) {
      if (e.GetBody()->GetPosition().y == 0) {
        check++;
      }
    }
    REQUIRE(check == 3);
  }

SECTION("Update function") {
b2Vec2 gravity(0, 100.0f);
b2World world_(gravity);
EnemyController enemy_controller;
enemy_controller.setup(world_);
enemy_controller.AddEnemies(2);
enemy_controller.GetEnemies().front().SetIsDead(true);
enemy_controller.update();
REQUIRE(enemy_controller.GetEnemies().size() == 1);
REQUIRE(enemy_controller.GetEnemies().front().GetBody()->GetPosition().y == 0);
}
}

/**********************EnemyControllertests over*********************/

/**********************WorldCreator Test*********************/

TEST_CASE("WorldCreator class", "[random]") {
  b2Vec2 gravity(0, 0.0f);
  b2World world_(gravity);
  WorldCreator world_creator;
  SECTION("Check for ceiling made") {
    world_creator.CreateCeiling(world_);
    REQUIRE(world_.GetBodyList()->GetPosition().y == -1.0f);
  }
  SECTION("Check for collision of player and enemy") {
    world_creator.CreateLeftWall(world_);
    REQUIRE(world_.GetBodyList()->GetPosition().x == 0.0f);
  }
  SECTION("Check for collision of bullet and enemy") {
    world_creator.CreateRightWall(world_);
    REQUIRE(world_.GetBodyList()->GetPosition().x ==
            conversions::ToBox2DCoordinates(800));
  }
}

/**********************WorldCreator tests over*********************/

/**********************BulletController Tests*********************/

TEST_CASE("Bullet Controller", "[]") {
  SECTION("Add enemy / Get enemy") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    int check = 0;
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    bullet_controller_.addBullet(b2Vec2(0, 0));
    REQUIRE(bullet_controller_.GetBullets().size() == 1);
    REQUIRE(
        bullet_controller_.GetBullets().front().GetBody()->GetPosition().x ==
        1);

    bullet_controller_.addBullet(b2Vec2(1, 0));
    for (Bullet b : bullet_controller_.GetBullets()) {
      if (b.GetBody()->GetPosition().y == -1) {
        check++;
      }
    }
    REQUIRE(check == 2);
  }
  SECTION("Update function") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    bullet_controller_.addBullet(b2Vec2(0, 0));
    bullet_controller_.GetBullets().front().SetIsDead(true);
    bullet_controller_.update();
    REQUIRE(enemy_controller.GetEnemies().size() == 0);
  }
}

/**********************BulletController Tests over*********************/

/**********************Bullet tests*********************/

TEST_CASE("Bullet", "[]") {
  b2BodyDef body_def;
  SECTION("Update function") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    body_def.type = b2_dynamicBody;
    body_def.position.Set(conversions::ToBox2DCoordinates(-1),
                          conversions::ToBox2DCoordinates(900));
    Bullet bullet;
    bullet.SetBody(world_.CreateBody(&body_def));
    bullet.update();
    REQUIRE(bullet.GetIsDead());
  }
}

/**********************Bullet tests over*********************/

/**********************Enemy tests*********************/
TEST_CASE("Enemy", "[]") {
  b2BodyDef body_def;
  SECTION("Update function") {
    b2Vec2 gravity(0, 100.0f);
    b2World world_(gravity);
    body_def.type = b2_dynamicBody;
    body_def.position.Set(conversions::ToBox2DCoordinates(-1),
                          conversions::ToBox2DCoordinates(900));
    Enemy enemy;
    enemy.SetBody(world_.CreateBody(&body_def));
    enemy.update();
    REQUIRE(enemy.IsDead());
  }
}
