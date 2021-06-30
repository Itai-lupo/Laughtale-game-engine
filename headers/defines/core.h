#pragma once
#include <cstdint>

namespace LTE
{
    typedef uint32_t eventLaughId;
    typedef uint32_t entityTaleId;
    typedef uint32_t vertexBufferId;
    typedef uint32_t indexBufferId;
    typedef uint32_t vertexArrayId;
    typedef uint32_t shaderId;
    typedef uint64_t windowPieceId;
    typedef uint32_t apoEnvelopeId;
    typedef uint32_t materialId;
    typedef uint32_t textureId;
    typedef uint32_t packetId;
    typedef uint32_t connectionId;

    enum renderAPI
    {
        None = 0, OpenGL = 1
    };

    enum sondWaves
    {
        mute = 0,
        sin,
        sowTooth,
        analogSowTooth,
        squre,
        analogSqure,
        triangels,
        noise,
        speaker
    };
}