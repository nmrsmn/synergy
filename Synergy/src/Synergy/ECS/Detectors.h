// Created by Niels Marsman on 15-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SYNERGY_ECS_DETECTORS_H
#define SYNERGY_ECS_DETECTORS_H

#include <experimental/type_traits>

namespace Synergy
{
    template <typename T>
    struct is_member_function : std::false_type {};

    template <typename Class, typename Return, typename Args>
    struct is_member_function<Return (Class::*) (Args...) const> : std::true_type {};

    template <typename T>
    constexpr bool is_member_function_v = is_member_function<T>::value;
}

/*
 * Detect vec fields
 */

template <typename T>
using position_field_t = decltype(std::declval<T&>().position.x + std::declval<T&>().position.y + std::declval<T&>().position.z);

template <typename T>
using supports_position_field = std::experimental::is_detected<position_field_t, T>;

/*
 * Detect
 */

template <typename T>
using initialize_member_t = decltype(std::declval<T&>().Initialize());

template <typename T>
using has_initialize_member = std::experimental::is_detected<initialize_member_t, T>;

/*
    Initialize
    Enable
 
    Start
 
    FrameStart
 
    FixedUpdate
 
    Update
    PostUpdate
 
    FrameEnd
    Disable
 
    Destroy
 */


/*
 template <typename T>                                                        \
 using FIELD##_field                                                          \
   = decltype(std::declval<T &>().FIELD.x + std::declval<T &>().FIELD.y);     \
                                                                              \
 template <typename T>                                                        \
 using has_##FIELD##_field = is_detected<FIELD##_field, T>;                   \
                                                                              \
 template <typename T>                                                        \
 constexpr bool has_##FIELD##_field_v = has_##FIELD##_field<T>::value;        \
                                                                              \
 template <typename T>                                                        \
 constexpr size_t FIELD##_field_size = sizeof(                                \
   std::conditional_t<has_##FIELD##_field_v<T>,                               \
                      decltype(std::declval<T &>().FIELD), void_t<T>>);
 
 
 #define GENERATE_DETECT_HAS_VOID_MEMFN(FN)                                     \
                                                                              \
 template <typename T>                                                        \
 using UpdateMemFn = decltype(std::declval<T &>().Update());                        \
                                                                              \
 template <typename T>                                                        \
 using HasUpdateMemFn = is_detected<UpdateMemFn, T>;                            \
                                                                              \
 template <typename T>                                                        \
 constexpr bool HasUpdateMemFn_v = HasUpdateMemFn<T>::value;
 
 

 template <typename T>
 using DetectDtMember = decltype(std::declval<T &>().Dt = 1.f);
 template <typename T>
 using HasDtMember = is_detected<DetectDtMember, T>;
 template <typename T>
 constexpr bool HasDtMember_v = HasDtMember<T>::value;

 // composition of all minimum requirements for a component
 template <typename T>
 constexpr bool IsComponent_v = std::is_copy_constructible_v<T>;

 
 */

#endif
