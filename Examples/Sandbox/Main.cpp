#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Application/GameApp.h"

#define SPP_TEST 0

#if SPP_TEST

template<typename T>
concept CArithmetic = std::integral<T> || std::floating_point<T>;

template<typename T>
struct TVec3
{
	TVec3() = default;
	TVec3(T x, T y, T z)
		:x(x), y(y), z(z) {}

	template<typename Other>
	TVec3(const TVec3<Other>& other)
	{
		this->x = (T)other.x;
		this->y = (T)other.y;
		this->z = (T)other.z;
	}

	T x = 0, y = 0, z = 0;

	//

	template<CArithmetic Other>
	TVec3 operator+(const TVec3<Other>& other)
	{
		return TVec3
		{
			this->x + (T)other.x,
			this->y + (T)other.y,
			this->z + (T)other.z
		};
	}

	template<CArithmetic Other>
	TVec3 operator+(const Other& other)
	{
		return TVec3
		{
			this->x + (T)other,
			this->y + (T)other,
			this->z + (T)other
		};
	}

	//

	template<CArithmetic Other>
	TVec3& operator+=(const TVec3<Other>& other)
	{
		this->x += (T)other.x;
		this->y += (T)other.y;
		this->z += (T)other.z;
		return *this;
	}

	template<CArithmetic Other>
	TVec3& operator+=(const Other& other)
	{
		this->x += (T)other;
		this->y += (T)other;
		this->z += (T)other;
		return *this;
	}

	//

	template<CArithmetic Other>
	TVec3 operator-(const TVec3<Other>& other)
	{
		return TVec3
		{
			this->x - (T)other.x,
			this->y - (T)other.y,
			this->z - (T)other.z
		};
	}

	template<CArithmetic Other>
	TVec3 operator-(const Other& other)
	{
		return TVec3
		{
			this->x - (T)other,
			this->y - (T)other,
			this->z - (T)other
		};
	}

	//

	template<CArithmetic Other>
	TVec3& operator-=(const TVec3<Other>& other)
	{
		this->x -= (T)other.x;
		this->y -= (T)other.y;
		this->z -= (T)other.z;
		return *this;
	}

	template<CArithmetic Other>
	TVec3& operator-=(const Other& other)
	{
		this->x -= (T)other;
		this->y -= (T)other;
		this->z -= (T)other;
		return *this;
	}

	//
	
	template<CArithmetic Other>
	TVec3 operator*(const TVec3<Other>& other)
	{
		return TVec3
		{
			this->x * (T)other.x,
			this->y * (T)other.y,
			this->z * (T)other.z
		};
	}

	template<CArithmetic Other>
	TVec3 operator*(const Other& other)
	{
		return TVec3
		{
			this->x * (T)other,
			this->y * (T)other,
			this->z * (T)other
		};
	}

	//

	template<CArithmetic Other>
	TVec3& operator*=(const TVec3<Other>& other)
	{
		this->x *= (T)other.x;
		this->y *= (T)other.y;
		this->z *= (T)other.z;
		return *this;
	}

	template<CArithmetic Other>
	TVec3& operator*=(const Other& other)
	{
		this->x *= (T)other;
		this->y *= (T)other;
		this->z *= (T)other;
		return *this;
	}
	
	//
	
	template<CArithmetic Other>
	TVec3 operator/(const TVec3<Other>& other)
	{
		return TVec3
		{
			this->x / (T)other.x,
			this->y / (T)other.y,
			this->z / (T)other.z,
		};
	}

	template<CArithmetic Other>
	TVec3 operator/(const Other& other)
	{
		return TVec3
		{
			this->x / (T)other,
			this->y / (T)other,
			this->z / (T)other
		};
	}

	//

	template<CArithmetic Other>
	TVec3& operator/=(const TVec3<Other>& other)
	{
		this->x /= (T)other.x;
		this->y /= (T)other.y;
		this->z /= (T)other.z;
		return *this;
	}

	template<CArithmetic Other>
	TVec3& operator/=(const Other& other)
	{
		this->x /= (T)other;
		this->y /= (T)other;
		this->z /= (T)other;
		return *this;
	}

