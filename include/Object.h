#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class Object
{
public:
	Object();
	~Object(void);

	Object(string name);

	int getXPos();
	void setXPos(int x);

	int getYPos();
	void setYPos(int y);

	Scalar getHSVmin();
	Scalar getHSVmax();

	void setHSVmin(int hmin, int smin, int vmin);
	void setHSVmax(int hmax, int smax, int vmax);

	string getType() {
		return type;
	}
	void setType(string t) {
		type = t;
	}

	Scalar getColor() {
		return Color;
	}
	void setColor(Scalar c) {

		Color = c;
	}

private:

	int xPos, yPos;
	string type;
	Scalar HSVmin, HSVmax;
	Scalar Color;
};

#endif /* OBJECT_H */

