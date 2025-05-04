#include "python_interface.h"

namespace toolkit_interface {

    python_interface::SerializedKeySet py_generate_key(
            const std::string& serialized_homseq,
            const std::string& serialized_context)
    {
        auto result = raw_generate_key(serialized_homseq, serialized_context);

        return std::make_tuple(
                std::make_tuple(
                    py::bytes(std::get<0>(std::get<0>(result))),
                    py::bytes(std::get<1>(std::get<0>(result)))
                ),
                py::bytes(std::get<1>(result))
        );
    }

    py::bytes py_enc(
            const std::string& serialized_context,
            const std::string& serialized_sk,
            const std::string& serialized_pt,
            bool pack_for_transmission,
            std::optional<int> n_axis_external)
    {
        std::string result = raw_enc(serialized_context, serialized_sk, serialized_pt,
                                     pack_for_transmission, n_axis_external);

        return py::bytes(result);
    }

    py::bytes py_dec(
            const std::string& serialized_context,
            const std::string& serialized_sk,
            const std::string& serialized_ct)
    {
        std::string result = raw_dec(serialized_context, serialized_sk, serialized_ct);

        return py::bytes(result);
    }

    py::bytes py_apply_client_block(
            const std::string& serialized_block,
            const std::string& serialized_context,
            const std::string& serialized_pt)
    {
        std::string result = raw_apply_client_block(serialized_block, serialized_context, serialized_pt);

        return py::bytes(result);
    }

} // namespace toolkit_interface
