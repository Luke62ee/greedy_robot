#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// coordinates for robot and treasure
struct Coordinate {
    int x;
    int y;
};

class GreedyRobot {
    public:
        //constructor
        GreedyRobot();
        GreedyRobot(int max_distance, int robotX, int robotY, int treasureX, int treasureY);

        //getters-setters
        void set_robot_coordinates(int x, int y);
        void set_treasure_coordinates(int x, int y);
        void set_max_distance(int max);

        int max_distance() const;
        int robot_x() const;
        int robot_y() const;
        int treasure_x() const;
        int treasure_y() const;
        int paths() const;

        //actions
        bool CheckNorthDistance(const string& movementPath);
        bool CheckSouthDistance(const string& movementPath);
        bool CheckWestDistance(const string& movementPath);
        bool CheckEastDistance(const string& movementPath);
        string MoveRobot(int& robotX, int& robotY, char direction, const string& movementPath);
        void SearchPathToTreasure(int robotX, int robotY, string movementPath, bool otherDirection);
        void FindPath(int robotX, int robotY, const string& movementPath);
        void FindOppPath(int robotX, int robotY, const string& movementPath);
        bool CheckDuplicate(const string& movementPath);
        void Print();
        
        
        //operators
        bool operator==(const GreedyRobot& other) const;
        bool operator!=(const GreedyRobot& other) const;
        bool operator>=(const GreedyRobot& other) const;
        bool operator<=(const GreedyRobot& other) const;
        bool operator<(const GreedyRobot& other) const;
        bool operator>(const GreedyRobot& other) const;
       

    private:
        Coordinate robot_;
        Coordinate treasure_;
        vector<string> all_paths_;
        int max_distance_;
        int paths_;
};  
#endif