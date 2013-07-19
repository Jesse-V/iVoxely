
#ifndef CHUNK
#define CHUNK

#include "Cube.hpp"
#include <unordered_map>

class Chunk
{
    //this class can be used to organize voxels. If a chunk is too far away,
    //all of its cubes don't need to be rendered (set their isVisible to false)

    //http://stackoverflow.com/questions/7222143/unordered-map-hash-function-c
    /*template <class T>
    inline void hash_combine(std::size_t & seed, const T & v)
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    namespace std
    {
        template<typename S, typename T> struct hash<pair<S, T>>
        {
            inline size_t operator()(const pair<S, T> & v) const
            {
                size_t seed = 0;
                ::hash_combine(seed, v.first);
                ::hash_combine(seed, v.second);
                return seed;
            }
        };
    }*/

    //category: hasNeighbor, isChunkEdge, isBottom

    static std::shared_ptr<Cube> getCubeAt(int x, int y, int z);

    private:
        struct GridLocation
        {
            int x, y, z;
        };

    private:
        //std::unordered_map<GridLocation, std::shared_ptr<Cube>> cubes_;
};

#endif
