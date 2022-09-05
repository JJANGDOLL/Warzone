#pragma once

#include "DrawDebugHelpers.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Utilities/Logger.h"
#include "Utilities/Helper.h"

#define CheckNull(p) { if (p == nullptr) return;}

#define NO_OVERLAPEVENTS(p) p->SetGenerateOverlapEvents(false)
#define NO_STEPUPON(p) p->CanCharacterStepUpOn = ECB_No
#define NO_COLLISION(p) p->SetCollisionEnabled(ECollisionEnabled::NoCollision)

//ProjectileMesh->SetGenerateOverlapEvents(false);
//ProjectileMesh->CanCharacterStepUpOn = ECB_No;
//ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);