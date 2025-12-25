#include <iostream>
#include <memory>
#include <string>
using namespace std;
namespace game {
class ICar {
 public:
  virtual ~ICar() = default;
  virtual void setModel(const string& model) = 0;
};
class ICar2 {
 public:
  virtual ~ICar2() = default;
  virtual string getModel() const = 0;
};
class Car : public ICar, public ICar2 {
 private:
  string model_;

 public:
  Car() : model_("unnamed") { cout << "This is constructor\n"; }
  Car(const strin& model) : model_(model) {
    cout << "This is parameterised constructor\n";
  }
  ~Car() override = default;
  void setModel(const string& model) override {
    cout << "This is setModel\n";
    model_ = model;
  }
  string getModel() const override {
    cout << "This is getModel\n";
    return model_;
  }
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
  Car operator+(const Car& other) {
    cout << "This is + operator overloading\n";
    return Car(this->model_ + other.model_);
  }
};
}  // namespace game
using namespace game;
int main() {
  {
    Car c1;
    c1.setModel("audi");
    cout << c1.getModel() << "\n";
  }
}