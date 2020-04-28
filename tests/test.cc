// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Cinder.h>
#include <cinder/Rand.h>
#include <mylibrary/engine.h>

#include <catch2/catch.hpp>
#include <mylibrary/BulletController.hpp>

#include "../apps/my_app.h"

TEST_CASE("engine step function", "[random]") {
  
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
    int check = 0;
    EnemyController enemy_controller;
    BulletController bullet_controller_;
    enemy_controller.setup(world_);
    bullet_controller_.setup(world_);
    enemy_controller.AddEnemies(1);
    myapp::Player player_(b2Vec2(0,0));
    myapp::Engine engine_(player_);
    bullet_controller_.addBullet(player_.GetLoc());
        engine_.Step(world_, enemy_controller,
                   bullet_controller_.GetBullets());
    REQUIRE(engine_.GetIsGameOver());
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







