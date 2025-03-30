#include "pt_shape.h"

namespace pt_shape {

PtShape::PtShape(
    int t_internal_n,
    std::vector<int64_t> t_external_shape,
    optional<int> t_n_axis_external
) : internal_n(t_internal_n) {
    if (t_external_shape.size() == 0) {
        external_shape = {internal_n};
    } else {
        external_shape = t_external_shape;
    }

    if (t_n_axis_external) {
        n_axis_external = t_n_axis_external.value();
    } else {
        int n = internal_n;
        // Calculate pads: (n - external_shape) % n
        std::vector<int64_t> pads(external_shape.size());
        for (size_t i = 0; i < external_shape.size(); ++i) {
            pads[i] = (n - external_shape[i]) % n;
        }
        // Find the index of the minimum pad value
        auto min_iter = std::min_element(pads.begin(), pads.end());
        n_axis_external = std::distance(pads.begin(), min_iter);
    }

    int external_n = external_shape[n_axis_external];
    int num_blocks = (external_n + internal_n - 1) / internal_n;

    int64_t reps_1 = std::accumulate(
        external_shape.begin(),
        external_shape.begin() + n_axis_external,
        1LL,
        std::multiplies<int64_t>()
    );

    int64_t reps_2 = std::accumulate(
        external_shape.begin() + n_axis_external + 1,
        external_shape.end(),
        1LL,
        std::multiplies<int64_t>()
    );

    internal_shape = {reps_1, num_blocks, reps_2, internal_n};
    intermediate_shape = {reps_1, num_blocks, internal_n, reps_2};
}

PtShape::PtShape() {}

void PtShape::init(lattica_proto::PtShape proto) {
    internal_n = proto.internal_n();
    n_axis_external = proto.n_axis_external();

    int num_external_shape = proto.external_shape_size();
    for (int i = 0; i < num_external_shape; i++)
        external_shape.push_back(proto.external_shape(i));
    int num_internal_shape = proto.internal_shape_size();
    for (int i = 0; i < num_internal_shape; i++)
        internal_shape.push_back(proto.internal_shape(i));
    int num_intermediate_shape = proto.intermediate_shape_size();
    for (int i = 0; i < num_intermediate_shape; i++)
        intermediate_shape.push_back(proto.intermediate_shape(i));
}

lattica_proto::PtShape PtShape::to_proto(optional<lattica_proto::PtShape*> t_proto) {
    lattica_proto::PtShape* proto = t_proto ? t_proto.value() : new lattica_proto::PtShape();
    proto->set_internal_n(internal_n);
    proto->set_n_axis_external(n_axis_external);
    for (int64_t external_shape_val : external_shape)
        proto->add_external_shape(external_shape_val);
    for (int64_t intermediate_shape_val : intermediate_shape)
        proto->add_intermediate_shape(intermediate_shape_val);
    for (int64_t internal_shape_val : internal_shape)
        proto->add_internal_shape(internal_shape_val);
    return *proto;
}

PtShape::PtShape(string& proto_str) : PtShape() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::PtShape proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

void PtShape::addKeysDim(int64_t num_keys) {
    internal_shape.insert(internal_shape.begin(), num_keys);
    external_shape.insert(external_shape.begin(), num_keys);
    n_axis_external += 1;
}

void PtShape::removeKeysDim() {
    if (!internal_shape.empty()) {
        internal_shape.erase(internal_shape.begin());
    }
    if (!external_shape.empty()) {
        external_shape.erase(external_shape.begin());
    }
    n_axis_external -= 1;
}

TTensor convert_internal_to_external(TTensor& a, PtShape& pt_shape) {
    a = a.moveaxis(-1 ,-2);
    a = a.flatten(-3, -2);
    int pad = a.size(-2) - pt_shape.external_shape[pt_shape.n_axis_external];
    if (pad > 0) {
        a = a.index({"...", Slice(None, -pad), Slice()});
    }
    a = a.reshape(pt_shape.external_shape);
    return a;
}

TTensor convert_external_to_internal(TTensor& a, PtShape& pt_shape) {
    int n = pt_shape.internal_n;
    int n_idx = pt_shape.n_axis_external;
    int pad = (n - a.size(n_idx)) % n;
    if (pad < 0) {
        pad += n;
    }
    a = t_eng::pad_single_axis(a, pad, -(a.dim() - n_idx));
    a = a.reshape(pt_shape.intermediate_shape);
    a = a.moveaxis(-2, -1);
    return a;
}

} // namespace pt_shape
