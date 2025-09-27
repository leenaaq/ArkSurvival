// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCharacter, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogItem, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogInventory, Log, All);

#define ARK_VALIDATE(Expression) \
if (!(Expression)) { \
UE_LOG(LogCharacter, Warning, TEXT("Validation Failed: %s in %s"), TEXT(#Expression), ANSI_TO_TCHAR(__FUNCTION__)); \
return; \
}