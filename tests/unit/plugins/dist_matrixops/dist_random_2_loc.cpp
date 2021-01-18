// Copyright (c) 2020 Hartmut Kaiser
// Copyright (c) 2020 Bita Hasheminezhad
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

void test_random_d_operation(std::string const& name, std::string const& code,
    std::string const& expected_str)
{
    phylanx::execution_tree::primitive_argument_type result =
        compile_and_run(name, code);
    phylanx::execution_tree::primitive_argument_type comparison =
        compile_and_run(name, expected_str);

    // comparing annotations
    HPX_TEST_EQ(hpx::cout, *(result.annotation()),*(comparison.annotation()));
}

///////////////////////////////////////////////////////////////////////////////
void test_random_1d_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc1d_0", R"(
            random_d(list(4), 0, 2)
        )", R"(
            annotate_d([42.0, 42.0], "random_array_1",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 2))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc1d_0", R"(
            random_d(list(4), 1, 2)
        )", R"(
            annotate_d([42.0, 42.0], "random_array_1",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 2, 4))))
        )");
    }
}

void test_random_1d_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc1d_1", R"(
            random_d(list(5), 0, 2)
        )", R"(
            annotate_d([42.0, 42.0, 42.0], "random_array_2",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 3))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc1d_1", R"(
            random_d(list(5), 1, 2)
        )", R"(
            annotate_d([42.0, 42.0], "random_array_2",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 3, 5))))
        )");
    }
}

void test_random_1d_2()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc1d_2", R"(
            random_d(list(7), 0, 2, "my_rand_13")
        )", R"(
            annotate_d([13.0, 13.0, 13.0, 13.0], "my_rand_13",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 4))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc1d_2", R"(
            random_d(list(7), 1, 2, "my_rand_13")
        )", R"(
            annotate_d([13.0, 13.0, 13.0], "my_rand_13",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 4, 7))))
        )");
    }
}

void test_random_1d_3()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test1d_3", R"(
            random_d(list(7), 0, 2, "my_rand_13_2", "sym")
        )", R"(
            annotate_d([13, 13, 13, 13], "my_rand_13_2",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 4))))
        )");
    }
    else
    {
        test_random_d_operation("test1d_3", R"(
            random_d(list(7), 1, 2, "my_rand_13_2", "sym")
        )", R"(
            annotate_d([13, 13, 13], "my_rand_13_2",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 4, 7))))
        )");
    }
}

///////////////////////////////////////////////////////////////////////////////
void test_random_2d_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc2d_0", R"(
            random_d(list(4, 6), 0, 2)
        )", R"(
            annotate_d([[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]],
                "random_array_3",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 3), list("rows", 0, 4))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc2d_0", R"(
            random_d(list(4, 6), 1, 2)
        )", R"(
            annotate_d([[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]],
                "random_array_3",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 3, 6), list("rows", 0, 4))))
        )");
    }
}

void test_random_2d_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc2d_1", R"(
            random_d(list(5, 4), 0, 2, "rand_42", "column")
        )", R"(
            annotate_d([[42.0, 42.0], [42.0, 42.0], [42.0, 42.0],
                        [42.0, 42.0], [42.0, 42.0]],
                "rand_42",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 2), list("rows", 0, 5))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc2d_1", R"(
            random_d(list(5, 4), 1, 2, "rand_42", "column")
        )", R"(
            annotate_d([[42.0, 42.0], [42.0, 42.0], [42.0, 42.0],
                        [42.0, 42.0], [42.0, 42.0]],
                "rand_42",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 2, 4), list("rows", 0, 5))))
        )");
    }
}

void test_random_2d_2()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc2d_2", R"(
            random_d(list(5, 4), 0, 2, "rand_5_4", "row")
        )", R"(
            annotate_d([[42.0, 42.0, 42.0, 42.0], [42.0, 42.0, 42.0, 42.0],
                [42.0, 42.0, 42.0, 42.0]],
                "rand_5_4",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 4), list("rows", 0, 3))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc2d_2", R"(
            random_d(list(5, 4), 1, 2, "rand_5_4", "row")
        )", R"(
            annotate_d([[42.0, 42.0, 42.0, 42.0], [42.0, 42.0, 42.0, 42.0]],
                "rand_5_4",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 0, 4), list("rows", 3, 5))))
        )");
    }
}

///////////////////////////////////////////////////////////////////////////////
void test_random_3d_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc3d_0", R"(
            random_d(list(2, 4, 6))
        )", R"(
            annotate_d([[[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]],
                        [[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]]],
                "random_array_4",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 3),
                        list("pages", 0, 2), list("rows", 0, 4))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc3d_0", R"(
            random_d(list(2, 4, 6))
        )", R"(
            annotate_d([[[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]],
                        [[42.0, 42.0, 42.0], [42.0, 42.0, 42.0],
                        [42.0, 42.0, 42.0], [42.0, 42.0, 42.0]]],
                "random_array_4",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 3, 6),
                        list("rows", 0, 4), list("pages", 0, 2))))
        )");
    }
}

void test_random_3d_1()
{
    if (hpx::get_locality_id() == 0)
    {
        test_random_d_operation("test_random_2loc3d_1", R"(
            random_d(list(2, 2, 2))
        )", R"(
            annotate_d([[[42.0, 42.0], [42.0, 42.0]]],
                "random_array_5",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 2),
                        list("pages", 0, 1), list("rows", 0, 2))))
        )");
    }
    else
    {
        test_random_d_operation("test_random_2loc3d_1", R"(
            random_d(list(2, 2, 2))
        )", R"(
            annotate_d([[[42.0, 42.0], [42.0, 42.0]]],
                "random_array_5",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 0, 2),
                        list("rows", 0, 2), list("pages", 1, 2))))
        )");
    }
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(int argc, char* argv[])
{
    // only annotations are compared
    test_random_1d_0();
    test_random_1d_1();
    test_random_1d_2();
    test_random_1d_3();

    test_random_2d_0();
    test_random_2d_1();
    test_random_2d_2();

    test_random_3d_0();
    test_random_3d_1();

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

