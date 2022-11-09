#pragma once
#include <ydb/core/base/events.h>

#include <library/cpp/actors/core/events.h>

namespace NKikimr::NColumnShard::NTiers {

enum EEvents {
    EvTierCleared = EventSpaceBegin(TKikimrEvents::ES_TIERING),
    EvEnd
};

static_assert(EEvents::EvEnd < EventSpaceEnd(TKikimrEvents::ES_TIERING), "expect EvEnd < EventSpaceEnd(TKikimrEvents::ES_TIERING)");
}