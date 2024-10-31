#ifndef STATISTICS_H
#define STATISTICS_H

#include "IsingStats.h"
#include <cassert>
#include <cstdint>
#include <map>
#include <vector>

class StatisticalModel{
  private:
    std::vector<double> magnets;
    std::vector<int32_t> buckets;

    double avgMagnetism;
    double avgEnergy;
  public:
    StatisticalModel();
    void loadData(const SimulationResult& res){
      this->magnets = res.magnetismResults;
      this->buckets = res.bucketResults;
    }

    size_t size() {
      assert(magnets.size() == buckets.size());
      return magnets.size();
    }

    std::map<int32_t,uint32_t> countBuckets();
  
};

#endif