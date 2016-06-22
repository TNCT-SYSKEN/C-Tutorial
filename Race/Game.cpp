#include "Game.h"

Game::Game(){
	start();
}

void Game::start(){
	pos = Vec2(320, 65);
	ac = 0;
	rad = 0;
	state = State::START;
}

void Game::update(){

	switch (state){
	case State::START:
		if (Input::KeySpace.clicked){
			state = State::GAME;
		}
		break;
	case State::GAME:
		input();
		check();
		break;
	case State::CLEAR:
		if (Input::KeySpace.clicked){
			state = State::START;
			start();
		}
		break;
	}
}

void Game::draw(){
	static Font font(30);

	switch (state){
	case State::START:
		font(L"Race").draw(200, 100);
		font(L"Spaceでゲームスタート").draw(50, 200);
		break;
	case State::GAME:
		Rect(0, 0, 640, 480).draw({ Palette::Darkgreen });

		Rect(240, 40, 160, 400).draw({ Palette::White });
		Circle(240, 240, 200).draw({ Palette::White });
		Circle(400, 240, 200).draw({ Palette::White });

		Rect(275, 115, 100, 250).draw({ Palette::Darkgreen });
		Circle(275, 240, 125).draw({ Palette::Darkgreen });
		Circle(375, 240, 125).draw({ Palette::Darkgreen });

		Line(40, 240, 150, 240).draw(10, { Palette::Red });

		Triangle(pos, 30.0).rotated(rad + TwoPi / 4).draw(Color(Palette::Yellow).setAlpha(123)).drawFrame(2.0, { Palette::Black });
		break;
	case State::CLEAR:
		font(L"GOAL!!").draw(200, 100);
		font(L"Spaceでタイトルへ").draw(50, 200);
		break;
	}
}

void Game::check(){
	Circle player(pos, 1.0);

	if ((Rect(240, 40, 160, 400).contains(player) ||
		Circle(240, 240, 200).contains(player) ||
		Circle(400, 240, 200).contains(player)) &&
		(!player.intersects(Rect(275, 115, 100, 250)) &&
		!player.intersects(Circle(275, 240, 125)) &&
		!player.intersects(Circle(375, 240, 125)))){
	}
	else{
		ac = Clamp(ac, -1.0, 1.0);
	}
	if (player.intersects(Line(40, 240, 150, 240))){
		state = State::CLEAR;
	}
}

void Game::input(){
	rad += (Input::KeyRight.pressed - Input::KeyLeft.pressed) * 0.15 / TwoPi;
	double dac = (Input::KeyUp.pressed - Input::KeyDown.pressed) * 0.1;
	if (dac != 0){
		ac += dac;
	}
	else if (ac > 0.1){
		ac -= 0.1;
	}
	pos.x += ac * Cos(rad);
	pos.y += ac * Sin(rad);
	if (pos.x < 0 || pos.y < 0 || pos.x > 640 || pos.y > 480){
		ac = 0;
	}
	pos = Vec2(Clamp(pos.x, 0.0, 640.0), Clamp(pos.y, 0.0, 480.0));
}