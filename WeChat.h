#ifndef _WECHAT_H
#define _WECHAT_H

#include <Windows.h>
#include <AclAPI.h>

static void CreateDenyMutexW(LPCWSTR lpMutextName)
{
    HANDLE hMutex = CreateMutexW(NULL, FALSE, lpMutextName);
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
    PSID pEveryoneSID = NULL; // everyoneÈº×éSID
    char szBuffer[4096];
    PACL pAcl = (PACL)szBuffer;

    AllocateAndInitializeSid(
        &SIDAuthWorld,
        1,
        SECURITY_WORLD_RID,
        0, 0, 0, 0, 0, 0, 0,
        &pEveryoneSID);

    InitializeAcl(pAcl, sizeof(szBuffer), ACL_REVISION);
    AddAccessDeniedAce(pAcl, ACL_REVISION, MUTEX_ALL_ACCESS, pEveryoneSID);
    SetSecurityInfo(hMutex, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pAcl, NULL);
}

// _WeChat_App_Instance_Identity_Mutex_Name 3.0
// XWeChat_App_Instance_Identity_Mutex_Name 4.0
static void EnableMultiWeChat()
{
    CreateDenyMutexW(L"_WeChat_App_Instance_Identity_Mutex_Name");
    CreateDenyMutexW(L"XWeChat_App_Instance_Identity_Mutex_Name");
}

#endif /* _WECHAT_H */
