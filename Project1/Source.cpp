#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class coordinate {
public:
	int x, y;
	
	coordinate() {}
	coordinate(int null) {
		x, y = NULL;
	}

	coordinate(int x_in, int y_in) {
		x = x_in;
		y = y_in;
	}
};

class coordinate_pair {
public:
	coordinate first, second;

	coordinate_pair() {}
	coordinate_pair(int null) {
		first, second = NULL;
	}

	coordinate_pair(coordinate a, coordinate b) {
		first = a;
		second = b;
	}
};

class line {
public:
	int x_coefficient, y_coefficient, y_intercept;

	line() {}
	line(int null) {
		x_coefficient, y_coefficient, y_intercept = NULL;
	}

	line(int x, int y, int yInt) {
		x_coefficient = x;
		y_coefficient = y;
		y_intercept = yInt;
	}
};

class Node {
public:
	coordinate current;
	Node* next;

	Node() {}
	Node(int x) {
		current = NULL;
		next = NULL;
	}
};

class Star_List {
public:
	Node* head;

	Star_List() {};
	Star_List(int x) {
		head = NULL;
	}

};

bool compare_cor(coordinate a, coordinate b) {
	if (a.x == b.x && a.y == b.y) {
		return true;
	}
	return false;
}

line compute_equation(coordinate a, coordinate b) {
	line result;

	result.x_coefficient = -(b.x - a.y);
	result.y_coefficient = b.x - a.x;
	result.y_intercept = result.y_coefficient*a.y + result.x_coefficient*a.x;

	return result;
}

coordinate cross_point(line line1, line line2) {
	double D = line1.x_coefficient * line2.y_coefficient - line1.y_coefficient * line2.x_coefficient;
	double DX = line1.y_intercept * line2.y_coefficient - line2.y_intercept * line1.y_coefficient;
	double DY = line1.x_coefficient * line2.y_intercept - line1.y_intercept * line2.x_coefficient;

	if (D != 0) {
		if (DX / D != (int)(DX / D) || DY / D != (int)(DY / D)) {
			return NULL;
		}

		coordinate result = NULL;
		result.x = (int)(DX / D);
		result.y = (int)(DY / D);

		return result;
	}
}

void main() {
	int totalNum = NULL;
	cin >> totalNum;

	coordinate* all_stars = new coordinate[totalNum];

}