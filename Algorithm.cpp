#include "Algorithm.h"
#include <time.h>


// Default constructor
Algorithm::Algorithm() {}

int Algorithm::calcDistanceFromDockingStation(){
    
    // Move elements from stack to temporary vector
    std::vector<char> temp;
    while (!pathToDocking.empty()) {
        temp.push_back(pathToDocking.top());
        pathToDocking.pop();
    }

    // Process the temporary vector to remove specified pairs
    std::vector<char> result;
    for (size_t i = 0; i < temp.size(); ++i) {
        if (i + 1 < temp.size() &&
            ((temp[i] == 'N' && temp[i + 1] == 'S') ||
             (temp[i] == 'S' && temp[i + 1] == 'N') ||
             (temp[i] == 'E' && temp[i + 1] == 'W') ||
             (temp[i] == 'W' && temp[i + 1] == 'E'))) {
            ++i; // Skip the next element
        } 
        else {
            result.push_back(temp[i]);
        }
    }

    // Move elements back to the stack
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        pathToDocking.push(*it);
    }

    return pathToDocking.size();
}

//std::vector<std::string> actions = {"MOVE", "CLEAN", "CHARGE", "DONE"};
std::string Algorithm::chooseAction(const VacuumCleaner& cleaner) {
    
    // If we have reached the maximum number of steps - end a program
    if(moveCounter == cleaner.getMaxStepsAllowed()) {
        return actions[3]; // DONE
    }
    int distance_from_docking_station = calcDistanceFromDockingStation();
    // The distance from the charging station is equal to the remaining battery
    if(cleaner.getBatteryLevel() <= distance_from_docking_station) {
        return actions[2]; // CHARGE    
    }
    //(cleaner.getBatteryLevel() > moveCounter)
    else { 
        // still dirty - keep cleannig
        if(cleaner.dirtSensor() > 0) {
            return actions[1]; // CLEAN
        }
        // cleaner.dirtSensor() == 0
        else{ 
            return actions[0]; // MOVE      
        }
    }
}

//std::vector<char> directions = {'N', 'E', 'S', 'W'};
char Algorithm::chooseDirection(const VacuumCleaner& cleaner) {
    
    std::vector<char> possibleDirections;

    if (cleaner.sensorWallN()) {  possibleDirections.push_back('N'); }
    if (cleaner.sensorWallS()) {  possibleDirections.push_back('S'); }
    if (cleaner.sensorWallE()) {  possibleDirections.push_back('E'); }
    if (cleaner.sensorWallW()) {  possibleDirections.push_back('W'); }

    // No possible directions
    if (possibleDirections.empty()) {
        throw std::runtime_error("The robot is stuck and cannot move in any direction\n"); 
    }

    // Choose a random direction from the possible directions
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % possibleDirections.size();
    char direction = possibleDirections[randomIndex];

    // Enter the opposite direction to the direction of progress to know how to return
    switch (direction) {
        case 'N':
            pathToDocking.push('S');
            break;
        case 'S':
            pathToDocking.push('N');
            break;
        case 'W':
            pathToDocking.push('E');
            break;
        case 'E':
            pathToDocking.push('W');
            break;
    }    
    
    return direction;
}
