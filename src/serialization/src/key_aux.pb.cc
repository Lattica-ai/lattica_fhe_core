// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: serialization/key_aux.proto
// Protobuf C++ Version: 5.27.1

#include "key_aux.pb.h"

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

inline constexpr RBGV_AuxKey::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        base_key_{nullptr},
        full_key_{nullptr},
        identity_key_{nullptr},
        square_key_{nullptr} {}

template <typename>
PROTOBUF_CONSTEXPR RBGV_AuxKey::RBGV_AuxKey(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct RBGV_AuxKeyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RBGV_AuxKeyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~RBGV_AuxKeyDefaultTypeInternal() {}
  union {
    RBGV_AuxKey _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RBGV_AuxKeyDefaultTypeInternal _RBGV_AuxKey_default_instance_;

inline constexpr CKKS_AuxKey::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        base_key_{nullptr},
        full_key_{nullptr},
        identity_key_{nullptr},
        square_key_{nullptr} {}

template <typename>
PROTOBUF_CONSTEXPR CKKS_AuxKey::CKKS_AuxKey(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct CKKS_AuxKeyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR CKKS_AuxKeyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~CKKS_AuxKeyDefaultTypeInternal() {}
  union {
    CKKS_AuxKey _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 CKKS_AuxKeyDefaultTypeInternal _CKKS_AuxKey_default_instance_;
}  // namespace lattica_proto
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_serialization_2fkey_5faux_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_serialization_2fkey_5faux_2eproto = nullptr;
const ::uint32_t
    TableStruct_serialization_2fkey_5faux_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _impl_.base_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _impl_.full_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _impl_.identity_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::CKKS_AuxKey, _impl_.square_key_),
        0,
        1,
        2,
        3,
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _impl_._has_bits_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _impl_.base_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _impl_.full_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _impl_.identity_key_),
        PROTOBUF_FIELD_OFFSET(::lattica_proto::RBGV_AuxKey, _impl_.square_key_),
        0,
        1,
        2,
        3,
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, 12, -1, sizeof(::lattica_proto::CKKS_AuxKey)},
        {16, 28, -1, sizeof(::lattica_proto::RBGV_AuxKey)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::lattica_proto::_CKKS_AuxKey_default_instance_._instance,
    &::lattica_proto::_RBGV_AuxKey_default_instance_._instance,
};
const char descriptor_table_protodef_serialization_2fkey_5faux_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\033serialization/key_aux.proto\022\rlattica_p"
    "roto\032\037serialization/ciphertexts.proto\"\251\002"
    "\n\013CKKS_AuxKey\0225\n\010base_key\030\001 \001(\0132\036.lattic"
    "a_proto.CKKS_CiphertextH\000\210\001\001\0225\n\010full_key"
    "\030\002 \001(\0132\036.lattica_proto.CKKS_CiphertextH\001"
    "\210\001\001\0229\n\014identity_key\030\003 \001(\0132\036.lattica_prot"
    "o.CKKS_CiphertextH\002\210\001\001\0227\n\nsquare_key\030\004 \001"
    "(\0132\036.lattica_proto.CKKS_CiphertextH\003\210\001\001B"
    "\013\n\t_base_keyB\013\n\t_full_keyB\017\n\r_identity_k"
    "eyB\r\n\013_square_key\"\251\002\n\013RBGV_AuxKey\0225\n\010bas"
    "e_key\030\001 \001(\0132\036.lattica_proto.RBGV_Ciphert"
    "extH\000\210\001\001\0225\n\010full_key\030\002 \001(\0132\036.lattica_pro"
    "to.RBGV_CiphertextH\001\210\001\001\0229\n\014identity_key\030"
    "\003 \001(\0132\036.lattica_proto.RBGV_CiphertextH\002\210"
    "\001\001\0227\n\nsquare_key\030\004 \001(\0132\036.lattica_proto.R"
    "BGV_CiphertextH\003\210\001\001B\013\n\t_base_keyB\013\n\t_ful"
    "l_keyB\017\n\r_identity_keyB\r\n\013_square_keyb\006p"
    "roto3"
};
static const ::_pbi::DescriptorTable* const descriptor_table_serialization_2fkey_5faux_2eproto_deps[1] =
    {
        &::descriptor_table_serialization_2fciphertexts_2eproto,
};
static ::absl::once_flag descriptor_table_serialization_2fkey_5faux_2eproto_once;
PROTOBUF_CONSTINIT const ::_pbi::DescriptorTable descriptor_table_serialization_2fkey_5faux_2eproto = {
    false,
    false,
    685,
    descriptor_table_protodef_serialization_2fkey_5faux_2eproto,
    "serialization/key_aux.proto",
    &descriptor_table_serialization_2fkey_5faux_2eproto_once,
    descriptor_table_serialization_2fkey_5faux_2eproto_deps,
    1,
    2,
    schemas,
    file_default_instances,
    TableStruct_serialization_2fkey_5faux_2eproto::offsets,
    file_level_enum_descriptors_serialization_2fkey_5faux_2eproto,
    file_level_service_descriptors_serialization_2fkey_5faux_2eproto,
};
namespace lattica_proto {
// ===================================================================

class CKKS_AuxKey::_Internal {
 public:
  using HasBits =
      decltype(std::declval<CKKS_AuxKey>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_._has_bits_);
};

void CKKS_AuxKey::clear_base_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.base_key_ != nullptr) _impl_.base_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
void CKKS_AuxKey::clear_full_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.full_key_ != nullptr) _impl_.full_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
void CKKS_AuxKey::clear_identity_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.identity_key_ != nullptr) _impl_.identity_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
void CKKS_AuxKey::clear_square_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.square_key_ != nullptr) _impl_.square_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000008u;
}
CKKS_AuxKey::CKKS_AuxKey(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:lattica_proto.CKKS_AuxKey)
}
inline PROTOBUF_NDEBUG_INLINE CKKS_AuxKey::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::lattica_proto::CKKS_AuxKey& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

