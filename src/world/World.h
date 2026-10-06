#pragma once
#include "world/Cell.h"
#include "app/Config.h"
#include <vector>
#include <deque>
#include <memory>
#include <cstddef>

namespace SSE {

class World {
public:
    World();

    void update(float cx, float cy);

    const CachedCell* cells() const { return cells_.get(); }
    std::size_t loadedCount() const { return loadedCount_; }
    std::size_t queueSize() const { return loadQueue_.size(); }

private:
    std::unique_ptr<CachedCell[]> cells_;
    std::vector<std::uint8_t> queued_;
    std::deque<int> loadQueue_;

    std::size_t loadedCount_ = 0;

    // Кэш последней обработанной ячейки для refillQueue
    int lastScanCcx_ = -999999;
    int lastScanCcy_ = -999999;

    // Кэш последней обработанной ячейки для unloadFarCells
    int lastUnloadCcx_ = -999999;
    int lastUnloadCcy_ = -999999;

    void loadCellData(int idx);
    void unloadFarCells(float cx, float cy, int ccx, int ccy, int r_cells);
    void refillQueue(float cx, float cy, int ccx, int ccy, int r_cells);
    void processQueue();
};

} // namespace SSE
