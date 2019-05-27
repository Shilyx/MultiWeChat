# MultiWeChat
实现微信多开的技术原理描述，提供bin，仅供windows系统原理学习使用

在启动微信之前运行本程序，即可实现后续微信的任意多开

本程序运行后无界面，不需要多次运行

![](https://raw.githubusercontent.com/Shilyx/MultiWeChat/master/Release/test.png)

核心代码都在WeChat.h中：

```cpp
static void EnableMultiWeChat()
{
    HANDLE hMutex = CreateMutexW(NULL, FALSE, L"_WeChat_App_Instance_Identity_Mutex_Name");
    SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
    PSID pEveryoneSID = NULL; // everyone
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
```

