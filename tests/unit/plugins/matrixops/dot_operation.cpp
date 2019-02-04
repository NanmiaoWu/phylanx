//   Copyright (c) 2017 Hartmut Kaiser
//   Copyright (c) 2017 Parsa Amini
//   Copyright (c) 2019 Bita Hasheminezhad
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/phylanx.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <blaze/Math.h>

void test_dot_operation_0d()
{
    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(7.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();
    HPX_TEST_EQ(
        42.0, phylanx::execution_tree::extract_numeric_value(f.get())[0]);
}

void test_dot_operation_0d_lit()
{
    phylanx::ir::node_data<double> lhs(6.0);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(7.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();
    HPX_TEST_EQ(
        42.0, phylanx::execution_tree::extract_numeric_value(f.get())[0]);
}

void test_dot_operation_0d1d()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(1007UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected = 6.0 * v;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_0d1d_lit()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(1007UL);

    phylanx::ir::node_data<double> lhs(6.0);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected = 6.0 * v;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_0d1d_numpy()
{
    blaze::DynamicVector<double> v{1.0, 3.0, 4.0};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();
    blaze::DynamicVector<double> expected{6.0, 18.0, 24.0};
    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_0d2d()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m = gen.generate(101UL, 101UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected = 6.0 * m;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_0d2d_lit()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m = gen.generate(101UL, 101UL);

    phylanx::ir::node_data<double> lhs(6.0);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected = 6.0 * m;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_0d2d_numpy()
{
    blaze::DynamicMatrix<double> m{{1.0, 3.0, 4.0}, {2.0, 5.0, 6.0}};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected{
        {6.0, 18.0, 24.0}, {12.0, 30.0, 36.0}};
    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d0d()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(1007UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected = v * 6.0;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d0d_lit()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(1007UL);

    phylanx::ir::node_data<double> lhs(v);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected = v * 6.0;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d0d_numpy()
{
    blaze::DynamicVector<double> v{1.0, 3.0, 4.0};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();
    blaze::DynamicVector<double> expected{6.0, 18.0, 24.0};
    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v1 = gen.generate(1007UL);
    blaze::DynamicVector<double> v2 = gen.generate(1007UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v1));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v2));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    double expected = blaze::dot(v1, v2);

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d_lit()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v1 = gen.generate(1007UL);
    blaze::DynamicVector<double> v2 = gen.generate(1007UL);

    phylanx::ir::node_data<double> lhs(v1);

    phylanx::execution_tree::primitive rhs =
            phylanx::execution_tree::primitives::create_variable(
                    hpx::find_here(), phylanx::ir::node_data<double>(v2));

    phylanx::execution_tree::primitive dot =
            phylanx::execution_tree::primitives::create_dot_operation(
                    hpx::find_here(),
                    phylanx::execution_tree::primitive_arguments_type{
                            std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
            dot.eval();

    double expected = blaze::dot(v1, v2);

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
                phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d_numpy()
{
    blaze::DynamicVector<double> v1{1.0, 4.0, 9.0, 7.0};
    blaze::DynamicVector<double> v2{3.0, 2.0, 1.0, 0.0};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v1));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v2));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    double expected=20.0;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d2d()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(101UL);

    blaze::Rand<blaze::DynamicMatrix<double>> mat_gen{};
    blaze::DynamicMatrix<double> m = mat_gen.generate(101UL, 104UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected = blaze::trans(blaze::trans(v) * m);

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d2d_lit()
{
    blaze::Rand<blaze::DynamicVector<double>> gen{};
    blaze::DynamicVector<double> v = gen.generate(101UL);

    blaze::Rand<blaze::DynamicMatrix<double>> mat_gen{};
    blaze::DynamicMatrix<double> m = mat_gen.generate(101UL, 104UL);

    phylanx::ir::node_data<double> lhs(v);

    phylanx::execution_tree::primitive rhs =
            phylanx::execution_tree::primitives::create_variable(
                    hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
            phylanx::execution_tree::primitives::create_dot_operation(
                    hpx::find_here(),
                    phylanx::execution_tree::primitive_arguments_type{
                            std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
            dot.eval();

    blaze::DynamicVector<double> expected = blaze::trans(blaze::trans(v) * m);

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
                phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_1d2d_numpy()
{
    blaze::DynamicVector<double> v{4.0, 2.0, 3.0};
    blaze::DynamicMatrix<double> m{
        {2.0, 3.0, 4.0}, {1.0, 3.0, 4.0}, {2.0, 5.0, 6.0}};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected{16.0, 33.0, 42.0};
    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d0d()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m = gen.generate(101UL, 101UL);

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected = m * 6.0;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d0d_lit()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m = gen.generate(101UL, 101UL);

    phylanx::ir::node_data<double> lhs(m);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected = m * 6.0;

    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d0d_numpy()
{
    blaze::DynamicMatrix<double> m{{1.0, 3.0, 4.0}, {2.0, 5.0, 6.0}};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(6.0));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected{
        {6.0, 18.0, 24.0}, {12.0, 30.0, 36.0}};
    HPX_TEST_EQ(phylanx::ir::node_data<double>{expected},
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d1d()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen1{};
    blaze::DynamicMatrix<double> m = gen1.generate(1007UL, 42UL);

    blaze::Rand<blaze::DynamicVector<double>> gen2{};
    blaze::DynamicVector<double> v = gen2.generate(42UL);

    blaze::DynamicVector<double> expected = m * v;

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
        std::move(lhs), std::move(rhs)
    });

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d1d_lit()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen1{};
    blaze::DynamicMatrix<double> m = gen1.generate(1007UL, 42UL);

    blaze::Rand<blaze::DynamicVector<double>> gen2{};
    blaze::DynamicVector<double> v = gen2.generate(42UL);

    blaze::DynamicVector<double> expected = m * v;

    phylanx::ir::node_data<double> lhs(m);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d1d_numpy()
{
    blaze::DynamicVector<double> v{4.0, 2.0, 3.0};
    blaze::DynamicMatrix<double> m{
        {2.0, 3.0, 4.0}, {1.0, 3.0, 4.0}};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(v));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicVector<double> expected{26.0, 22.0};
    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d2d()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m1 = gen.generate(42UL, 42UL);
    blaze::DynamicMatrix<double> m2 = gen.generate(42UL, 42UL);

    blaze::DynamicMatrix<double> expected = m1 * m2;

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m1));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m2));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)
            });

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d2d_lit()
{
    blaze::Rand<blaze::DynamicMatrix<double>> gen{};
    blaze::DynamicMatrix<double> m1 = gen.generate(42UL, 42UL);
    blaze::DynamicMatrix<double> m2 = gen.generate(42UL, 42UL);

    blaze::DynamicMatrix<double> expected = m1 * m2;

    phylanx::ir::node_data<double> lhs(m1);

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m2));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_dot_operation_2d2d_numpy()
{
    blaze::DynamicMatrix<double> m1{{4.0, 2.0}, {3.0, 5.0}};
    blaze::DynamicMatrix<double> m2{{2.0, 3.0, 4.0}, {1.0, 3.0, 4.0}};

    phylanx::execution_tree::primitive lhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m1));

    phylanx::execution_tree::primitive rhs =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(m2));

    phylanx::execution_tree::primitive dot =
        phylanx::execution_tree::primitives::create_dot_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(lhs), std::move(rhs)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        dot.eval();

    blaze::DynamicMatrix<double> expected{
        {10.0, 18.0, 24.0}, {11.0, 24.0, 32.0}};
    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

