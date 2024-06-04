#include <cmath>
#include <iostream>
#include <vector>

struct Vector2 {
  double x, y;
  Vector2(double x, double y) : x(x), y(y){};
  Vector2() = default;
};

std::ostream &operator<<(std::ostream &output, Vector2 vec) {
  output << "(" << vec.x << "," << vec.y << ")";
  return output;
}

class Segment {
private:
  Vector2 begin;
  Vector2 end;
  double planeVelocity;
  double beginTime;
  double endTime;

public:
  virtual void Show() {
    std::cout << begin << '\t' << end << '\t' << planeVelocity << '\t'
              << beginTime << '\t' << endTime;
  }
  virtual double calculateEndTime() {
    double result{};
    double distance = sqrt(pow(end.x - begin.x, 2) + pow(end.y - begin.y, 2));
    result = distance / planeVelocity;
    return result + beginTime;
  }
  Segment(Vector2 begin_, Vector2 end_, double plane_, double timeB)
      : begin(begin_), end(end_), planeVelocity(plane_), beginTime(timeB) {
    endTime = calculateEndTime();
  }
};

class FlightPlan {
public:
  FlightPlan() = default;
  ~FlightPlan() = default;
  void addSegment(Vector2 begin, Vector2 end, double plane, double time_begin) {
    Segment newSeg(begin, end, plane, time_begin);
    flightParts.push_back(newSeg);
  }
  void printOut() {
    std::cout << "BEGIN\tEND\tVELOCITY\tBEGINTIME\tENDTIME\n";
    for (auto segment : flightParts) {
      segment.Show();
      std::cout << '\n';
    }
  }

private:
  std::vector<Segment> flightParts;
};

int main() {
  Vector2 begin1(0.0, 0.0), end1(32.0, -12.0), begin2(-36.0, -500.0),
      end2(50.0, 1000.0);
  double begtime1 = 591.4, begtime2 = 3900.32, plane1 = 16.0, plane2 = 50.0;
  FlightPlan Boeing{};
  Boeing.addSegment(begin1,end1,plane1,begtime1);
  Boeing.addSegment(begin2,end2,plane2,begtime2);
  Boeing.printOut();
  return 0;
}