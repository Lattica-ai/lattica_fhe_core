#include "dataclasses.h"
#include "serialization_utils.h"

namespace perm_utils {

CrtPermutations::CrtPermutations(TTensor& t_new_idxs) : new_idxs(t_new_idxs) {}

void CrtPermutations::init(lattica_proto::CrtPermutations proto) {
    new_idxs = serialization_utils::deser_tensor(proto.new_idxs());
}

lattica_proto::CrtPermutations CrtPermutations::to_proto(std::optional<lattica_proto::CrtPermutations*> t_proto) {
    lattica_proto::CrtPermutations* proto = t_proto ? t_proto.value() : new lattica_proto::CrtPermutations();
    serialization_utils::ser_tensor(new_idxs, proto->mutable_new_idxs());
    return *proto;
}

CrtPermutations::CrtPermutations(const std::string& proto_str)
    : CrtPermutations() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    lattica_proto::CrtPermutations proto;
    proto.ParseFromString(proto_str);
    init(proto);
}

int CrtPermutations::get_n() {
    return new_idxs.size(1);
}

int CrtPermutations::get_nperms() {
    return new_idxs.size(0);
}

} // namespace perm_utils
