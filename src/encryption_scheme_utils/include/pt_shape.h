#pragma once

#include "pt_shape.pb.h"
#include "tensor_engine.h"

namespace pt_shape {

class PtShape {
public:
    PtShape() = default;
    PtShape(const string& proto_str);
    PtShape(
        int t_internal_n,
        std::vector<int64_t> t_external_shape,
        optional<int> t_n_axis_external = nullopt
    );

    void init(lattica_proto::PtShape proto);
    lattica_proto::PtShape to_proto(optional<lattica_proto::PtShape*> t_proto = nullopt);

    std::vector<int64_t>& get_external_shape() { return external_shape; }
    std::vector<int64_t>& get_internal_shape() { return internal_shape; }
    std::vector<int64_t>& get_intermediate_shape() { return intermediate_shape; }
    int get_n_axis_external() {return n_axis_external;}
    int get_internal_n() { return internal_n; }

private:
    void addKeysDim(int64_t num_keys);
    void removeKeysDim();

    int internal_n;
    std::vector<int64_t> external_shape;
    std::vector<int64_t> internal_shape;
    std::vector<int64_t> intermediate_shape;
    int n_axis_external;

}; // class PtShape

TTensor convert_internal_to_external(TTensor& a, PtShape& pt_shape);
TTensor convert_external_to_internal(TTensor& a, PtShape& pt_shape);

} // namespace pt_shape