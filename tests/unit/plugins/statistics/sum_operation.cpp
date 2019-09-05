// Copyright (c) 2018 Parsa Amini
// Copyright (c) 2018 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/phylanx.hpp>

#include <hpx/hpx_main.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/testing.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <blaze/Math.h>

void test_0d()
{
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(42.0));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{42.};

    HPX_TEST_EQ(
        expected, phylanx::execution_tree::extract_numeric_value(f.get())[0]);
}

void test_0d_keep_dims_true()
{
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(42.0));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{42.};

    HPX_TEST_EQ(
        expected, phylanx::execution_tree::extract_numeric_value(f.get())[0]);
}

void test_0d_keep_dims_false()
{
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(42.0));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{42.};

    HPX_TEST_EQ(
        expected, phylanx::execution_tree::extract_numeric_value(f.get())[0]);
}

void test_1d()
{
    blaze::DynamicVector<double> subject{6., 9., 13., 42., 54.};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 124.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_1d_keep_dims_true()
{
    blaze::DynamicVector<double> subject{6., 9., 13., 42., 54.};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(true));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{124.};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_1d_keep_dims_false()
{
    blaze::DynamicVector<double> subject{6., 9., 13., 42., 54.};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 124.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_1d_keep_dims_false_init()
{
    blaze::DynamicVector<double> subject{6., 9., 13., 42., 54.};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));
    phylanx::execution_tree::primitive init =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(2.));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0),
                std::move(arg1), std::move(arg2), std::move(init)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 126.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 178.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d_axis0()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(0));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{73., 105.};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d_axis1()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(1));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{15., 55., 108.};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d_keep_dims_true()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(true));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicMatrix<double> expected{{178.}};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d_keep_dims_false()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 178.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_2d_axis1_keep_dims_false_init()
{
    blaze::DynamicMatrix<double> subject{{6., 9.}, {13., 42.}, {54., 54.}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(0));
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));
    phylanx::execution_tree::primitive init =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(2));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0),
                std::move(arg1), std::move(arg2), std::move(init)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicVector<double> expected{75., 107.};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 178.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_axis0()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(0));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicMatrix<double> expected{{73., 105.}};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_axis1()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(1));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicMatrix<double> expected{{6., 9.}, {13., 42.}, {54., 54.}};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_axis2()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(2));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicMatrix<double> expected{{15.}, {55.}, {108.}};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_keep_dims_true()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(true));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicTensor<double> expected{{{178.}}};

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_keep_dims_false()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ast::nil{});
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{
                std::move(arg0), std::move(arg1), std::move(arg2)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    double expected = 178.;

    HPX_TEST_EQ(phylanx::ir::node_data<double>(std::move(expected)),
        phylanx::execution_tree::extract_numeric_value(f.get()));
}

void test_3d_axis2_keep_dims_false_init()
{
    blaze::DynamicTensor<double> subject{
        {{6., 9.}}, {{13., 42.}}, {{54., 54.}}};
    phylanx::execution_tree::primitive arg0 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(subject));
    phylanx::execution_tree::primitive arg1 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::int64_t>(2));
    phylanx::execution_tree::primitive arg2 =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<std::uint8_t>(false));
    phylanx::execution_tree::primitive init =
        phylanx::execution_tree::primitives::create_variable(
            hpx::find_here(), phylanx::ir::node_data<double>(2.));

    phylanx::execution_tree::primitive sum =
        phylanx::execution_tree::primitives::create_sum_operation(
            hpx::find_here(),
            phylanx::execution_tree::primitive_arguments_type{std::move(arg0),
                std::move(arg1), std::move(arg2), std::move(init)});

    hpx::future<phylanx::execution_tree::primitive_argument_type> f =
        sum.eval();

    blaze::DynamicMatrix<double> expected{{17.}, {57.}, {110.}};

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

void test_operation(std::string const& code, std::string const& expected_str)
{
    HPX_TEST_EQ(compile_and_run(code), compile_and_run(expected_str));
}

///////////////////////////////////////////////////////////////////////////////
void test_operation_3d_slice()
{
    test_operation("sum([[[1.,2.], [4.,1.], [3.,4.]],"
                   "[[3.,6.], [2.,-2.], [1.,1.]]], list(1,2))",
        "[15., 11.]");
    test_operation("sum([[[1.,2.], [4.,1.], [3.,4.]],"
                   "[[3.,6.], [2.,-2.], [1.,1.]]], list(0,-1))",
        "[12.,  5.,  9.]");
}

void test_operation_4d()
{
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]])",
        "54.0");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], nil, "
        "true)",
        "[[[[54.0]]]]");

    //test_operation(
    //    "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
    //    "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 0)",
    //    "[[[ 2.,  4.],[ 8.,  2.],[ 6.,  6.]],"
    //    "[[ 6., 12.],[ 0.,  4.],[ 2.,  2.]]]");
    //test_operation(
    //    "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
    //    "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 0, "
    //    "true)",
    //    "[[[[ 2.,  4.],[ 8.,  2.],[ 6.,  6.]],"
    //    "[[ 6., 12.],[ 0.,  4.],[ 2.,  2.]]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 1)",
        "[[[ 4.,  8.],[ 6., -1.],[ 4.,  5.]],"
        "[[ 4.,  8.],[ 2.,  7.],[ 4.,  3.]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 1, "
        "true)",
        "[[[[ 4.,  8.],[ 6., -1.],[ 4.,  5.]]],"
        "[[[ 4.,  8.],[ 2.,  7.],[ 4.,  3.]]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 2)",
        "[[[ 8.,  7.],[ 6.,  5.]],"
        "[[ 8.,  5.],[ 2., 13.]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 2, "
        "true)",
        "[[[[ 8.,  7.]],[[ 6.,  5.]]],"
        "[[[ 8.,  5.]],[[ 2., 13.]]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 3)",
        "[[[3., 5., 7.],[9., 0., 2.]],"
        "[[3., 5., 5.],[9., 4., 2.]]]");
    test_operation(
        "sum([[[[1.,2.], [4.,1.], [3.,4.]],[[3.,6.], [2.,-2.], [1.,1.]]],"
        "[[[1.,2.], [4.,1.], [3.,2.]],[[3.,6.], [-2.,6.], [1.,1.]]]], 3, "
        "true)",
        "[[[[3.],[5.],[7.]],"
        "[[9.],[0.],[2.]]],"
        "[[[3.],[5.],[5.]],"
        "[[9.],[4.],[2.]]]]");
}

int main(int argc, char* argv[])
{
    test_0d();
    test_1d();
    test_1d_keep_dims_true();
    test_1d_keep_dims_false();
    test_1d_keep_dims_false_init();
    test_2d();
    test_2d_axis0();
    test_2d_axis1();
    test_2d_keep_dims_true();
    test_2d_keep_dims_false();
    test_2d_axis1_keep_dims_false_init();
    test_3d();
    test_3d_axis0();
    test_3d_axis1();
    test_3d_axis2();
    test_3d_keep_dims_true();
    test_3d_keep_dims_false();
    test_3d_axis2_keep_dims_false_init();
    test_operation_3d_slice();

    test_operation_4d();

    return hpx::util::report_errors();
}
