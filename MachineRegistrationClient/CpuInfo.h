#pragma once

#ifndef _CPU_INFO_H_
#define _CPU_INFO_H_


#include <string>
#include <sstream>

// intrinsics
#if defined(__GNUC__)    // GCC
#include <cpuid.h>
#elif defined(_MSC_VER)    // MSVC
#if _MSC_VER >=1400    // VC2005
#include <intrin.h>
#endif    // #if _MSC_VER >=1400
#else
#error Only supports MSVC or GCC.
#endif    // #if defined(__GNUC__)

namespace thatboy
{
	void getCpuIdEx(unsigned int CPUInfo[4], unsigned int InfoType, unsigned int ECXValue)
	{
#if defined(__GNUC__)    // GCC
		__cpuid_count(InfoType, ECXValue, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)    // MSVC
#if defined(_WIN64) || _MSC_VER>=1600    // 64λ�²�֧���������. 1600: VS2010, ��˵VC2008 SP1֮���֧��__cpuidex.
		__cpuidex(reinterpret_cast<int*>(CPUInfo), InfoType, ECXValue);
#else
		if (NULL == CPUInfo)    return;
		_asm {
			// load. ��ȡ�������Ĵ���.
			mov edi, CPUInfo;    // ׼����ediѰַCPUInfo
			mov eax, InfoType;
			mov ecx, ECXValue;
			// CPUID
			cpuid;
			// save. ���Ĵ������浽CPUInfo
			mov[edi], eax;
			mov[edi + 4], ebx;
			mov[edi + 8], ecx;
			mov[edi + 12], edx;
		}
#endif
#endif    // #if defined(__GNUC__)
	}

	void getCpuId(unsigned int CPUInfo[4], unsigned int InfoType)
	{
#if defined(__GNUC__)    // GCC
		__cpuid(InfoType, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#elif defined(_MSC_VER)    // MSVC
#if _MSC_VER>=1400    // VC2005��֧��__cpuid
		__cpuid(reinterpret_cast<int*>(CPUInfo), InfoType);
#else
		getcpuidex(CPUInfo, InfoType, 0);
#endif
#endif    // #if defined(__GNUC__)
	}

	// ȡ��CPU���̣�Vendor��.
	std::string getCpuVendor()
	{
		std::string vendor(13, '\0');
		unsigned int dwBuf[4];
		// Function 0: Vendor-ID and Largest Standard Function
		getCpuId(dwBuf, 0);
		// save. ���浽pvendor
		*reinterpret_cast<unsigned int*>(&vendor[0]) = dwBuf[1];    // ebx: ǰ�ĸ��ַ�.
		*reinterpret_cast<unsigned int*>(&vendor[4]) = dwBuf[3];    // edx: �м��ĸ��ַ�.
		*reinterpret_cast<unsigned int*>(&vendor[8]) = dwBuf[2];    // ecx: ����ĸ��ַ�.
		vendor[12] = '\0';
		return vendor;
	}

	// ȡ��CPU�̱꣨Brand��.
	std::string getCpuBrand()
	{
		std::string vendor(49, '\0');
		unsigned int dwBuf[4];
		// Function 0x80000000: Largest Extended Function Number
		getCpuId(dwBuf, 0x80000000U);
		if (dwBuf[0] < 0x80000004U)    return 0;
		// Function 80000002h,80000003h,80000004h: Processor Brand String
		getCpuId(reinterpret_cast<unsigned int*>(&vendor[0]), 0x80000002U);    // ǰ16���ַ�.
		getCpuId(reinterpret_cast<unsigned int*>(&vendor[16]), 0x80000003U);    // �м�16���ַ�.
		getCpuId(reinterpret_cast<unsigned int*>(&vendor[32]), 0x80000004U);    // ���16���ַ�.
		vendor[48] = '\0';
		return vendor;
	}

	std::string getCpuSerialId()
	{
		char serialId[33];
		unsigned int dwBuf[4];
		getCpuId(dwBuf, 2);
		sprintf(serialId, "%08X%08X%08X%08X", dwBuf[0], dwBuf[1], dwBuf[2], dwBuf[3]);
		serialId[32] = '\0';
		return serialId;
	}
}
#endif // !_CPU_INFO_H