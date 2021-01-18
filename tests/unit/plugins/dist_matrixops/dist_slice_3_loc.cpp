// Copyright (c) 2020 Bita Hasheminezhad
// Copyright (c) 2020 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <phylanx/phylanx.hpp>

#include <hpx/hpx_init.hpp>
#include <hpx/iostream.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/modules/testing.hpp>

#include <string>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
phylanx::execution_tree::primitive_argument_type compile_and_run(
    std::string const& name, std::string const& codestr)
{
    phylanx::execution_tree::compiler::function_list snippets;
    phylanx::execution_tree::compiler::environment env =
        phylanx::execution_tree::compiler::default_environment();

    auto const& code =
        phylanx::execution_tree::compile(name, codestr, snippets, env);
    return code.run().arg_;
}

void test_slice_d_operation(std::string const& name, std::string const& code,
    std::string const& expected_str)
{
    phylanx::execution_tree::primitive_argument_type result =
        compile_and_run(name, code);
    phylanx::execution_tree::primitive_argument_type comparison =
        compile_and_run(name, expected_str);

    HPX_TEST_EQ(hpx::cout, result, comparison);
}

///////////////////////////////////////////////////////////////////////////////
void test_slice_column_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_column_3loc_0", R"(
            slice_column_d(annotate_d([[1, 2, 3]], "array_0",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 0, 3), list("rows", 3, 4)))),
            0)
        )", R"(
            annotate_d([1], "array_0_sliced/1",
                list("tile", list("columns", 3, 4)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_column_3loc_0", R"(
            slice_column_d(annotate_d([[4, 5, 6], [7, 8, 9]], "array_0",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 3), list("rows", 1, 3)))),
            0)
        )", R"(
            annotate_d([4, 7], "array_0_sliced/1",
                list("tile", list("columns", 1, 3)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_column_3loc_0", R"(
            slice_column_d(annotate_d([[-1, -2, -3]], "array_0",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 3), list("rows", 0, 1)))),
            0)
        )", R"(
            annotate_d([-1], "array_0_sliced/1",
                list("tile", list("columns", 0, 1)))
        )");
    }
}

void test_slice_column_local_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_column_3loc_local_0", R"(
            slice_column(annotate_d([[1, 2, 3]], "array_local_0",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 0, 3), list("rows", 3, 4)))),
            0)
        )", "[1]");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_column_3loc_local_0", R"(
            slice_column(annotate_d([[4, 5, 6], [7, 8, 9]], "array_local_0",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 3), list("rows", 1, 3)))),
            0)
        )", "[4, 7]");
    }
    else
    {
        test_slice_d_operation("test_slice_column_3loc_local_0", R"(
            slice_column(annotate_d([[-1, -2, -3]], "array_local_0",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 3), list("rows", 0, 1)))),
            0)
        )", "[-1]");
    }
}

void test_slice_column_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_column_3loc_1", R"(
            slice_column_d(annotate_d([[3, 4], [13, 14], [-3, -4], [-13, -14]],
                "array_1",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 2, 4), list("rows", 0, 4)))),
            1)
        )", R"(
            annotate_d([], "array_1_sliced/1",
                list("tile", list("columns", 0, 0)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_column_3loc_1", R"(
            slice_column_d(annotate_d([[1, 2], [11, 12]], "array_1",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 2), list("rows", 0, 2)))),
            1)
        )", R"(
            annotate_d([2, 12], "array_1_sliced/1",
                list("tile", list("columns", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_column_3loc_1", R"(
            slice_column_d(annotate_d([[-1, -2], [-11, -12]], "array_1",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 2), list("rows", 2, 4)))),
            1)
        )", R"(
            annotate_d([-2, -12], "array_1_sliced/1",
                list("tile", list("columns", 2, 4)))
        )");
    }
}

void test_slice_column_local_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_column_3loc_local_1", R"(
            slice_column(annotate_d([[3, 4], [13, 14], [-3, -4], [-13, -14]],
                "array_local_1",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 2, 4), list("rows", 0, 4)))),
            1)
        )", "[4, 14, -4, -14]");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_column_3loc_local_1", R"(
            slice_column(annotate_d([[1, 2], [11, 12]], "array_local_1",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 2), list("rows", 0, 2)))),
            1)
        )", "[2, 12]");
    }
    else
    {
        test_slice_d_operation("test_slice_column_3loc_local_1", R"(
            slice_column(annotate_d([[-1, -2], [-11, -12]], "array_local_1",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 2), list("rows", 2, 4)))),
            1)
        )", "[-2, -12]");
    }
}