///////////////////////////////////////////////////////////////////////////////
phylanx::execution_tree::primitive_argument_type compile_and_run(
    std::string const& codestr)
{
    phylanx::execution_tree::compiler::function_list snippets;
    phylanx::execution_tree::compiler::environment env =
        phylanx::execution_tree::compiler::default_environment();

    auto const& code = phylanx::execution_tree::compile(codestr, snippets, env);
    return code.run();
}

///////////////////////////////////////////////////////////////////////////////
void test_dot_operation(std::string const& code,
    std::string const& expected_str)
{
    HPX_TEST_EQ(compile_and_run(code), compile_and_run(expected_str));
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // outer product
    //test_dot_operation("outer(6., 7.)", "[[42.]]");
    //test_dot_operation("outer(6., [1, 2, 7])", "[[6., 12., 42.]]");
    //test_dot_operation("outer(3., [[1, 2, 7]])", "[[3., 6., 21.]]");
    //test_dot_operation("outer([0, 7, 1], 6)", "[[ 0], [42], [ 6]]");
    test_dot_operation("outer([1, 2, 3], [4, 5, 6, 7])",
        "[[ 4,  5,  6,  7],[ 8, 10, 12, 14],[12, 15, 18, 21]]");
    //test_dot_operation("outer([1, 2, 3], [[42, 1, 1],[4, 5, 6]])",
    //    "[[ 42,   1,   1,   4,   5,   6],[ 84,   2,   2,   8,  10,  12],"
    //    "[126,   3,   3,  12,  15,  18]]");
    //test_dot_operation("outer([[1,1],[2,3]], 3)", "[[3],[3],[6],[9]");
    //test_dot_operation("outer([[1, 1],[2, 3]], [1, 4, 5])",
    //    "[[ 1,  4,  5],[ 1,  4,  5],[ 2,  8, 10],[ 3, 12, 15]]");
    //test_dot_operation("outer([[1, 1],[2, 3]], [[1, 4, 5]])",
    //    "[[ 1,  4,  5],[ 1,  4,  5],[ 2,  8, 10],[ 3, 12, 15]]");

#if defined(PHYLANX_HAVE_BLAZE_TENSOR)
    //test_dot_operation("outer(3, [[[1,2],[2,3]]])", "[[3, 6, 6, 9]]");
    //test_dot_operation("outer([1, 2, 3], [[[42, 1]],[[4, 5]]])",
    //    "[[ 42,   1,   4,   5], [ 84,   2,   8,  10], [126,   3,  12,  15]]");
    //test_dot_operation("outer([[1, 2],[4, 3]], [[[42, 1]],[[4, 5]]])",
    //    "[[ 42,   1,   4,   5], [ 84,   2,   8,  10], [168,   4,  16,  20], "
    //    "[126,  3,  12,  15]]");
    //test_dot_operation("outer([[[-1, 6],[1, 3]]], [[[0, 7]],[[2, 3]]])",
    //    "[[ 0, -7, -2, -3],[ 0, 42, 12, 18],[ 0, 7, 2, 3],[ 0, 21, 6, 9]]");
    //test_dot_operation("outer([[[-1, 6],[1, 3]]], 7)", "[[-7],[42],[ 7],[21]]");
    //test_dot_operation("outer([[[-1, 6],[1, 3]]], [0, 2, 7])",
    //    "[[ 0, -2, -7],[ 0, 12, 42],[ 0,  2,  7],[ 0,  6, 21]]");
    //test_dot_operation("outer([[[-1, 6],[1, 3]]], [[0, 2],[4, 7]])",
    //    "[[ 0, -2, -4, -7],[ 0, 12, 24, 42],[ 0, 2, 4, 7],[ 0,  6, 12, 21]]");
#endif

    // dot product
    test_dot_operation_0d();
    test_dot_operation_0d_lit();
    test_dot_operation_0d1d();
    test_dot_operation_0d1d_lit();
    test_dot_operation_0d1d_numpy();
    test_dot_operation_0d2d();
    test_dot_operation_0d2d_lit();
    test_dot_operation_0d2d_numpy();

    test_dot_operation_1d0d();
    test_dot_operation_1d0d_lit();
    test_dot_operation_1d0d_numpy();
    test_dot_operation_1d();
    test_dot_operation_1d_lit();
    test_dot_operation_1d_numpy();
    test_dot_operation_1d2d();
    test_dot_operation_1d2d_lit();
    test_dot_operation_1d2d_numpy();

    test_dot_operation_2d0d();
    test_dot_operation_2d0d_lit();
    test_dot_operation_2d0d_numpy();
    test_dot_operation_2d1d();
    test_dot_operation_2d1d_lit();
    test_dot_operation_2d1d_numpy();
    test_dot_operation_2d2d();
    test_dot_operation_2d2d_lit();
    test_dot_operation_2d2d_numpy();

#if defined(PHYLANX_HAVE_BLAZE_TENSOR)
    test_dot_operation("dot(2, [[[1,2,3,4]],[[5,6,7,8]]])",
                       "[[[ 2,  4,  6,  8]], [[10, 12, 14, 16]]]");
    test_dot_operation("dot([1,-1,0,1], [[[3, 2, 5.], [1, 10., 2], [3, 2, 15],"
        "[1, 11, 2]],[[4, 20, 5.], [1, 10., 2], [40, 12, 5], [1, 13, 21]]])",
        "[[ 3.,  3.,  5.], [ 4., 23., 24.]]");
    test_dot_operation(
        "dot([[1,-1,0, 1],[0, 1,0, 1]], [[[3, 2, 5.], [1, 10., 2], [3, 2, 15],"
        "[1, 11, 2]],[[4, 20, 5.], [1, 10., 2], [40, 12, 5], [1, 13, 21]]])",
        "[[[ 3.,  3.,  5.], [ 4., 23., 24.]], [[ 2., 21.,  4.], "
        "[ 2., 23., 23.]]]");

    test_dot_operation("dot([[[3, 2, 5], [1, 10, 2], [3, 42, 15], [1, 11, 2]]],"
        "3)",
        "[[[  9,   6,  15],[  3,  30,  6],[  9, 126,  45],[  3,  33,  6]]]");
    test_dot_operation("dot([[[3, 2, 5], [1, 10, 2], [3, 42, 15], [1, 11, 2]]],"
                       "[1, 0, 2])","[[13,  5, 33,  5]]");
    test_dot_operation("dot([[[3, 2, 5], [1, 10, 2], [3, 2, 15], [1, 11, 2]]],"
                       "[[1, -1],[1, 0],[2, 1]])",
        "[[[15,  2],[15,  1],[35, 12],[16,  1]]]");
#endif

    // tensordot
    //// axes = 0 (scalar axes)
    test_dot_operation("tensordot(6., 7., 0)", "42.");
    test_dot_operation("tensordot(6., [1, 2, 7], 0)", "[6., 12., 42.]");
    test_dot_operation("tensordot(3., [[1, 2, 7]], 0)", "[[3., 6., 21.]]");
    test_dot_operation("tensordot([0, 7, 1], 6, 0)", "[0, 42, 6]");
    test_dot_operation("tensordot([1, 2, 3], [4, 5, 6, 7], 0)",
        "[[ 4,  5,  6,  7],[ 8, 10, 12, 14],[12, 15, 18, 21]]");
    test_dot_operation("tensordot([[1,1],[2,3]], 3, 0)", "[[3, 3],[6, 9]]");

#if defined(PHYLANX_HAVE_BLAZE_TENSOR)
    test_dot_operation(
        "tensordot(3, [[[1,2],[2,3]]], 0)", "[[[3, 6],[6, 9]]]");
    test_dot_operation("tensordot([1, 2, 3], [[42, 1, 1],[4, 5, 6]], 0)",
        "[[[ 42,  1,  1],[  4,  5,  6]],[[ 84,  2,  2],[ 8, 10,  12]],"
        "[[126,  3,  3],[ 12,  15,  18]]]");
    test_dot_operation("tensordot([[[1,2],[2,3]]], 3, 0)", "[[[3, 6],[6, 9]]]");
    test_dot_operation("tensordot([[42, 1, 1],[4, 5, 6]], [1, 2], 0)",
        "[[[42, 84],[ 1,  2],[ 1,  2]],[[ 4,  8],[ 5, 10],[ 6, 12]]]");


#endif

    //// axes = 1 (scalar axes), same as dot product but does not deal with <1d
    test_dot_operation(
        "tensordot([1, 2, 3], [[42, 1],[4, 5],[0, 6]], 1)", "[50, 29]");

#if defined(PHYLANX_HAVE_BLAZE_TENSOR)
    test_dot_operation("tensordot([[[1, 2],[3, 4]],[[5, 6],[7, 8]]],[[1,-1],"
                       "[1, 1]], 1)",
        "[[[ 3,  1],[ 7,  1]],[[11,  1],[15,  1]]]");
    test_dot_operation(
        "tensordot([[[3, 2, 5], [1, 10, 2], [3, 42, 15], [1, 11, 2]]],"
        "[1, 0, 2], 1)", "[[13,  5, 33,  5]]");
#endif
    return hpx::util::report_errors();
}

