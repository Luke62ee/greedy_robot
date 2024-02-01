#include "greedy_robot.h"
#include <algorithm>
#include <string>

GreedyRobot::GreedyRobot() {
    max_distance_ = 0; 
	robot_.x = 0; 
	robot_.y = 0; 
	treasure_.x = 0; 
	treasure_.y = 0; 
}

GreedyRobot::GreedyRobot(int max_distance, int robotX, int robotY, int treasureX, int treasureY) {
    max_distance_ = max_distance; 
	robot_.x = robotX; 
	robot_.y = robotY; 
	treasure_.x = treasureX; 
	treasure_.y = treasureY;
	FindPath(robot_.x, robot_.y, "");
	FindOppPath(robot_.x, robot_.y, "");
    Print();
}

void GreedyRobot::set_robot_coordinates(int x, int y) {
    robot_.x = x;
    robot_.y = y;
}

void GreedyRobot::set_treasure_coordinates(int x, int y) {
    treasure_.x = x;
    treasure_.y = y;
}

void GreedyRobot::set_max_distance(int max) {
    max_distance_ = max;
}

int GreedyRobot::max_distance() const {
    return max_distance_;
}

int GreedyRobot::robot_x() const {
    return robot_.x;
}

int GreedyRobot::robot_y() const {
    return robot_.y;
}

int GreedyRobot::treasure_x() const {
    return treasure_.x;
}

int GreedyRobot::treasure_y() const {
    return treasure_.y;
}

int GreedyRobot::paths() const {
    return paths_;
}

// To check if the robot go North consecutively more than the max distance
// Return true if the consecutive North is more than max distance
// Because it can't be more than max_distance
bool GreedyRobot::CheckNorthDistance(const string& movementPath) {
    // If the movement path is empty, there is nothing to check
    if (movementPath.empty()) {
        return false;
    }

    // Initial a counter to record consecutive North movements
    int count = 0;

    // Iterate through the movement path from the end to the beginning
    // Because I want 
    for (auto i = movementPath.end(); i != movementPath.begin(); i--) {
        // If the current movement is North, increment the count
        if (*i == 'N') {
            count++;
        } else {
            // If it encounters a movement that is not North, break the loop
            break;
        }
    }
    return (count >= max_distance_) ? true : false;
}

// This is the same idea for South
bool GreedyRobot::CheckSouthDistance(const string &movementPath) {
    if (movementPath.empty()) {
        return false;
    }

    int count = 0;
    for (auto i = movementPath.end(); i != movementPath.begin(); i--) {
        if (*i == 'S') {
            count++;
        } else {
            break;
        }
    }
    return (count >= max_distance_) ? true : false;
}

// This is the same idea for West
bool GreedyRobot::CheckWestDistance(const string &movementPath) {
    if (movementPath.empty()) {
        return false;
    }
    int count = 0;
    for (auto i = movementPath.end(); i != movementPath.begin(); i--) {
        if (*i == 'W') {
            count++;
        } else {
            break;
        }
    }
    return (count >= max_distance_) ? true : false;
}

// This is the same idea for East
bool GreedyRobot::CheckEastDistance(const string &movementPath) {
    if (movementPath.empty()) {
        return false;
    }
    int count = 0;
    for (auto i = movementPath.end(); i != movementPath.begin(); i--) {
        if (*i == 'W') {
            count++;
        } else {
            break;
        }
    }
    return (count >= max_distance_) ? true : false;
}

// This function will move the robot to different directions
string GreedyRobot::MoveRobot(int& robotX, int& robotY, char direction, const string& movementPath) {
    // Create a new path by adding the current direction to the previous path
    string newPath = movementPath + direction;

    // Update the robot's position based on the direction
    switch(direction) {
        // Robot move up on y-coordinate, if it is N
        case 'N' : robotY++; break;
        // Robot move down on y-coordinate, if it is S
        case 'S' : robotY--; break;
        // Robot move right on x-coordinate, if it is E
        case 'E' : robotX++; break;
        // Robot move left on x-coordinate, if it is W
        case 'W' : robotX--; break;
    }
    // Return the updated path
    return newPath;
}

