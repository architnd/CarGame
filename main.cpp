#include <iostream>
#include <memory>
#include <string>
using namespace std;

namespace game {
class ICar {
 public:
  virtual ~ICar() = default;
  virtual void setModel(const std::string& model) = 0;
  virtual std::string getModel() const = 0;
};

class IVehicle {
 public:
  virtual ~IVehicle() = default;
  virtual void drive() = 0;
};

class Car : public ICar, public IVehicle {
 public:
  Car() : model_("unnamed") { cout << "This is a Default Constructor\n"; }
  Car(const std::string& model) : model_(model) {
    cout << "This is the parameterised constructor\n";
  }
  ~Car() override = default;
  void setModel(const std::string& model) override {
    cout << "This is setModel\n";
    model_ = model;
  }
  std::string getModel() const override {
    cout << "This is getModel\n";
    return model_;
  }
  void drive() override { cout << "This is drive\n"; }
  Car(const Car& other) {
    cout << "This is copy constructor\n";
    model_ = other.model_;
  }
  Car& operator=(const Car& other) {
    cout << "This is copy assignment operator\n";
    model_ = other.model_;
    return *this;
  }
  Car(Car&& other) {
    cout << "This is move constructor\n";
    model_ = std::move(other.model_);
  }
  Car& operator=(Car&& other) {
    cout << "This is move assignment operator\n";
    model_ = std::move(other.model_);
    return *this;
  }
  bool operator==(const Car& other) {
    cout << "This is == operator overloading\n";
    return this->model_ == other.model_;
  }
  Car operator+(const Car& other){
    cout << "This is + operator overloading\n";
    return Car(this->model_ + other.model_);
  }
  void operator()() {
    cout << "This is () operator overloading\n";
  }

 private:
  std::string model_;
};
}  // namespace game

using namespace game;

int main() {
  {
    Car c1;
    c1.setModel("mahindra");
    cout << c1.getModel() << "\n";
    c1.drive();
  }
  {
    Car c1("mahindra");
  }
  {
    Car* c1 = new Car("audi");
    cout << c1->getModel() << "\n";
    delete c1;
  }
  {
    std::unique_ptr<Car> c1 = std::make_unique<Car>("bmw");
    cout << c1->getModel() << "\n";
    // std::unique_ptr<Car> c2 = c1; //Not allowed
  }
  {
    std::shared_ptr<Car> c1 = std::make_shared<Car>("bmw");
    cout << c1->getModel() << "\n";
    std::shared_ptr<Car> c2 = c1;
    cout << c2->getModel() << "\n";
    cout << c1.use_count() << "\n";
    c2.reset();
    cout << c1.use_count() << "\n";
  }
  {
    Car c1("jaguar");
    Car c2(c1);
  }
  {
    Car c1("jaguar");
    Car c2;
    c2 = c1;
  }
  {
    Car c1("tesla");
    cout << c1.getModel() << "\n";
    Car c2(std::move(c1));
    cout << c1.getModel() << "\n";
    cout << c2.getModel() << "\n";
  }
  {
    Car c1("nano");
    Car c2;
    cout << c1.getModel() << "\n";
    c2 = std::move(c1);
    cout << c1.getModel() << "\n";
    cout << c2.getModel() << "\n";
  }
  {
    Car c1("toyota");
    Car c2;
    if (c1 == c2) {
      cout << "Equal\n";
    } else {
      cout << "Not Equal\n";
    }
  }
  {
    Car c1("jeep");
    Car c2("mercedes");
    Car c3(c1+c2);
    cout << c1.getModel() << "\n";
    cout << c2.getModel() << "\n";
    cout << c3.getModel() << "\n";
  }
  {
    Car c1("ferrari");
    c1();
  }
  return 0;
}