#include "lab3.h"
#include <windows.h>

#include <string>
//
// lab3 code should be located here!
//
#define MAX_SEM_COUNT 10
#define THREADCOUNT 12
#define PAUSE 10 /* ms */

using namespace std;



//Threads
HANDLE aThread,bThread,cThread,
eThread,dThread,fThread,
hThread,gThread,kThread,
mThread,pThread,nThread;
//Mutex
HANDLE stdout_mutex;
DWORD IDThread;
//Unsyhrionized sems
HANDLE FirstSemaphore,SecondSemaphore;
//syhrionized sems
HANDLE sem_k,sem_p,sem_m;

unsigned int lab3_thread_graph_id() 
{
    return 14;
}

const char* lab3_unsynchronized_threads()
{
    return "cde";
}

const char* lab3_sequential_threads()
{
    return "pkm";
}

void wait(HANDLE name) {
    WaitForSingleObject(name, INFINITE);
}

DWORD WINAPI a(LPVOID pVoid)
{

    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout <<"a"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();

    }
    //ReleaseSemaphore(FirstSemaphore, 2, NULL);
    return 0;
}

DWORD WINAPI d(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "d"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    return 0;
}

DWORD WINAPI k(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "k"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    wait(gThread);
    for (int i = 0;i < 3;i++) {
        wait(sem_k);
        wait(stdout_mutex);
        cout << "k"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(sem_m, 1, NULL);
    }
    return 0;
}

DWORD WINAPI m(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "m"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    wait(gThread);
    for (int i = 0;i < 3;i++) {
        wait(sem_m);
        wait(stdout_mutex);
        cout << "m"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(sem_p, 1, NULL);
    }
    wait(pThread);
    wait(kThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "m"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI h(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "h"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    return 0;
}

DWORD WINAPI n(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "n"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    return 0;
}

DWORD WINAPI p(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(sem_p);
        wait(stdout_mutex);
        cout << "p"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
        ReleaseSemaphore(sem_k, 1, NULL);
    }

    return 0;
}

DWORD WINAPI g(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "g"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    wait(fThread);
    wait(hThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "g"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI f(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "f"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    wait(eThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "f"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI e(LPVOID pVoid)
{
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "e"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    wait(cThread);
    wait(dThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "e"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI c(LPVOID pVoid)
{

    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "c"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    ReleaseSemaphore(FirstSemaphore, 1, NULL);
    wait(bThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "c"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

DWORD WINAPI b(LPVOID pVoid)
{

    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "b"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }

    wait(aThread);
    for (int i = 0;i < 3;i++) {
        wait(stdout_mutex);
        cout << "b"  << flush;
        ReleaseMutex(stdout_mutex);
        computation();
    }
    return 0;
}

int lab3_init()
{

    int inc = 10;

    stdout_mutex = CreateMutex(NULL, false, NULL);
    if (stdout_mutex == NULL)
        return GetLastError();

    FirstSemaphore = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    SecondSemaphore = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem_m = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem_k = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem_p = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    if (FirstSemaphore == NULL)
        return GetLastError();
    if (SecondSemaphore == NULL)
        return GetLastError();
    if (sem_m == NULL)
        return GetLastError();
    if (sem_k == NULL)
        return GetLastError();
    if (sem_p == NULL)
        return GetLastError();

    aThread = CreateThread(NULL, 0, (a), 0, 0, &IDThread);
    if (aThread == NULL)
        return GetLastError();

    bThread = CreateThread(NULL, 0,(b),0, 0, &IDThread);
    if (bThread == NULL)
        return GetLastError();

    wait(aThread);

    cThread = CreateThread(NULL, 0,(c), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    // ждем пока поток b закончит работу
    wait(bThread);
    wait(FirstSemaphore);
    dThread = CreateThread(NULL, 0,(d), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    eThread = CreateThread(NULL, 0,(e), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();
    wait(cThread);
    wait(dThread);
    fThread = CreateThread(NULL, 0,(f), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    wait(eThread);
    hThread = CreateThread(NULL, 0,(h), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();
    gThread = CreateThread(NULL, 0,(g), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    wait(fThread);
    wait(hThread);
    kThread = CreateThread(NULL, 0,(k), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();
    mThread = CreateThread(NULL, 0,(m), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    wait(gThread);
    ReleaseSemaphore(sem_k, 1, NULL);
    pThread = CreateThread(NULL, 0,(p), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    wait(pThread);
    wait(kThread);
    nThread = CreateThread(NULL, 0,(n), 0, 0, &IDThread);
    if (cThread == NULL)
        return GetLastError();

    wait(mThread);
    wait(pThread);
    // закрываем дескриптор
    CloseHandle(sem_m);
    CloseHandle(sem_k);
    CloseHandle(sem_p);

    CloseHandle(FirstSemaphore);
    CloseHandle(SecondSemaphore);

    CloseHandle(FirstSemaphore);

    CloseHandle(aThread);
    CloseHandle(eThread);
    CloseHandle(cThread);
    CloseHandle(bThread);
    CloseHandle(dThread);
    CloseHandle(kThread);
    CloseHandle(fThread);
    CloseHandle(mThread);
    CloseHandle(gThread);
    CloseHandle(hThread);
    CloseHandle(nThread);
    CloseHandle(pThread);
    // CreateThread();
    //  WaitForMultipleObjects();
    // ...
    CloseHandle(stdout_mutex);

    return 0;
}