	template<typename Other>
	TVec3<T> operator<<(TVec3<Other> val)
	{
		return TVec3{
			(T)((i32)this->x << (i32)val.x),
			(T)((i32)this->y << (i32)val.y),
			(T)((i32)this->z << (i32)val.z)
		};
	}

	TVec3 operator<<(i32 val)
	{
		return TVec3{
			(T)((i32)this->x << val),
			(T)((i32)this->y << val),
			(T)((i32)this->z << val)
		};
	}

	template<typename Other>
	TVec3<T> operator>>(TVec3<Other> val)
	{
		return TVec3{
			(T)((i32)this->x >> (i32)val.x),
			(T)((i32)this->y >> (i32)val.y),
			(T)((i32)this->z >> (i32)val.z)
		};
	}

	TVec3 operator>>(i32 val)
	{
		return TVec3{
			(T)((i32)this->x >> val),
			(T)((i32)this->y >> val),
			(T)((i32)this->z >> val)
		};
	}
	
	template<typename Other>
	TVec3 operator&(TVec3<Other> val)
	{
		return TVec3{
			this->x & val.x,
			this->y & val.y,
			this->z & val.z
		};
	}

	//

	T product()
	{
		return this->x * this->y * this->z;
	}

	TVec3 pow2()
	{
		return TVec3<T>
		{
			(T)ceil(log(this->x) / log(2)),
			(T)ceil(log(this->y) / log(2)),
			(T)ceil(log(this->z) / log(2))
		};
	}

	TVec3 sign()
	{
		return TVec3<T>
		{
			(T)((i32)(T(0.f) < this->x) - (i32)(this->x < T(0.f))),
			(T)((i32)(T(0.f) < this->y) - (i32)(this->y < T(0.f))),
			(T)((i32)(T(0.f) < this->z) - (i32)(this->z < T(0.f)))
		};
	}

	TVec3 abs()
	{
		return TVec3<T>
		{
			std::abs(this->x),
			std::abs(this->y),
			std::abs(this->z)
		};
	}

	TVec3 floor()
	{
		return TVec3<T>
		{
			std::floor(this->x),
			std::floor(this->y),
			std::floor(this->z)
		};
	}

	template<CArithmetic Other>
	TVec3<Other> cast()
	{
		return TVec3<Other>
		{
			(Other)this->x,
			(Other)this->y,
			(Other)this->z
		};
	}

	TVec3<T> xyz() { return TVec3<T>{ x, y, z }; }
	TVec3<T> yzx() { return TVec3<T>{ y, z, x }; }
	TVec3<T> zxy() { return TVec3<T>{ z, x, y }; }
};

template<CArithmetic T>
TVec3<T> minimum(TVec3<T> a, TVec3<T> b)
{
	return TVec3<T>{
		min(a.x, b.x),
		min(a.y, b.y),
		min(a.z, b.z),
	};
}

template<CArithmetic T>
TVec3<T> step(TVec3<T> edge, TVec3<T> value)
{
	return TVec3<T>{
		value.x < edge.x ? (T)0 : (T)1,
		value.y < edge.y ? (T)0 : (T)1,
		value.z < edge.z ? (T)0 : (T)1,
	};
}

template<CArithmetic T>
TVec3<bool> equal(TVec3<T> a, TVec3<T> b)
{
	return TVec3<bool>{ a.x == b.x, a.y == b.y, a.z == b.z  };
}

template<CArithmetic T>
TVec3<bool> lessThan(TVec3<T> a, TVec3<T> b)
{
	return TVec3<bool>{ a.x < b.x, a.y < b.y, a.z < b.z  };
}

template<CArithmetic T>
TVec3<bool> lessThanEqual(TVec3<T> a, TVec3<T> b)
{
	return TVec3<bool>{ a.x <= b.x, a.y <= b.y, a.z <= b.z  };
}

template<CArithmetic T>
TVec3<bool> greaterThan(TVec3<T> a, TVec3<T> b)
{
	return TVec3<bool>{ a.x > b.x, a.y > b.y, a.z > b.z  };
}

