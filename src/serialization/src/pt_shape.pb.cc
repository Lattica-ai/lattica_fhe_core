// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: serialization/pt_shape.proto
// Protobuf C++ Version: 5.27.1

#include "pt_shape.pb.h"

#include <algorithm>
#include <type_traits>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/generated_message_tctable_impl.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace lattica_proto {

inline constexpr PtShape::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : external_shape_{},
        _external_shape_cached_byte_size_{0},
        internal_shape_{},
        _internal_shape_cached_byte_size_{0},
        intermediate_shape_{},
        _intermediate_shape_cached_byte_size_{0},
        internal_n_{0},
        n_axis_external_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR PtShape::PtShape(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct PtShapeDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PtShapeDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~PtShapeDefaultTypeInternal() {}
  union {
    PtShape _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PtShapeDefaultTypeInternal _PtShape_default_instance_;
}  // namespace lattica_proto
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_serialization_2fpt_5fshape_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_serialization_2fpt_5fshape_2eproto = nullptr;
const ::uint32_t
    TableStruct_serialization_2fpt_5fshape_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _impl_.internal_n_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _impl_.external_shape_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _impl_.internal_shape_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _impl_.intermediate_shape_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::PtShape, _impl_.n_axis_external_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::lattica_proto::PtShape)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::lattica_proto::_PtShape_default_instance_._instance,
};
const char descriptor_table_protodef_serialization_2fpt_5fshape_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\034serialization/pt_shape.proto\022\rlattica_"
    "proto\"\202\001\n\007PtShape\022\022\n\ninternal_n\030\001 \001(\005\022\026\n"
    "\016external_shape\030\002 \003(\005\022\026\n\016internal_shape\030"
    "\003 \003(\005\022\032\n\022intermediate_shape\030\004 \003(\005\022\027\n\017n_a"
    "xis_external\030\005 \001(\005b\006proto3"
};
static ::absl::once_flag descriptor_table_serialization_2fpt_5fshape_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_serialization_2fpt_5fshape_2eproto = {
    false,
    false,
    186,
    descriptor_table_protodef_serialization_2fpt_5fshape_2eproto,
    "serialization/pt_shape.proto",
    &descriptor_table_serialization_2fpt_5fshape_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_serialization_2fpt_5fshape_2eproto::offsets,
    file_level_enum_descriptors_serialization_2fpt_5fshape_2eproto,
    file_level_service_descriptors_serialization_2fpt_5fshape_2eproto,
};
namespace lattica_proto {
// ===================================================================

class PtShape::_Internal {
 public:
};

PtShape::PtShape(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:lattica_proto.PtShape)
}
inline PROTOBUF_NDEBUG_INLINE PtShape::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::lattica_proto::PtShape& from_msg)
      : external_shape_{visibility, arena, from.external_shape_},
        _external_shape_cached_byte_size_{0},
        internal_shape_{visibility, arena, from.internal_shape_},
        _internal_shape_cached_byte_size_{0},
        intermediate_shape_{visibility, arena, from.intermediate_shape_},
        _intermediate_shape_cached_byte_size_{0},
        _cached_size_{0} {}

PtShape::PtShape(
    ::google::protobuf::Arena* arena,
    const PtShape& from)
    : ::google::protobuf::Message(arena) {
  PtShape* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, internal_n_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, internal_n_),
           offsetof(Impl_, n_axis_external_) -
               offsetof(Impl_, internal_n_) +
               sizeof(Impl_::n_axis_external_));

  // @@protoc_insertion_point(copy_constructor:lattica_proto.PtShape)
}
inline PROTOBUF_NDEBUG_INLINE PtShape::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : external_shape_{visibility, arena},
        _external_shape_cached_byte_size_{0},
        internal_shape_{visibility, arena},
        _internal_shape_cached_byte_size_{0},
        intermediate_shape_{visibility, arena},
        _intermediate_shape_cached_byte_size_{0},
        _cached_size_{0} {}

