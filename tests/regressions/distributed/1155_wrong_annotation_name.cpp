// Copyright (c) 2020 Bita Hasheminezhad
// Copyright (c) 2020 Hartmut Kaiser

//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/phylanx.hpp>

#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/modules/testing.hpp>

#include <cstdint>
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

void test_dist_operation(std::string const& name, std::string const& code,
    std::string const& expected_str)
{
    phylanx::execution_tree::primitive_argument_type result =
        compile_and_run(name, code);
    phylanx::execution_tree::primitive_argument_type comparison =
        compile_and_run(name, expected_str);

    HPX_TEST_EQ(result, comparison);
}

////////////////////////////////////////////////////////////////////////////////
void test_maximum_1d_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_dist_operation("test_maximum_1d_2loc_0", R"(
            maximum(
                annotate_d([13., 42.], "lhs",
                    list("tile", list("columns", 0, 2))),
                annotate_d([101., 12.], "rhs",
                    list("tile", list("columns", 0, 2))))
        )", R"(
            annotate_d([101., 42.0], "lhs/1",
                list("args",
                    list("locality", 0, 2),
                    list("tile", list("columns", 0, 2))))
        )");
    }
    else
    {
        test_dist_operation("test_maximum_1d_2loc_0", R"(
            maximum(
                annotate_d([33.], "lhs",
                    list("tile", list("columns", 2, 3))),
                annotate_d([65.], "rhs",
                    list("tile", list("columns", 2, 3))))
        )", R"(
            annotate_d([65.], "lhs/1",
                list("args",
                    list("locality", 1, 2),
                    list("tile", list("columns", 2, 3))))
        )");
    }
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(int argc, char* argv[])
{
    HPX_TEST(hpx::get_num_localities(hpx::launch::sync) == 2);

    test_maximum_1d_0();

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    std::vector<std::string> cfg = { "hpx.run_hpx_main!=1" };

    hpx::init_params params;
    params.cfg = std::move(cfg);
    HPX_TEST_EQ(hpx::init(argc, argv, params), 0);

    return hpx::util::report_errors();
}
