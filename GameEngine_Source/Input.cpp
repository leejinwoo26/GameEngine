#include "Input.h"

namespace GE
{
    std::vector<Input::Key> Input::mKeys = {};

    int ASCII[(UINT)eKeyCode::End] =
    {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',
    };

    GE::Input::Input()
    {
    }

    GE::Input::~Input()
    {
    }

    void GE::Input::Initialize()
    {
        createKeys();
    }

    void GE::Input::Update()
    {
        updateKeys();
    }
    void Input::createKeys()
    {
        for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
        {
            Key key = {};
            key.bPressed = false;
            key.state = eKeyState::NONE;
            key.keyCode = eKeyCode(i);
            mKeys.push_back(key);
        }
    }
    void Input::updateKeys()
    {
        for (size_t i = 0; i < mKeys.size(); i++)
        {
            updateKey(mKeys[i]);
        }
    }
    void Input::updateKey(Input::Key& key)
    {
        if (isKeyDown(key.keyCode))
        {
            updateKeyDown(key);
        }
        else
        {
            updateKeyUp(key);
        }
    }
    bool Input::isKeyDown(eKeyCode code)
    {
        return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
    }
    void Input::updateKeyDown(Input::Key& key)
    {
        if (key.bPressed == true)
            key.state = eKeyState::PRESSED;
        else
            key.state = eKeyState::DOWN;

        key.bPressed = true;
    }
    void Input::updateKeyUp(Input::Key& key)
    {
        if (key.bPressed == true)
            key.state = eKeyState::UP;
        else
            key.state = eKeyState::NONE;

        key.bPressed = false;
    }
}