CKKS_AuxKey::CKKS_AuxKey(
    ::google::protobuf::Arena* arena,
    const CKKS_AuxKey& from)
    : ::google::protobuf::Message(arena) {
  CKKS_AuxKey* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.base_key_ = (cached_has_bits & 0x00000001u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(
                              arena, *from._impl_.base_key_)
                        : nullptr;
  _impl_.full_key_ = (cached_has_bits & 0x00000002u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(
                              arena, *from._impl_.full_key_)
                        : nullptr;
  _impl_.identity_key_ = (cached_has_bits & 0x00000004u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(
                              arena, *from._impl_.identity_key_)
                        : nullptr;
  _impl_.square_key_ = (cached_has_bits & 0x00000008u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(
                              arena, *from._impl_.square_key_)
                        : nullptr;

  // @@protoc_insertion_point(copy_constructor:lattica_proto.CKKS_AuxKey)
}
inline PROTOBUF_NDEBUG_INLINE CKKS_AuxKey::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void CKKS_AuxKey::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, base_key_),
           0,
           offsetof(Impl_, square_key_) -
               offsetof(Impl_, base_key_) +
               sizeof(Impl_::square_key_));
}
CKKS_AuxKey::~CKKS_AuxKey() {
  // @@protoc_insertion_point(destructor:lattica_proto.CKKS_AuxKey)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void CKKS_AuxKey::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.base_key_;
  delete _impl_.full_key_;
  delete _impl_.identity_key_;
  delete _impl_.square_key_;
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
CKKS_AuxKey::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              &_table_.header,
              nullptr,  // OnDemandRegisterArenaDtor
              nullptr,  // IsInitialized
              PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_._cached_size_),
              false,
          },
          &CKKS_AuxKey::MergeImpl,
          &CKKS_AuxKey::kDescriptorMethods,
          &descriptor_table_serialization_2fkey_5faux_2eproto,
          nullptr,  // tracker
      };
  ::google::protobuf::internal::PrefetchToLocalCache(&_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_data_.tc_table);
  return _data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 4, 0, 2> CKKS_AuxKey::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_._has_bits_),
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    4,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_CKKS_AuxKey_default_instance_._instance,
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::lattica_proto::CKKS_AuxKey>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // optional .lattica_proto.CKKS_Ciphertext square_key = 4;
    {::_pbi::TcParser::FastMtS1,
     {34, 3, 3, PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.square_key_)}},
    // optional .lattica_proto.CKKS_Ciphertext base_key = 1;
    {::_pbi::TcParser::FastMtS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.base_key_)}},
    // optional .lattica_proto.CKKS_Ciphertext full_key = 2;
    {::_pbi::TcParser::FastMtS1,
     {18, 1, 1, PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.full_key_)}},
    // optional .lattica_proto.CKKS_Ciphertext identity_key = 3;
    {::_pbi::TcParser::FastMtS1,
     {26, 2, 2, PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.identity_key_)}},
  }}, {{
    65535, 65535
  }}, {{
    // optional .lattica_proto.CKKS_Ciphertext base_key = 1;
    {PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.base_key_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.CKKS_Ciphertext full_key = 2;
    {PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.full_key_), _Internal::kHasBitsOffset + 1, 1,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.CKKS_Ciphertext identity_key = 3;
    {PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.identity_key_), _Internal::kHasBitsOffset + 2, 2,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.CKKS_Ciphertext square_key = 4;
    {PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.square_key_), _Internal::kHasBitsOffset + 3, 3,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::lattica_proto::CKKS_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::CKKS_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::CKKS_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::CKKS_Ciphertext>()},
  }}, {{
  }},
};

