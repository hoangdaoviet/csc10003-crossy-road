#ifndef OBJECT_H
#define OBJECT_H

class Object {
private:
	int x;
	int y;
public:
	Object();
	Object(int X, int Y);

	int getX() const;
	int getY() const;

	virtual void draw();
};

#endif // !OBJECT_H
