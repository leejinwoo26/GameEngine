#include "pch.h"
#include "UiBase.h"
namespace GE
{
	UiBase::UiBase(eUIType type)
		: mType(type)
		, mbMouseOn(false)
	{
	}
	UiBase::~UiBase()
	{
	}
	void UiBase::Initialize()
	{
		OnInit();
	}
	void UiBase::Active()
	{
		mbEnabled = true;
		OnActive();
	}
	void UiBase::InActive()
	{
		mbEnabled = false;
		OnInActive();
	}
	void UiBase::Update()
	{
		if (mbEnabled)
		{
			OnUpdate();
		}
	}
	void UiBase::LateUpdate()
	{
		if (mbEnabled)
			OnLateUpdate();
	}
	void UiBase::Render(HDC hdc)
	{
		if (mbEnabled)
			OnRender(hdc);
	}

	void UiBase::UIClear()
	{
		OnClear();
	}
	void UiBase::OnInit()
	{
	}
	void UiBase::OnActive()
	{
	}
	void UiBase::OnInActive()
	{
	}
	void UiBase::OnUpdate()
	{
	}
	void UiBase::OnClear()
	{
	}
	void UiBase::OnLateUpdate()
	{
	}
	void UiBase::OnRender(HDC hdc)
	{
	}
}