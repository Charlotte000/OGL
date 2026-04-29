#include "Utils.hpp"

#include <OGL/Buffer.h>
#include <OGL/Context.h>

#include <gtest/gtest.h>

TEST(BufferTest, Create)
{
    Context cnt;

    OGL::Buffer buff;
    EXPECT_NO_THROW(OGL::Context::checkError());
}

TEST(BufferTest, Data)
{
    Context cnt;

    OGL::Buffer buff;
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> srcData = generateData(100);
    buff.write(srcData.data(), srcData.size() * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> dstData(100);
    buff.read(dstData.data(), 100 * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(srcData, dstData);
}

TEST(BufferTest, Copy)
{
    Context cnt;

    OGL::Buffer srcBuff;
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> srcData = generateData(100);
    srcBuff.write(srcData.data(), srcData.size() * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    OGL::Buffer dstBuff = srcBuff;
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> dstData(100);
    dstBuff.read(dstData.data(), 100 * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(srcData, dstData);
}

TEST(BufferTest, Map)
{
    Context cnt;

    OGL::Buffer buff;
    EXPECT_NO_THROW(OGL::Context::checkError());

    buff.write(nullptr, 100 * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> srcData = generateData(100);

    float* mapPtr = reinterpret_cast<float*>(buff.map(OGL::Access::WRITE_ONLY));
    EXPECT_NO_THROW(OGL::Context::checkError());

    for (size_t i = 0; i < srcData.size(); i++)
        *(mapPtr + i) = srcData[i];

    buff.unmap();
    EXPECT_NO_THROW(OGL::Context::checkError());

    std::vector<float> dstData(100);
    buff.read(dstData.data(), 100 * sizeof(float));
    EXPECT_NO_THROW(OGL::Context::checkError());

    EXPECT_EQ(srcData, dstData);
}