#ifndef OBSTACLE_H
#define OBSATCLE_H

class Obstacle {
private:
	int x;
	int y;
	int code; //0: bush, 1: cactus, 2: rock, 3: empty wagon
public:
	Obstacle();
	Obstacle(int X, int Y, int code);

	int getX() const;
	int getY() const;

	void draw();
};

#endif // !OBSTACLE_H
