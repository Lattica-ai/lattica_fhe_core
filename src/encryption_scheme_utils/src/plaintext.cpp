#include <ATen/ATen.h>
#include "plaintext.h"

namespace plaintext {

TTensor encode_pt(context::Context& context, TTensor& pt) {
    return t_eng::mod(pt, context.p());
}

TTensor decode_pt(context::Context& context, TTensor& pt) {
    auto p = context.p();
    return pt - ((pt > (p/2)) * p);
}

} // namespace plaintext
