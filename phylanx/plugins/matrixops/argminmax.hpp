// Copyright (c) 2018 Parsa Amini
// Copyright (c) 2018-2020 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(PHYLANX_PRIMITIVES_ARGMINMAX_2019_01_19_1130AM)
#define PHYLANX_PRIMITIVES_ARGMINMAX_2019_01_19_1130AM

#include <phylanx/config.hpp>
#include <phylanx/execution_tree/primitives/base_primitive.hpp>
#include <phylanx/execution_tree/primitives/primitive_component_base.hpp>

#include <hpx/futures/future.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace phylanx { namespace execution_tree { namespace primitives
{
    template <typename Op, typename Derived>
    class argminmax
      : public primitive_component_base
      , public std::enable_shared_from_this<Derived>
    {
    protected:
        hpx::future<primitive_argument_type> eval(
            primitive_arguments_type const& operands,
            primitive_arguments_type const& args,
            eval_context ctx) const override;

    public:
        argminmax() = default;

        argminmax(primitive_arguments_type&& operands,
            std::string const& name, std::string const& codename);

    private:
        primitive_argument_type argminmax0d(
            primitive_arguments_type&& args) const;
        primitive_argument_type argminmax1d(
            primitive_arguments_type&& args) const;
        primitive_argument_type argminmax2d(
            primitive_arguments_type&& args) const;
        primitive_argument_type argminmax3d(
            primitive_arguments_type&& args) const;
    };
}}}

#endif
