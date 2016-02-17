/*
 *  Copyright (c) 2016, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include "mcrouter/lib/McRequest.h"
#include "mcrouter/lib/network/ThriftMessageList.h"
#include "mcrouter/lib/network/ThriftMessageTraits.h"
#include "mcrouter/lib/network/TypedThriftMessage.h"

namespace facebook {
namespace memcache {

/**
 * The following convertToMcRequest() methods convert requests,
 * in the form of Typed Structs to the corresponding McRequestWithOp<...>'s
 */
template <class GetType>
McRequestWithMcOp<OpFromType<GetType, RequestOpMapping>::value>
convertToMcRequest(TypedThriftMessage<GetType>&& treq,
                   GetLikeT<TypedThriftMessage<GetType>> = 0);

template <class UpdateType>
McRequestWithMcOp<OpFromType<UpdateType, RequestOpMapping>::value>
convertToMcRequest(TypedThriftMessage<UpdateType>&& treq,
                   UpdateLikeT<TypedThriftMessage<UpdateType>> = 0);

template <class DeleteType>
McRequestWithMcOp<OpFromType<DeleteType, RequestOpMapping>::value>
convertToMcRequest(TypedThriftMessage<DeleteType>&& treq,
                   DeleteLikeT<TypedThriftMessage<DeleteType>> = 0);

template <class ArithType>
McRequestWithMcOp<OpFromType<ArithType, RequestOpMapping>::value>
convertToMcRequest(TypedThriftMessage<ArithType>&& treq,
                   ArithmeticLikeT<TypedThriftMessage<ArithType>> = 0);

McRequestWithMcOp<mc_op_version>
convertToMcRequest(TypedThriftMessage<cpp2::McVersionRequest>&& treq);

McRequestWithMcOp<mc_op_touch>
convertToMcRequest(TypedThriftMessage<cpp2::McTouchRequest>&& treq);

} // memcache
} // facebook

#include "TypedToMcRequestConverter-inl.h"