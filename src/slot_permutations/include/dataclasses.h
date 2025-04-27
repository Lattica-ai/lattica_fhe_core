#pragma once

#include "slot_permutations.pb.h"
#include "tensor_engine.h"

namespace perm_utils {

class CrtPermutations {
public:
    CrtPermutations() = default;
    CrtPermutations(TTensor& t_new_idxs);
    CrtPermutations(const std::string& proto_str);

    void init(lattica_proto::CrtPermutations proto);
    lattica_proto::CrtPermutations to_proto(std::optional<lattica_proto::CrtPermutations*> t_proto = std::nullopt);

    int get_n();
    int get_nperms();
    TTensor& get_new_idxs() { return new_idxs; }

private:
    TTensor new_idxs;
};

} // namespace perm_utils