void test_slice_row_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_0", R"(
            slice_row_d(annotate_d([[1, 2], [11, 12], [-1, -2], [-11, -12]],
                "array_2",
                list("tile", list("columns", 0, 2), list("rows", 0, 4))),
            3)
        )", R"(
            annotate_d([-11, -12], "array_2_sliced/1",
                list("tile", list("rows", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_0", R"(
            slice_row_d(annotate_d([[3], [13], [-3], [-13]], "array_2",
                    list("tile", list("columns", 2, 3), list("rows", 0, 4))),
            3)
        )", R"(
            annotate_d([-13], "array_2_sliced/1",
                list("tile", list("rows", 2, 3)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_0", R"(
            slice_row_d(annotate_d([[4], [14], [-4], [-14]], "array_2",
                    list("tile", list("columns", 3, 4), list("rows", 0, 4))),
            3)
        )", R"(
            annotate_d([-14], "array_2_sliced/1",
                list("tile", list("rows", 3, 4)))
        )");
    }
}

void test_slice_row_local_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_local_0", R"(
            slice_row(annotate_d([[1, 2], [11, 12], [-1, -2], [-11, -12]],
                "array_local_2",
                list("tile", list("columns", 0, 2), list("rows", 0, 4))),
            3)
        )", "[-11, -12]");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_local_0", R"(
            slice_row(annotate_d([[3], [13], [-3], [-13]], "array_local_2",
                    list("tile", list("columns", 2, 3), list("rows", 0, 4))),
            3)
        )", "[-13]");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_local_0", R"(
            slice_row(annotate_d([[4], [14], [-4], [-14]], "array_local_2",
                    list("tile", list("columns", 3, 4), list("rows", 0, 4))),
            3)
        )", "[-14]");
    }
}

void test_slice_row_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_1", R"(
            slice_row_d(annotate_d([[3, 4], [13, 14], [-3, -4], [-13, -14]],
                "array_3",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 2, 4), list("rows", 0, 4)))),
            1)
        )", R"(
            annotate_d([13, 14], "array_3_sliced/1",
                list("tile", list("rows", 2, 4)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_1", R"(
            slice_row_d(annotate_d([[1, 2], [11, 12]], "array_3",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 2), list("rows", 0, 2)))),
            1)
        )", R"(
            annotate_d([11, 12], "array_3_sliced/1",
                list("tile", list("rows", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_1", R"(
            slice_row_d(annotate_d([[-1, -2], [-11, -12]], "array_3",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 2), list("rows", 2, 4)))),
            1)
        )", R"(
            annotate_d([], "array_3_sliced/1",
                list("tile", list("rows", 0, 0)))
        )");
    }
}

void test_slice_row_local_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_local_1", R"(
            slice_row(annotate_d([[3, 4], [13, 14], [-3, -4], [-13, -14]],
                "array_local_3",
                list("args",
                    list("locality", 0, 3),
                    list("tile", list("columns", 2, 4), list("rows", 0, 4)))),
            1)
        )", "[13, 14]");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_local_1", R"(
            slice_row(annotate_d([[1, 2], [11, 12]], "array_local_3",
                list("args",
                    list("locality", 1, 3),
                    list("tile", list("columns", 0, 2), list("rows", 0, 2)))),
            1)
        )", "[11, 12]");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_local_1", R"(
            slice_row(annotate_d([[-1, -2], [-11, -12]], "array_local_3",
                list("args",
                    list("locality", 2, 3),
                    list("tile", list("columns", 0, 2), list("rows", 2, 4)))),
            1)
        )", "[-11, -12]");
    }
}

