// Copyright (c) 2018 Bita Hasheminezhad
// Copyright (c) 2018 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <phylanx/config.hpp>
#include <phylanx/ir/node_data.hpp>
#include <phylanx/plugins/keras_support/softmax_operation.hpp>

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

#include <blaze/Math.h>
#include <blaze_tensor/Math.h>

///////////////////////////////////////////////////////////////////////////////
namespace phylanx { namespace execution_tree { namespace primitives
{
    ///////////////////////////////////////////////////////////////////////////
    match_pattern_type const softmax_operation::match_data =
    {
        hpx::make_tuple("softmax",
        std::vector<std::string>{
            "softmax(_1)",
            "softmax(_1,_2)"
        },
        &create_softmax_operation, &create_primitive<softmax_operation>,
        R"(a, axis
        Args:

            a (array_like) : input array
            axis (optional, integer): an axis to softmax along. The
                default is the last axis (axis == -1) of an array. Axis
                is effective for >1d arrays.

        Returns:

        Returns an array of the same shape which is the normalized exponential
        function of the given array.  The resulting array consists of real
        values in the range (0..1], which add up to 1 in direction of the given axis)")
    };

    ///////////////////////////////////////////////////////////////////////////
    softmax_operation::softmax_operation(primitive_arguments_type&& operands,
        std::string const& name, std::string const& codename)
      : primitive_component_base(std::move(operands), name, codename)
    {}

    primitive_argument_type softmax_operation::softmax0d() const
    {
        return primitive_argument_type{static_cast<double>(1.)};
    }

    ///////////////////////////////////////////////////////////////////////////
    primitive_argument_type softmax_operation::softmax1d(arg_type&& arg) const
    {
        if (!arg.is_ref())
        {
            arg.vector() = blaze::softmax(arg.vector());
            return primitive_argument_type{std::move(arg)};
        }
        return primitive_argument_type{blaze::softmax(arg.vector())};
    }

    ///////////////////////////////////////////////////////////////////////////
    primitive_argument_type softmax_operation::softmax2d_axis0(
        arg_type&& arg) const
    {
        if (!arg.is_ref())
        {
            arg.matrix() = blaze::softmax<blaze::columnwise>(arg.matrix());
            return primitive_argument_type{std::move(arg)};
        }
        return primitive_argument_type{
            blaze::softmax<blaze::columnwise>(arg.matrix())};
    }

    primitive_argument_type softmax_operation::softmax2d_axis1(
        arg_type&& arg) const
    {
        if (!arg.is_ref())
        {
            arg.matrix() = blaze::softmax<blaze::rowwise>(arg.matrix());
            return primitive_argument_type{std::move(arg)};
        }
        return primitive_argument_type{
            blaze::softmax<blaze::rowwise>(arg.matrix())};
    }

    primitive_argument_type softmax_operation::softmax2d(
        arg_type&& arg, std::int64_t axis) const
    {
        switch (axis)
        {
        case -2: HPX_FALLTHROUGH;
        case 0:
            return softmax2d_axis0(std::move(arg));

        case -1: HPX_FALLTHROUGH;
        case 1:
            return softmax2d_axis1(std::move(arg));

        default:
            break;
        }
        HPX_THROW_EXCEPTION(hpx::bad_parameter,
            "softmax_operation::softmax2d",
            generate_error_message(
                "the softmax_operation primitive requires operand axis "
                "to be between -2 and 1 for matrices."));
    }

