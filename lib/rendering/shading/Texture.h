// Copyright 2023-2024 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <moonray/rendering/bvh/shading/Intersection.h>
#include <moonray/rendering/bvh/shading/State.h>

#ifdef __ARM_NEON__
// This works around OIIO including x86 based headers due to detection of SSE
// support due to sse2neon.h being included elsewhere
#define __IMMINTRIN_H
#define __NMMINTRIN_H
#define OIIO_NO_SSE 1
#define OIIO_NO_AVX 1
#define OIIO_NO_AVX2 1
#endif
#include <OpenImageIO/texture.h>

// -------------------------------------------------
// Types and functions used by both BasicTexture and
// UdimTexture classes.
// -------------------------------------------------

namespace moonray {

namespace texture {
class TextureSampler;
typedef OIIO::TextureSystem::TextureHandle TextureHandle;
}

namespace shading {

enum TextureQuality {
    TrilinearAnisotropic = 0,
    TrilinearIsotropic,
    LinearMipClosestTexel,
    ClosestMipClosestTexel,
    QualityCount
};

// Chooses from one of the foloowing texture option indices based
// on the path type at the current intersection.
// * ClosestMipClosestTexel
// * LinearMipClosestTexel
// * TrilinearAnisotropic
// * TrilinearIsotropic
int getTextureOptionIndex(bool isDisplacement, const shading::State &state);
int getTextureOptionIndex(bool isDisplacement, shading::Intersection::PathType pathType);

// checks if data and display windows have valid
// (non-negative) pixel coordinates
bool checkTextureWindow(texture::TextureSampler* textureSampler,
                        texture::TextureHandle* handle,
                        const std::string &filename,
                        std::string &errorMsg);

} // namespace shading
} // namespace moonray

