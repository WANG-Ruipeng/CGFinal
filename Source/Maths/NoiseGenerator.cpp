#include "NoiseGenerator.h"

#include "../World/WorldConstants.h"

#include <cmath>

NoiseGenerator::NoiseGenerator(int seed)
    : m_seed(seed)
{
    m_noiseParameters.octaves = 7;
    m_noiseParameters.amplitude = 70;
    m_noiseParameters.smoothness = 235;
    m_noiseParameters.heightOffset = -5;
    m_noiseParameters.roughness = 0.53;
}

void NoiseGenerator::setParameters(const NoiseParameters &params) noexcept
{
    m_noiseParameters = params;
}
//都是随便乱填的数字，重要的还是seed
double NoiseGenerator::getNoise(int n) const noexcept
{
    n += m_seed;
    n = (n << 13) ^ n;
    auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

    return 1.0 - ((double)newN / 1073741824.0);
}
//进行一个方法的重载
double NoiseGenerator::getNoise(double x, double z) const noexcept
{
    return getNoise(x + z * 57.0);
}
//这里用的插值函数是cos函数，因为这样出来的地形（我感觉）最好看
double NoiseGenerator::lerp(double a, double b, double z) const noexcept
{
    double mu2 = (1 - std::cos(z * 3.14)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::noise(double x, double z) const noexcept
{
    double floorX = (double)((int)x); // 对浮点数向下取整
    double floorZ = (double)((int)z);

    double s = 0.0, t = 0.0, u = 0.0,
         v = 0.0;

    s = getNoise(floorX, floorZ);// 周围变量的r值
    t = getNoise(floorX + 1, floorZ);
    u = getNoise(floorX,floorZ + 1);
    v = getNoise(floorX + 1, floorZ + 1);

    double rec1 = lerp(s, t, x - floorX); //进行插值
    double rec2 = lerp(u, v,x - floorX);
    double rec3 = lerp(rec1, rec2,z - floorZ);
    return rec3;
}

double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ) const
    noexcept
{
    auto newX = (x + (chunkX * CHUNK_SIZE));
    auto newZ = (z + (chunkZ * CHUNK_SIZE));

    if (newX < 0 || newZ < 0){
        return WATER_LEVEL - 1;
    }
    
    double totalValue = 0.0;

    for (int i = 0; i < m_noiseParameters.octaves - 1;i++){
        double frequency = pow(2.0,i); //每次循环增加频率（报告13页的公式）
        double amplitude = pow(m_noiseParameters.roughness,i); // 每次循环减少幅度
        totalValue +=
            noise(((double)newX) * frequency / m_noiseParameters.smoothness,
                  ((double)newZ) * frequency / m_noiseParameters.smoothness) *
            amplitude;
    }

    double val = (((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) +
               m_noiseParameters.heightOffset;

    return val > 0 ? val : 1;
}