PROTOBUF_NOINLINE void CKKS_AuxKey::Clear() {
// @@protoc_insertion_point(message_clear_start:lattica_proto.CKKS_AuxKey)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(_impl_.base_key_ != nullptr);
      _impl_.base_key_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(_impl_.full_key_ != nullptr);
      _impl_.full_key_->Clear();
    }
    if (cached_has_bits & 0x00000004u) {
      ABSL_DCHECK(_impl_.identity_key_ != nullptr);
      _impl_.identity_key_->Clear();
    }
    if (cached_has_bits & 0x00000008u) {
      ABSL_DCHECK(_impl_.square_key_ != nullptr);
      _impl_.square_key_->Clear();
    }
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

::uint8_t* CKKS_AuxKey::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:lattica_proto.CKKS_AuxKey)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional .lattica_proto.CKKS_Ciphertext base_key = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        1, *_impl_.base_key_, _impl_.base_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.CKKS_Ciphertext full_key = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        2, *_impl_.full_key_, _impl_.full_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.CKKS_Ciphertext identity_key = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        3, *_impl_.identity_key_, _impl_.identity_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.CKKS_Ciphertext square_key = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        4, *_impl_.square_key_, _impl_.square_key_->GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lattica_proto.CKKS_AuxKey)
  return target;
}

