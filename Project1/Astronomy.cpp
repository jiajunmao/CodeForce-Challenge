#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//Declaration
class line;
Star_List rest_stars;
Star_List visited_stars;

//Define coordinate class
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

	string to_str();
	bool on_line(line data);
	bool is_equal(coordinate comp);
	bool is_equal(int null);
};

string coordinate::to_str() {
	string result = NULL;

	result = (char)"[" + (char)x + (char)"," + (char)y + (char)"]";
	return result;
}

bool coordinate::is_equal(coordinate comp) {
	return x == comp.x && y == comp.y;
}

bool coordinate::is_equal(int null) {
	if (x == NULL && y == NULL)
		return true;
	else
		return false;
}

bool coordinate::on_line(line data) {
	return (data.x_coefficient * x + data.y_intercept) == y * data.y_coefficient;
}

bool is_equal(coordinate a, coordinate b) {
	return a.x == b.x && a.y == b.y;
}

//Define coordinate_pair class
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

	bool is_equal(coordinate_pair comp);
	bool is_equal(int null);
};

bool coordinate_pair::is_equal(coordinate_pair comp) {
	return comp.first.is_equal(first) && comp.second.is_equal(second);
}

bool coordinate_pair::is_equal(int null) {
	if (first.is_equal(NULL) && second.is_equal(NULL))
		return true;
	else
		return false;
}

bool is_equal(coordinate_pair a, coordinate_pair b) {
	return a.is_equal(b);
}

//Define line class
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

	bool is_equal(line comp);
};

bool line::is_equal(line comp) {
	return x_coefficient == comp.x_coefficient &&
		y_coefficient == comp.y_coefficient &&
		y_intercept == comp.y_intercept;
}

bool is_equal(line a, line b) {
	return a.is_equal(b);
}

//Define Star_List
class Node_Cor {
public:
	coordinate current;
	Node_Cor* next;

	Node_Cor() {}
	Node_Cor(int x) {
		current = NULL;
		next = NULL;
	}
};

class Star_List {
public:
	Node_Cor * head;

	Star_List() {};
	Star_List(int x) {
		head = NULL;
	}

	void Print();
	void Append(coordinate data);
	void Delete(coordinate data);
	int Length();
	bool Contains(coordinate target);
};

void Star_List::Print() {

	//Temperary pointer
	Node_Cor *tmp = head;

	//Check if the list is empty
	if (tmp == NULL) {
		cout << "ERROR at Print(), List Empty" << endl;
		return;
	}

	//Check if there is only one element
	if (tmp->next == NULL) {
		cout << tmp->current.to_str();
		cout << "-->";
	}
	else {
		do {
			cout << tmp->current.to_str();
			cout << "-->";
			tmp = tmp->next;
		} while (tmp != NULL);

		cout << "NULL" << endl;
	}

}

void Star_List::Append(coordinate data) {

	//Create new node
	Node_Cor* new_node = NULL;
	new_node->current = data;
	new_node->next = NULL;

	//Temporary pointer
	Node_Cor *tmp = head;

	//Traverse the list and point the pointer to the end
	if (tmp != NULL) {
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}

		//Point the last node to the new node
		tmp->next = new_node;
	}

	//If the list is empty, set to be the first
	else {
		head = new_node;
	}
}

void Star_List::Delete(coordinate data) {

	Node_Cor *tmp = head;

	//If the lit is empty
	if (tmp == NULL) {
		return;
	}

	//If tmp is the last node
	if (tmp->next == NULL) {
		delete tmp;
		head = NULL;
	}
	else {
		//Traverse through the node
		Node_Cor *prev = NULL;
		do {
			if (is_equal(tmp->current, data)) {
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		} while (tmp != NULL);

		//Adjust the pointer of the list
		prev->next = tmp->next;

		//Delete the current node
		delete tmp;
	}
}

int Star_List::Length() {

	int length = 1;
	Node_Cor *tmp = head;

	//Assume that the list is empty
	if (tmp == NULL) return 0;

	//Assume that the list has only one element
	if (tmp != NULL && tmp->next == NULL) return 1;

	//The list has multiple element
	else {
		while (tmp->next != NULL) {
			length++;
			tmp = tmp->next;
		}
		length++;
	}

	return length;
}

bool Star_List::Contains(coordinate data) {
	Node_Cor *tmp = head;

	//If the list is empty
	if (tmp == NULL) return false;

	//If the list has only one element
	if (tmp != NULL && tmp->next == NULL) {
		if (tmp->current.is_equal(data))
			return true;
		else
			return false;
	}

	//If the list has multiple element
	while (tmp->next != NULL) {
		if (tmp->current.is_equal(data))
			return true;
		tmp = tmp->next;
	}
	if (tmp->current.is_equal(data))
		return true;
	else
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

Star_List input_handle() {
	//Creating the list to store coordinates
	Star_List list = NULL;

	coordinate tmp = NULL;

	//Input the total number of stars
	int totalNum = NULL;
	cin >> totalNum;

	string tmp_num;

	//Input the coordinate of the stars into the list
	while (true) {
		getline(cin, tmp_num);
		if (tmp_num.empty()) break;
		else {
			tmp.x = tmp_num[0];
			tmp.y = tmp_num[2];
			list.Append(tmp);
			tmp = NULL;
		}
	}
	return list;
}

bool starpair_backtrack(Star_List rest, Star_List visited, line current_line) {

	//Pointer for traversing the rest_stars
	Node_Cor *tmp = rest_stars.head;

	//FAILSAFE: if two list has the same amount of stars
	if (rest_stars.Length() == visited_stars.Length())
		return true;

	//BASECASE: if two list has one element in difference
	if (rest_stars.Length() - visited_stars.Length() == 1) {
		visited_stars = NULL;
		coordinate tmp = NULL;
		Node_Cor *traverser = rest_stars.head;

		while (visited_stars.Contains(traverser->current))
			traverser = traverser->next;

		visited_stars.Append(traverser->current);

		return true;
	}

	//Define the coordinate pair for the current backtrack choice
	coordinate_pair choice = NULL;

	//Select two elements from the unvisited stars and form a pair
	for (int i = 0; i < 1; i++) {
		while (visited_stars.Contains(tmp->current)) {
			tmp = tmp->next;
		}
		if (choice.is_equal(NULL))
			choice.first = tmp->current;
		else
			choice.second = tmp->current;
	}
	
	//RECURSIVECASE: Compute the current line and the cross point
	line choice_line = compute_equation(choice.first, choice.second);
	coordinate choice_cross = NULL;
	if (cross_point(current_line, choice_line).is_equal(NULL))
		visited_stars.Append(choice.second);
}

void main() {
	rest_stars = input_handle;
}