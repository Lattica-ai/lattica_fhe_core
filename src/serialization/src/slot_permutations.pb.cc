// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: serialization/slot_permutations.proto
// Protobuf C++ Version: 5.27.1

#include "slot_permutations.pb.h"

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

inline constexpr CrtPermutations::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        new_idxs_{nullptr} {}

template <typename>
PROTOBUF_CONSTEXPR CrtPermutations::CrtPermutations(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct CrtPermutationsDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CrtPermutationsDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~CrtPermutationsDefaultTypeInternal() {}
  union {
    CrtPermutations _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CrtPermutationsDefaultTypeInternal _CrtPermutations_default_instance_;
}  // namespace lattica_proto
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_serialization_2fslot_5fpermutations_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_serialization_2fslot_5fpermutations_2eproto = nullptr;
const ::uint32_t
    TableStruct_serialization_2fslot_5fpermutations_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CrtPermutations, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CrtPermutations, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CrtPermutations, _impl_.new_idxs_),
        0,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, 9, -1, sizeof(::lattica_proto::CrtPermutations)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::lattica_proto::_CrtPermutations_default_instance_._instance,
};
const char descriptor_table_protodef_serialization_2fslot_5fpermutations_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n%serialization/slot_permutations.proto\022"
    "\rlattica_proto\032\033serialization/generic.pr"
    "oto\"@\n\017CrtPermutations\022-\n\010new_idxs\030\002 \001(\013"
    "2\033.lattica_proto.TensorHolderb\006proto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_serialization_2fslot_5fpermutations_2eproto_deps[1] =
    {
        &::descriptor_table_serialization_2fgeneric_2eproto,
};
static ::absl::once_flag descriptor_table_serialization_2fslot_5fpermutations_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_serialization_2fslot_5fpermutations_2eproto = {
    false,
    false,
    157,
    descriptor_table_protodef_serialization_2fslot_5fpermutations_2eproto,
    "serialization/slot_permutations.proto",
    &descriptor_table_serialization_2fslot_5fpermutations_2eproto_once,
    descriptor_table_serialization_2fslot_5fpermutations_2eproto_deps,
    1,
    1,
    schemas,
    file_default_instances,
    TableStruct_serialization_2fslot_5fpermutations_2eproto::offsets,
    file_level_enum_descriptors_serialization_2fslot_5fpermutations_2eproto,
    file_level_service_descriptors_serialization_2fslot_5fpermutations_2eproto,
};
namespace lattica_proto {
// ===================================================================

class CrtPermutations::_Internal {
 public:
  using HasBits =
      decltype(std::declval<CrtPermutations>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(CrtPermutations, _impl_._has_bits_);
};

void CrtPermutations::clear_new_idxs() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.new_idxs_ != nullptr) _impl_.new_idxs_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
CrtPermutations::CrtPermutations(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:lattica_proto.CrtPermutations)
}
inline PROTOBUF_NDEBUG_INLINE CrtPermutations::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::lattica_proto::CrtPermutations& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

CrtPermutations::CrtPermutations(
    ::google::protobuf::Arena* arena,
    const CrtPermutations& from)
    : ::google::protobuf::Message(arena) {
  CrtPermutations* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.new_idxs_ = (cached_has_bits & 0x00000001u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::TensorHolder>(
                              arena, *from._impl_.new_idxs_)
                        : nullptr;

  // @@protoc_insertion_point(copy_constructor:lattica_proto.CrtPermutations)
}
inline PROTOBUF_NDEBUG_INLINE CrtPermutations::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void CrtPermutations::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  _impl_.new_idxs_ = {};
}
CrtPermutations::~CrtPermutations() {
  // @@protoc_insertion_point(destructor:lattica_proto.CrtPermutations)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void CrtPermutations::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.new_idxs_;
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
CrtPermutations::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              &_table_.header,
              nullptr,  // OnDemandRegisterArenaDtor
              nullptr,  // IsInitialized
              PROTOBUF_FIELD_OFFSET(CrtPermutations, _impl_._cached_size_),
              false,
          },
          &CrtPermutations::MergeImpl,
          &CrtPermutations::kDescriptorMethods,
          &descriptor_table_serialization_2fslot_5fpermutations_2eproto,
          nullptr,  // tracker
      };
  ::google::protobuf::internal::PrefetchToLocalCache(&_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_data_.tc_table);
  return _data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 1, 0, 2> CrtPermutations::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(CrtPermutations, _impl_._has_bits_),
    0, // no _extensions_
    2, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967293,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    1,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_CrtPermutations_default_instance_._instance,
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::lattica_proto::CrtPermutations>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // .lattica_proto.TensorHolder new_idxs = 2;
    {::_pbi::TcParser::FastMtS1,
     {18, 0, 0, PROTOBUF_FIELD_OFFSET(CrtPermutations, _impl_.new_idxs_)}},
  }}, {{
    65535, 65535
  }}, {{
    // .lattica_proto.TensorHolder new_idxs = 2;
    {PROTOBUF_FIELD_OFFSET(CrtPermutations, _impl_.new_idxs_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::lattica_proto::TensorHolder>()},
  }}, {{
  }},
};

PROTOBUF_NOINLINE void CrtPermutations::Clear() {
// @@protoc_insertion_point(message_clear_start:lattica_proto.CrtPermutations)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(_impl_.new_idxs_ != nullptr);
    _impl_.new_idxs_->Clear();
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

::uint8_t* CrtPermutations::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:lattica_proto.CrtPermutations)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // .lattica_proto.TensorHolder new_idxs = 2;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        2, *_impl_.new_idxs_, _impl_.new_idxs_->GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lattica_proto.CrtPermutations)
  return target;
}

::size_t CrtPermutations::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lattica_proto.CrtPermutations)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .lattica_proto.TensorHolder new_idxs = 2;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size +=
        1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.new_idxs_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void CrtPermutations::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<CrtPermutations*>(&to_msg);
  auto& from = static_cast<const CrtPermutations&>(from_msg);
  ::google::protobuf::Arena* arena = _this->GetArena();
  // @@protoc_insertion_point(class_specific_merge_from_start:lattica_proto.CrtPermutations)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    ABSL_DCHECK(from._impl_.new_idxs_ != nullptr);
    if (_this->_impl_.new_idxs_ == nullptr) {
      _this->_impl_.new_idxs_ =
          ::google::protobuf::Message::CopyConstruct<::lattica_proto::TensorHolder>(arena, *from._impl_.new_idxs_);
    } else {
      _this->_impl_.new_idxs_->MergeFrom(*from._impl_.new_idxs_);
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void CrtPermutations::CopyFrom(const CrtPermutations& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lattica_proto.CrtPermutations)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void CrtPermutations::InternalSwap(CrtPermutations* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.new_idxs_, other->_impl_.new_idxs_);
}

::google::protobuf::Metadata CrtPermutations::GetMetadata() const {
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
        (::_pbi::AddDescriptors(&descriptor_table_serialization_2fslot_5fpermutations_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
