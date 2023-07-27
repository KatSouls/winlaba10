
//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>

#include <Sddl.h>
#include <stdio.h>
#include "atlbase.h"


using namespace std;

wstring GetUserNameFromProcess(DWORD id) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
    wstring endUser;// = L"";
    wstring endDomain;// = L"";

    if (hProcess != NULL)
    {
        HANDLE  hToken = NULL;

        if (OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
        {
            DWORD tokenSize = 0;
            GetTokenInformation(hToken, TokenUser, NULL, 0, &tokenSize);

            if (tokenSize > 0)
            {
                BYTE* data = new BYTE[tokenSize];
                GetTokenInformation(hToken, TokenUser, data, tokenSize, &tokenSize);
                TOKEN_USER* pUser = (TOKEN_USER*)data;
                PSID pSID = pUser->User.Sid;
                DWORD userSize = 0;
                DWORD domainSize = 0;
                SID_NAME_USE sidName;
                LookupAccountSid(NULL, pSID, NULL, &userSize, NULL, &domainSize, &sidName);
                wchar_t* user = new wchar_t[userSize + 1];
                wchar_t* domain = new wchar_t[domainSize + 1];
                LookupAccountSid(NULL, pSID, user, &userSize, domain, &domainSize, &sidName);
                user[userSize] = L'\0';
                domain[domainSize] = L'\0';
                endUser = user;
                endDomain = domain;
                delete[] domain;
                delete[] user;
                delete[] data;
            }

            CloseHandle(hToken);
        }

        CloseHandle(hProcess);

        if (endUser != L"")
            return endUser;
    }

    return L"";
}


wstring GetUserNameFromSID(DWORD id, PSID pSID) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id); // 1- OpenProcess
    wstring endUser;// = L"";
    wstring endDomain;// = L"";

    if (hProcess != NULL)
    {
        HANDLE  hToken = NULL;

        if (OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)) // 2- OpenProcessToken
        {
            DWORD tokenSize = 0;
            GetTokenInformation(hToken, TokenUser, NULL, 0, &tokenSize);

            if (tokenSize > 0)
            {
                BYTE* data = new BYTE[tokenSize];
                GetTokenInformation(hToken, TokenUser, data, tokenSize, &tokenSize); // 3- GetTokenInformation
                DWORD userSize = 0;
                DWORD domainSize = 0;
                SID_NAME_USE sidName;
                LookupAccountSid(NULL, pSID, NULL, &userSize, NULL, &domainSize, &sidName);
                wchar_t* user = new wchar_t[userSize + 1];
                wchar_t* domain = new wchar_t[domainSize + 1];
                LookupAccountSid(NULL, pSID, user, &userSize, domain, &domainSize, &sidName); // 4- LookupAccountSid
                user[userSize] = L'\0';
                domain[domainSize] = L'\0';
                endUser = user;
                endDomain = domain;
                delete[] domain;
                delete[] user;
                delete[] data;
            }

            CloseHandle(hToken);
        }

        CloseHandle(hProcess);

        if (endUser != L"")
            return endUser;
    }

    return {};
}



int main()
{
    setlocale(0, "ru");

    HANDLE hProcc = GetCurrentProcess();
    int pid = GetProcessId(hProcc);

    //zd1

    HANDLE hToken;

    OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);

    DWORD len = 0;
    GetTokenInformation(hToken, TokenUser, 0, 0, &len);

    TOKEN_USER* pUser = (TOKEN_USER*)malloc(len);

    GetTokenInformation(hToken, TokenUser, pUser, len, &len);

    TCHAR* sidd = 0;
    ConvertSidToStringSid(pUser->User.Sid, &sidd);
    printf("SID: %ws\n", sidd);



    PSID psid = pUser->User.Sid;
    wcout << "GetUserNameFromSID(SID) this PC: " << GetUserNameFromSID(pid, psid) << endl << endl;



    LPCWSTR strSid;
    PSID psid1;

    strSid = TEXT("S-1-1-0");
    ConvertStringSidToSid(strSid, &psid1);
    wcout << "GetUserNameFromSID(SID)  " << strSid << "  : " << GetUserNameFromSID(pid, psid1) << endl;

    strSid = TEXT("S-1-2-0");
    ConvertStringSidToSid(strSid, &psid1);
    wcout << "GetUserNameFromSID(SID)  " << strSid << "  : " << GetUserNameFromSID(pid, psid1) << endl;

    strSid = TEXT("S-1-5-2");
    ConvertStringSidToSid(strSid, &psid1);
    wcout << "GetUserNameFromSID(SID)  " << strSid << "  : " << GetUserNameFromSID(pid, psid1) << endl;

    strSid = TEXT("S-1-5-32-544");
    ConvertStringSidToSid(strSid, &psid1);
    wcout << "GetUserNameFromSID(SID)  " << strSid << "  : " << GetUserNameFromSID(pid, psid1) << endl;

    strSid = TEXT("S-1-5-32-546");
    ConvertStringSidToSid(strSid, &psid1);
    wcout << "GetUserNameFromSID(SID)  " << strSid << "  : " << GetUserNameFromSID(pid, psid1) << endl;

    cout << "\n\n";


    //zd2


    cout << hProcc << "-  int: " << (int)hProcc << "-  getProcesId(Handle): " << pid << "-  OpenProcess(pid): " << (int)OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid) << "-  int: " << (int)hProcc << endl;

    wcout << "GetUserNameFromProcess(pid): " << GetUserNameFromProcess(pid) << endl;










    CloseHandle(hToken);
    LocalFree(sidd);
    free(pUser);


}