// This function would search all the possible paths to the treasure
void GreedyRobot::SearchPathToTreasure(int robotX, int robotY, string movementPath, bool checkOpp) {
    // If the robot's current location is the same as treasure's location
    // Check the path is duplicate or not
    // If not, add it to the list of all valid paths
    if (robotX == treasure_.x && robotY == treasure_.y) {
        if (!CheckDuplicate(movementPath)) {
            all_paths_.push_back(movementPath);
        }
        return;
    }

    // If the robot is on the left side of treasure
    // Move to East if it doesn't over the times of max_distance
    if (robotX < treasure_.x) {
        if (!CheckEastDistance(movementPath)) {
            int newRobotX = robotX + 1;
            SearchPathToTreasure(newRobotX, robotY, movementPath + 'E', checkOpp);
        }
    }

    // If the robot is on the right side of treasure
    // Move to West if it doesn't over the times of max_distance
    if (robotX > treasure_.x) {
        if (!CheckWestDistance(movementPath)) {
            int newRobotX = robotX - 1;
            SearchPathToTreasure(newRobotX, robotY, movementPath + 'W', checkOpp);
        }
    }

    // If the robot is on the down side of treasure
    // Move to North if it doesn't over the times of max_distance
    if (robotY < treasure_.y) {
        if (!CheckNorthDistance(movementPath)) {
            int newRobotY = robotY + 1;
            SearchPathToTreasure(robotX, newRobotY, movementPath + 'N', checkOpp);
        }
    }

    // If the robot is on the top side of treasure
    // Move to South if it doesn't over the times of max_distance
    if (robotY > treasure_.y) {
        if (!CheckSouthDistance(movementPath)) {
            int newRobotY = robotY - 1;
            SearchPathToTreasure(robotX, newRobotY, movementPath + 'S', checkOpp);
        }
    }
    // If it is true, call the function recursively , but switch to the opposite value
    // It helps to check every possible direction path
    if(checkOpp) {
        SearchPathToTreasure(robotX, robotY, movementPath, !checkOpp);
    }
}

// This function intials the search for all possible paths from the robot to the treasure
void GreedyRobot::FindPath(int robotX, int robotY, const string &movementPath) {
    // Set checkOpposite to false, so it doesn't need to find other path
    const bool checkOpp = false;

    // Call search function to search for the paths
    SearchPathToTreasure(robotX, robotY, movementPath, checkOpp);
}

// This one helps to search if there is any other potential way we can search for the treasure
// It will also search for the oppsite way to see is it the shortest one
void GreedyRobot::FindOppPath(int robotX, int robotY, const string &movementPath) {
    const bool checkOpp = true;
    SearchPathToTreasure(robotX, robotY, movementPath, checkOpp);
}

// To check whether movementPath already exists in all_paths_
// Return true if it exists
bool GreedyRobot::CheckDuplicate(const string &movementPath) {
    // It will search through the while all_paths_ from the beginning to the end
    // If it doesnt find it, it will return false;
    // If the returned iterator is not equal to the end iterator, it means movementPath is found, so it returns true.
    return find(all_paths_.begin(), all_paths_.end(), movementPath) != all_paths_.end();
}

// It prints the output
void GreedyRobot::Print() {
    // Check if the robot and the treasure are at the same coordinate
    if (robot_.x == treasure_.x && robot_.y == treasure_.y) {
        cout << "Already there!" << endl;
    } else {
        // Initialize paths counter
        int pathCount = 0;

        // Iterate through all the paths stored in all_paths_
        for (const auto& path : all_paths_) {
            // Initialize a counter for consecutive moves
            int count = 1;

            // Iterate through the path string, starting from 2nd character
            for (int  i = 1; i < path.size(); i++) {

                // If the current move is the same as the previous one, increment the count
                if (path[i] == path[i - 1]) {
                    count++;
                
                  // Else reset the count if the moves are different
                } else {
                    count = 1;
                }

                // If the consecutive moves is more than max_distance, break the loop
                if (count > max_distance_) {
                    break;
                }
            }

            // If the count is valid, print it, and increment pathCount;
            if (count <= max_distance_) {
                cout << path << endl;
                pathCount++;
            }
        }
        // Print the total path
        cout << "Number of paths: " << pathCount << endl;
    }
}

bool GreedyRobot::operator==(const GreedyRobot& other) const {
    if ((*this).paths_ == other.paths_) {
		return true;
	}
	else {
		return false;
	}
}

bool GreedyRobot::operator!=(const GreedyRobot& other) const {
    if ((*this).paths_ != other.paths_) {
		return true;
	}
	else {
		return false;
	}
}

bool GreedyRobot::operator>=(const GreedyRobot& other) const {
    if ((*this).paths_ > other.paths_) {
		return true;
	}
	else {
		return false;
	}
}

bool GreedyRobot::operator<=(const GreedyRobot& other) const {
    if ((*this).paths_ <= other.paths_) {
		return true;
	}
	else {
		return false;
	}
}

bool GreedyRobot::operator<(const GreedyRobot& other) const {
    if ((*this).paths_ < other.paths_) {
		return true;
	}
	else {
		return false;
	}
}

bool GreedyRobot::operator>(const GreedyRobot& other) const {
    if ((*this).paths_ > other.paths_) {
		return true;
	}
	else {
		return false;
	}
}
