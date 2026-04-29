// At the moment, only 32-bit float texture format tests are implemented,
// since they are the only formats that can be tested without precision loss with the current implementation of OGL::Image classes.
#include "Utils.hpp"

#include <OGL/Context.h>

#include <OGL/Texture1D.h>
#include <OGL/Texture1DArray.h>
#include <OGL/Texture2D.h>
#include <OGL/Texture2DArray.h>
#include <OGL/Texture3D.h>
#include <OGL/TextureCubeMap.h>
#include <OGL/TextureCubeMapArray.h>

#include <glm/glm.hpp>
#include <gtest/gtest.h>

TEST(TextureTest, Texture1D_Create)
{
    Context cnt;

    OGL::Texture1D texture(
        glm::uvec1(10),
        OGL::ImageFormat::R32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<1, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_1D);
    EXPECT_EQ(texture.size(), glm::uvec1(10));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::R32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE);
}

TEST(TextureTest, Texture1DArray_Create)
{
    Context cnt;

    OGL::Texture1DArray texture(
        glm::uvec2(10, 20),
        OGL::ImageFormat::RG32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<2, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_1D_ARRAY);
    EXPECT_EQ(texture.size(), glm::uvec2(10, 20));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::RG32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::REPEAT);
}

TEST(TextureTest, Texture2D_Create)
{
    Context cnt;

    OGL::Texture2D texture(
        glm::uvec2(10, 20),
        OGL::ImageFormat::DEPTH32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<2, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_2D);
    EXPECT_EQ(texture.size(), glm::uvec2(10, 20));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::DEPTH32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE);
}

TEST(TextureTest, Texture2DArray_Create)
{
    Context cnt;

    OGL::Texture2DArray texture(
        glm::uvec3(10, 20, 30),
        OGL::ImageFormat::RGB32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_2D_ARRAY);
    EXPECT_EQ(texture.size(), glm::uvec3(10, 20, 30));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::RGB32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().z, OGL::Wrap::REPEAT);
}

TEST(TextureTest, Texture3D_Create)
{
    Context cnt;

    OGL::Texture3D texture(
        glm::uvec3(10, 20, 30),
        OGL::ImageFormat::RG32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::MIRRORED_REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_3D);
    EXPECT_EQ(texture.size(), glm::uvec3(10, 20, 30));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::RG32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().z, OGL::Wrap::MIRRORED_REPEAT);
}

TEST(TextureTest, TextureCubeMap_Create)
{
    Context cnt;

    OGL::TextureCubeMap texture(
        glm::uvec2(10, 10),
        OGL::ImageFormat::RGBA32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::MIRRORED_REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_CUBE_MAP);
    EXPECT_EQ(texture.size(), glm::uvec3(10, 10, 6));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::RGBA32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().z, OGL::Wrap::MIRRORED_REPEAT);
}

TEST(TextureTest, TextureCubeMapArray_Create)
{
    Context cnt;

    OGL::TextureCubeMapArray texture(
        glm::uvec3(10, 10, 3),
        OGL::ImageFormat::RGBA32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::MIRRORED_REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(texture.target(), GL_TEXTURE_CUBE_MAP_ARRAY);
    EXPECT_EQ(texture.size(), glm::uvec3(10, 10, 3 * 6));
    EXPECT_EQ(texture.internalFormat(), OGL::ImageFormat::RGBA32F);
    EXPECT_EQ(texture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(texture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(texture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(texture.wrap().z, OGL::Wrap::MIRRORED_REPEAT);
}

TEST(TextureTest, Texture1D_Data)
{
    Context cnt;

    OGL::Image1D srcImg = generateImage(glm::uvec1(10));

    OGL::Texture1D texture(srcImg, OGL::ImageFormat::R32F);
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Image1D dstImg = texture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, 0, 0, 1), dst);
    }
}

TEST(TextureTest, Texture2D_Data)
{
    Context cnt;

    std::vector<float> srcData = generateData(10 * 20);

    OGL::Texture2D texture(glm::uvec2(10, 20), OGL::ImageFormat::DEPTH32F);
    EXPECT_NO_THROW(OGL::Context::checkError());

    texture.update(srcData.data(), glm::uvec2(0, 0), glm::uvec2(10, 20), OGL::PixelFormat::DEPTH, OGL::Type::FLOAT);
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::array<float, 10 * 20> dstData;
    texture.read(dstData.data(), dstData.size() * sizeof(float), glm::uvec2(0, 0), glm::uvec2(10, 20), OGL::PixelFormat::DEPTH, OGL::Type::FLOAT);
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcData.size(); i++)
        EXPECT_EQ(srcData[i], dstData[i]);
}

TEST(TextureTest, Texture3D_Data)
{
    Context cnt;

    OGL::Image3D srcImg = generateImage(glm::uvec3(10, 20, 30));

    OGL::Texture3D texture(srcImg, OGL::ImageFormat::RG32F);
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Image3D dstImg = texture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, src.g, 0, 1), dst);
    }
}

