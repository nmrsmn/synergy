// Created by Niels Marsman on 15-04-2020.
// Copyright © 2019 Niels Marsman. All rights reserved.

#include <glad/glad.h>

#include "Synergy/Platform/GLFW.h"
#include "Synergy/Input.h"

namespace Synergy::Platforms
{
    bool GLFW::Init()
    {
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description)
        {
            SYNERGY_LOG_ERROR("Platform error ({0}): {1}", error, description);
        });
        
        return true;
    }

    bool GLFW::Start()
    {   
        return true;
    }

    bool GLFW::Shutdown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        
        return true;
    }

    bool GLFW::CreateContext()
    {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);
        
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        UpdateWindowSize({ width, height });
        
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        SYNERGY_ASSERT(status, "Failed to initialize glad!");
        
        SYNERGY_LOG_INFO("Graphic info:");
        SYNERGY_LOG_INFO("\tVendor:\t\t\t{}", glGetString(GL_VENDOR));
        SYNERGY_LOG_INFO("\tRenderer:\t\t{}", glGetString(GL_RENDERER));
        SYNERGY_LOG_INFO("\tVersion:\t\t{}", glGetString(GL_VERSION));

        return true;
    }

    bool GLFW::CreateWindow(glm::vec2 offset, glm::vec2 size, bool fullscreen)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        window = glfwCreateWindow(size.x, size.y, "Synergy", nullptr, nullptr);
        SYNERGY_ASSERT(window, "Failed to create window.");
        
        glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
        glfwSetWindowUserPointer(window, this);
        
        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            GLFW* platform = (GLFW*) glfwGetWindowUserPointer(window);
            platform->CloseWindow();
        });
        
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            GLFW* platform = (GLFW*) glfwGetWindowUserPointer(window);
            platform->UpdateKeyState(platform->keys[key], action != GLFW_RELEASE);
        });
        
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFW* platform = (GLFW*) glfwGetWindowUserPointer(window);
            platform->UpdateMouseState(button, action != GLFW_RELEASE);
        });
        
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y)
        {
            GLFW* platform = (GLFW*) glfwGetWindowUserPointer(window);
            platform->UpdateMousePosition({ x, y });
        });
        
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            GLFW* platform = (GLFW*) glfwGetWindowUserPointer(window);
            platform->UpdateWindowSize({ width, height });
        });
        
        keys[GLFW_KEY_UNKNOWN] = Input::Key::UNKNOWN;
        keys[GLFW_KEY_A] = Input::Key::A; keys[GLFW_KEY_B] = Input::Key::B; keys[GLFW_KEY_C] = Input::Key::C;
        keys[GLFW_KEY_D] = Input::Key::D; keys[GLFW_KEY_E] = Input::Key::E; keys[GLFW_KEY_F] = Input::Key::F;
        keys[GLFW_KEY_G] = Input::Key::G; keys[GLFW_KEY_H] = Input::Key::H; keys[GLFW_KEY_I] = Input::Key::I;
        keys[GLFW_KEY_J] = Input::Key::J; keys[GLFW_KEY_K] = Input::Key::K; keys[GLFW_KEY_L] = Input::Key::L;
        keys[GLFW_KEY_M] = Input::Key::M; keys[GLFW_KEY_N] = Input::Key::N; keys[GLFW_KEY_O] = Input::Key::O;
        keys[GLFW_KEY_P] = Input::Key::P; keys[GLFW_KEY_Q] = Input::Key::Q; keys[GLFW_KEY_R] = Input::Key::R;
        keys[GLFW_KEY_S] = Input::Key::S; keys[GLFW_KEY_T] = Input::Key::T; keys[GLFW_KEY_U] = Input::Key::U;
        keys[GLFW_KEY_V] = Input::Key::V; keys[GLFW_KEY_W] = Input::Key::W; keys[GLFW_KEY_X] = Input::Key::X;
        keys[GLFW_KEY_Y] = Input::Key::Y; keys[GLFW_KEY_Z] = Input::Key::Z;
        
        keys[GLFW_KEY_F1] = Input::Key::F1; keys[GLFW_KEY_F2] = Input::Key::F2; keys[GLFW_KEY_F3] = Input::Key::F3;
        keys[GLFW_KEY_F4] = Input::Key::F4; keys[GLFW_KEY_F5] = Input::Key::F5; keys[GLFW_KEY_F6] = Input::Key::F6;
        keys[GLFW_KEY_F7] = Input::Key::F7; keys[GLFW_KEY_F8] = Input::Key::F8; keys[GLFW_KEY_F9] = Input::Key::F9;
        keys[GLFW_KEY_F10] = Input::Key::F10; keys[GLFW_KEY_F11] = Input::Key::F11; keys[GLFW_KEY_F12] = Input::Key::F12;
        keys[GLFW_KEY_F13] = Input::Key::F13; keys[GLFW_KEY_F14] = Input::Key::F14; keys[GLFW_KEY_F15] = Input::Key::F15;
        keys[GLFW_KEY_F16] = Input::Key::F16; keys[GLFW_KEY_F17] = Input::Key::F17; keys[GLFW_KEY_F18] = Input::Key::F18;
        keys[GLFW_KEY_F19] = Input::Key::F19; keys[GLFW_KEY_F20] = Input::Key::F20; keys[GLFW_KEY_F21] = Input::Key::F21;
        keys[GLFW_KEY_F22] = Input::Key::F22; keys[GLFW_KEY_F23] = Input::Key::F23; keys[GLFW_KEY_F24] = Input::Key::F24;
        keys[GLFW_KEY_F25] = Input::Key::F25;
        
        keys[GLFW_KEY_0] = Input::Key::KEY_0; keys[GLFW_KEY_1] = Input::Key::KEY_1; keys[GLFW_KEY_2] = Input::Key::KEY_2;
        keys[GLFW_KEY_3] = Input::Key::KEY_3; keys[GLFW_KEY_4] = Input::Key::KEY_4; keys[GLFW_KEY_5] = Input::Key::KEY_5;
        keys[GLFW_KEY_6] = Input::Key::KEY_6; keys[GLFW_KEY_7] = Input::Key::KEY_7; keys[GLFW_KEY_8] = Input::Key::KEY_8;
        keys[GLFW_KEY_9] = Input::Key::KEY_9;
        
        keys[GLFW_KEY_KP_0] = Input::Key::KEYPAD_0; keys[GLFW_KEY_KP_1] = Input::Key::KEYPAD_1; keys[GLFW_KEY_KP_2] = Input::Key::KEYPAD_2;
        keys[GLFW_KEY_KP_3] = Input::Key::KEYPAD_3; keys[GLFW_KEY_KP_4] = Input::Key::KEYPAD_4; keys[GLFW_KEY_KP_5] = Input::Key::KEYPAD_5;
        keys[GLFW_KEY_KP_6] = Input::Key::KEYPAD_6; keys[GLFW_KEY_KP_7] = Input::Key::KEYPAD_7; keys[GLFW_KEY_KP_8] = Input::Key::KEYPAD_8;
        keys[GLFW_KEY_KP_9] = Input::Key::KEYPAD_9;
        
        keys[GLFW_KEY_KP_DECIMAL] = Input::Key::KEYPAD_DECIMAL;
        keys[GLFW_KEY_KP_DIVIDE] = Input::Key::KEYPAD_DIVIDE;
        keys[GLFW_KEY_KP_MULTIPLY] = Input::Key::KEYPAD_MULTIPLY;
        keys[GLFW_KEY_KP_SUBTRACT] = Input::Key::KEYPAD_SUBTRACT;
        keys[GLFW_KEY_KP_ADD] = Input::Key::KEYPAD_ADD;
        keys[GLFW_KEY_KP_ENTER] = Input::Key::KEYPAD_RETURN;
        keys[GLFW_KEY_KP_EQUAL] = Input::Key::KEYPAD_EQUALS;
        
        keys[GLFW_KEY_SPACE] = Input::Key::SPACE;
        keys[GLFW_KEY_APOSTROPHE] = Input::Key::APOSTROPHE;
        keys[GLFW_KEY_COMMA] = Input::Key::COMMA;
        keys[GLFW_KEY_MINUS] = Input::Key::SUBTRACT;
        keys[GLFW_KEY_PERIOD] = Input::Key::PERIOD;
        keys[GLFW_KEY_SLASH] = Input::Key::SLASH;

        keys[GLFW_KEY_SEMICOLON] = Input::Key::SEMICOLON;
        keys[GLFW_KEY_EQUAL] = Input::Key::EQUALS;

        keys[GLFW_KEY_LEFT_BRACKET] = Input::Key::LEFT_BRACKET;
        keys[GLFW_KEY_BACKSLASH] = Input::Key::BACKSLASH;
        keys[GLFW_KEY_RIGHT_BRACKET] = Input::Key::RIGHT_BRACKET;
        keys[GLFW_KEY_GRAVE_ACCENT] = Input::Key::GRAVE;
        keys[GLFW_KEY_WORLD_1] = Input::Key::NONUS_HASH;
        keys[GLFW_KEY_WORLD_2] = Input::Key::NONUS_BACKSLASH;

        keys[GLFW_KEY_ESCAPE] = Input::Key::ESCAPE;
        keys[GLFW_KEY_ENTER] = Input::Key::RETURN;
        keys[GLFW_KEY_TAB] = Input::Key::TAB;
        keys[GLFW_KEY_BACKSPACE] = Input::Key::BACKSPACE;
        keys[GLFW_KEY_INSERT] = Input::Key::INSERT;
        keys[GLFW_KEY_DELETE] = Input::Key::DELETE;
        keys[GLFW_KEY_RIGHT] = Input::Key::RIGHT;
        keys[GLFW_KEY_LEFT] = Input::Key::LEFT;
        keys[GLFW_KEY_DOWN] = Input::Key::DOWN;
        keys[GLFW_KEY_UP] = Input::Key::UP;
        keys[GLFW_KEY_PAGE_UP] = Input::Key::PAGEUP;
        keys[GLFW_KEY_PAGE_DOWN] = Input::Key::PAGEDOWN;
        keys[GLFW_KEY_HOME] = Input::Key::HOME;
        keys[GLFW_KEY_END] = Input::Key::END;
        keys[GLFW_KEY_CAPS_LOCK] = Input::Key::CAPSLOCK;
        keys[GLFW_KEY_SCROLL_LOCK] = Input::Key::SCROLLLOCK;
        keys[GLFW_KEY_NUM_LOCK] = Input::Key::NUMLOCK;
        keys[GLFW_KEY_PRINT_SCREEN] = Input::Key::PRINTSCREEN;
        keys[GLFW_KEY_PAUSE] = Input::Key::PAUSE;

        keys[GLFW_KEY_LEFT_SHIFT] = Input::Key::LEFT_SHIFT;
        keys[GLFW_KEY_LEFT_CONTROL] = Input::Key::LEFT_CTRL;
        keys[GLFW_KEY_LEFT_ALT] = Input::Key::LEFT_ALT;
        keys[GLFW_KEY_LEFT_SUPER] = Input::Key::LEFT_PLATFORM;
        keys[GLFW_KEY_RIGHT_SHIFT] = Input::Key::RIGHT_SHIFT;
        keys[GLFW_KEY_RIGHT_CONTROL] = Input::Key::RIGHT_CTRL;
        keys[GLFW_KEY_RIGHT_ALT] = Input::Key::RIGHT_ALT;
        keys[GLFW_KEY_RIGHT_SUPER] = Input::Key::RIGHT_PLATFORM;
        keys[GLFW_KEY_MENU] = Input::Key::MENU;
        
        return true;
    }

    bool GLFW::UpdateWindow()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        return true;
    }

    void GLFW::UpdateWindowTitle(const char* title)
    {
        glfwSetWindowTitle(window, title);
    }

    bool GLFW::StartEventLoop()
    {
        return true;
    }

    bool GLFW::HandleEvent()
    {
        return true;
    }
}
