#pragma once

#include "generic.pb.h"
#include "tensor_engine.h"

namespace serialization_utils {

    lattica_proto::DataType ser_dtype(at::ScalarType dtype);
    at::ScalarType deser_dtype(lattica_proto::DataType proto);
    void ser_tensor(TTensor& tensor, lattica_proto::TensorHolder* proto);
    TTensor deser_tensor(lattica_proto::TensorHolder proto);
    TTensor deser_tensor_from_str(std::string& proto_str);
    std::string ser_tensor_to_bytes(TTensor& tensor);
}

