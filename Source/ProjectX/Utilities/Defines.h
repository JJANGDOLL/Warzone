#pragma once

#define CheckNull(p) { if(p == nullptr) return; }
#define CheckNullResult(p, result)  { if(p == nullptr) return result; }

#define NO_OVERLAPEVENTS(p) p->SetGenerateOverlapEvents(false)
#define NO_STEPUPON(p) p->CanCharacterStepUpOn = ECB_No
#define NO_COLLISION(p) p->SetCollisionEnabled(ECollisionEnabled::NoCollision)