::size_t CKKS_AuxKey::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lattica_proto.CKKS_AuxKey)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::_pbi::Prefetch5LinesFrom7Lines(reinterpret_cast<const void*>(this));
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional .lattica_proto.CKKS_Ciphertext base_key = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.base_key_);
    }

    // optional .lattica_proto.CKKS_Ciphertext full_key = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.full_key_);
    }

    // optional .lattica_proto.CKKS_Ciphertext identity_key = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.identity_key_);
    }

    // optional .lattica_proto.CKKS_Ciphertext square_key = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.square_key_);
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void CKKS_AuxKey::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<CKKS_AuxKey*>(&to_msg);
  auto& from = static_cast<const CKKS_AuxKey&>(from_msg);
  ::google::protobuf::Arena* arena = _this->GetArena();
  // @@protoc_insertion_point(class_specific_merge_from_start:lattica_proto.CKKS_AuxKey)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(from._impl_.base_key_ != nullptr);
      if (_this->_impl_.base_key_ == nullptr) {
        _this->_impl_.base_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(arena, *from._impl_.base_key_);
      } else {
        _this->_impl_.base_key_->MergeFrom(*from._impl_.base_key_);
      }
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(from._impl_.full_key_ != nullptr);
      if (_this->_impl_.full_key_ == nullptr) {
        _this->_impl_.full_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(arena, *from._impl_.full_key_);
      } else {
        _this->_impl_.full_key_->MergeFrom(*from._impl_.full_key_);
      }
    }
    if (cached_has_bits & 0x00000004u) {
      ABSL_DCHECK(from._impl_.identity_key_ != nullptr);
      if (_this->_impl_.identity_key_ == nullptr) {
        _this->_impl_.identity_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(arena, *from._impl_.identity_key_);
      } else {
        _this->_impl_.identity_key_->MergeFrom(*from._impl_.identity_key_);
      }
    }
    if (cached_has_bits & 0x00000008u) {
      ABSL_DCHECK(from._impl_.square_key_ != nullptr);
      if (_this->_impl_.square_key_ == nullptr) {
        _this->_impl_.square_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::CKKS_Ciphertext>(arena, *from._impl_.square_key_);
      } else {
        _this->_impl_.square_key_->MergeFrom(*from._impl_.square_key_);
      }
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void CKKS_AuxKey::CopyFrom(const CKKS_AuxKey& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lattica_proto.CKKS_AuxKey)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void CKKS_AuxKey::InternalSwap(CKKS_AuxKey* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.square_key_)
      + sizeof(CKKS_AuxKey::_impl_.square_key_)
      - PROTOBUF_FIELD_OFFSET(CKKS_AuxKey, _impl_.base_key_)>(
          reinterpret_cast<char*>(&_impl_.base_key_),
          reinterpret_cast<char*>(&other->_impl_.base_key_));
}

::google::protobuf::Metadata CKKS_AuxKey::GetMetadata() const {
  return ::google::protobuf::Message::GetMetadataImpl(GetClassData()->full());
}
// ===================================================================

class RBGV_AuxKey::_Internal {
 public:
  using HasBits =
      decltype(std::declval<RBGV_AuxKey>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
      8 * PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_._has_bits_);
};

void RBGV_AuxKey::clear_base_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.base_key_ != nullptr) _impl_.base_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
void RBGV_AuxKey::clear_full_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.full_key_ != nullptr) _impl_.full_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
void RBGV_AuxKey::clear_identity_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.identity_key_ != nullptr) _impl_.identity_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
void RBGV_AuxKey::clear_square_key() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  if (_impl_.square_key_ != nullptr) _impl_.square_key_->Clear();
  _impl_._has_bits_[0] &= ~0x00000008u;
}
RBGV_AuxKey::RBGV_AuxKey(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:lattica_proto.RBGV_AuxKey)
}
inline PROTOBUF_NDEBUG_INLINE RBGV_AuxKey::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from, const ::lattica_proto::RBGV_AuxKey& from_msg)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

