#include <iostream>
#include <string>


class Ship
{
public:
    Ship() : position{0, 0}, waypoint{1, 10} {}
    void north(int distance) {
        waypoint.first += distance;
    }
    void south(int distance) {
        waypoint.first -= distance;
    }
    void east(int distance) {
        waypoint.second += distance;
    }
    void west(int distance) {
        waypoint.second -= distance;
    }
    void forward(int steps) {
        position.first  += steps * waypoint.first;
        position.second += steps * waypoint.second;
    }
    void left(int degrees) {
        int quarter_turns = degrees / 90;
        for (int i = 0; i < quarter_turns; ++i) {
            auto [d_lat, d_lon] = waypoint;
            waypoint = { d_lon, -d_lat };
        }
    }
    void right(int degrees) {
        int degrees_left = 360 - degrees;
        left(degrees_left);
    }
    int get_latitude() {
        return position.first;
    }
    int get_longitude() {
        return position.second;
    }

private:
    std::pair<int, int> position;
    std::pair<int, int> waypoint;
};


int main()
{
    Ship ship;

    while (std::cin.good()) {
        std::string action;
        std::cin >> action;
        if (action.length() == 0) {
            continue;
        }

        const char type = action[0];
        const int value = std::stoi(action.substr(1));
        if (type == 'N') {
            ship.north(value);
        } else if (type == 'S') {
            ship.south(value);
        } else if (type == 'E') {
            ship.east(value);
        } else if (type == 'W') {
            ship.west(value);
        } else if (type == 'F') {
            ship.forward(value);
        } else if (type == 'L') {
            ship.left(value);
        } else if (type == 'R') {
            ship.right(value);
        }
    }

    std::cout << (std::abs(ship.get_latitude()) + std::abs(ship.get_longitude())) << std::endl;
}
