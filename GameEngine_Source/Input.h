#pragma once
#include "CommonInclude.h"

namespace GE
{
	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE
	};

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		LEFT,RIGHT,DOWN,UP,
		LBUTTON,MBUTTON,RBUTTON,
		End,
	};

	class Input
	{
	public:
		Input();
		~Input();

		struct Key
		{
			eKeyCode keyCode;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();

		static bool GetKeyDown(eKeyCode keyCode) {return mKeys[(UINT)keyCode].state == eKeyState::DOWN;}
		static bool GetKeyUp(eKeyCode keyCode) { return mKeys[(UINT)keyCode].state == eKeyState::UP; }
		static bool GetKey(eKeyCode keyCode) { return mKeys[(UINT)keyCode].state == eKeyState::PRESSED; }
		static Vector2 GetMousePosition() { return mMousePosition; }

	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(Input::Key& key);
		static bool isKeyDown(eKeyCode code);
		static void updateKeyDown(Input::Key& key);
		static void updateKeyUp(Input::Key& key);
		static void updateMousePos();


	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePosition;
	};

}
