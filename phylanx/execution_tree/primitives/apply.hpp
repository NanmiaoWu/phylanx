//  Copyright (c) 2018 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_PRIMITIVES_APPLY_FEB_09_2018_0744PM)
#define PHYLANX_PRIMITIVES_APPLY_FEB_09_2018_0744PM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>

#include <string>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    class apply : public primitive_component_base
    {
    public:
        static match_pattern_type const match_data;

        apply() = default;

        PHYLANX_EXPORT apply(std::vector<primitive_argument_type>&& operands);

        PHYLANX_EXPORT primitive_argument_type eval_direct(
            std::vector<primitive_argument_type> const& params) const override;
    };

    PHYLANX_EXPORT primitive create_apply(hpx::id_type const& locality,
        std::vector<primitive_argument_type>&& operands,
        std::string const& name = "");
}}}

#endif


