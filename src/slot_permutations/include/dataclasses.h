#pragma once

#include "slot_permutations.pb.h"
#include "tensor_engine.h"

namespace perm_utils {

class CrtPermutations {
public:
    TTensor new_idxs;

    CrtPermutations();
    CrtPermutations(TTensor& t_new_idxs);

    void init(lattica_proto::CrtPermutations proto);
    lattica_proto::CrtPermutations to_proto(std::optional<lattica_proto::CrtPermutations*> t_proto = std::nullopt);
    CrtPermutations(std::string& proto_str);

    int get_n();
    int get_nperms();
};

} // namespace perm_utils