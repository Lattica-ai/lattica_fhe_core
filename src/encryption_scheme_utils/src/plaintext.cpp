#include "ATen/ATen.h"
#include "plaintext.h"

namespace plaintext {

TTensor encode_pt(context::Context& context, TTensor& pt) {
    return t_eng::mod(pt, context.params.p());
}

TTensor decode_pt(context::Context& context, TTensor& pt) {
    auto p = context.params.p();
    return pt - ((pt > (p/2)) * p);
}

} // namespace plaintext
