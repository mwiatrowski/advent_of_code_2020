#include <iostream>
#include <string>


class Ship
{
public:
    Ship() : latitude(0), longitude(0), direction{0, 1} {}
    void north(int distance) {
        latitude += distance;
    }
    void south(int distance) {
        latitude -= distance;
    }
    void east(int distance) {
        longitude += distance;
    }
    void west(int distance) {
        longitude -= distance;
    }
    void forward(int distance) {
        latitude  += direction.first  * distance;
        longitude += direction.second * distance;
    }
    void left(int degrees) {
        int quarter_turns = degrees / 90;
        for (int i = 0; i < quarter_turns; ++i) {
            auto [d_lat, d_lon] = direction;
            direction = { d_lon, -d_lat };
        }
    }
    void right(int degrees) {
        int degrees_left = 360 - degrees;
        left(degrees_left);
    }
    int get_latitude() {
        return latitude;
    }
    int get_longitude() {
        return longitude;
    }

private:
    int latitude;
    int longitude;
    std::pair<int, int> direction;
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