template<CArithmetic T>
TVec3<bool> greaterThanEqual(TVec3<T> a, TVec3<T> b)
{
	return TVec3<bool>{ a.x >= b.x, a.y >= b.y, a.z >= b.z  };
}

static bool Any(TVec3<bool> val)
{
	return val.x || val.y || val.z;
}

static constexpr u32 MAX_VOXEL_LEVEL = 15;
static constexpr u32 MAX_RAY_WALK = 128;

using vec3 = TVec3<f32>;
using ivec3 = TVec3<i32>;

struct VoxelBuffer
{
	std::vector<u8> data;
};

struct VoxelData
{
	VoxelBuffer level[MAX_VOXEL_LEVEL];
};

struct VoxelInfo
{
	u32 activelevels;
	u32 pageSize;
	ivec3 dimensions;

	std::array<ivec3, MAX_VOXEL_LEVEL> levelDimension;

	std::array<vec3, MAX_VOXEL_LEVEL> voxelSizes;
	std::array<vec3, MAX_VOXEL_LEVEL> HalfVoxel;

	std::array<ivec3, MAX_VOXEL_LEVEL> spatialSubsetCount;
	std::array<ivec3, MAX_VOXEL_LEVEL> spatialSubsetMask;
	std::array<ivec3, MAX_VOXEL_LEVEL> spatialSubsetVoxelDimensions;
	std::array<ivec3, MAX_VOXEL_LEVEL> spatialSubsetVoxelDimensionsP2;
	
	VoxelInfo Initalize()
	{
		VoxelInfo voxelInfo = *this;

		u64 PageSize = 512 * 1024;

		for (u32 Iter = 0; Iter < MAX_VOXEL_LEVEL; Iter++)
		{
			auto dim = (voxelInfo.dimensions >> Iter).cast<u64>();

			u64 maxSize = dim.x * dim.y * dim.z;

			if (maxSize <= PageSize)
			{
				voxelInfo.spatialSubsetVoxelDimensions[Iter] = dim.cast<i32>();
				voxelInfo.spatialSubsetMask[Iter] = voxelInfo.spatialSubsetVoxelDimensions[Iter] - ivec3(1, 1, 1);
				voxelInfo.spatialSubsetCount[Iter] = ivec3(1,1,1);
			}
			else
			{
				ivec3 spatialdim = ivec3(1, 1, 1);

				while (spatialdim.product() < PageSize)
				{
					i32 lowestValue = 10000;
					i32 lowestIdx = -1;

					auto func = [&lowestValue, &lowestIdx](i32 comp, u64 dim, i32 iter)
						{
							if (comp < lowestValue && comp < dim)
							{
								lowestValue = comp;
								lowestIdx = iter;
							}
						};

					func(spatialdim.x, dim.x, 0);
					func(spatialdim.y, dim.y, 1);
					func(spatialdim.z, dim.z, 2);

					if (lowestIdx == 0)
						spatialdim.x <<= 1;
					else if (lowestIdx == 1)
						spatialdim.y <<= 1;
					else if (lowestIdx == 2)
						spatialdim.z <<= 1;
				}

				__ARC_ASSERT(spatialdim.product() == PageSize, "Invalid spatial dimension");

				voxelInfo.spatialSubsetVoxelDimensions[Iter] = spatialdim;
				voxelInfo.spatialSubsetMask[Iter] = voxelInfo.spatialSubsetVoxelDimensions[Iter] - ivec3(1, 1, 1);
				voxelInfo.spatialSubsetCount[Iter] = dim / voxelInfo.spatialSubsetVoxelDimensions[Iter];
			}

			voxelInfo.levelDimension[Iter] = dim;
			voxelInfo.spatialSubsetVoxelDimensionsP2[Iter] = voxelInfo.spatialSubsetVoxelDimensions[Iter].pow2();

			voxelInfo.voxelSizes[Iter] = (vec3(1, 1, 1) << Iter);
			voxelInfo.HalfVoxel[Iter]  = (vec3(1, 1, 1) << Iter) / 2.f;
		}

		voxelInfo.pageSize = PageSize;

		return voxelInfo;
	}
};

