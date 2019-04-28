#pragma once

class GameObj
{
public:
    GameObj() = default;

    uint64_t id = 0;
};

//TODO singleton
class GameObjMgr
{
    bool addGameObj(GameObj* obj)
    {
        if (!obj) return false;

        auto it = _gameobjs.find(obj->id);
        if (it == _gameobjs.end()) {
            _gameobjs.insert(std::make_pair(obj->id, obj));
            return true;
        }
        return false;
    }

    void removeGameObj(GameObj* obj)
    {
        if (!obj) return ;

        auto it = _gameobjs.find(obj->id);
        if (it != _gameobjs.end()) {
            _gameobjs.erase(it);
        }
    }

    GameObj* getGameObj(uint64_t objid)
    {
        auto it = _gameobjs.find(objid);
        if (it != _gameobjs.end())
            return it->second;
        return nullptr;
    }

private:
    std::unordered<uint64_t, GameObj*> _gameobjs;
};