RBGV_AuxKey::RBGV_AuxKey(
    ::google::protobuf::Arena* arena,
    const RBGV_AuxKey& from)
    : ::google::protobuf::Message(arena) {
  RBGV_AuxKey* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_, from);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.base_key_ = (cached_has_bits & 0x00000001u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(
                              arena, *from._impl_.base_key_)
                        : nullptr;
  _impl_.full_key_ = (cached_has_bits & 0x00000002u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(
                              arena, *from._impl_.full_key_)
                        : nullptr;
  _impl_.identity_key_ = (cached_has_bits & 0x00000004u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(
                              arena, *from._impl_.identity_key_)
                        : nullptr;
  _impl_.square_key_ = (cached_has_bits & 0x00000008u) ? ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(
                              arena, *from._impl_.square_key_)
                        : nullptr;

  // @@protoc_insertion_point(copy_constructor:lattica_proto.RBGV_AuxKey)
}
inline PROTOBUF_NDEBUG_INLINE RBGV_AuxKey::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void RBGV_AuxKey::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, base_key_),
           0,
           offsetof(Impl_, square_key_) -
               offsetof(Impl_, base_key_) +
               sizeof(Impl_::square_key_));
}
RBGV_AuxKey::~RBGV_AuxKey() {
  // @@protoc_insertion_point(destructor:lattica_proto.RBGV_AuxKey)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void RBGV_AuxKey::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.base_key_;
  delete _impl_.full_key_;
  delete _impl_.identity_key_;
  delete _impl_.square_key_;
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
RBGV_AuxKey::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              &_table_.header,
              nullptr,  // OnDemandRegisterArenaDtor
              nullptr,  // IsInitialized
              PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_._cached_size_),
              false,
          },
          &RBGV_AuxKey::MergeImpl,
          &RBGV_AuxKey::kDescriptorMethods,
          &descriptor_table_serialization_2fkey_5faux_2eproto,
          nullptr,  // tracker
      };
  ::google::protobuf::internal::PrefetchToLocalCache(&_data_);
  ::google::protobuf::internal::PrefetchToLocalCache(_data_.tc_table);
  return _data_.base();
}
PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 4, 0, 2> RBGV_AuxKey::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_._has_bits_),
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    4,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_RBGV_AuxKey_default_instance_._instance,
    nullptr,  // post_loop_handler
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::lattica_proto::RBGV_AuxKey>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // optional .lattica_proto.RBGV_Ciphertext square_key = 4;
    {::_pbi::TcParser::FastMtS1,
     {34, 3, 3, PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.square_key_)}},
    // optional .lattica_proto.RBGV_Ciphertext base_key = 1;
    {::_pbi::TcParser::FastMtS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.base_key_)}},
    // optional .lattica_proto.RBGV_Ciphertext full_key = 2;
    {::_pbi::TcParser::FastMtS1,
     {18, 1, 1, PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.full_key_)}},
    // optional .lattica_proto.RBGV_Ciphertext identity_key = 3;
    {::_pbi::TcParser::FastMtS1,
     {26, 2, 2, PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.identity_key_)}},
  }}, {{
    65535, 65535
  }}, {{
    // optional .lattica_proto.RBGV_Ciphertext base_key = 1;
    {PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.base_key_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.RBGV_Ciphertext full_key = 2;
    {PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.full_key_), _Internal::kHasBitsOffset + 1, 1,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.RBGV_Ciphertext identity_key = 3;
    {PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.identity_key_), _Internal::kHasBitsOffset + 2, 2,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .lattica_proto.RBGV_Ciphertext square_key = 4;
    {PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.square_key_), _Internal::kHasBitsOffset + 3, 3,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::lattica_proto::RBGV_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::RBGV_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::RBGV_Ciphertext>()},
    {::_pbi::TcParser::GetTable<::lattica_proto::RBGV_Ciphertext>()},
  }}, {{
  }},
};

PROTOBUF_NOINLINE void RBGV_AuxKey::Clear() {
// @@protoc_insertion_point(message_clear_start:lattica_proto.RBGV_AuxKey)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(_impl_.base_key_ != nullptr);
      _impl_.base_key_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(_impl_.full_key_ != nullptr);
      _impl_.full_key_->Clear();
    }
    if (cached_has_bits & 0x00000004u) {
      ABSL_DCHECK(_impl_.identity_key_ != nullptr);
      _impl_.identity_key_->Clear();
    }
    if (cached_has_bits & 0x00000008u) {
      ABSL_DCHECK(_impl_.square_key_ != nullptr);
      _impl_.square_key_->Clear();
    }
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

