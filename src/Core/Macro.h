﻿#pragma once

#define MESH_EDITOR_EXPAND_MACRO(x) x
#define MESH_EDITOR_STRINGIFY_MACRO(x) #x

#ifdef MESH_EDITOR_ENABLE_ASSERTS
    // Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
    // provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
    #define MESH_EDITOR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LOG_ERROR(msg, __VA_ARGS__); __debugbreak(); } }
    #define MESH_EDITOR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) MESH_EDITOR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define MESH_EDITOR_INTERNAL_ASSERT_NO_MSG(type, check) MESH_EDITOR_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", MESH_EDITOR_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define MESH_EDITOR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define MESH_EDITOR_INTERNAL_ASSERT_GET_MACRO(...) MESH_EDITOR_EXPAND_MACRO( MESH_EDITOR_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, MESH_EDITOR_INTERNAL_ASSERT_WITH_MSG, MESH_EDITOR_INTERNAL_ASSERT_NO_MSG) )

    // Currently accepts at least the condition and one additional parameter (the message) being optional
    #define MESH_EDITOR_ASSERT(...) MESH_EDITOR_EXPAND_MACRO( MESH_EDITOR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define MESH_EDITOR_CORE_ASSERT(...) MESH_EDITOR_EXPAND_MACRO( MESH_EDITOR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define MESH_EDITOR_ASSERT(...)
    #define MESH_EDITOR_CORE_ASSERT(...)
#endif