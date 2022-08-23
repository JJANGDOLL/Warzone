#pragma once

#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Utilities/Logger.h"
#include "Utilities/Helper.h"

#define CheckNull(p) { if (p == nullptr) return;}