struct RayInfo
{
	vec3 rayOrg;
	vec3 rayDir;
	vec3 rayDirSign;
	vec3 rayDirInvAbs;
	vec3 rayDirInv;
	vec3 lastStep;

	i32 curMisses = 0;
};

struct StepInfo
{
	vec3 step;
	vec3 tdelta;
};

static bool ValidSample(vec3 InPosition, ivec3 dimension)
{
	if (Any(lessThan(InPosition, vec3(0.f, 0.f, 0.f))) || Any(greaterThanEqual(ivec3(InPosition), dimension)))
	{
		return false;
	}

	return true;
}

static u64 GetOffset(ivec3 InPosition, u32 InLevel, VoxelInfo* pInfo)
{
	ivec3 LocalVoxel = InPosition & pInfo->spatialSubsetMask[InLevel];

	u32 LocalVoxelId =
		LocalVoxel.x +
		LocalVoxel.y * pInfo->spatialSubsetVoxelDimensions[InLevel].x +
		LocalVoxel.z * pInfo->spatialSubsetVoxelDimensions[InLevel].x * pInfo->spatialSubsetVoxelDimensions[InLevel].y;

	ivec3 PageCubePos = InPosition >> pInfo->spatialSubsetVoxelDimensionsP2[InLevel];
	u32 pageIdx =
		PageCubePos.x +
		PageCubePos.y * pInfo->spatialSubsetCount[InLevel].x +
		PageCubePos.z * pInfo->spatialSubsetCount[InLevel].x * pInfo->spatialSubsetCount[InLevel].y;

	u32 pageOffset = pInfo->pageSize * pageIdx;

	return LocalVoxelId + pageOffset;
}

static i32 GetUnscaledAtLevel(ivec3 InPosition, u32 InLevel, VoxelInfo* pInfo, VoxelData* pData)
{
	ivec3 levelPos = InPosition >> InLevel;

	u32 MemOffset = GetOffset(InPosition, InLevel, pInfo);
	u8 voxel = pData->level[InLevel].data[MemOffset];
	
	return i32(voxel);
}

static VoxelData GenerateVoxelLevel(VoxelInfo& info)
{
	VoxelData voxelData;

	for (u32 Iter = 0; Iter < MAX_VOXEL_LEVEL; Iter++)
	{
		ivec3 dim = info.levelDimension[Iter];
		i32 size = dim.x * dim.y * dim.z;

		voxelData.level[Iter].data.resize(size);

		i8 val = Iter == 0 ? 1 : 255;
		memset(voxelData.level[Iter].data.data(), val, size * sizeof(u8));
	}

	ivec3 pos = { 0 ,63, 360 };

	u64 offset = GetOffset(pos >> 0, 0, &info);
	voxelData.level[0].data[offset] = 55;

	return voxelData;
}


VoxelInfo voxelInfoData = {
	.activelevels = 6,
	.dimensions = ivec3(32, 64, 512)
};


struct Input
{
	vec3 org;
	vec3 dir;
	f32 timeToHit;
};

// samplePos	0		32	224
// voxel		0		32	224
// rayOrg		3.529	64	247.663
// voxelSize	32		32	32
// org / size	0.110	2	7.739
// floor		0		1	7
// rayOrg		20.467	78.397	207.270
// timeToHit	46.105
// rayDir		-0.367	-0.312	0.876
// epsilon		0.001


// samplePos	0		64		224
// voxel		0		64		224	
// rayOrg		3.575	64.046	247.709
// voxelSize	32		32		32
// org / size	0.112	2.001	7.741
// floor		0		2		7
// rayOrg		20.467	78.397	270.270
// timeToHit	46.105
// rayDir		-0.366	-0.311	0.877
// epsilon		0.001

Input Input_325_5 = {
	.org = vec3(20.467f, 78.397f, 207.270f),
	.dir = vec3(-0.367f, -0.312f, 0.876f),
	.timeToHit = 46.105f
};

// Iter			5
// CurrentLevel 0

// rayOrg		20.767	78.685	207.270
// rayDir		-0.179	-0.127	0.976	
// timeToHit	115.815

