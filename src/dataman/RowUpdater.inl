/* Copyright (c) 2018 - present, VE Software Inc. All rights reserved
 *
 * This source code is licensed under Apache 2.0 License
 *  (found in the LICENSE.Apache file in the root directory)
 */

namespace nebula {

template<typename T>
typename std::enable_if<std::is_integral<T>::value, ResultType>::type
RowUpdater::setInt(const folly::StringPiece name, T v) noexcept {
    RU_GET_TYPE_BY_NAME()

    uint64_t hash;
    switch (type->get_type()) {
        case storage::cpp2::SupportedType::INT:
            hash = folly::hash::SpookyHashV2::Hash64(name.begin(),
                                                     name.size(),
                                                     0);
            updatedFields_[hash] = (int64_t)v;
            break;
        default:
            return ResultType::E_INCOMPATIBLE_TYPE;
    }

    return ResultType::SUCCEEDED;
}


template<typename T>
typename std::enable_if<std::is_integral<T>::value, ResultType>::type
RowUpdater::getInt(const folly::StringPiece name, T& v) const noexcept {
    RU_CHECK_UPDATED_FIELDS(Int)

    switch (it->second.which()) {
    case VALUE_TYPE_INT:
        v = boost::get<int64_t>(it->second);
        break;
    default:
        return ResultType::E_INCOMPATIBLE_TYPE;
    }

    return ResultType::SUCCEEDED;
}

}  // namespace nebula
