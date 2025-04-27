#include "serialization_utils.h"

namespace serialization_utils {

    lattica_proto::DataType ser_dtype(at::ScalarType dtype) {
        switch (dtype) {
            case at::kInt:
                return lattica_proto::DataType::INT32;
            case at::kLong:
                return lattica_proto::DataType::INT64;
            case at::kFloat:
                return lattica_proto::DataType::FLOAT;
            case at::kDouble:
                return lattica_proto::DataType::DOUBLE;
            case at::kComplexFloat:
                return lattica_proto::DataType::COMPLEX_FLOAT;
            case at::kComplexDouble:
                return lattica_proto::DataType::COMPLEX_DOUBLE;
            case at::kBool:
                return lattica_proto::DataType::BOOL;
            default:
                throw std::invalid_argument("Unsupported data type");
        }
    }

    at::ScalarType deser_dtype(lattica_proto::DataType proto) {
        switch (proto) {
            case lattica_proto::DataType::INT32:
                return at::kInt;
            case lattica_proto::DataType::INT64:
                return at::kLong;
            case lattica_proto::DataType::FLOAT:
                return at::kFloat;
            case lattica_proto::DataType::DOUBLE:
                return at::kDouble;
            case lattica_proto::DataType::COMPLEX_FLOAT:
                return at::kComplexFloat;
            case lattica_proto::DataType::COMPLEX_DOUBLE:
                return at::kComplexDouble;
            case lattica_proto::DataType::BOOL:
                return at::kBool;
            default:
                throw std::invalid_argument("Unsupported data type");
        }
    }

    void ser_tensor(TTensor& tensor, lattica_proto::TensorHolder* proto) {
        tensor = tensor.contiguous();
        proto->set_dtype(ser_dtype(tensor.scalar_type()));
        proto->clear_sizes();
        for (const auto& size : tensor.sizes()) {
              proto->add_sizes(size);
        }
        proto->clear_strides();
        for (const auto& stride : tensor.strides()) {
              proto->add_strides(stride);
        }
        const void* dataPtr = tensor.data_ptr();
        size_t dataSize = tensor.nbytes();
        std::string data(static_cast<const char*>(dataPtr), dataSize);
        proto->set_data(data);
    }

    TTensor deser_tensor(lattica_proto::TensorHolder proto) {
        at::ScalarType dtype = deser_dtype(proto.dtype());

        std::vector<int64_t> sizes;
        for (int i = 0; i < proto.sizes_size(); i++) {
            sizes.push_back(proto.sizes(i));
        }
        std::vector<int64_t> strides;
        for (int i = 0; i < proto.strides_size(); i++) {
            strides.push_back(proto.strides(i));
        }
        auto rawData = proto.data().c_str();
        at::TensorOptions options = at::TensorOptions().dtype(dtype);
        TTensor tensor = at::from_blob((void*)rawData, sizes, strides, options).clone();
        return tensor;
    }

    TTensor deser_tensor_from_str(const std::string& proto_str) {
        lattica_proto::TensorHolder proto = lattica_proto::TensorHolder();
        proto.ParseFromString(proto_str);
        return deser_tensor(proto);
    }

    std::string ser_tensor_to_bytes(TTensor& tensor) {
        lattica_proto::TensorHolder proto = lattica_proto::TensorHolder();
        ser_tensor(tensor, &proto);
        return proto.SerializeAsString();
    }
}