// DirZeroEpsilon			 0		 0		0
// rayDir					-0.179	-0.127	0.976
// rayInfo.rayDir			-0.179	-0.127	0.976
// rayInfo.rayDirSign		-1		-1		1
// rayInfo.rayDirInv		-5.584	-7.887	1.025
// rayInfo.rayDirInvAbs		 5.584	 7.887	1.025

// samplePos	-1		63		320
// posCopy		0		63		320
// lastStep		-1		0		0
// tDelta		5.584	7.887	1.025
// step			-1		-1		1
// dim			1		0		0
// tMax			5.734	7.886	0.755
// tmaxcopy		0.15	7.886	0.755
// tMaxMins		0.755	0.15	0.15

//					step			tDelta
// stepInfo	0	-1  -1  +1		5.584	7.887	1.025
// stepInfo	1	-2  -2  +2		11.168	15.773	2.050
// stepInfo	2	-4  -4  +4		22.337	31.547	4.1	
// stepInfo	3	-8  -8  +8		44.673	63.093	8.2
// stepInfo	4	-16 -16 +16		89.346	126.186	16.4
// stepInfo	5	-32 -32 +32		178.693	252.373	32.799
// stepInfo	6	-64 -64 +64		357.386	504.745	65.599

//				   sample		  level			localVoxel		voxelIdx	pageCubePos	 pageIdx	memOffset	pageOffset	mem+page
// Iter 0		0	32	320			5			0	1	10		    21		 0	 0	 0		0			 21			0			21	
// Iter 1		0	48	320			4			0	3	20		   166		 0	 0	 0		0			166			0		   166
// Iter 2		0	56	320			3			0	7	40		  1308		 0	 0	 0		0		   1308			0		  1308
// Iter 3		0	60	320			2			0	15	80		 10360		 0	 0	 0		0		  10360			0		 10360
// Iter 4		0	62	320			1			0	31	160		 82416		 0	 0	 0		0		  82416			0		 82416
// Iter 5		0	63	320			0			0	63	64		133088		 0	 0	 1		1		 133088		  524288	657376

Input Input_677_330 = {
	.org = vec3(20.767f, 78.685f, 207.270f),
	.dir = vec3(-0.179f, -0.127f, 0.976f),
	.timeToHit = 115.815f
};

