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
        for (size_t i = 0; i < (UINT)eKeyCode::End; i++)
        {
            Key key = {};
            key.bPressed = false;
            key.state = eKeyState::NONE;
            key.keyCode = eKeyCode(i); 
            mKeys.push_back(key);
        }
    }

    void GE::Input::Update()
    {
        for (size_t i = 0; i < mKeys.size(); i++)
        {
            if (GetAsyncKeyState(ASCII[i]) & 0x8000) {

                if (mKeys[i].bPressed == true)
                    mKeys[i].state = eKeyState::PRESSED;
                else
                    mKeys[i].state = eKeyState::DOWN;
                mKeys[i].bPressed = true;
            }
            else
            {
                if (mKeys[i].bPressed == true)
                    mKeys[i].state = eKeyState::UP;
                else
                    mKeys[i].state = eKeyState::NONE;
                mKeys[i].bPressed = false;
            }
        }
    }
}