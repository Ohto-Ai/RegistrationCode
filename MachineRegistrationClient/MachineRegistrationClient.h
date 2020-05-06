#pragma once
#ifndef _MACHINEREGISTRATION_H_
#define _MACHINEREGISTRATION_H_

#ifndef REGISTRATION_CODE_API

#ifdef __GNUC__
#define REGISTRATION_CODE_API extern "C"
#else
#ifdef _MSC_VER
#if defined MACHINEREGISTRATION_EXPORTS || defined MACHINEREGISTRATIONCLIENT_EXPORTS
#define REGISTRATION_CODE_API extern "C" __declspec(dllexport)
#else
#define REGISTRATION_CODE_API extern "C" __declspec(dllimport)
#endif
#endif // _MSVC_VER_
#endif // __GNUC__
#endif // !REGISTRATIONCODEAPI

#if defined MACHINEREGISTRATION_EXPORTS || defined MACHINE_REG_ADMINISTRATORS_CALL	// for admin call

/**
	ע��
	param machineId, �������к�
	param envirment, ���ڽ��MachineId����ע���� XXXXX-XXXXX-XXXXX-XXXXX
	param registerCode, �洢ע����
	return keyValue, ���������������Կ����Ҫ��
*/
REGISTRATION_CODE_API int _stdcall RegisterClient(const char* machineId, const char* envirment, char* registerCode);
/**
	��֤
	ע��
	param machineId, �������к�
	param envirment, ���ڽ��MachineId����ע���� XXXXX-XXXXX-XXXXX-XXXXX
	param registerCode, �ͻ��ṩ��ע����
	return keyValue, ���������������Կ����Ҫ��
*/
REGISTRATION_CODE_API int _stdcall VerifyClient(const char* machineId, const char* envirment, const char* registerCode);
#endif // MACHINEREGISTRATION_EXPORTS

/**
	��֤
	param envirment, ���ڽ��MachineId����ע���룬�Ա�У��
	param registerCode, �ͻ��ṩ��ע����
	return keyValue, ���������������Կ����Ҫ����У��ʧ�ܷ���0
*/
REGISTRATION_CODE_API int _stdcall VerifyMachine(const char* envirment, const char* registerCode);

/**
	���к�
	param machineId, �洢�������к� XXXX-XXXX-XXXX-XXXX-XXXX
	return keyValue, ���������������Կ����Ҫ����У��ʧ�ܷ���0
*/
REGISTRATION_CODE_API void _stdcall QueryMachineId(char* machineId);




#endif // !_REGISTRATION_CODE_H_