bool RayCast()
{
	Input InputData = Input_677_330;

	VoxelInfo voxelInfo = voxelInfoData.Initalize();
	VoxelData voxelData = GenerateVoxelLevel(voxelInfo);

	//

	vec3 InRayOrg = InputData.org;
	vec3 InRayDir = InputData.dir;

	f32 InTimeToHit = InputData.timeToHit;

	//

	RayInfo rayInfo;
	rayInfo.rayOrg = InRayOrg;

	f32 epsilon = 0.001f;
	vec3 DirZeroEpsilon = vec3(equal(InRayDir, vec3(0, 0, 0))) * epsilon;

	rayInfo.rayDir = InRayDir + DirZeroEpsilon;
	rayInfo.rayDirSign = rayInfo.rayDir.sign();
	rayInfo.rayDirInv = vec3{ 1.f / InRayDir.x, 1.f / InRayDir.y, 1.f / InRayDir.z };
	rayInfo.rayDirInvAbs = rayInfo.rayDirInv.abs();

	f32 timeToHit = InTimeToHit;

	rayInfo.rayOrg = rayInfo.rayOrg + (rayInfo.rayDir * (timeToHit + epsilon));

	u32 CurrentLevel = voxelInfo.activelevels - 1;
	u32 LastLevel = 0;

	std::array<StepInfo, MAX_VOXEL_LEVEL> stepInfo = {};

	for (u32 Iter = 0; Iter < MAX_VOXEL_LEVEL; Iter++)
	{
		stepInfo[Iter].step = voxelInfo.voxelSizes[Iter] * rayInfo.rayDirSign;
		stepInfo[Iter].tdelta = voxelInfo.voxelSizes[Iter] * rayInfo.rayDirInvAbs;
	}

	vec3 voxel = (rayInfo.rayOrg / voxelInfo.voxelSizes[CurrentLevel]).floor() * voxelInfo.voxelSizes[CurrentLevel];
	vec3 tMax = (voxel - rayInfo.rayOrg + voxelInfo.HalfVoxel[CurrentLevel] + stepInfo[CurrentLevel].step * vec3(0.5, 0.5, 0.5)) * rayInfo.rayDirInv;

	vec3 dim = vec3(0, 0, 0);
	vec3 samplePos = voxel;

	vec3 samplePosWorld = rayInfo.rayOrg;
	f32 rayTime = 0.f;

	rayInfo.lastStep = rayInfo.rayDir;

	for (i32 Iter = 0; Iter < MAX_RAY_WALK; Iter++)
	{
		LastLevel = CurrentLevel;

		if (!ValidSample(samplePos, voxelInfo.dimensions))
		{
			ARC_LOG("TEST", "[1] InvalidSample: {} {} {}", samplePos.x, samplePos.y, samplePos.z);
			return false;
		}

		bool bDidStep = true;
		bool bLevelChangeRecalc = false;

		i32 voxelHit = GetUnscaledAtLevel(samplePos, CurrentLevel, &voxelInfo, &voxelData);

		if (voxelHit != 0)
		{
			rayInfo.curMisses = 0;

			if (CurrentLevel == 0)
			{
				ARC_LOG("TEST", "VoxelHit: {}", voxelHit);
				return true;
			}

			CurrentLevel--;
			bLevelChangeRecalc = true;
		}
		else
		{
			bDidStep = true;

			vec3 tMaxMins = minimum(tMax.yzx(), tMax.zxy());
			dim = step(tMax, tMaxMins);
			tMax += (dim * stepInfo[CurrentLevel].tdelta);
			rayInfo.lastStep = (dim * stepInfo[CurrentLevel].step);

			samplePos += rayInfo.lastStep;

			if (!ValidSample(samplePos, voxelInfo.dimensions))
			{
				ARC_LOG("TEST", "[2] InvalidSample: {} {} {}", samplePos.x, samplePos.y, samplePos.z);
				return false;
			}

			rayInfo.curMisses++;

			if (CurrentLevel < voxelInfo.activelevels - 1 && 
				rayInfo.curMisses > 2 &&
				GetUnscaledAtLevel(samplePos, CurrentLevel + 1, &voxelInfo, &voxelData) == 0)	
			{
				bLevelChangeRecalc = true;
				CurrentLevel++;
			}
		}

		if (bDidStep)
		{

		}

		if (bLevelChangeRecalc)
		{
			voxel = (samplePosWorld / voxelInfo.voxelSizes[CurrentLevel]).floor() * voxelInfo.voxelSizes[CurrentLevel];
			tMax = (voxel - samplePosWorld + voxelInfo.HalfVoxel[CurrentLevel] + stepInfo[CurrentLevel].step * vec3(0.5f, 0.5f, 0.5f)) * (rayInfo.rayDirInv);
				
			dim = vec3(0.f, 0.f, 0.f);
			samplePos = voxel;
		}
	}
	
	return false;
}

#endif

#include "Scene/Scene.h"

struct TestComponent
{
	u32 a;
	u32 v;
};

void Test()
{
	using namespace arc;

	EntityWorld world;

	auto entity = world.CreateEntity();
	auto comp = entity.AddComponent<TestComponent>({ 1, 2 });

	auto 

	__debugbreak();
}

namespace arc
{
	class SandboxApplication : public GameApplication
	{
	public:
		SandboxApplication() = default;
		~SandboxApplication() override = default;
	protected:
		void Create() override
		{
			mGameEngine->CreateAppWindow(AppWindowInfo{
					.width = 800,
					.height = 600,
					.title = "Sandbox"
				});

			GameApplication::Create();

#if SPP_TEST
			bool bResult = RayCast();
			ARC_LOG("TEST", "RaycastResult {}", bResult ? "True" : "False");
#endif

			Test();
		}

		void Destroy() override
		{
			GameApplication::Destroy();
		}

		void Tick(f32 deltaTime) override
		{
			GameApplication::Tick(deltaTime);
		}
	};
}


i32 APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdline, _In_ i32 nCmdShow)
{
	auto sandbox = std::make_unique<arc::SandboxApplication>();
	sandbox->Run();
}