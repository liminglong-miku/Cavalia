#pragma once
#ifndef __CAVALIA_TPCC_BENCHMARK_TPCC_COMMAND_REPLAYER_H__
#define __CAVALIA_TPCC_BENCHMARK_TPCC_COMMAND_REPLAYER_H__

#include <Replayer/CommandReplayer.h>

#include "AtomicProcedures/DeliveryProcedure.h"
#include "AtomicProcedures/NewOrderProcedure.h"
#include "AtomicProcedures/PaymentProcedure.h"
#include "AtomicProcedures/OrderStatusProcedure.h"
#include "AtomicProcedures/StockLevelProcedure.h"

namespace Cavalia{
	namespace Benchmark{
		namespace Tpcc{
			namespace Replayer{
				using namespace Cavalia::Database;
				class TpccCommandReplayer : public CommandReplayer{
				public:
					TpccCommandReplayer(const std::string &filename, BaseStorageManager *const storage_manager, const size_t &thread_count) : CommandReplayer(filename, storage_manager, thread_count){}
					virtual ~TpccCommandReplayer(){}

				private:
					virtual void PrepareProcedures(){
						using namespace AtomicProcedures;
						registers_[TupleType::DELIVERY] = [](size_t node_id) {
							DeliveryProcedure *procedure = (DeliveryProcedure*)MemAllocator::AllocNode(sizeof(DeliveryProcedure), node_id);
							new(procedure)DeliveryProcedure(TupleType::DELIVERY);
							return procedure;
						};
						deregisters_[TupleType::DELIVERY] = [](char *ptr){
							MemAllocator::FreeNode(ptr, sizeof(DeliveryProcedure));
						};
						registers_[TupleType::NEW_ORDER] = [](size_t node_id) {
							NewOrderProcedure *procedure = (NewOrderProcedure*)MemAllocator::AllocNode(sizeof(NewOrderProcedure), node_id);
							new(procedure)NewOrderProcedure(TupleType::NEW_ORDER);
							return procedure;
						};
						deregisters_[TupleType::NEW_ORDER] = [](char *ptr){
							MemAllocator::FreeNode(ptr, sizeof(NewOrderProcedure));
						};
						registers_[TupleType::PAYMENT] = [](size_t node_id) {
							PaymentProcedure *procedure = (PaymentProcedure*)MemAllocator::AllocNode(sizeof(PaymentProcedure), node_id);
							new(procedure)PaymentProcedure(TupleType::PAYMENT);
							return procedure;
						};
						deregisters_[TupleType::PAYMENT] = [](char *ptr){
							MemAllocator::FreeNode(ptr, sizeof(PaymentProcedure));
						};
						registers_[TupleType::ORDER_STATUS] = [](size_t node_id) {
							OrderStatusProcedure *procedure = (OrderStatusProcedure*)MemAllocator::AllocNode(sizeof(OrderStatusProcedure), node_id);
							new(procedure)OrderStatusProcedure(TupleType::ORDER_STATUS);
							return procedure;
						};
						deregisters_[TupleType::ORDER_STATUS] = [](char *ptr){
							MemAllocator::FreeNode(ptr, sizeof(OrderStatusProcedure));
						};
						registers_[TupleType::STOCK_LEVEL] = [](size_t node_id) {
							StockLevelProcedure *procedure = (StockLevelProcedure*)MemAllocator::AllocNode(sizeof(StockLevelProcedure), node_id);
							new(procedure)StockLevelProcedure(TupleType::STOCK_LEVEL);
							return procedure;
						};
						deregisters_[TupleType::STOCK_LEVEL] = [](char *ptr){
							MemAllocator::FreeNode(ptr, sizeof(StockLevelProcedure));
						};
					}

					virtual TxnParam* DeserializeParam(const size_t &param_type, const CharArray &entry){
						TxnParam *tuple;
						if (param_type == TupleType::DELIVERY){
							tuple = new DeliveryParam();
						}
						else if (param_type == TupleType::NEW_ORDER){
							tuple = new NewOrderParam();
						}
						else if (param_type == TupleType::PAYMENT){
							tuple = new PaymentParam();
						}
						else{
							return NULL;
						}
						tuple->Deserialize(entry);
						return tuple;
					}

				private:
					TpccCommandReplayer(const TpccCommandReplayer &);
					TpccCommandReplayer& operator=(const TpccCommandReplayer &);
				};
			}
		}
	}
}

#endif
