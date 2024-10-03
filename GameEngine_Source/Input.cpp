#include "Input.h"
#include "Application.h"

extern GE::Application app;

namespace GE
{
    std::vector<Input::Key> Input::mKeys = {};
    Vector2 Input::mMousePosition = Vector2(0.f,0.f);

    int ASCII[(UINT)eKeyCode::End] =
    {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',
        VK_LEFT,VK_RIGHT,VK_DOWN,VK_UP,
        VK_LBUTTON,VK_MBUTTON,VK_RBUTTON
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
        if (GetFocus())
        {
            if (isKeyDown(key.keyCode))
            {
                updateKeyDown(key);
            }
            else
            {
                updateKeyUp(key);
            }
            updateMousePos();
        }
        else
        {
            //키 초기화 필요
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
    void Input::updateMousePos()
    {
        POINT mousePos = {};
        GetCursorPos(&mousePos);
        ScreenToClient(app.GetHwnd(), &mousePos);

        UINT width = app.GetWidth();
        UINT height = app.GetHeight();


        mMousePosition = Vector2(-1.f, -1.f);

        if (mousePos.x < width && mousePos.x > 0)
        {
            mMousePosition.x = mousePos.x;
        }
        if (mousePos.y < height && mousePos.y > 0)
        {
            mMousePosition.y = mousePos.y;
        }
    }
}