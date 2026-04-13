#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;

// base class
class BaseCar {
protected:
    string model_;
    int position_{0};

    static inline int finishLine_ = 60;
    static inline string winnerName_;

public:
    BaseCar(string model) : model_(model) {}
    virtual ~BaseCar() = default;

    string GetModel() const { return model_; }
    int GetPosition() const { return position_; }
    static string GetWinner() { return winnerName_; }

    virtual void Update() = 0; 
};

// normal car inherited class
class NormalCar : public BaseCar {
public:
    NormalCar(string model) : BaseCar(model) {}
    
    void Update() override {
        if (winnerName_.empty()) {
            position_ += rand() % 3; 

            if (position_ >= finishLine_ && winnerName_.empty()) {
                winnerName_ = model_;
            }
        }
    }
};

// fast car inherited class
class FastCar : public BaseCar {
public:
    FastCar(string model) : BaseCar(model) {}
    
    void Update() override {
        if (winnerName_.empty()) {
            position_ += rand() % 5; 

            if (position_ >= finishLine_ && winnerName_.empty()) {
                winnerName_ = model_;
            }
        }
    }
};

// steady car inherited class
class SteadyCar : public BaseCar {
public:
    SteadyCar(string model) : BaseCar(model) {}
    
    void Update() override {
        if (winnerName_.empty()) {
            position_ += 1; 

            if (position_ >= finishLine_ && winnerName_.empty()) {
                winnerName_ = model_;
            }
        }
    }
};

int main() {
    srand(time(nullptr));

    // countdown timer
    cout << "\033[2J\033[H";
    cout << "\nWelcome to the C++ Racing Simulator!\n\n";
    for (int i = 3; i > 0; --i) {
        cout << "Starting in " << i << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // car objects
    vector<unique_ptr<BaseCar>> cars;

    cars.emplace_back(std::make_unique<NormalCar>("NormalCar-1"));
    cars.emplace_back(std::make_unique<FastCar>("FastCar-2"));
    cars.emplace_back(std::make_unique<SteadyCar>("SteadyCar-3"));
    cars.emplace_back(std::make_unique<NormalCar>("NormalCar-4"));
    cars.emplace_back(std::make_unique<FastCar>("FastCar-5"));

    // main game loop
    while (BaseCar::GetWinner().empty()) {
        cout << "\033[2J\033[3J\033[H";
        cout << "\n";
        
        for (int i = 0; i < cars.size(); ++i) {
            BaseCar& car = *cars[i]; 

            // update and render car
            car.Update();

            string name = car.GetModel();
            name.resize(15, ' ');

            cout << name << " |";
            cout << string(car.GetPosition(), ' ') << "[CAR]\n";
        }
        
        cout << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // game over
    cout << "\n!!! WINNER: " << BaseCar::GetWinner() << " !!!\n\n";

    return 0;
}