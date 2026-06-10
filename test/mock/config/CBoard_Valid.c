#include <FAF/FAF_Setup_Internal.h>
#include "CBoard_Valid.h"

#include "../drivers/DummyDriver_API.h"
#include "../drivers/DummyDriver_Class.h"

DRIVER_LIST_INIT(valid,
    DRIVER_DECLARE_MEMBER(DummyDriver, dummy)
)
DRIVER_LIST_APPEND(valid, DummyDriver, dummy, NULL)
DRIVER_LIST_END

PROVIDER_SUPPLY_CREATE(valid,
    PROVIDER_SUPPLY_APPEND(valid, DummyDriver, dummy, "Dummy Example Driver")
)