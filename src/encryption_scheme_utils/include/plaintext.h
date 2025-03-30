#pragma once

#include "tensor_engine.h"
#include "context.h"

namespace plaintext {

TTensor encode_pt(context::Context& context, TTensor& pt);
TTensor decode_pt(context::Context& context, TTensor& pt);

} // namespace plaintext