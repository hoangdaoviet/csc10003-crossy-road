#ifndef OBSTACLE_H
#define OBSATCLE_H

class Obstacle {
private:
	int x;
	int y;
public:
	Obstacle();
	Obstacle(int X, int Y);

	int getX() const;
	int getY() const;

	virtual void draw();
};

#endif // !OBSTACLE_H
