#pragma once

#include <qsharedmemory.h>
#include <qsystemsemaphore.h>

namespace{
inline bool singleApplication(QSharedMemory *obj)
{
    // Evgenii Legotckoi 2016 год
    QSystemSemaphore semaphore("<uniq id> 24SomeQuiteRandomText23QtSym_launcher", 1);  // создаём семафор
    semaphore.acquire(); // Поднимаем семафор, запрещая другим экземплярам работать с разделяемой памятью

    /** @// в linux/unix разделяемая память не освобождается при аварийном завершении приложения,
     *     поэтому необходимо избавиться от данного мусора
    **/
    QSharedMemory nix_fix_shared_memory("<uniq id memory> 24SomeQuiteRandomText23QtMem_launcher");
    if (nix_fix_shared_memory.attach())
    {
        nix_fix_shared_memory.detach();
    }

    bool is_running;            // переменная для проверки уже запущенного приложения
    if (obj->attach())          // пытаемся присоединить экземпляр разделяемой памяти
    {                           // к уже существующему сегменту
        is_running = true;      // Если успешно, то определяем, что уже есть запущенный экземпляр
    } else {
        obj->create(1);         // В противном случае выделяем 1 байт памяти
        is_running = false;     // И определяем, что других экземпляров не запущено
    }
    semaphore.release();        // Опускаем семафор

    // Если уже запущен один экземпляр приложения, то сообщаем об этом пользователю
    // и завершаем работу текущего экземпляра приложения
    if (is_running)
    {
        return false;
    }else{
        return true;
    }
}
}