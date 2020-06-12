//   Copyright (c) 2020 Hartmut Kaiser
//   Copyright (c) 2020 Nanmiao Wu
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/phylanx.hpp>

#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
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

///////////////////////////////////////////////////////////////////////////////
void test_all_gather_d_operation(std::string const& name,
    std::string const& code, std::string const& expected_str)
{
    phylanx::execution_tree::primitive_argument_type result =
        compile_and_run(name, code);
    phylanx::execution_tree::primitive_argument_type comparison =
        compile_and_run(name, expected_str);

    HPX_TEST_EQ(hpx::cout, result, comparison);
    std::cout << result;
}

////////////////////////////////////////////////////////////////////////////////
void test_all_gather_2d_0()
{
    if (hpx::get_locality_id() == 0)
    {
        test_all_gather_d_operation("test2d_0", R"(
            all_gather_d(
                annotate_d([[1, 2, 3], [4, 5, 6]], "array_0",
                    list("tile", list("columns", 0, 3), list("rows", 0, 2))
                )
            )
        )", "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");
    }
    else
    {
        test_all_gather_d_operation("test1d_0", R"(
            all_gather_d(
                annotate_d([[7, 8, 9]], "array_0",
                    list("tile", list("columns", 0, 3), list("rows", 2, 3))
                )
            )
        )", "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");
    }
}






////////////////////////////////////////////////////////////////////////////////
int hpx_main(int argc, char* argv[])
{
    test_all_gather_2d_0();

    hpx::finalize();
    return hpx::util::report_errors();
}

int main(int argc, char* argv[])
{
    std::vector<std::string> cfg = {
        "hpx.run_hpx_main!=1"
    };

    return hpx::init(argc, argv, cfg);
}
