#pragma once
#include "ModioSubsystem.h"
#include "Tests/Commands/ModioTestCommandBase.h"

#if WITH_DEV_AUTOMATION_TESTS
class FModioGetModInfoAsyncCommand : public FModioTestLatentCommandBaseExpectedResult
{
	FModioModID ModID;

public:
	FModioGetModInfoAsyncCommand(FAutomationTestBase* AssociatedTest, const FModioModID ModID,
									 ModioTestExpectedResult ExpectedResult)
		: FModioTestLatentCommandBaseExpectedResult(AssociatedTest, ExpectedResult),
		  ModID(ModID)
	{}

	using FModioTestLatentCommandBase::Update;
	virtual void Start() override
	{
		Modio->GetModInfoAsync(ModID, FOnGetModInfoDelegateFast::CreateSP(this, &FModioGetModInfoAsyncCommand::Callback));
	}
	void Callback(FModioErrorCode ec, TOptional<FModioModInfo> ModInfo)
	{
		CurrentTest->TestEqual("GetModInfo completes without errors", ec, false);
		CurrentTest->TestTrue("When GetModInfo returns without error, ModInfo should have a value",
							  ModInfo.IsSet());
		Done();
	}
};

class FModioGetModInfoBadResponseAsyncCommand : public FModioTestLatentCommandBaseExpectedResult
{
	FModioModID ModID;

public:
	FModioGetModInfoBadResponseAsyncCommand(FAutomationTestBase* AssociatedTest, const FModioModID ModID,
							ModioTestExpectedResult ExpectedResult)
		: FModioTestLatentCommandBaseExpectedResult(AssociatedTest, ExpectedResult),
		  ModID(ModID)
	{}

	using FModioTestLatentCommandBase::Update;
	virtual void Start() override
	{
		Modio->GetModInfoAsync(ModID, FOnGetModInfoDelegateFast::CreateSP(this, &FModioGetModInfoBadResponseAsyncCommand::Callback));
	}
	void Callback(FModioErrorCode ec, TOptional<FModioModInfo> ModInfo)
	{
		CurrentTest->TestEqual("GetModInfo handles invalid responses correctly", CheckExpectedValue(ec, ExpectedResult), true);
		CurrentTest->TestFalse("When GetModInfo returns an invalid response, ModInfo has no value", ModInfo.IsSet());
		Done();
	}
};

#endif