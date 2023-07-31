#pragma once

#if WITH_AUTOMATION_TESTS

namespace TestUtils
{
    UWorld* GetTestGameWorld();

    bool IsMapExist(const FString& Name);

}  // namespace TestUtils

#endif
