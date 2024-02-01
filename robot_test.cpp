#include "greedy_robot.h"

using namespace std;



// Please use g++ robot_test.cpp greedy_robot.cpp to complier
int main(int argc, char* argv[]) {

	if (argc == 6) {

		int max = atoi(argv[1]);
		int Rx = atoi(argv[2]);
		int Ry = atoi(argv[3]);
		int Tx = atoi(argv[4]);
		int Ty = atoi(argv[5]);

		cout << "greedy_robot: " << atoi(argv[1]) << " " << atoi(argv[2]) << " "
		<< atoi(argv[3]) << " " << atoi(argv[4]) <<  " " << atoi(argv[5]) << endl;
		GreedyRobot g1(max, Rx, Ry, Tx, Ty);
		cout << " " << endl;
	}
	else {
		cout << "Please enter valid value." << endl;
	}
}