void test_slice_row_assign_2()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_2", R"(
            define(a, annotate_d([[1, 2], [4, 5], [7, 8]], "array_4",
                list("tile", list("columns", 0, 2), list("rows", 0, 3))))
            define(v, annotate_d([-7], "value_0",
                list("tile", list("columns", 0, 1))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[1, 2], [4, 5], [-7, -8]], "array_4/1",
                list("tile", list("rows", 0, 3), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_2", R"(
            define(a, annotate_d([[3], [6], [9]], "array_4",
                list("tile", list("columns", 2, 3), list("rows", 0, 3))))
            define(v, annotate_d([-8], "value_0",
                list("tile", list("columns", 1, 2))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[3], [6], [-9]], "array_4/1",
                list("tile", list("rows", 0, 3), list("columns", 2, 3)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_2", R"(
            define(a, annotate_d([[10, 11, 12]], "array_4",
                list("tile", list("columns", 0, 3), list("rows", 3, 4))))
            define(v, annotate_d([-9], "value_0",
                list("tile", list("columns", 2, 3))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[10, 11, 12]], "array_4/1",
                list("tile", list("rows", 3, 4), list("columns", 0, 3)))
        )");
    }
}

void test_slice_row_assign_3()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_3", R"(
            define(a, annotate_d([[1, 2], [5, 6]], "array_5",
                list("tile", list("columns", 0, 2), list("rows", 0, 2))))
            define(v, annotate_d([5], "value_1",
                list("tile", list("rows", 0, 1))))
            store(slice_row_d(a, 3), v)
            a
        )", R"(
            annotate_d([[1, 2], [5, 6]], "array_5/1",
                list("tile", list("rows", 0, 2), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_3", R"(
            define(a, annotate_d([[-1, -2], [-5, -6]], "array_5",
                list("tile", list("columns", 0, 2), list("rows", 2, 4))))
            define(v, annotate_d([6, 7], "value_1",
                list("tile", list("rows", 1, 3))))
            store(slice_row_d(a, 3), v)
            a
        )", R"(
            annotate_d([[-1, -2], [5, 6]], "array_5/1",
                list("tile", list("rows", 2, 4), list("columns", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_3", R"(
            define(a, annotate_d([[3, 4], [7, 8], [-3, -4], [-7, -8]], "array_5",
                list("tile", list("columns", 2, 4), list("rows", 0, 4))))
            define(v, annotate_d([8], "value_1",
                list("tile", list("rows", 3, 4))))
            store(slice_row_d(a, 3), v)
            a
        )", R"(
            annotate_d([[3, 4], [7, 8], [-3, -4], [7, 8]], "array_5/1",
                list("tile", list("rows", 0, 4), list("columns", 2, 4)))
        )");
    }
}

void test_slice_row_assign_4()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_4", R"(
            define(a, annotate_d([[1, 2], [4, 5], [7, 8]], "array_6",
                list("tile", list("columns", 0, 2), list("rows", 0, 3))))
            define(v, annotate_d([], "value_2",
                list("tile", list("columns", 0, 0))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[1, 2], [4, 5], [-7, -8]], "array_6/1",
                list("tile", list("rows", 0, 3), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_4", R"(
            define(a, annotate_d([[3], [6], [9]], "array_6",
                list("tile", list("columns", 2, 3), list("rows", 0, 3))))
            define(v, annotate_d([-7, -8], "value_2",
                list("tile", list("columns", 0, 2))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[3], [6], [-9]], "array_6/1",
                list("tile", list("rows", 0, 3), list("columns", 2, 3)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_4", R"(
            define(a, annotate_d([[10, 11, 12]], "array_6",
                list("tile", list("columns", 0, 3), list("rows", 3, 4))))
            define(v, annotate_d([-9], "value_2",
                list("tile", list("columns", 2, 3))))
            store(slice_row_d(a, 2), v)
            a
        )", R"(
            annotate_d([[10, 11, 12]], "array_6/1",
                list("tile", list("rows", 3, 4), list("columns", 0, 3)))
        )");
    }
}

void test_slice_row_assign_5()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_5", R"(
            define(a, annotate_d([[1, 2], [4, 5]], "array_7",
                list("tile", list("columns", 0, 2), list("rows", 0, 2))))
            define(v, annotate_d([], "value_3",
                list("tile", list("rows", 0, 0))))
            store(slice_row_d(a, 1), v)
            a
        )", R"(
            annotate_d([[1, 2], [42, 43]], "array_7/1",
                list("tile", list("rows", 0, 2), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_5", R"(
            define(a, annotate_d([[7, 8], [10, 11]], "array_7",
                list("tile", list("columns", 0, 2), list("rows", 2, 4))))
            define(v, annotate_d([], "value_3",
                list("tile", list("rows", 0, 0))))
            store(slice_row_d(a, 1), v)
            a
        )", R"(
            annotate_d([[7, 8], [10, 11]], "array_7/1",
                list("tile", list("rows", 2, 4), list("columns", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_5", R"(
            define(a, annotate_d([[3], [6], [9], [12]], "array_7",
                list("tile", list("columns", 2, 3), list("rows", 0, 4))))
            define(v, annotate_d([42, 43, 44], "value_3",
                list("tile", list("rows", 0, 3))))
            store(slice_row_d(a, 1), v)
            a
        )", R"(
            annotate_d([[3], [44], [9], [12]], "array_7/1",
                list("tile", list("rows", 0, 4), list("columns", 2, 3)))
        )");
    }
}

void test_slice_row_assign_local_2()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_local_2", R"(
            define(a, annotate_d([[1, 2], [4, 5], [7, 8]], "array_local_4",
                list("tile", list("columns", 0, 2), list("rows", 0, 3))))
            define(v, [-1, -2])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-1, -2], [4, 5], [7, 8]], "array_local_4/1",
                list("tile", list("rows", 0, 3), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_local_2", R"(
            define(a, annotate_d([[3], [6], [9]], "array_local_4",
                list("tile", list("columns", 2, 3), list("rows", 0, 3))))
            define(v, [-3])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-3], [6], [9]], "array_local_4/1",
                list("tile", list("rows", 0, 3), list("columns", 2, 3)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_local_2", R"(
            define(a, annotate_d([[10, 11, 12]], "array_local_4",
                list("tile", list("columns", 0, 3), list("rows", 3, 4))))
            define(v, [-10, -11, -12])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-10, -11, -12]], "array_local_4/1",
                list("tile", list("rows", 3, 4), list("columns", 0, 3)))
        )");
    }
}

void test_slice_row_assign_local_3()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_local_3", R"(
            define(a, annotate_d([[1, 2], [5, 6]], "array_local_5",
                list("tile", list("columns", 0, 2), list("rows", 0, 2))))
            define(v, [-5, -6])
            store(slice_row(a, 1), v)
            a
        )", R"(
            annotate_d([[1, 2], [-5, -6]], "array_local_5/1",
                list("tile", list("rows", 0, 2), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_local_3", R"(
            define(a, annotate_d([[-1, -2], [-5, -6]], "array_local_5",
                list("tile", list("columns", 0, 2), list("rows", 2, 4))))
            define(v, [5, 6])
            store(slice_row(a, 1), v)
            a
        )", R"(
            annotate_d([[-1, -2], [5, 6]], "array_local_5/1",
                list("tile", list("rows", 2, 4), list("columns", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_local_3", R"(
            define(a, annotate_d([[3, 4], [7, 8], [-3, -4], [-7, -8]],
                "array_local_5",
                list("tile", list("columns", 2, 4), list("rows", 0, 4))))
            define(v, [10, 11])
            store(slice_row(a, 1), v)
            a
        )", R"(
            annotate_d([[3, 4], [10, 11], [-3, -4], [-7, -8]],
                "array_local_5/1",
                list("tile", list("rows", 0, 4), list("columns", 2, 4)))
        )");
    }
}

void test_slice_row_assign_local_4()
{
    if (hpx::get_locality_id() == 0)
    {
        test_slice_d_operation("test_slice_row_3loc_local_4", R"(
            define(a, annotate_d([[1, 2], [4, 5]], "array_local_6",
                list("tile", list("columns", 0, 2), list("rows", 0, 2))))
            define(v, [-1, -2])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-1, -2], [4, 5]], "array_local_6/1",
                list("tile", list("rows", 0, 2), list("columns", 0, 2)))
        )");
    }
    else if (hpx::get_locality_id() == 1)
    {
        test_slice_d_operation("test_slice_row_3loc_local_4", R"(
            define(a, annotate_d([[7, 8], [10, 11]], "array_local_6",
                list("tile", list("columns", 0, 2), list("rows", 2, 4))))
            define(v, [-7, -8])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-7, -8], [10, 11]], "array_local_6/1",
                list("tile", list("rows", 2, 4), list("columns", 0, 2)))
        )");
    }
    else
    {
        test_slice_d_operation("test_slice_row_3loc_local_4", R"(
            define(a, annotate_d([[3], [6], [9], [12]], "array_local_6",
                list("tile", list("columns", 2, 3), list("rows", 0, 4))))
            define(v, [-3])
            store(slice_row(a, 0), v)
            a
        )", R"(
            annotate_d([[-3], [6], [9], [12]], "array_local_6/1",
                list("tile", list("rows", 0, 4), list("columns", 2, 3)))
        )");
    }
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(int argc, char* argv[])
{
    test_slice_column_0();
    test_slice_column_1();

    test_slice_column_local_0();
    test_slice_column_local_1();

    test_slice_row_0();
    test_slice_row_1();

    test_slice_row_local_0();
    test_slice_row_local_1();

    test_slice_row_assign_2();
    test_slice_row_assign_3();
    test_slice_row_assign_4();
    test_slice_row_assign_5();

    test_slice_row_assign_local_2();
    test_slice_row_assign_local_3();
    test_slice_row_assign_local_4();


    hpx::finalize();
    return hpx::util::report_errors();
}
int main(int argc, char* argv[])
{
    std::vector<std::string> cfg = {
        "hpx.run_hpx_main!=1"
    };

    hpx::init_params params;
    params.cfg = std::move(cfg);
    return hpx::init(argc, argv, params);
}

