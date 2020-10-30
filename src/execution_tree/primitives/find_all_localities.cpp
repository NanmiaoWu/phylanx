//  Copyright (c) 2017-2018 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/find_all_localities.hpp>

#include <hpx/iostream.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/naming.hpp>
#include <hpx/include/util.hpp>
#include <hpx/errors/throw_exception.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace phylanx { namespace execution_tree { namespace primitives
{
    ///////////////////////////////////////////////////////////////////////////
    primitive create_find_all(hpx::id_type const& locality,
        primitive_arguments_type&& operands,
        std::string const& name, std::string const& codename)
    {
        static std::string type("find_all_localities");
        return create_primitive_component(
            locality, type, std::move(operands), name, codename);
    }

    match_pattern_type const find_all_localities::match_data =
    {
        hpx::make_tuple("find_all_localities",
            std::vector<std::string>{"find_all_localities()"},
            &create_find_all, &create_primitive<find_all_localities>,
            R"(
            Args:

            Returns:
              All the localities available on the system.)"
            )
    };

    ///////////////////////////////////////////////////////////////////////////
    find_all_localities::find_all_localities(
            primitive_arguments_type&& operands,
            std::string const& name, std::string const& codename)
      : primitive_component_base(std::move(operands), name, codename)
    {}

    hpx::future<primitive_argument_type> find_all_localities::eval(
        primitive_arguments_type const& operands,
        primitive_arguments_type const& args, eval_context ctx) const
    {
        auto this_ = this->shared_from_this();
        return hpx::dataflow(hpx::launch::sync, hpx::util::unwrapping(
            [this_ = std::move(this_)](primitive_arguments_type&& args)
                -> primitive_argument_type
            {
                primitive_arguments_type values;
                for (auto const& loc : hpx::find_all_localities())
                {
                    std::int64_t v = hpx::naming::get_locality_id_from_id(loc);
                    values.push_back(primitive_argument_type{v});
                }

                phylanx::execution_tree::primitive_argument_type p(values);
                return p;
            }),
            detail::map_operands(
                operands, functional::value_operand{}, args, name_, codename_,
                std::move(ctx)));
    }
}}}
