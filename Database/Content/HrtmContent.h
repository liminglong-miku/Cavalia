#pragma once
#ifndef __CAVALIA_DATABASE_HRTM_CONTENT_H__
#define __CAVALIA_DATABASE_HRTM_CONTENT_H__

#include <atomic>
#include <cstdint>

namespace Cavalia {
	namespace Database {
		class HrtmContent {
		public:
			HrtmContent() : timestamp_(0) {}

			void SetTimestamp(const uint64_t &timestamp) {
				assert(timestamp_ <= timestamp);
				timestamp_.store(timestamp, std::memory_order_relaxed);
			}

			uint64_t GetTimestamp() const {
				return timestamp_.load(std::memory_order_relaxed);
			}

			uint64_t IncrementTimestamp() {
				return timestamp_.fetch_add(1, std::memory_order_relaxed);
			}

		private:
			std::atomic<uint64_t> timestamp_;
		};
	}
}

#endif
