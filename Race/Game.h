#pragma once

# include <Siv3D.hpp>

# define BOLL_SIZE 10

class Game{
public:
	enum State{
		START,
		GAME,
		CLEAR,
	};
	//コンストラクタ
	Game();
	void start();

	void update();
	void draw();

	void input();
	void check();

private:
	//ボールの位置と速さ
	double rad, ac;
	Vec2 pos;

	State state;
};