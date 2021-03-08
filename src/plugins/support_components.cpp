//  Copyright (c) 2019 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>
#include <phylanx/util/distributed_vector.hpp>
#include <phylanx/util/distributed_tensor.hpp>
#include <phylanx/util/distributed_matrix.hpp>

#include <cstddef>
#include <cstdint>
#include <utility>

#include <blaze/Math.h>
#include <blaze_tensor/Math.h>

////////////////////////////////////////////////////////////////////////////////
using std_int64_t = std::int64_t;
using std_uint8_t = std::uint8_t;

REGISTER_DISTRIBUTED_VECTOR(double);
REGISTER_DISTRIBUTED_VECTOR(std_int64_t);
REGISTER_DISTRIBUTED_VECTOR(std_uint8_t);

REGISTER_DISTRIBUTED_MATRIX(double);
REGISTER_DISTRIBUTED_MATRIX(std_int64_t);
REGISTER_DISTRIBUTED_MATRIX(std_uint8_t);

REGISTER_DISTRIBUTED_TENSOR(double);
REGISTER_DISTRIBUTED_TENSOR(std_int64_t);
REGISTER_DISTRIBUTED_TENSOR(std_uint8_t);