::uint8_t* RBGV_AuxKey::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:lattica_proto.RBGV_AuxKey)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional .lattica_proto.RBGV_Ciphertext base_key = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        1, *_impl_.base_key_, _impl_.base_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.RBGV_Ciphertext full_key = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        2, *_impl_.full_key_, _impl_.full_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.RBGV_Ciphertext identity_key = 3;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        3, *_impl_.identity_key_, _impl_.identity_key_->GetCachedSize(), target, stream);
  }

  // optional .lattica_proto.RBGV_Ciphertext square_key = 4;
  if (cached_has_bits & 0x00000008u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        4, *_impl_.square_key_, _impl_.square_key_->GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:lattica_proto.RBGV_AuxKey)
  return target;
}

::size_t RBGV_AuxKey::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:lattica_proto.RBGV_AuxKey)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::_pbi::Prefetch5LinesFrom7Lines(reinterpret_cast<const void*>(this));
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional .lattica_proto.RBGV_Ciphertext base_key = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.base_key_);
    }

    // optional .lattica_proto.RBGV_Ciphertext full_key = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.full_key_);
    }

    // optional .lattica_proto.RBGV_Ciphertext identity_key = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.identity_key_);
    }

    // optional .lattica_proto.RBGV_Ciphertext square_key = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.square_key_);
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void RBGV_AuxKey::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<RBGV_AuxKey*>(&to_msg);
  auto& from = static_cast<const RBGV_AuxKey&>(from_msg);
  ::google::protobuf::Arena* arena = _this->GetArena();
  // @@protoc_insertion_point(class_specific_merge_from_start:lattica_proto.RBGV_AuxKey)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(from._impl_.base_key_ != nullptr);
      if (_this->_impl_.base_key_ == nullptr) {
        _this->_impl_.base_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(arena, *from._impl_.base_key_);
      } else {
        _this->_impl_.base_key_->MergeFrom(*from._impl_.base_key_);
      }
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(from._impl_.full_key_ != nullptr);
      if (_this->_impl_.full_key_ == nullptr) {
        _this->_impl_.full_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(arena, *from._impl_.full_key_);
      } else {
        _this->_impl_.full_key_->MergeFrom(*from._impl_.full_key_);
      }
    }
    if (cached_has_bits & 0x00000004u) {
      ABSL_DCHECK(from._impl_.identity_key_ != nullptr);
      if (_this->_impl_.identity_key_ == nullptr) {
        _this->_impl_.identity_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(arena, *from._impl_.identity_key_);
      } else {
        _this->_impl_.identity_key_->MergeFrom(*from._impl_.identity_key_);
      }
    }
    if (cached_has_bits & 0x00000008u) {
      ABSL_DCHECK(from._impl_.square_key_ != nullptr);
      if (_this->_impl_.square_key_ == nullptr) {
        _this->_impl_.square_key_ =
            ::google::protobuf::Message::CopyConstruct<::lattica_proto::RBGV_Ciphertext>(arena, *from._impl_.square_key_);
      } else {
        _this->_impl_.square_key_->MergeFrom(*from._impl_.square_key_);
      }
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void RBGV_AuxKey::CopyFrom(const RBGV_AuxKey& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:lattica_proto.RBGV_AuxKey)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}


void RBGV_AuxKey::InternalSwap(RBGV_AuxKey* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.square_key_)
      + sizeof(RBGV_AuxKey::_impl_.square_key_)
      - PROTOBUF_FIELD_OFFSET(RBGV_AuxKey, _impl_.base_key_)>(
          reinterpret_cast<char*>(&_impl_.base_key_),
          reinterpret_cast<char*>(&other->_impl_.base_key_));
}

::google::protobuf::Metadata RBGV_AuxKey::GetMetadata() const {
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
        (::_pbi::AddDescriptors(&descriptor_table_serialization_2fkey_5faux_2eproto),
         ::std::false_type{});
#include "google/protobuf/port_undef.inc"
