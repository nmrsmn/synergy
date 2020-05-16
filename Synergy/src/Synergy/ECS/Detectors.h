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
 * Detect (system) members
 */

// Initialize
template <typename T>
using initialize_member_t = decltype(std::declval<T&>().Initialize());

template <typename T>
using has_initialize_member = std::experimental::is_detected<initialize_member_t, T>;

// Destroy
template <typename T>
using destroy_member_t = decltype(std::declval<T&>().Destroy());

template <typename T>
using has_destroy_member = std::experimental::is_detected<destroy_member_t, T>;

// Enable
template <typename T>
using enable_member_t = decltype(std::declval<T&>().Enable());

template <typename T>
using has_enable_member = std::experimental::is_detected<enable_member_t, T>;

// Disable
template <typename T>
using disable_member_t = decltype(std::declval<T&>().Disable());

template <typename T>
using has_disable_member = std::experimental::is_detected<disable_member_t, T>;

// Load
template <typename T>
using load_member_t = decltype(std::declval<T&>().Load());

template <typename T>
using has_load_member = std::experimental::is_detected<load_member_t, T>;

// Unload
template <typename T>
using unload_member_t = decltype(std::declval<T&>().Unload());

template <typename T>
using has_unload_member = std::experimental::is_detected<unload_member_t, T>;

// Reload
template <typename T>
using reload_member_t = decltype(std::declval<T&>().Reload());

template <typename T>
using has_reload_member = std::experimental::is_detected<reload_member_t, T>;

// Frame Start
template <typename T>
using frame_start_member_t = decltype(std::declval<T&>().FrameStart());

template <typename T>
using has_frame_start_member = std::experimental::is_detected<frame_start_member_t, T>;

// Frame End
template <typename T>
using frame_end_member_t = decltype(std::declval<T&>().FrameEnd());

template <typename T>
using has_frame_end_member = std::experimental::is_detected<frame_end_member_t, T>;

// Fixed Update
template <typename T>
using fixed_update_member_t = decltype(std::declval<T&>().FixedUpdate());

template <typename T>
using has_fixed_update_member = std::experimental::is_detected<fixed_update_member_t, T>;

// Pre Process
template <typename T>
using pre_process_member_t = decltype(std::declval<T&>().PreProcess());

template <typename T>
using has_pre_process_member = std::experimental::is_detected<pre_process_member_t, T>;

// Process
template <typename T, typename = void>
struct has_process_member : std::false_type {};

template <typename T>
struct has_process_member<T, std::enable_if_t<Synergy::is_member_function_v<decltype(&T::Process)>>> : std::true_type {};

// Post Process
template <typename T>
using post_process_member_t = decltype(std::declval<T&>().PostProcess());

template <typename T>
using has_post_process_member = std::experimental::is_detected<post_process_member_t, T>;

// Update
template <typename T>
using update_member_t = decltype(std::declval<T&>().Update());

template <typename T>
using has_update_member = std::experimental::is_detected<update_member_t, T>;

// Post Update
template <typename T>
using post_update_member_t = decltype(std::declval<T&>().PostUpdate());

template <typename T>
using has_post_update_member = std::experimental::is_detected<post_update_member_t, T>;

#endif
