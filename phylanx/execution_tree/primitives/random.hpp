//   Copyright (c) 2017-2018 Hartmut Kaiser
//
//   Distributed under the Boost Software License, Version 1.0. (See accompanying
//   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_PRIMITIVES_RANDOM_OCT_10_2017_0258PM)
#define PHYLANX_PRIMITIVES_RANDOM_OCT_10_2017_0258PM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>

#include <hpx/lcos/future.hpp>

#include <string>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    class random : public primitive_component_base
    {
    public:
        static match_pattern_type const match_data;

        random() = default;

        random(std::vector<primitive_argument_type>&& operands);

        hpx::future<primitive_argument_type> eval(
            std::vector<primitive_argument_type> const& args) const override;
    };

    PHYLANX_EXPORT primitive create_random(hpx::id_type const& locality,
        std::vector<primitive_argument_type>&& operands,
        std::string const& name = "");
}}}

#endif
