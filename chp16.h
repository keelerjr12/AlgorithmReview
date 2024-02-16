#ifndef CHP_16_H
#define CHP_16_H

#include <vector>

struct Activity {
  double start;
  double end;
};

std::vector<Activity> select(const std::vector<Activity>& activities);

#endif // CHP_16_H