TEST(TextureTest, TextureCubeMap_Data)
{
    Context cnt;

    OGL::Image3D srcImg = generateImage(glm::uvec3(10, 10, 6));

    OGL::TextureCubeMap texture(srcImg, OGL::ImageFormat::RGBA32F);
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Image3D dstImg = texture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, src.g, src.b, src.a), dst);
    }
}

TEST(TextureTest, Texture1D_Copy)
{
    Context cnt;

    OGL::Image1D srcImg = generateImage(glm::uvec1(10));

    OGL::Texture1D srcTexture(
        srcImg,
        OGL::ImageFormat::R32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<1, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Texture1D dstTexture = srcTexture;
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(dstTexture.target(), GL_TEXTURE_1D);
    EXPECT_EQ(dstTexture.size(), glm::uvec1(10));
    EXPECT_EQ(dstTexture.internalFormat(), OGL::ImageFormat::R32F);
    EXPECT_EQ(dstTexture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(dstTexture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(dstTexture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE);

    OGL::Image1D dstImg = dstTexture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, 0, 0, 1), dst);
    }
}

TEST(TextureTest, Texture2D_Copy)
{
    Context cnt;

    std::vector<float> srcData = generateData(10 * 20);

    OGL::Texture2D srcTexture(
        glm::uvec2(10, 20),
        OGL::ImageFormat::DEPTH32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<2, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    srcTexture.update(srcData.data(), glm::uvec2(0, 0), glm::uvec2(10, 20), OGL::PixelFormat::DEPTH, OGL::Type::FLOAT);
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Texture2D dstTexture = srcTexture;
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(dstTexture.target(), GL_TEXTURE_2D);
    EXPECT_EQ(dstTexture.size(), glm::uvec2(10, 20));
    EXPECT_EQ(dstTexture.internalFormat(), OGL::ImageFormat::DEPTH32F);
    EXPECT_EQ(dstTexture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(dstTexture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(dstTexture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(dstTexture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE);

    std::array<float, 10 * 20> dstData;
    dstTexture.read(dstData.data(), dstData.size() * sizeof(float), glm::uvec2(0, 0), glm::uvec2(10, 20), OGL::PixelFormat::DEPTH, OGL::Type::FLOAT);
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcData.size(); i++)
        EXPECT_EQ(srcData[i], dstData[i]);
}

TEST(TextureTest, Texture3D_Copy)
{
    Context cnt;

    OGL::Image3D srcImg = generateImage(glm::uvec3(10, 20, 30));

    OGL::Texture3D srcTexture(
        srcImg,
        OGL::ImageFormat::RG32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::MIRRORED_REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Texture3D dstTexture = srcTexture;
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(dstTexture.target(), GL_TEXTURE_3D);
    EXPECT_EQ(dstTexture.size(), glm::uvec3(10, 20, 30));
    EXPECT_EQ(dstTexture.internalFormat(), OGL::ImageFormat::RG32F);
    EXPECT_EQ(dstTexture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(dstTexture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(dstTexture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(dstTexture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(dstTexture.wrap().z, OGL::Wrap::MIRRORED_REPEAT);

    OGL::Image3D dstImg = dstTexture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, src.g, 0, 1), dst);
    }
}

TEST(TextureTest, TextureCubeMap_Copy)
{
    Context cnt;

    OGL::Image3D srcImg = generateImage(glm::uvec3(10, 10, 6));

    OGL::TextureCubeMap srcTexture(
        srcImg,
        OGL::ImageFormat::RGBA32F,
        glm::vec<2, OGL::Filter>{ OGL::Filter::LINEAR, OGL::Filter::NEAREST },
        glm::vec<3, OGL::Wrap>{ OGL::Wrap::CLAMP_TO_EDGE, OGL::Wrap::MIRROR_CLAMP_TO_EDGE, OGL::Wrap::MIRRORED_REPEAT }
    );
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::TextureCubeMap dstTexture = srcTexture;
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(dstTexture.target(), GL_TEXTURE_CUBE_MAP);
    EXPECT_EQ(dstTexture.size(), glm::uvec3(10, 10, 6));
    EXPECT_EQ(dstTexture.internalFormat(), OGL::ImageFormat::RGBA32F);
    EXPECT_EQ(dstTexture.filter().x, OGL::Filter::LINEAR); EXPECT_EQ(dstTexture.filter().y, OGL::Filter::NEAREST);
    EXPECT_EQ(dstTexture.wrap().x, OGL::Wrap::CLAMP_TO_EDGE); EXPECT_EQ(dstTexture.wrap().y, OGL::Wrap::MIRROR_CLAMP_TO_EDGE); EXPECT_EQ(dstTexture.wrap().z, OGL::Wrap::MIRRORED_REPEAT);

    OGL::Image3D dstImg = dstTexture.read();
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcImg.pixels.size(); i++)
    {
        glm::vec4 src = srcImg.pixels[i], dst = dstImg.pixels[i];
        EXPECT_EQ(glm::vec4(src.r, src.g, src.b, src.a), dst);
    }
}
