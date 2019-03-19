#pragma once

#include <vector>
#include <memory>

#include <daedalus/DaedalusGameState.h>

#include "game/perceptionmsg.h"

#include "interactive.h"
#include "movetrigger.h"
#include "trigger.h"

class Npc;
class Item;
class World;

class WorldObjects final {
  public:
    WorldObjects(World &owner);
    ~WorldObjects();

    void           tick(uint64_t dt);

    void           onInserNpc (Daedalus::GameState::NpcHandle handle, const std::string &point);
    void           onRemoveNpc(Daedalus::GameState::NpcHandle handle);

    void           updateAnimation();

    size_t         npcCount()    const { return npcArr.size(); }
    const Npc&     npc(size_t i) const { return *npcArr[i];    }
    Npc&           npc(size_t i)       { return *npcArr[i];    }

    void           addTrigger(ZenLoad::zCVobData&& vob);
    Trigger*       findTrigger(const char* name);

    Item*          addItem(size_t itemInstance, const char *at);
    Item*          addItem(const ZenLoad::zCVobData &vob);
    Item*          takeItem(Item& it);
    void           removeItem(Item& it);
    size_t         hasItems(const std::string& tag,size_t itemCls);
    void           addInteractive(const ZenLoad::zCVobData &vob);

    Interactive*   findInteractive(const Npc& pl, const Tempest::Matrix4x4 &v, int w, int h, float rangeMin, float rangeMax, float azi);
    Npc*           findNpc        (const Npc& pl, const Tempest::Matrix4x4 &v, int w, int h, float rangeMin, float rangeMax, float azi);
    Item*          findItem       (const Npc& pl, const Tempest::Matrix4x4 &v, int w, int h, float rangeMin, float rangeMax, float azi);

    void           marchInteractives(Tempest::Painter &p, const Tempest::Matrix4x4 &mvp, int w, int h) const;

    Interactive*   aviableMob(const Npc& pl,const std::string& name);
    bool           aiUseMob  (Npc &pl, const std::string& name);

    void           sendPassivePerc(Npc& self,Npc& other,Npc& victum,int32_t perc);

  private:
    World&                             owner;
    std::vector<Interactive>           interactiveObj;
    std::vector<std::unique_ptr<Npc>>  npcArr;
    std::vector<std::unique_ptr<Item>> itemArr;

    std::vector<Trigger>               triggers;
    std::vector<MoveTrigger>           triggersMv;

    std::vector<PerceptionMsg>         sndPerc;

    template<class T>
    T* findObj(std::vector<T>& src,const Npc &pl,
               float minDist, float maxDist, float maxAngle,
               const Tempest::Matrix4x4 &v, int w, int h);
  };