    ///////////////////////////////////////////////////////////////////////////
    primitive_argument_type softmax_operation::softmax3d_axis0(
        arg_type&& arg) const
    {
        auto t = arg.tensor();
        if (!arg.is_ref())
        {
            for (std::size_t i = 0; i != t.rows(); ++i)
            {
                blaze::rowslice(t, i) =
                    blaze::softmax<blaze::rowwise>(blaze::rowslice(t, i));
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicTensor<val_type> result(t.pages(), t.rows(), t.columns());
        for (std::size_t i = 0; i != t.rows(); ++i)
        {
            auto slice = blaze::rowslice(t, i);
            blaze::rowslice(result, i) = blaze::softmax<blaze::rowwise>(slice);
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax3d_axis1(
        arg_type&& arg) const
    {
        auto t = arg.tensor();
        if (!arg.is_ref())
        {
            for (std::size_t i = 0; i != t.columns(); ++i)
            {
                blaze::columnslice(t, i) =
                    blaze::softmax<blaze::rowwise>(blaze::columnslice(t, i));
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicTensor<val_type> result(t.pages(), t.rows(), t.columns());
        for (std::size_t i = 0; i != t.columns(); ++i)
        {
            auto slice = blaze::columnslice(t, i);
            blaze::columnslice(result, i) = blaze::softmax<blaze::rowwise>(slice);
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax3d_axis2(
        arg_type&& arg) const
    {
        auto t = arg.tensor();
        if (!arg.is_ref())
        {
            for (std::size_t i = 0; i != t.pages(); ++i)
            {
                blaze::pageslice(t, i) =
                    blaze::softmax<blaze::rowwise>(blaze::pageslice(t, i));
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicTensor<val_type> result(t.pages(), t.rows(), t.columns());
        for (std::size_t i = 0; i != t.pages(); ++i)
        {
            auto slice = blaze::pageslice(t, i);
            blaze::pageslice(result, i) = blaze::softmax<blaze::rowwise>(slice);
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax3d(
        arg_type&& arg, std::int64_t axis) const
    {
        switch (axis)
        {
        case -3: HPX_FALLTHROUGH;
        case 0:
            return softmax3d_axis0(std::move(arg));

        case -2: HPX_FALLTHROUGH;
        case 1:
            return softmax3d_axis1(std::move(arg));

        case -1: HPX_FALLTHROUGH;
        case 2:
            return softmax3d_axis2(std::move(arg));

        default:
            break;
        }
        HPX_THROW_EXCEPTION(hpx::bad_parameter,
            "softmax_operation::softmax3d",
            generate_error_message(
                "the softmax_operation primitive requires operand axis "
                "to be between -3 and 2 for tensors."));
    }

    ///////////////////////////////////////////////////////////////////////////
    primitive_argument_type softmax_operation::softmax4d_axis0(
        arg_type&& arg) const
    {
        auto q = arg.quatern();
        std::size_t quats = q.columns();
        std::size_t pages = q.rows();

        for (std::size_t l = 0; l != quats; ++l)
        {
            auto t = quatslice(blaze::trans(q), l);
            for (std::size_t i = 0; i != pages; ++i)
            {
                blaze::pageslice(t, i) =
                    blaze::softmax<blaze::rowwise>(blaze::pageslice(t, i));
            }
        }
        blaze::DynamicArray<4UL, val_type> result = q;
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax4d_axis1(
        arg_type&& arg) const
    {
        auto q = arg.quatern();
        std::size_t quats = q.quats();
        std::size_t columns = q.columns();
        if (!arg.is_ref())
        {
            for (std::size_t l = 0; l != quats; ++l)
            {
                auto t = quatslice(q, l);
                for (std::size_t i = 0; i != columns; ++i)
                {
                    blaze::columnslice(t, i) =
                        blaze::softmax<blaze::columnwise>(
                            blaze::columnslice(t, i));
                }
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicArray<4UL, val_type> result(
            quats, q.pages(), q.rows(), columns);
        for (std::size_t l = 0; l != quats; ++l)
        {
            auto t = quatslice(q, l);
            auto res_tensor = quatslice(result, l);
            for (std::size_t i = 0; i != columns; ++i)
            {
                auto slice = blaze::columnslice(t, i);
                blaze::columnslice(res_tensor, i) =
                    blaze::softmax<blaze::columnwise>(slice);
            }
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax4d_axis2(
        arg_type&& arg) const
    {
        auto q = arg.quatern();
        std::size_t quats = q.quats();
        std::size_t pages = q.pages();
        if (!arg.is_ref())
        {
            for (std::size_t l = 0; l != quats; ++l)
            {
                auto t = quatslice(q, l);
                for (std::size_t i = 0; i != pages; ++i)
                {
                    blaze::pageslice(t, i) = blaze::softmax<blaze::columnwise>(
                        blaze::pageslice(t, i));
                }
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicArray<4UL, val_type> result(
            quats, pages, q.rows(), q.columns());
        for (std::size_t l = 0; l != quats; ++l)
        {
            auto t = quatslice(q, l);
            auto res_tensor = quatslice(result, l);
            for (std::size_t i = 0; i != pages; ++i)
            {
                auto slice = blaze::pageslice(t, i);
                blaze::pageslice(res_tensor, i) =
                    blaze::softmax<blaze::columnwise>(slice);
            }
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax4d_axis3(
        arg_type&& arg) const
    {
        auto q = arg.quatern();
        std::size_t quats = q.quats();
        std::size_t pages = q.pages();
        if (!arg.is_ref())
        {
            for (std::size_t l = 0; l != quats; ++l)
            {
                auto t = quatslice(q, l);
                for (std::size_t i = 0; i != pages; ++i)
                {
                    blaze::pageslice(t, i) =
                        blaze::softmax<blaze::rowwise>(blaze::pageslice(t, i));
                }
            }
            return primitive_argument_type{std::move(arg)};
        }

        blaze::DynamicArray<4UL, val_type> result(
            quats, pages, q.rows(), q.columns());
        for (std::size_t l = 0; l != quats; ++l)
        {
            auto t = quatslice(q, l);
            auto res_tensor = quatslice(result, l);
            for (std::size_t i = 0; i != pages; ++i)
            {
                auto slice = blaze::pageslice(t, i);
                blaze::pageslice(res_tensor, i) =
                    blaze::softmax<blaze::rowwise>(slice);
            }
        }
        return primitive_argument_type{std::move(result)};
    }

    primitive_argument_type softmax_operation::softmax4d(
        arg_type&& arg, std::int64_t axis) const
    {
        switch (axis)
        {
        case -4: HPX_FALLTHROUGH;
        case 0:
            return softmax4d_axis0(std::move(arg));

        case -3: HPX_FALLTHROUGH;
        case 1:
            return softmax4d_axis1(std::move(arg));

        case -2: HPX_FALLTHROUGH;
        case 2:
            return softmax4d_axis2(std::move(arg));

        case -1: HPX_FALLTHROUGH;
        case 3:
            return softmax4d_axis3(std::move(arg));

        default:
            break;
        }
        HPX_THROW_EXCEPTION(hpx::bad_parameter,
            "softmax_operation::softmax4d",
            generate_error_message(
                "the softmax_operation primitive requires operand axis "
                "to be between -4 and 3 for 4d arrays."));
    }

    ///////////////////////////////////////////////////////////////////////////
    hpx::future<primitive_argument_type> softmax_operation::eval(
        primitive_arguments_type const& operands,
        primitive_arguments_type const& args,
        eval_context ctx) const
    {
        if (operands.empty() || operands.size() > 2)
        {
            HPX_THROW_EXCEPTION(hpx::bad_parameter,
                "softmax_operation::eval",
                util::generate_error_message(
                    "the softmax_operation primitive requires exactly one, or "
                    "two operands",
                    name_, codename_));
        }

        for (auto const& i : operands)
        {
            if (!valid(i))
            {
                HPX_THROW_EXCEPTION(hpx::bad_parameter,
                    "softmax_operation::eval",
                    util::generate_error_message(
                        "the softmax_operation primitive requires that the "
                        "arguments given by the operands array are "
                        "valid",
                        name_, codename_));
            }
        }

        auto this_ = this->shared_from_this();
        return hpx::dataflow(hpx::launch::sync,
            hpx::unwrapping([this_ = std::move(this_)](
                                      primitive_arguments_type&& args)
                                      -> primitive_argument_type {
                // Extract axis
                std::int64_t axis =
                    static_cast<std::int64_t>(-1);

                // axis is the second argument
                if (args.size() > 1)
                {
                    if (valid(args[1]))
                        axis = execution_tree::extract_scalar_integer_value_strict(
                            args[1], this_->name_, this_->codename_);
                }

                // Extract the array, the result should always be double
                arg_type a = extract_numeric_value(
                    std::move(args[0]), this_->name_, this_->codename_);

                std::size_t a_dims = a.num_dimensions();

                switch (a_dims)
                {
                case 0:
                    return this_->softmax0d();

                case 1:
                    return this_->softmax1d(std::move(a));

                case 2:
                    return this_->softmax2d(std::move(a), axis);

                case 3:
                    return this_->softmax3d(std::move(a), axis);

                case 4:
                    return this_->softmax4d(std::move(a), axis);

                default:
                    HPX_THROW_EXCEPTION(hpx::bad_parameter,
                        "softmax_operation::eval",
                        util::generate_error_message("operand a has an invalid "
                                                        "number of dimensions",
                            this_->name_, this_->codename_));
                }
            }),
            detail::map_operands(
                operands, functional::value_operand{}, args,
                name_, codename_, std::move(ctx)));
    }
}}}

