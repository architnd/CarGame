#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
using namespace std;
class ICar {
 public:
  virtual ~ICar() = default;
  virtual std::string GetModel() const = 0;
  
  // Added to interface so we don't need to cast to MyCar
  virtual int GetPosition() const = 0; 
  virtual void Update() = 0;           
};

class MyCar : public ICar {
 private:
  std::string model_;
  int position_{0};

  static inline int finishLine_ = 60;
  static inline std::string winnerName_;

 public:
  MyCar(std::string model)
      : model_(model) {}

  ~MyCar() override = default;

  string GetModel() const override {
    return model_;
  }

  // Added override keyword
  int GetPosition() const override {
    return position_;
  }

  // Added override keyword
  void Update() override {
    if (winnerName_.empty()) {
      position_ += rand() % 3;
      
      if (position_ >= finishLine_ && winnerName_.empty()) {
        winnerName_ = model_;
      }
    }
  }

  static string GetWinner() {
    return winnerName_;
  }
};

int main() {
  srand(time(nullptr));

  int numCars = 5;
  vector<unique_ptr<ICar>> cars;

  for (int i = 0; i < numCars; ++i) {
    cars.emplace_back(std::make_unique<MyCar>(
        "CAR-" + std::to_string(i + 1)));
  }

  // Main Game/Renderer Loop
  while (MyCar::GetWinner().empty()) {
    cout << "\033[2J\033[H";
    cout << "\n";
    for (int i = 0; i < numCars; ++i) {
      // Dereference the unique_ptr to get a reference to the interface
      // No dynamic_cast or pointers needed!
      ICar& car = *cars[i]; 
      
      // Update car position
      car.Update();
      
      // Render car
      cout << car.GetModel() << " : ";
      cout << string(car.GetPosition(), ' ') << "[CAR]---->\n";
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  cout << "\nWinner car: " << MyCar::GetWinner() << "\n";

  return 0;
}