inline void PtShape::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, internal_n_),
           0,
           offsetof(Impl_, n_axis_external_) -
               offsetof(Impl_, internal_n_) +
               sizeof(Impl_::n_axis_external_));
}
PtShape::~PtShape() {
  // @@protoc_insertion_point(destructor:lattica_proto.PtShape)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void PtShape::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
PtShape::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              &_table_.header,
              nullptr,  // OnDemandRegisterArenaDtor
              nullptr,  // IsInitialized
              PROTOBUF_FIELD_OFFSET(PtShape, _impl_._cached_size_),
              false,
          },
          &PtShape::MergeImpl,
          &PtShape::kDescriptorMethods,
          &descriptor_table_serialization_2fpt_5fshape_2eproto,
          nullptr,  // tracker
      };
  ::google::protobuf::internal::PrefetchToLocalCache(&_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_data_.tc_table);
  return _data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<3, 5, 0, 0, 2> PtShape::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    5, 56,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967264,  // skipmap
    offsetof(decltype(_table_), field_entries),
    5,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_PtShape_default_instance_._instance,
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::lattica_proto::PtShape>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    {::_pbi::TcParser::MiniParse, {}},
    // int32 internal_n = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(PtShape, _impl_.internal_n_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(PtShape, _impl_.internal_n_)}},
    // repeated int32 external_shape = 2;
    {::_pbi::TcParser::FastV32P1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(PtShape, _impl_.external_shape_)}},
    // repeated int32 internal_shape = 3;
    {::_pbi::TcParser::FastV32P1,
     {26, 63, 0, PROTOBUF_FIELD_OFFSET(PtShape, _impl_.internal_shape_)}},
    // repeated int32 intermediate_shape = 4;
    {::_pbi::TcParser::FastV32P1,
     {34, 63, 0, PROTOBUF_FIELD_OFFSET(PtShape, _impl_.intermediate_shape_)}},
    // int32 n_axis_external = 5;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(PtShape, _impl_.n_axis_external_), 63>(),
     {40, 63, 0, PROTOBUF_FIELD_OFFSET(PtShape, _impl_.n_axis_external_)}},
    {::_pbi::TcParser::MiniParse, {}},
    {::_pbi::TcParser::MiniParse, {}},
  }}, {{
    65535, 65535
  }}, {{
    // int32 internal_n = 1;
    {PROTOBUF_FIELD_OFFSET(PtShape, _impl_.internal_n_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // repeated int32 external_shape = 2;
    {PROTOBUF_FIELD_OFFSET(PtShape, _impl_.external_shape_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kPackedInt32)},
    // repeated int32 internal_shape = 3;
    {PROTOBUF_FIELD_OFFSET(PtShape, _impl_.internal_shape_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kPackedInt32)},
    // repeated int32 intermediate_shape = 4;
    {PROTOBUF_FIELD_OFFSET(PtShape, _impl_.intermediate_shape_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kPackedInt32)},
    // int32 n_axis_external = 5;
    {PROTOBUF_FIELD_OFFSET(PtShape, _impl_.n_axis_external_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
  }},
  // no aux_entries
  {{
  }},
};

PROTOBUF_NOINLINE void PtShape::Clear() {
// @@protoc_insertion_point(message_clear_start:lattica_proto.PtShape)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.external_shape_.Clear();
  _impl_.internal_shape_.Clear();
  _impl_.intermediate_shape_.Clear();
  ::memset(&_impl_.internal_n_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.n_axis_external_) -
      reinterpret_cast<char*>(&_impl_.internal_n_)) + sizeof(_impl_.n_axis_external_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

::uint8_t* PtShape::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:lattica_proto.PtShape)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int32 internal_n = 1;
  if (this->_internal_internal_n() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<1>(
            stream, this->_internal_internal_n(), target);
  }

  // repeated int32 external_shape = 2;
  {
    int byte_size = _impl_._external_shape_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          2, _internal_external_shape(), byte_size, target);
    }
  }

  // repeated int32 internal_shape = 3;
  {
    int byte_size = _impl_._internal_shape_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          3, _internal_internal_shape(), byte_size, target);
    }
  }

  // repeated int32 intermediate_shape = 4;
  {
    int byte_size = _impl_._intermediate_shape_cached_byte_size_.Get();
    if (byte_size > 0) {
      target = stream->WriteInt32Packed(
          4, _internal_intermediate_shape(), byte_size, target);
    }
  }

  // int32 n_axis_external = 5;
  if (this->_internal_n_axis_external() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<5>(
            stream, this->_internal_n_axis_external(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lattica_proto.PtShape)
  return target;
}

::size_t PtShape::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lattica_proto.PtShape)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::_pbi::Prefetch5LinesFrom7Lines(reinterpret_cast<const void*>(this));
  // repeated int32 external_shape = 2;
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal_external_shape())
    ;
    _impl_._external_shape_cached_byte_size_.Set(::_pbi::ToCachedSize(data_size));
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }
  // repeated int32 internal_shape = 3;
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal_internal_shape())
    ;
    _impl_._internal_shape_cached_byte_size_.Set(::_pbi::ToCachedSize(data_size));
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }
  // repeated int32 intermediate_shape = 4;
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal_intermediate_shape())
    ;
    _impl_._intermediate_shape_cached_byte_size_.Set(::_pbi::ToCachedSize(data_size));
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }
  // int32 internal_n = 1;
  if (this->_internal_internal_n() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_internal_n());
  }

  // int32 n_axis_external = 5;
  if (this->_internal_n_axis_external() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_n_axis_external());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void PtShape::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<PtShape*>(&to_msg);
  auto& from = static_cast<const PtShape&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:lattica_proto.PtShape)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_external_shape()->MergeFrom(from._internal_external_shape());
  _this->_internal_mutable_internal_shape()->MergeFrom(from._internal_internal_shape());
  _this->_internal_mutable_intermediate_shape()->MergeFrom(from._internal_intermediate_shape());
  if (from._internal_internal_n() != 0) {
    _this->_impl_.internal_n_ = from._impl_.internal_n_;
  }
  if (from._internal_n_axis_external() != 0) {
    _this->_impl_.n_axis_external_ = from._impl_.n_axis_external_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void PtShape::CopyFrom(const PtShape& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lattica_proto.PtShape)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void PtShape::InternalSwap(PtShape* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.external_shape_.InternalSwap(&other->_impl_.external_shape_);
  _impl_.internal_shape_.InternalSwap(&other->_impl_.internal_shape_);
  _impl_.intermediate_shape_.InternalSwap(&other->_impl_.intermediate_shape_);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PtShape, _impl_.n_axis_external_)
      + sizeof(PtShape::_impl_.n_axis_external_)
      - PROTOBUF_FIELD_OFFSET(PtShape, _impl_.internal_n_)>(
          reinterpret_cast<char*>(&_impl_.internal_n_),
          reinterpret_cast<char*>(&other->_impl_.internal_n_));
}

::google::protobuf::Metadata PtShape::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace lattica_proto
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::std::false_type
    _static_init2_ PROTOBUF_UNUSED =
        (::_pbi::AddDescriptors(&descriptor_table_serialization_2fpt_5fshape_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
